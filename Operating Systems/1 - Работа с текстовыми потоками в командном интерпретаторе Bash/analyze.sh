#!/usr/bin/env bash
TASKID=13
logFile="dns-tunneling.log"

export LC_NUMERIC="C"

# Вычисление общего количества запросов
totalRequests=$(wc -l < "$logFile")

# Подсчет количества запросов для каждого домена
count1yf=$(grep -c "1yf.de." "$logFile")
count2yf=$(grep -c "2yf.de." "$logFile")
countWhatsapp=$(grep -c "whatsapp.net." "$logFile")

# Оставляем ваш оригинальный метод подсчета для google.com
VAR_2=$(grep -E "(\\s|^)([a-zA-Z0-9_\\-]+\\.)*google\\.com\\.\\s" "$logFile" | wc -l)

# Проценты запросов для каждого домена
percent1yf=$(awk -v count="$count1yf" -v total="$totalRequests" 'BEGIN {printf "%.3f\n", (count/total)*100}')
percent2yf=$(awk -v count="$count2yf" -v total="$totalRequests" 'BEGIN {printf "%.3f\n", (count/total)*100}')
percentWhatsapp=$(awk -v count="$countWhatsapp" -v total="$totalRequests" 'BEGIN {printf "%.3f\n", (count/total)*100}')
percentGoogle=$(awk -v count="$VAR_2" -v total="$totalRequests" 'BEGIN {printf "%.3f\n", (count/total)*100}')

# Запись результатов в файл
{
    echo "$percent1yf"
    echo "$percent2yf"
    echo "$percentWhatsapp"
    echo "$percentGoogle"
} > results.txt

# Вывод общего количества строк для VAR_1
VAR_1="$totalRequests"
echo "VAR_1: $VAR_1"
echo "VAR_2: $VAR_2"


