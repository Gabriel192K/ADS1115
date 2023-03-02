/*
 * Read ADC.cpp
 *
 * Created: 3/1/2023 4:33:41 PM
 * Author : Office 5
 */ 

#include "ADS1115/ADS1115.h"
#include "USART/USART.h"
#include "Time/Time.h"

ADS1115 ads(&TWI, 0x48);

int main(void)
{
    USART.begin(9600);
    Time.begin();
    USART.printP(PSTR("ADS1115 Reading ADC example code\n"));
    if (ads.begin())
        USART.printP(PSTR("ADS1115 working\n"));
    else
    {
        USART.printP(PSTR("ADS1115 not working\n"));
        while(1);
    }
    while (1) 
    {
        USART.println();
        for (uint8_t i = 0; i< 4; i++)
            USART.printf("ADC[%hhu]: %d\n", i, ads.read(i));
        USART.println();
        Time.delayMillis(1000);
    }
}

