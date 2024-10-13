#include "RTE_Components.h"
#include CMSIS_device_header

void delay(volatile uint32_t count){
    while(count--)
        __NOP();
}

int main()
{
    // Включаем GPIOD
    *((volatile uint32_t*)0x40021014) |= (1 << 20);

    // Устанавливаем PD6 и PD14 в режим вывода
    *((volatile uint32_t*)0x48000C00) |= ((1 << (6 * 2)) | (1 << (14 * 2)));

while(1){

    // Устанавливаем "1" на PD6 и "0" на PD14
    *((volatile uint32_t*)0x48000C14) ^= (1 << 6);
    *((volatile uint32_t*)0x48000C14) ^= (1 << 14);
    delay(64);

    // Устанавливаем "1" на PD14
    *((volatile uint32_t*)0x48000C14) ^= (1 << 14);
    delay(64);
    }
}
