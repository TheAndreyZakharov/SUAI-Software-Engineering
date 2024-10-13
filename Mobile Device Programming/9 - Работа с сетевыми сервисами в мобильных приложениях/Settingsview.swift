
import SwiftUI
import CoreLocation
import MapKit
import Combine


// Структура для хранения информации о стране
struct CountryInfo: Codable {
    struct Name: Codable {
        var common: String
    }
    
    var name: Name
    var alpha2Code: String
    var flags: Flags
    
    struct Flags: Codable {
        var png: String
    }
    
    var flagImageUrl: String {
        return flags.png
    }
    
    enum CodingKeys: String, CodingKey {
        case name
        case alpha2Code = "cca2"
        case flags
    }
}

class CustomPointAnnotation: NSObject, MKAnnotation, Identifiable {
    dynamic var coordinate: CLLocationCoordinate2D
    let id = UUID()  // Добавлен идентификатор
    
    init(coordinate: CLLocationCoordinate2D) {
        self.coordinate = coordinate
    }
}

// Класс для управления местоположением пользователя
class LocationManager: NSObject, ObservableObject, CLLocationManagerDelegate {
    private let locationManager = CLLocationManager()
    @Published var location: CLLocation?
    @Published var userAnnotation = CustomPointAnnotation(coordinate: CLLocationCoordinate2D(latitude: 0, longitude: 0))
    private var cancellables: Set<AnyCancellable> = []
    private var locationSubject = PassthroughSubject<CLLocation, Never>()
    
    override init() {
        super.init()
        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyNearestTenMeters // Увеличение точности
        locationManager.requestWhenInUseAuthorization()
        locationManager.startUpdatingLocation()
    }
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        if let newLocation = locations.first {
            location = newLocation
            userAnnotation.coordinate = newLocation.coordinate
        }
    }
    
    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
        print("Ошибка при получении местоположения: \(error.localizedDescription)")
    }
    
    func locationManager(_ manager: CLLocationManager, didChangeAuthorization status: CLAuthorizationStatus) {
        switch status {
        case .notDetermined:
            manager.requestWhenInUseAuthorization()
        case .authorizedWhenInUse, .authorizedAlways:
            manager.startUpdatingLocation()
        case .restricted, .denied:
            print("Доступ к геолокации ограничен или отклонен")
        default:
            break
        }
    }
    
    func getCountryName(completion: @escaping (String?) -> Void) {
        guard let location = location else {
            completion(nil)
            return
        }
        
        let geocoder = CLGeocoder()
        geocoder.reverseGeocodeLocation(location) { placemarks, error in
            if let error = error {
                print("Ошибка обратного геокодирования: \(error)")
                completion(nil)
            } else {
                completion(placemarks?.first?.isoCountryCode)
            }
        }
    }
    
}

struct SettingsView: View {
    @StateObject private var locationManager = LocationManager()
    @State private var showingImagePicker = false
    @State private var inputImage: UIImage?
    @State private var avatarImage: Image?
    @State private var countryInfo: CountryInfo?
    @State var firstName = "Андрей"
    @State var lastName = "Захаров"
    
    var body: some View {
        NavigationView {
            ScrollView {
                VStack(spacing: 20) {
                    Text("🔧")
                        .font(.largeTitle)
                        .padding(.top, 20)
                    Text("Настройки профиля")
                        .font(.title)
                        .padding()
                    
                    avatarSection
                    Spacer(minLength: 20)
                    
                    Group {
                        HStack {
                            Text("Имя:")
                                .frame(width: 80, alignment: .leading)
                            TextField("Введите имя", text: $firstName)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                        }
                        
                        HStack {
                            Text("Фамилия:")
                                .frame(width: 80, alignment: .leading)
                            TextField("Введите фамилию", text: $lastName)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                        }
                    }
                    .frame(maxWidth: .infinity)
                    .padding([.leading, .trailing], 20)
                    
                    Text("Ваше местоположение:")
                        .padding(.top, 30)
                    
                    UserLocationMapView(locationManager: locationManager)
                        .frame(height: 300)
                        .cornerRadius(12)
                        .padding()
                    
                    if let location = locationManager.location {
                        Text("Текущее местоположение: \(location.coordinate.latitude), \(location.coordinate.longitude)")
                            .padding()
                    } else {
                        Text("Местоположение не определено")
                            .padding()
                    }
                    
                    // Добавление информации о стране и флага под координатами
                    if let countryInfo = countryInfo {
                        VStack {
                            Text("Страна: \(countryInfo.name.common)") // Использование countryInfo.name.common
                            AsyncImage(url: URL(string: countryInfo.flagImageUrl)) { phase in
                                if let image = phase.image {
                                    image.resizable()
                                } else if phase.error != nil {
                                    Text("Ошибка загрузки изображения")
                                } else {
                                    ProgressView()
                                }
                            }
                            .frame(width: 100, height: 50)
                            .clipShape(Rectangle())
                            .cornerRadius(5)
                        }
                    }

                    
                    NavigationLink(destination: AskView()) {
                        Text("Обратиться в техническую поддержку")
                            .foregroundColor(.white)
                            .frame(maxWidth: .infinity)
                            .padding()
                            .background(Color.blue)
                            .cornerRadius(10)
                            .contentShape(Rectangle())
                    }
                    .padding([.top, .horizontal])
                    .padding(.bottom, 40)
                }
                .padding(.bottom, 20)
                .onReceive(locationManager.$location) { newLocation in
                    if let newLocation = newLocation {
                        locationManager.getCountryName { countryCode in
                            if let countryCode = countryCode {
                                print("Код страны: \(countryCode)")
                                self.fetchCountryData(for: countryCode)
                            } else {
                                print("Код страны не получен")
                            }
                        }
                    }
                }
            }
            .sheet(isPresented: $showingImagePicker, onDismiss: loadImage) {
                ImagePicker(image: self.$inputImage)
            }
        }
    }
    
