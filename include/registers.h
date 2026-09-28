#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

// GPIO

#define RCC_AHB1ENR (*(volatile uint32_t *)(0x40023800 + 0x30))

#define GPIOA_MODER (*(volatile uint32_t *)(0x40020000 + 0x00))
#define GPIOB_MODER (*(volatile uint32_t *)(0x40020400 + 0x00))

#define GPIOA_ODR   (*(volatile uint32_t *)(0x40020000 + 0x14))
#define GPIOB_ODR   (*(volatile uint32_t *)(0x40020400 + 0x14))

#define GPIOA_IDR   (*(volatile uint32_t *)(0x40020000 + 0x10))
#define GPIOA_PUPDR (*(volatile uint32_t *)(0x40020000 + 0x0C))

#define GPIOA_BSRR  (*(volatile uint32_t *)(0x40020000 + 0x18))
#define GPIOB_BSRR  (*(volatile uint32_t *)(0x40020400 + 0x18))

// TIMER

#define RCC_APB1ENR (*(volatile uint32_t *)(0x40023800 + 0x40))
#define TIMER2_PSC  (*(volatile uint32_t *)(0x40000000 + 0x28))
#define TIMER2_ARR  (*(volatile uint32_t *)(0x40000000 + 0x2C))
#define TIMER2_CNT  (*(volatile uint32_t *)(0x40000000 + 0x24))
#define TIMER2_CR1  (*(volatile uint32_t *)(0x40000000 + 0x00))
#define TIMER2_SR   (*(volatile uint32_t *)(0x40000000 + 0x10))

// PWR (Power Control)
#define PWR_CR       (*(volatile uint32_t *)(0x40007000 + 0x00))

// RCC additions (base 0x40023800)
#define RCC_APB1ENR  (*(volatile uint32_t *)(0x40023800 + 0x40))  // you may already have this
#define RCC_BDCR     (*(volatile uint32_t *)(0x40023800 + 0x70))
#define RCC_CSR      (*(volatile uint32_t *)(0x40023800 + 0x74))

// RTC (base 0x40002800)
#define RTC_TR       (*(volatile uint32_t *)(0x40002800 + 0x00))
#define RTC_DR       (*(volatile uint32_t *)(0x40002800 + 0x04))
#define RTC_CR       (*(volatile uint32_t *)(0x40002800 + 0x08))
#define RTC_ISR      (*(volatile uint32_t *)(0x40002800 + 0x0C))
#define RTC_PRER     (*(volatile uint32_t *)(0x40002800 + 0x10))
#define RTC_WPR      (*(volatile uint32_t *)(0x40002800 + 0x24))

#endif