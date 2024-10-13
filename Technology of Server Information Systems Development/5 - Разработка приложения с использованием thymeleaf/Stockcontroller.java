package com.example.ThymeleafProject;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@Controller
@RequestMapping("/stocks")  // Изменено с /patients на /stocks
class StockController {  // Изменено имя класса

    private List<ItemObj> stocks = new ArrayList<>();  // Изменено название списка

    @GetMapping
    public String getAllStocks(Model model) {  // Изменено название метода
        model.addAttribute("stocks", stocks);  // Изменено имя атрибута
        return "stocks";  // Изменено имя возвращаемого представления
    }

    @PostMapping
    public String addStock(@ModelAttribute ItemObj stock) {  // Изменено название метода и параметра
        stocks.add(stock);
        return "redirect:/stocks";  // Изменен URL перенаправления
    }

    @GetMapping("/{id}")
    public String getStock(@PathVariable int id, Model model) {  // Изменено название метода
        model.addAttribute("stock", stocks.get(id));  // Изменено имя атрибута
        return "stock";  // Изменено имя возвращаемого представления
    }

    @PostMapping("/{id}")
    public String deleteStock(@PathVariable int id) {  // Изменено название метода
        stocks.remove(id);
        return "redirect:/stocks";  // Изменен URL перенаправления
    }
}

