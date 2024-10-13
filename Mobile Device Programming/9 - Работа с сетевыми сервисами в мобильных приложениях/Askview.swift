
import SwiftUI

struct AskView: View {
    @State private var name: String = ""
    @State private var email: String = ""
    @State private var message: String = ""
    @State private var requests: [SupportRequest] = []
    @State private var selectedRequest: SupportRequest?
    @State private var showingDetail = false
    @State private var isEditing = false
    @State private var showingConfirmationDialog = false
    @State private var requestToDelete: SupportRequest?
    
    private let databaseManager = DatabaseManager()
    
    var body: some View {
        NavigationView {
            VStack {
                Form {
                    TextField("Name", text: $name)
                    TextField("Email", text: $email)
                    TextField("Message", text: $message)
                    
                    Button("Send") {
                        let newRequest = SupportRequest(id: 0, name: name, email: email, message: message)
                        databaseManager.createRequest(newRequest)
                        loadRequests()
                        name = ""
                        email = ""
                        message = ""
                    }
                }
                
                List(requests) { request in
                    HStack {
                        Text(request.message)
                        Spacer()
                        Button(action: {
                            self.selectedRequest = request
                            self.isEditing = false
                            self.showingDetail = true
                        }) {
                            Text("👁")
                        }
                        .buttonStyle(BorderlessButtonStyle()) // Для улучшения взаимодействия
                        Button(action: {
                            self.selectedRequest = request
                            self.isEditing = true
                            self.showingDetail = true
                        }) {
                            Text("✏️")
                        }
                        .buttonStyle(BorderlessButtonStyle()) // Для улучшения взаимодействия
                        Button(action: {
                            self.requestToDelete = request
                            self.showingConfirmationDialog = true
                        }) {
                            Text("🗑")
                        }
                        .buttonStyle(BorderlessButtonStyle()) // Для улучшения взаимодействия
                    }
                
                }
                .onAppear(perform: loadRequests)
            }
            .navigationBarTitle("Support Requests")
            .sheet(isPresented: $showingDetail) {
                if isEditing {
                    EditRequestView(request: $selectedRequest, databaseManager: databaseManager, loadRequests: loadRequests)
                } else {
                    DetailRequestView(request: selectedRequest)
                }
            }
            .alert(isPresented: $showingConfirmationDialog) {
                Alert(title: Text("Подтверждение удаления"),
                      message: Text("Вы уверены, что хотите удалить этот запрос?"),
                      primaryButton: .destructive(Text("Удалить")) {
                    if let requestToDelete = self.requestToDelete {
                        databaseManager.deleteRequest(id: requestToDelete.id)
                        loadRequests()
                    }
                },
                      secondaryButton: .cancel()
                )
            }
        }
    }
    
    private func loadRequests() {
        requests = databaseManager.readRequests()
    }
}

struct DetailRequestView: View {
    var request: SupportRequest?
    
    var body: some View {
        VStack {
            if let request = request {
                Text(request.name)
                Text(request.email)
                Text(request.message)
            }
        }
    }
}

struct EditRequestView: View {
    @Binding var request: SupportRequest?
    var databaseManager: DatabaseManager
    var loadRequests: () -> Void
    
    @State private var tempName: String = ""
    @State private var tempEmail: String = ""
    @State private var tempMessage: String = ""
    
    var body: some View {
        VStack {
            if let request = request {
                TextField("Name", text: $tempName)
                TextField("Email", text: $tempEmail)
                TextField("Message", text: $tempMessage)
                
                Button("Update") {
                    if var updatedRequest = self.request {
                        updatedRequest.name = tempName
                        updatedRequest.email = tempEmail
                        updatedRequest.message = tempMessage
                        databaseManager.updateRequest(updatedRequest)
                        loadRequests()
                    }
                }
            }
        }
        .onAppear {
            // Инициализация временных переменных, когда View появляется
            if let request = request {
                tempName = request.name
                tempEmail = request.email
                tempMessage = request.message
            }
        }
    }
}


struct AskView_Previews: PreviewProvider {
    static var previews: some View {
        AskView()
    }
}




