//
//  ShopView.swift
//  Laba
//
//  Created by Андрей Захаров on 07.03.2024.
//

import SwiftUI

struct ShopView: View {
    @Binding var balance: Int
    @State private var showAlert = false
    @State private var alertTitle = ""
    
    // Структура для хранения информации о товарах
    struct Product {
        var emoji: String
        var price: Int
        var count: Int
    }
    
    @State private var products: [Product] = [
        Product(emoji: "🥤", price: 50, count: 0),
        Product(emoji: "🍔", price: 100, count: 0),
        Product(emoji: "🚗", price: 5000, count: 0),
        Product(emoji: "🏠", price: 10000, count: 0)
    ]
    
    var body: some View {
        VStack {
            Text("🎰")
                .font(.largeTitle)
                .padding()
            Text("Магазин")
                .font(.title)
                .padding()
            Text("Баланс: \(balance)🪙")
                .font(.title2)
                .padding()
            
            // Список товаров
            ForEach($products.indices, id: \.self) { index in
                HStack {
                    Text(products[index].emoji)
                        .font(.largeTitle)
                        .frame(width: 50, alignment: .leading) // Фиксированная ширина для эмодзи
                    Text("\(products[index].price)🪙")
                        .frame(width: 100, alignment: .leading) // Фиксированная ширина для цен
                    Button("Купить") {
                        buyProduct(index: index)
                    }
                    .padding(8)
                    .background(Color.blue) // Фон кнопки
                    .foregroundColor(.white) // Цвет текста
                    .cornerRadius(8) // Скругленные углы
                    Spacer()
                    Text("x\(products[index].count)")
                }
                .padding()
            }
            
            Spacer()
        }
        .alert(isPresented: $showAlert) {
            Alert(title: Text(alertTitle), dismissButton: .default(Text("OK")))
        }
    }
    
    // Функция покупки товара
    func buyProduct(index: Int) {
        if products[index].price <= balance {
            balance -= products[index].price
            products[index].count += 1
        } else {
            alertTitle = "Недостаточно средств для покупки!"
            showAlert = true
        }
    }
}


// Preview section
// В конце файла ShopView.swift

struct ShopView_Previews: PreviewProvider {
    // Создание временной @State переменной для баланса
    @State static var tempBalance = 10000
    
    static var previews: some View {
        // Использование временной привязки к tempBalance для предварительного просмотра
        ShopView(balance: $tempBalance)
    }
}
