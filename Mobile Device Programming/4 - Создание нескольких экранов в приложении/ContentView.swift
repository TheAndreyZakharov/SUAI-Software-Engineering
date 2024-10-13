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
    @State private var balance: Int = 10000
    @State private var betAmount: Int = 100

    
    var body: some View {
        NavigationView {
            
            VStack {
                Text("🎰")
                    .font(.largeTitle)
                    .padding()
                Spacer(minLength: 10)
                
                HStack {
                    VStack {
                        Text("Баланс:")
                            .font(.headline)
                        Text("\(balance)🪙")
                            .font(.title2)
                    }
                    Spacer()
                    VStack {
                        Text("Ставка:")
                            .font(.headline)
                        TextField("100", value: $betAmount, format: .number)
                            .textFieldStyle(RoundedBorderTextFieldStyle())
                            .keyboardType(.numberPad)
                            .frame(width: 80)
                    }
                }
                .padding()
                Spacer(minLength: 10)
                
                
                
                Text("Угадайте число")
                    .font(.title)
                Spacer(minLength: 20)
                
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
                Spacer(minLength: 20)
                
                Button("Проверить") {
                    checkGuess()
                }
                
                .padding()
                .background(Color.blue)
                .foregroundColor(.white)
                .cornerRadius(10)
                Spacer(minLength: 20)
                Spacer(minLength: 20)
                Spacer(minLength: 20)
                    .alert(isPresented: $showAlert) {
                        Alert(title: Text(alertTitle), dismissButton: .default(Text("OK")))
                    }
                Spacer(minLength: 20)
                
                // Кнопка для перехода в магазин
                NavigationLink("Перейти в магазин", destination: ShopView(balance: $balance))
                    .padding()
                
                Spacer()
                
                
            }
            .padding()
        }
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
        if betAmount > balance {
            alertTitle = "Ваша ставка превышает баланс!"
            showAlert = true // Показываем уведомление
            return // Выходим из функции
        }
        balance -= betAmount // Вычитаем ставку
        let guess = Int(userGuess)
        
        if guess == randomNumber {
            var winMultiplier = 1.0
            switch numberRange {
            case "1 - 5":
                winMultiplier = 2.0
            case "1 - 10":
                winMultiplier = 5.0
            case "1 - 20":
                winMultiplier = 10.0
            default:
                break
            }
            balance += Int(Double(betAmount) * winMultiplier) // Добавляем выигрыш
            alertTitle = "Правильно! Вы угадали число!"
            updateRandomNumber() // Обновляем число только после угадывания
        } else {
            if isHintEnabled {
                if guess < randomNumber {
                    alertTitle = "Слишком мало! Попробуйте число побольше."
                } else {
                    alertTitle = "Слишком много! Попробуйте число поменьше."
                }
            } else {
                alertTitle = "Не угадали! Попробуйте еще раз."
            }
        }
        
        showAlert = true // Показываем уведомление
    }




}

// Preview section
struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}





