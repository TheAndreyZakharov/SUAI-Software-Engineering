//
//  ContentView.swift
//  Laba
//
//  Created by Андрей Захаров on 28.02.2024.
//

import SwiftUI

struct ContentView: View {
    @State private var userGuess = ""
    @State private var randomNumber = Int.random(in: 1...10)
    @State private var showAlert = false
    @State private var alertTitle = ""
    
    var body: some View {
        VStack {
            Text("Угадайте число от 1 до 10")
                .font(.title)
            
            TextField("Введите ваше число", text: $userGuess)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .keyboardType(.numberPad)
                .padding()
            
            Button("Проверить") {
                checkGuess()
            }
            .alert(isPresented: $showAlert) {
                Alert(title: Text(alertTitle), dismissButton: .default(Text("OK")))
            }
        }
        .padding()
    }
    
    func checkGuess() {
        guard let guess = Int(userGuess) else {
            alertTitle = "Введите число!"
            showAlert = true
            return
        }
        
        if guess < randomNumber {
            alertTitle = "Слишком мало!"
        } else if guess > randomNumber {
            alertTitle = "Слишком много!"
        } else {
            alertTitle = "Правильно! Вы угадали число!"
            randomNumber = Int.random(in: 1...10)
        }
        
        showAlert = true
        userGuess = ""
    }
}

// Секция предпросмотра
struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}




