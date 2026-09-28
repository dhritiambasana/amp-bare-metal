#include "registers.h"
#include "rtc.h"

void rtc_init(void)
{
    // 1. Enable PWR peripheral clock
    RCC_APB1ENR |= (1 << 28);   // PWREN

    // 2. Disable backup domain write protection
    PWR_CR |= (1 << 8);         // DBP

    // 3. Enable LSI oscillator
    RCC_CSR |= (1 << 0);        // LSION
    while (!(RCC_CSR & (1 << 1)));  // wait for LSIRDY

    // 4. Select LSI as RTC clock source, enable RTC
    RCC_BDCR &= ~(0x3 << 8);    // clear RTCSEL bits
    RCC_BDCR |=  (0x2 << 8);    // RTCSEL = 10 -> LSI
    RCC_BDCR |=  (1 << 15);     // RTCEN

    // 5. Unlock RTC register write protection
    RTC_WPR = 0xCA;
    RTC_WPR = 0x53;

    // 6. Enter Init mode
    RTC_ISR |= (1 << 7);            // INIT
    while (!(RTC_ISR & (1 << 6)));  // wait for INITF

    // 7. Set prescaler for ~1Hz tick (assumes ~32kHz LSI, see note below)
    RTC_PRER = (127 << 16) | (249 << 0);  // PREDIV_A = 127, PREDIV_S = 249

    // 8. Set initial time to 00:00:00 (BCD format)
    RTC_TR = 0x00000000;
    RTC_DR = 0x00002101;  // arbitrary placeholder date, BCD (not used for display here)

    // 9. Exit Init mode
    RTC_ISR &= ~(1 << 7);

    // 10. Re-lock write protection
    RTC_WPR = 0xFF;
}

void rtc_get_time(int *hh, int *mm, int *ss)
{
    uint32_t tr1, tr2;

    do {
        tr1 = RTC_TR; // 0x0000 0000
        tr2 = RTC_TR; // 0x0000 0000
    } while (tr1 != tr2);   // reject torn reads, retry until stable

    int ht = (tr1 >> 20) & 0x3;
    int hu = (tr1 >> 16) & 0xF;
    int mnt = (tr1 >> 12) & 0x7;
    int mnu = (tr1 >> 8)  & 0xF;
    int st  = (tr1 >> 4)  & 0x7;
    int su  = (tr1 >> 0)  & 0xF;

    *hh = ht * 10 + hu;
    *mm = mnt * 10 + mnu;
    *ss = st * 10 + su;
}