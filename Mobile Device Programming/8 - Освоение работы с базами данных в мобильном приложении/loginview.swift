import SwiftUI

struct LogView: View {
    var logs: [String] // Массив строк с записями лога
    
    var body: some View {
        VStack {
            Text("📒")
                .font(.largeTitle)
                .padding()
            Text("Лог операций")
                .font(.title)
                .padding()
            
            // Проверяем, есть ли записи в логе
            if logs.isEmpty {
                Text("Записей в логе нет")
                    .padding()
            } else {
                List(logs.reversed(), id: \.self) { log in
                    Text(log)
                }
            }
        }
    }
}

// Предпросмотр
struct LogView_Previews: PreviewProvider {
    static var previews: some View {
        // Создание примера данных для предпросмотра
        let sampleLogs = ["Покупка: 🥤 за 50🪙", "Выигрыш: 500 в режиме 1 - 10"]
        
        // Возвращаем LogView с примерными данными
        LogView(logs: sampleLogs)
    }
}

