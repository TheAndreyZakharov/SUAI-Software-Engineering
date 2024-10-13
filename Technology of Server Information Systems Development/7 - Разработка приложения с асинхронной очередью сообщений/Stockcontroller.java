package com.example.Project;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

@Controller
@RequestMapping("/stocks")
public class StockController {

    private final ItemObjRepository itemObjRepository;
    private final MyKafkaProducer myKafkaProducer;
    private final ObjectMapper objectMapper = new ObjectMapper();



    @Autowired
    public StockController(ItemObjRepository itemObjRepository, MyKafkaProducer myKafkaProducer) {
        this.itemObjRepository = itemObjRepository;
        this.myKafkaProducer = myKafkaProducer;

    }

    @GetMapping
    public String getAllStocks(Model model) {
        model.addAttribute("stocks", itemObjRepository.findAll());
        return "stocks";
    }

    @PostMapping
    public String addStock(@ModelAttribute ItemObj stock) {
        itemObjRepository.save(stock);
        if (myKafkaProducer != null) {
            String message = convertStockToMessage(stock);
            myKafkaProducer.sendMessage("myTopic", String.valueOf(stock.getStockID()), message);
        }
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

    private String convertStockToMessage(ItemObj patient) {
        try {
            return objectMapper.writeValueAsString(patient);
        } catch (Exception e) {
            throw new RuntimeException("Ошибка при преобразовании", e);
        }
    }

}

