//
//  ContentView.swift
//  Laba
//
//  Created by Андрей Захаров on 28.02.2024.
//

import SwiftUI

struct ContentView: View {
    @State private var userGuess: Double = 5
    @State private var randomNumber = Int.random(in: 1...10)
    @State private var showAlert = false
    @State private var alertTitle = ""
    @State private var isHintEnabled: Bool = false
    @State private var numberRange = "1 - 10"
    let numberRanges = ["1 - 5", "1 - 10", "1 - 20"]
    
    var body: some View {
        VStack {
            
            Text("🎰")
                .font(.largeTitle)
                .padding()
            
            Text("Угадайте число")
                .font(.title)
            
            Picker("Выберите диапазон чисел", selection: $numberRange) {
                ForEach(numberRanges, id: \.self) {
                    Text($0)
                }
            }
            .pickerStyle(SegmentedPickerStyle())
            .padding()
            .onChange(of: numberRange) { _ in
                updateRandomNumber()
            }
            Text("Выбранное число: \(Int(userGuess))")
            
            Slider(value: $userGuess, in: 1...CGFloat(getUpperRangeLimit()), step: 1)
                .padding()
            
            Toggle("Включить подсказки", isOn: $isHintEnabled)
                .padding()
            
            Button("Проверить") {
                checkGuess()
            }
            .padding()
            .background(Color.blue)
            .foregroundColor(.white)
            .cornerRadius(10)
            .alert(isPresented: $showAlert) {
                Alert(title: Text(alertTitle), dismissButton: .default(Text("OK")))
            }
        }
        .padding()
    }
    
    func updateRandomNumber() {
        let limit = getUpperRangeLimit()
        randomNumber = Int.random(in: 1...limit)
        userGuess = min(userGuess, Double(limit))
    }
    
    func getUpperRangeLimit() -> Int {
        switch numberRange {
        case "1 - 20":
            return 20
        case "1 - 5":
            return 5
        default: // "1 - 10"
            return 10
        }
    }
    
    func checkGuess() {
        let guess = Int(userGuess)
        
        if guess < randomNumber {
            alertTitle = isHintEnabled ? "Слишком мало!" : "Не угадали!"
        } else if guess > randomNumber {
            alertTitle = isHintEnabled ? "Слишком много!" : "Не угадали!"
        } else {
            alertTitle = "Правильно! Вы угадали число!"
            updateRandomNumber()
        }
        
        showAlert = true
    }
}

// Preview section
struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
