
import Foundation
import SQLite3

struct SupportRequest: Identifiable {
    let id: Int32
    var name: String
    var email: String
    var message: String
}


class DatabaseManager {
    var db: OpaquePointer?
    
    init() {
        openDatabase()
        createTable()
    }
    
    func openDatabase() {
        let fileURL = try! FileManager.default.url(for: .documentDirectory,
                                                   in: .userDomainMask,
                                                   appropriateFor: nil,
                                                   create: false)
            .appendingPathComponent("SupportDatabase.sqlite")
        
        if sqlite3_open(fileURL.path, &db) != SQLITE_OK {
            print("Error opening database")
            return
        }
    }
    
    func createTable() {
        let createTableString = """
        CREATE TABLE IF NOT EXISTS SupportRequests(
        Id INTEGER PRIMARY KEY AUTOINCREMENT,
        Name TEXT,
        Email TEXT,
        Message TEXT);
        """
        
        if sqlite3_exec(db, createTableString, nil, nil, nil) != SQLITE_OK {
            let errmsg = String(cString: sqlite3_errmsg(db)!)
            print("Error creating table: \(errmsg)")
        }
    }
    
    func createRequest(_ request: SupportRequest) {
        let insertStatementString = "INSERT INTO SupportRequests (Name, Email, Message) VALUES (?, ?, ?);"
        var insertStatement: OpaquePointer?
        
        if sqlite3_prepare_v2(db, insertStatementString, -1, &insertStatement, nil) == SQLITE_OK {
            sqlite3_bind_text(insertStatement, 1, (request.name as NSString).utf8String, -1, nil)
            sqlite3_bind_text(insertStatement, 2, (request.email as NSString).utf8String, -1, nil)
            sqlite3_bind_text(insertStatement, 3, (request.message as NSString).utf8String, -1, nil)
            
            if sqlite3_step(insertStatement) == SQLITE_DONE {
                print("Successfully inserted row.")
            } else {
                print("Could not insert row.")
            }
        } else {
            print("INSERT statement could not be prepared.")
        }
        sqlite3_finalize(insertStatement)
    }
    
    func readRequests() -> [SupportRequest] {
        let queryStatementString = "SELECT * FROM SupportRequests;"
        var queryStatement: OpaquePointer?
        var requests = [SupportRequest]()
        
        if sqlite3_prepare_v2(db, queryStatementString, -1, &queryStatement, nil) == SQLITE_OK {
            while sqlite3_step(queryStatement) == SQLITE_ROW {
                let id = sqlite3_column_int(queryStatement, 0)
                let name = String(describing: String(cString: sqlite3_column_text(queryStatement, 1)))
                let email = String(describing: String(cString: sqlite3_column_text(queryStatement, 2)))
                let message = String(describing: String(cString: sqlite3_column_text(queryStatement, 3)))
                
                requests.append(SupportRequest(id: id, name: name, email: email, message: message))
            }
        } else {
            print("SELECT statement could not be prepared")
        }
        
        sqlite3_finalize(queryStatement)
        return requests
    }
    
    func updateRequest(_ request: SupportRequest) {
        let updateStatementString = "UPDATE SupportRequests SET Name = ?, Email = ?, Message = ? WHERE Id = ?;"
        var updateStatement: OpaquePointer?
        
        if sqlite3_prepare_v2(db, updateStatementString, -1, &updateStatement, nil) == SQLITE_OK {
            sqlite3_bind_text(updateStatement, 1, (request.name as NSString).utf8String, -1, nil)
            sqlite3_bind_text(updateStatement, 2, (request.email as NSString).utf8String, -1, nil)
            sqlite3_bind_text(updateStatement, 3, (request.message as NSString).utf8String, -1, nil)
            sqlite3_bind_int(updateStatement, 4, request.id)
            
            if sqlite3_step(updateStatement) == SQLITE_DONE {
                print("Successfully updated row.")
            } else {
                print("Could not update row.")
            }
        } else {
            print("UPDATE statement could not be prepared.")
        }
        
        sqlite3_finalize(updateStatement)
    }
    
    func deleteRequest(id: Int32) {
        let deleteStatementString = "DELETE FROM SupportRequests WHERE Id = ?;"
        var deleteStatement: OpaquePointer?
        
        if sqlite3_prepare_v2(db, deleteStatementString, -1, &deleteStatement, nil) == SQLITE_OK {
            sqlite3_bind_int(deleteStatement, 1, id)
            
            if sqlite3_step(deleteStatement) == SQLITE_DONE {
                print("Successfully deleted row.")
            } else {
                print("Could not delete row.")
            }
        } else {
            print("DELETE statement could not be prepared.")
        }
        
        sqlite3_finalize(deleteStatement)
    }
    
    deinit {
        sqlite3_close(db)
    }
}
