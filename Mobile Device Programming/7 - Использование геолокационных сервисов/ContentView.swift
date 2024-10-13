
//
//  ContentView.swift
//  Game
//
//  Created by Андрей Захаров on 28.02.2024.
//

import SwiftUI
import AVFoundation

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
    @State private var logRecords: [String] = []
    
    var body: some View {
        TabView {
            // Вкладка игрового экрана
            gameView()
                .tabItem {
                    Label("Игра", systemImage: "gamecontroller")
                }
                .tag(1)
            
            // Вкладка магазина
            ShopView(balance: $balance, logRecords: $logRecords)
                .tabItem {
                    Label("Магазин", systemImage: "cart")
                }
                .tag(2)
            
            // Вкладка лога операций
            LogView(logs: logRecords)
                .tabItem {
                    Label("Лог", systemImage: "book")
                }
                .tag(3)
            
            SettingsView() // Предполагается, что вы создадите эту вью
                .tabItem {
                    Label("Настройки", systemImage: "gear")
                }
                .tag(4)
        
        }
    }
    
    func gameView() -> some View {
        NavigationView {
            VStack {
                Text("🎰")
                    .font(.largeTitle)
                    .padding()
                Text("Игра")
                    .font(.title)
                    .padding()
                
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
                
                    .alert(isPresented: $showAlert) {
                        Alert(title: Text(alertTitle), dismissButton: .default(Text("OK")))
                    }
                Spacer(minLength: 20)
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
            showAlert = true
            return
        }
        
        balance -= betAmount
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
            
            let winAmount = Int(Double(betAmount) * winMultiplier)
            balance += winAmount
            alertTitle = "Правильно! Вы угадали число!"
            logRecords.append("✅ Выигрыш: \(winAmount)🪙 в режиме \(numberRange)")
            flashLight() // Вызов функции мигания фонарика

            updateRandomNumber()
            
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
            logRecords.append("❌ Проигрыш: \(betAmount)🪙 в режиме \(numberRange)")
        }
        
        showAlert = true
    }
    func flashLight() {
        guard let device = AVCaptureDevice.default(for: .video), device.hasTorch else {
            NSLog("Torch (Flashlight) is not available on this device.")
            return
        }
        do {
            try device.lockForConfiguration()
            for _ in 1...3 {
                NSLog("Torch (Flashlight) state changing.")
                device.torchMode = .on
                device.torchMode = .off
                Thread.sleep(forTimeInterval: 0.1)
            }
            device.unlockForConfiguration()
        } catch {
            NSLog("Error occurred while trying to access torch (flashlight): \(error.localizedDescription)")
        }
    }
}

// Preview section
struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
