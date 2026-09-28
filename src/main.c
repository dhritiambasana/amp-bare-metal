#include "registers.h"
#include "sevenseg.h"
#include "rtc.h"

void SystemInit(void) {}
void _init(void) {}
void _fini(void) {}

//? LED blink (GPIO) && Half IR

// int main(void) {
//     RCC_AHB1ENR |= (1 << 0);            // enable GPIOA clock

//     GPIOA_MODER &= ~(0x3 << (12 * 2));  // PA12 -> outout
//     GPIOA_MODER &= ~(0x3 << (11 * 2));  // PA11 -> input
//     GPIOA_MODER |=  (0x1 << (12 * 2));  // set PA12 as

//     // GPIOA_OTYPER

//     GPIOA_MODER &= ~(0x3 << (2 * 2)); // PA03 -> input

//     GPIOA_PUPDR &= ~(0x3 << (11 * 2));
//     GPIOA_PUPDR |=  (0x2 << (11 * 2)); // pull-down

//     GPIOA_PUPDR &= ~(0x3 << (2 * 2));
//     GPIOA_PUPDR |=  (0x2 << (2 * 2)); // pull-down

//     // GPIOA_ODR ^= (1 << 12);

//     while (1) {
//         if (GPIOA_IDR & (1 << 11)) {
//             GPIOA_ODR |= (1 << 12);
//         }
//         // GPIOA_ODR &= ~(1 << 12);
//         for (volatile int i = 0; i < 4000; i++);
//         if (GPIOA_IDR & (1 << 2)) {
//             GPIOA_ODR |= (1 << 12);
//         }

//         GPIOA_ODR &= ~(1 << 12);
//     }
//     return 0;
// }

// int main()
// {
//     i_gpio();
//     i_timer();

//     while (1)
//     {
//         GPIOA_ODR &= ~(0x1 << 11);
//         GPIOB_ODR |= (0x1 << 2);
//         GPIOB_ODR |= (0x1 << 12);
//         display(8);
//         d_timer_polling();

//         GPIOA_ODR |= (0x1 << 11);
//         GPIOB_ODR &= ~(0x1 << 2);
//         GPIOB_ODR |= (0x1 << 12);
//         display(2);
//         d_timer_polling();

//         GPIOA_ODR |= (0x1 << 11);
//         GPIOB_ODR |= (0x1 << 2);
//         GPIOB_ODR &= ~(0x1 << 12);
//         display(6);
//         d_timer_polling();
//     }

//     return 0;
// }

int main(void)
{
    i_gpio();
    i_timer();
    rtc_init();

    while (1)
    {
        int hh, mm, ss;
        rtc_get_time(&hh, &mm, &ss);

        int minute_tens = mm / 10;
        int minute_units = mm % 10;      // only 1 digit available for minutes
        int sec_tens = ss / 10;
        int sec_units = ss % 10;

        GPIOB_ODR &= ~(0x1 << 9);
        GPIOA_ODR |= (0x1 << 11);
        GPIOB_ODR |= (0x1 << 8);
        GPIOB_ODR |= (0x1 << 12);
        display(minute_tens);
        d_timer_polling();

        GPIOB_ODR |= (0x1 << 9);
        GPIOA_ODR &= ~(0x1 << 11);
        GPIOB_ODR |= (0x1 << 8);
        GPIOB_ODR |= (0x1 << 12);
        display(minute_units);
        d_timer_polling();

        GPIOB_ODR |= (0x1 << 9);
        GPIOA_ODR |= (0x1 << 11);
        GPIOB_ODR &= ~(0x1 << 8);
        GPIOB_ODR |= (0x1 << 12);
        display(sec_tens);
        d_timer_polling();

        GPIOB_ODR |= (0x1 << 9);
        GPIOA_ODR |= (0x1 << 11);
        GPIOB_ODR |= (0x1 << 8);
        GPIOB_ODR &= ~(0x1 << 12);
        display(sec_units);
        d_timer_polling();
    }

    return 0;
}