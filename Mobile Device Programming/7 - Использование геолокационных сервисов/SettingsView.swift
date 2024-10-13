//
//  SettingsView.swift
//  Game
//
//  Created by Андрей Захаров on 07.03.2024.
//

import SwiftUI
import AVFoundation
import CoreLocation
import MapKit

struct SettingsView: View {
    @StateObject private var locationManager = LocationManager()
    @State private var showingImagePicker = false
    @State private var inputImage: UIImage?
    @State private var avatarImage: Image?
    @State var firstName = "Андрей"
    @State var lastName = "Захаров"
    @State var mapRegion = MKCoordinateRegion(
        center: CLLocationCoordinate2D(latitude: 0, longitude: 0),
        span: MKCoordinateSpan(latitudeDelta: 0.01, longitudeDelta: 0.01)
    )
    
    var body: some View {
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

                // Карта для отображения текущего местоположения
                Map(coordinateRegion: $mapRegion)
                    .frame(height: 300)
                    .cornerRadius(12)
                    .padding()
                
                // Текстовые координаты под картой
                if let location = locationManager.location {
                    Text("Текущее местоположение: \(location.coordinate.latitude), \(location.coordinate.longitude)")
                        .padding()
                } else {
                    Text("Местоположение не определено")
                        .padding()
                }
            }
            .padding(.bottom, 20)
            .onReceive(locationManager.$location) { newLocation in
                if let newLocation = newLocation {
                    mapRegion.center = newLocation.coordinate
                }
            }
        }
        .sheet(isPresented: $showingImagePicker, onDismiss: loadImage) {
            ImagePicker(image: self.$inputImage)
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
}


class LocationManager: NSObject, ObservableObject, CLLocationManagerDelegate {
    private let locationManager = CLLocationManager()
    @Published var location: CLLocation? = nil
    
    override init() {
        super.init()
        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyBest
        locationManager.requestWhenInUseAuthorization()
        locationManager.startUpdatingLocation()
    }
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        location = locations.first
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
}



struct ImagePicker: UIViewControllerRepresentable {
    @Environment(\.presentationMode) var presentationMode
    @Binding var image: UIImage?
    
    func makeUIViewController(context: Context) -> UIImagePickerController {
        let picker = UIImagePickerController()
        if UIImagePickerController.isSourceTypeAvailable(.camera) {
            picker.sourceType = .camera
        } else {
            // Обработка случая, когда камера недоступна
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
        SettingsView()
    }
}


