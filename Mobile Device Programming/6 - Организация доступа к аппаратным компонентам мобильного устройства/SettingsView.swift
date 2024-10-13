//
//  SettingsView.swift
//  Laba
//
//  Created by Андрей Захаров on 07.03.2024.
//

import SwiftUI
import AVFoundation

struct SettingsView: View {
    @State private var showingImagePicker = false
    @State private var inputImage: UIImage?
    @State private var avatarImage: Image?
    @State var firstName = "Андрей"
    @State var lastName = "Захаров"
    
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
            }
            .padding(.bottom, 20)
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
            print("Камера активирована")
            if let uiImage = info[.originalImage] as? UIImage {
                parent.image = uiImage
                print("Изображение выбрано")
            }
            parent.presentationMode.wrappedValue.dismiss()
        }
        
        func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
            print("Выбор изображения отменён")
            parent.presentationMode.wrappedValue.dismiss()
        }
    }

}

struct SettingsView_Previews: PreviewProvider {
    static var previews: some View {
        SettingsView()
    }
}

