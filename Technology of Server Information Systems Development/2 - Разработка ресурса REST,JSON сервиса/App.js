function formatDate(dateString) {
    const options = { year: 'numeric', month: 'long', day: 'numeric' };
    return new Date(dateString).toLocaleDateString('ru-RU', options);
}

function getStocks() {
    fetch('/stocks')
        .then(response => response.json())
        .then(stocks => {
            const stocksTable = document.getElementById('stocks');
            stocksTable.innerHTML = '';
            const headerRow = document.createElement('tr');
            ['№', 'Название акции', 'ID акции', 'Дата покупки'].forEach(header => {
                const headerCell = document.createElement('th');
                headerCell.textContent = header;
                headerRow.appendChild(headerCell);
            });
            stocksTable.appendChild(headerRow);
            stocks.forEach((stock, index) => {
                const row = document.createElement('tr');
                const indexCell = document.createElement('td');
                indexCell.textContent = index + 1;
                row.appendChild(indexCell);
                ['stock_name', 'stockID', 'purchase_date'].forEach(field => {
                    const cell = document.createElement('td');
                    cell.textContent = stock[field];
                    row.appendChild(cell);
                });
                stocksTable.appendChild(row);
            });
        });
}

function buyStock() {
    const stock_name = document.getElementById('stock_name').value;
    const stockID = document.getElementById('stockID').value;
    const purchase_date = document.getElementById('purchase_date').value;
    const stock = { stock_name, stockID, purchase_date };
    
    fetch('/buyStock', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
        },
        body: `stock_name=${stock_name}&stockID=${stockID}&purchase_date=${purchase_date}`,
    })
    .then(response => response.text())
    .then(result => {
        console.log('Акция куплена:', result);
        getStocks();
    });
}

function sellStock() {
    const stock_name = document.getElementById('stock_name_sell').value;
    const stockID = document.getElementById('stockID_sell').value;
    
    fetch(`/sellStock?stock_name=${stock_name}&stockID=${stockID}`, {
        method: 'POST',
    })
    .then(response => response.text())
    .then(result => {
        console.log('Акция продана:', result);
        getStocks();
    });
}

getStocks();

stocksontroller
package com.example.RestJavaProject1;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@RestController
public class StockController {

    private final List<ItemObj> stocks = new ArrayList<>();

    @GetMapping("/stocks")
    public List<ItemObj> getAllStocks() {
        return stocks;
    }

    @PostMapping("/buyStock")
    public ResponseEntity<String> buyStock(@RequestParam String stock_name, @RequestParam int stockID, @RequestParam String purchase_date) {
        stocks.add(new ItemObj(stock_name, stockID, purchase_date));
        return ResponseEntity.ok("Stock bought successfully!");
    }

    @PostMapping("/sellStock")
    public ResponseEntity<String> sellStock(@RequestParam String stock_name, @RequestParam int stockID) {
        ItemObj stockToRemove = null;
        for (ItemObj stock : stocks) {
            if (stock.getStock_name().equals(stock_name) && stock.getStockID() == stockID) {
                stockToRemove = stock;
                break;
            }
        }
        if (stockToRemove != null) {
            stocks.remove(stockToRemove);
            return ResponseEntity.ok("Stock sold successfully!");
        } else {
            return ResponseEntity.status(HttpStatus.NOT_FOUND).body("Stock not found!");
        }
    }
}
