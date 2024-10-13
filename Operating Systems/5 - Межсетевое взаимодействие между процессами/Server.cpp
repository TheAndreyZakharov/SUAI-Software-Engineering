// Copyright (c) 2024 Andrey Zakharov.
// Licensed under the <LICENSE NAME>
// This code is based on public sources, including MSDN.

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <string>

// Other headers
#pragma comment(lib, "Ws2_32.lib")

bool IsPrime(int num) {
  if (num <= 1) return false;
  for (int i = 2; i * i <= num; ++i) {
    if (num % i == 0) return false;
  }
  return true;
}

std::string NumberToWords(int num) {
  const char* units[] = {"zero", "one", "two", "three", "four",
                         "five", "six", "seven", "eight", "nine"};
  const char* teens[] = {"ten", "eleven", "twelve", "thirteen",
                         "fourteen", "fifteen", "sixteen",
                         "seventeen", "eighteen", "nineteen"};
  const char* tens[] = {"", "", "twenty", "thirty", "forty", "fifty",
                        "sixty", "seventy", "eighty", "ninety"};
  const char* hundred = "hundred";

  if (num < 0) return "minus " + NumberToWords(-num);
  if (num < 10) return units[num];
  if (num < 20) return teens[num - 10];
  if (num < 100) {
    return tens[num / 10] + (num % 10 ? " " + units[num % 10] : "");
  }
  if (num < 1000) {
    return units[num / 100] + " " + hundred +
           (num % 100 ? " and " + NumberToWords(num % 100) : "");
  }
  return "number too large";
}

int main() {
  WSADATA wsaData;
  int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (result != 0) {
    std::cerr << "WSAStartup failed: " << result << std::endl;
    return 1;
  }

  SOCKET m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (m_socket == INVALID_SOCKET) {
    std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
    WSACleanup();
    return 1;
  }

  sockaddr_in service = {0};
  service.sin_family = AF_INET;
  service.sin_addr.s_addr = INADDR_ANY;
  service.sin_port = htons(27015);

  if (bind(m_socket,
  reinterpret_cast<SOCKADDR*>(&service),
  sizeof(service)) == SOCKET_ERROR) {
    std::cerr << "bind() failed." << std::endl;
    closesocket(m_socket);
    WSACleanup();
    return 1;
  }

  if (listen(m_socket, 1) == SOCKET_ERROR) {
    std::cerr << "Error listening on socket." << std::endl;
    closesocket(m_socket);
    WSACleanup();
    return 1;
  }

  std::cout << "Waiting for a client to connect..." << std::endl;
  while (true) {
    SOCKET AcceptSocket = accept(m_socket, NULL, NULL);
    if (AcceptSocket == INVALID_SOCKET) {
      std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
      continue;
    }
    std::cout << "Client Connected." << std::endl;

    while (true) {
      char recvbuf[32] = {0};
      int bytesRecv = recv(AcceptSocket, recvbuf, sizeof(recvbuf) - 1, 0);
      if (bytesRecv <= 0) break;

      recvbuf[bytesRecv] = '\0';
      int num = atoi(recvbuf);
      bool prime = IsPrime(num);
      std::string words = NumberToWords(num);

      char sendbuf[256];
      snprintf(sendbuf, sizeof(sendbuf), "%d %s", prime ? 1 : 0, words.c_str());
      send(AcceptSocket, sendbuf, strlen(sendbuf), 0);
    }
    closesocket(AcceptSocket);
    std::cout << "Client Disconnected." << std::endl;
  }

  closesocket(m_socket);
  WSACleanup();
  return 0;
}
