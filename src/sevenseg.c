#include "registers.h"
#include "sevenseg.h"

// Segment bit masks
#define SEG_A (1 << 7)   // PA7
#define SEG_B (1 << 12)  // PA12
#define SEG_F (1 << 6)   // PA6
#define SEG_G (1 << 5)   // PA5
#define SEG_C (1 << 5)   // PB5
#define SEG_D (1 << 4)   // PB4
#define SEG_E (1 << 3)   // PB3

void i_gpio(void)
{
    RCC_AHB1ENR |= (1 << 0); // GPIOA
    RCC_AHB1ENR |= (1 << 1); // GPIOB

    // ACCESSING INDIVIDUAL LEDS OF SEGMENT (DATAPIN)

    GPIOA_MODER &= ~(0x3 << (5 * 2));
    GPIOA_MODER |=  (0x1 << (5 * 2));  // PA05 -> output

    GPIOA_MODER &= ~(0x3 << (6 * 2));
    GPIOA_MODER |=  (0x1 << (6 * 2));  // PA06 -> output

    GPIOA_MODER &= ~(0x3 << (7 * 2));
    GPIOA_MODER |=  (0x1 << (7 * 2));  // PA07 -> output

    GPIOA_MODER &= ~(0x3 << (12 * 2));
    GPIOA_MODER |=  (0x1 << (12 * 2)); // PA12 -> output

    GPIOB_MODER &= ~(0x3 << (3 * 2));
    GPIOB_MODER |=  (0x1 << (3 * 2));  // PB03 -> output

    GPIOB_MODER &= ~(0x3 << (4 * 2));
    GPIOB_MODER |=  (0x1 << (4 * 2));  // PB04 -> output

    GPIOB_MODER &= ~(0x3 << (5 * 2));
    GPIOB_MODER |=  (0x1 << (5 * 2));  // PB05 -> output

    // GND AKA SELECTION LINES

    GPIOA_MODER &= ~(0x3 << (11 * 2));
    GPIOA_MODER |=  (0x1 << (11 * 2)); // PA11 -> output

    GPIOB_MODER &= ~(0x3 << (12 * 2));
    GPIOB_MODER |=  (0x1 << (12 * 2)); // PB12 -> output

    GPIOB_MODER &= ~(0x3 << (8 * 2));
    GPIOB_MODER |=  (0x1 << (8 * 2));  // PB08 -> output

    GPIOB_MODER &= ~(0x3 << (9 * 2));
    GPIOB_MODER |=  (0x1 << (9 * 2));  // PB09 -> output
}

void i_timer(void)
{
    RCC_APB1ENR |= (1 << 0);
    TIMER2_PSC = 15999;
    TIMER2_ARR = 2;
    TIMER2_CNT = 0;
    TIMER2_CR1 |= (1 << 0);
}

void d_timer_polling(void)
{
    while (!(TIMER2_SR & 0x1))
    {
    }
    TIMER2_SR &= ~(0x1);
}

void display(int num)
{
    switch (num)
    {
    case 0: // a b c d e f, g OFF
        GPIOA_ODR |=  (SEG_A | SEG_B | SEG_F);
        GPIOA_ODR &= ~(SEG_G);
        GPIOB_ODR |=  (SEG_C | SEG_D | SEG_E);
        break;

    case 1: // b c
        GPIOA_ODR |=  (SEG_B);
        GPIOA_ODR &= ~(SEG_A | SEG_F | SEG_G);
        GPIOB_ODR |=  (SEG_C);
        GPIOB_ODR &= ~(SEG_D | SEG_E);
        break;

    case 2: // a b d e g
        GPIOA_ODR |=  (SEG_A | SEG_B | SEG_G);
        GPIOA_ODR &= ~(SEG_F);
        GPIOB_ODR |=  (SEG_D | SEG_E);
        GPIOB_ODR &= ~(SEG_C);
        break;

    case 3: // a b c d g
        GPIOA_ODR |=  (SEG_A | SEG_B | SEG_G);
        GPIOA_ODR &= ~(SEG_F);
        GPIOB_ODR |=  (SEG_C | SEG_D);
        GPIOB_ODR &= ~(SEG_E);
        break;

    case 4: // b c f g
        GPIOA_ODR |=  (SEG_B | SEG_F | SEG_G);
        GPIOA_ODR &= ~(SEG_A);
        GPIOB_ODR |=  (SEG_C);
        GPIOB_ODR &= ~(SEG_D | SEG_E);
        break;

    case 5: // a c d f g
        GPIOA_ODR |=  (SEG_A | SEG_F | SEG_G);
        GPIOA_ODR &= ~(SEG_B);
        GPIOB_ODR |=  (SEG_C | SEG_D);
        GPIOB_ODR &= ~(SEG_E);
        break;

    case 6: // a c d e f g
        GPIOA_ODR |=  (SEG_A | SEG_F | SEG_G);
        GPIOA_ODR &= ~(SEG_B);
        GPIOB_ODR |=  (SEG_C | SEG_D | SEG_E);
        break;

    case 7: // a b c
        GPIOA_ODR |=  (SEG_A | SEG_B);
        GPIOA_ODR &= ~(SEG_F | SEG_G);
        GPIOB_ODR |=  (SEG_C);
        GPIOB_ODR &= ~(SEG_D | SEG_E);
        break;

    case 8: // all segments
        GPIOA_ODR |= (SEG_A | SEG_B | SEG_F | SEG_G);
        GPIOB_ODR |= (SEG_C | SEG_D | SEG_E);
        break;

    case 9: // a b c d f g
        GPIOA_ODR |=  (SEG_A | SEG_B | SEG_F | SEG_G);
        GPIOB_ODR |=  (SEG_C | SEG_D);
        GPIOB_ODR &= ~(SEG_E);
        break;

    default:
        // blank the digit rather than leaving old segments lit
        GPIOA_ODR &= ~(SEG_A | SEG_B | SEG_F | SEG_G);
        GPIOB_ODR &= ~(SEG_C | SEG_D | SEG_E);
        break;
    }
}