package com.example.Project;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Profile;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.stereotype.Service;

@Service
@Profile("consumer")
public class MyKafkaConsumer {
    private final ItemObjRepository repository;
    private final ObjectMapper objectMapper = new ObjectMapper();

    @Autowired
    public MyKafkaConsumer(ItemObjRepository repository) {
        this.repository = repository;
    }

    @KafkaListener(topics = "myTopic")
    public void listen(String message) {
        System.out.println(message);
        // Преобразование сообщения обратно в ItemObj и сохранение его в базе данных
        ItemObj itemObj = convertMessageToItemObj(message);
        repository.save(itemObj);
    }

    private ItemObj convertMessageToItemObj(String message) {
        try {
            return objectMapper.readValue(message, ItemObj.class);
        } catch (Exception e) {
            throw new RuntimeException("Ошибка при преобразовании сообщения", e);
        }
    }
}

