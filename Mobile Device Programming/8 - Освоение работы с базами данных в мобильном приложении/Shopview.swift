import SwiftUI

struct ShopView: View {
    @Binding var balance: Int
    @Binding var logRecords: [String]
    @State private var showAlert = false
    @State private var alertTitle = ""
    
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
            Text("🛒")
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
                        .frame(width: 50, alignment: .leading)
                    Text("\(products[index].price)🪙")
                        .frame(width: 100, alignment: .leading)
                    Button("Купить") {
                        buyProduct(index: index)
                    }
                    .padding(8)
                    .background(Color.blue)
                    .foregroundColor(.white)
                    .cornerRadius(8)
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
    
    func buyProduct(index: Int) {
        if products[index].price <= balance {
            balance -= products[index].price
            products[index].count += 1
            logRecords.append("🛒 Покупка: \(products[index].emoji) за \(products[index].price)🪙")
        } else {
            alertTitle = "Недостаточно средств для покупки!"
            showAlert = true
        }
    }
}

struct ShopView_Previews: PreviewProvider {
    @State static var tempBalance = 10000
    @State static var tempLogRecords: [String] = []
    
    static var previews: some View {
        ShopView(balance: $tempBalance, logRecords: $tempLogRecords)
    }
}