    var avatarSection: some View {
        ZStack {
            if let avatarImage = avatarImage {
                avatarImage
                    .resizable()
                    .scaledToFit()
                    .frame(width: 200, height: 200)
                    .clipShape(Circle())
                    .overlay(Circle().stroke(Color.gray, lineWidth: 4))
            } else {
                Circle()
                    .frame(width: 200, height: 200)
                    .overlay(Circle().stroke(Color.gray, lineWidth: 4))
            }
        }
        .onTapGesture {
            self.showingImagePicker = true
        }
    }
    
    func loadImage() {
        guard let inputImage = inputImage else { return }
        avatarImage = Image(uiImage: inputImage)
    }
    
    func fetchCountryData(for countryCode: String) {
        let urlString = "https://restcountries.com/v3.1/alpha/\(countryCode)"
        guard let url = URL(string: urlString) else {
            print("Некорректный URL")
            return
        }
        
        URLSession.shared.dataTask(with: url) { data, response, error in
            if let error = error {
                print("Ошибка запроса данных о стране: \(error.localizedDescription)")
                return
            }
            guard let data = data else {
                print("Данные не получены")
                return
            }
            if let countryInfos = try? JSONDecoder().decode([CountryInfo].self, from: data),
               let countryInfo = countryInfos.first {
                DispatchQueue.main.async {
                    self.countryInfo = countryInfo
                    print("Страна: \(countryInfo.name), Флаг: \(countryInfo.flagImageUrl)")
                }
            } else {
                print("Ошибка декодирования данных")
            }
        }.resume()
    }

}

struct UserLocationMapView: View {
    @ObservedObject var locationManager: LocationManager
    
    var body: some View {
        Map(coordinateRegion: .constant(
            MKCoordinateRegion(
                center: locationManager.location?.coordinate ?? CLLocationCoordinate2D(latitude: 0, longitude: 0),
                span: MKCoordinateSpan(latitudeDelta: 0.01, longitudeDelta: 0.01)
            )
        ),
            showsUserLocation: true,
            userTrackingMode: .constant(.follow),
            annotationItems: [locationManager.userAnnotation] // Используйте userAnnotation напрямую
        ) { annotation in
            MapPin(coordinate: annotation.coordinate) // Теперь coordinate это прямой доступ к CLLocationCoordinate2D
        }
    }
}


struct ImagePicker: UIViewControllerRepresentable {
    @Environment(\.presentationMode) var presentationMode
    @Binding var image: UIImage?
    
    func makeUIViewController(context: Context) -> UIImagePickerController {
        let picker = UIImagePickerController()
        if UIImagePickerController.isSourceTypeAvailable(.camera) {
            picker.sourceType = .camera
        } else {
            print("Камера недоступна на данном устройстве")
        }
        picker.delegate = context.coordinator
        return picker
    }
    
    func updateUIViewController(_ uiViewController: UIImagePickerController, context: Context) {}
    
    func makeCoordinator() -> Coordinator {
        Coordinator(self)
    }
    
    class Coordinator: NSObject, UINavigationControllerDelegate, UIImagePickerControllerDelegate {
        let parent: ImagePicker
        
        init(_ parent: ImagePicker) {
            self.parent = parent
        }
        
        func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
            if let uiImage = info[.originalImage] as? UIImage {
                parent.image = uiImage
            }
            parent.presentationMode.wrappedValue.dismiss()
        }
        
        func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
            parent.presentationMode.wrappedValue.dismiss()
        }
    }
}

struct SettingsView_Previews: PreviewProvider {
    static var previews: some View {
        NavigationView {
            SettingsView()
        }
    }
}




