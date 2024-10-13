// Copyright (c) 2024 Andrey Zakharov.
// Licensed under the <LICENSE NAME>
// This code is based on public sources, including MSDN.

// C system headers
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// C++ system headers
#include <iostream>
#include <string>

const char* server_ip = "192.168.31.70";  // Укажите IP-адрес вашего сервера
const int server_port = 27015;  // Укажите порт сервера

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Создание сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);

    // Конвертация IPv4 и IPv6 адресов из текста в бинарную форму
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    // Подключение к серверу
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }

    while (true) {
        std::cout << "Enter a number (or 'exit' to quit): ";
        std::string input;
        std::cin >> input;
        if (input == "exit") break;  // Условие выхода из цикла

        // Отправка числа
        send(sock, input.c_str(), input.length(), 0);
        std::cout << "Number sent" << std::endl;

        // Получение ответа от сервера
        int valread = read(sock, buffer, 1024);
        if (valread > 0) {
            buffer[valread] = '\0';
            std::cout << "Server response: " << buffer << std::endl;
        }
        memset(buffer, 0, sizeof(buffer));  // Очистка буфера
    }

    close(sock);
    return 0;
}


