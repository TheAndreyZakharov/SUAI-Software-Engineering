package com.example.ThymeleafProject;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

@Controller
@RequestMapping("/stocks")
public class StockController {

    private final ItemObjRepository itemObjRepository;

    @Autowired
    public StockController(ItemObjRepository itemObjRepository) {
        this.itemObjRepository = itemObjRepository;
    }

    @GetMapping
    public String getAllStocks(Model model) {
        model.addAttribute("stocks", itemObjRepository.findAll());
        return "stocks";
    }

    @PostMapping
    public String addStock(@ModelAttribute ItemObj stock) {
        itemObjRepository.save(stock);
        return "redirect:/stocks";
    }

    @GetMapping("/{id}")
    public String getStock(@PathVariable Integer id, Model model) {
        itemObjRepository.findById(id)
                .ifPresent(stock -> model.addAttribute("stock", stock));
        return itemObjRepository.findById(id).isPresent() ? "stock" : "redirect:/stocks";
    }

    @PostMapping("/delete/{id}")
    public String deleteStock(@PathVariable Integer id) {
        itemObjRepository.deleteById(id);
        return "redirect:/stocks";
    }

}
