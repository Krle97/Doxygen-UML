/// @file  WDG_cfg.h
/// @brief Header configuration file of WatchDog module

#ifndef WDG_CFG_H
#define WDG_CFG_H

/// Define used for writing/reading from 8-bit register address
#define WDG_nREG8(x) (*(volatile uint8_t *)(x))

/// MCU Status Register Address- provides information on which reset source caused an MCU reset
#define WDG_nREG8_MCUSR 0x34
/// Define used for accessing PORF - Power-on Reset Flag
#define WDG_nPORF  0u
/// Define used for accessing EXTRF- External Reset Flag
#define WDG_nEXTRF 1u
/// Define used for accessing BORF - Brown-out Reset Flag
#define WDG_nBORF  2u
/// Define used for accessing WDRF - Watchdog System Reset Flag
#define WDG_nWDRF  3u

/// Watchdog Timer Control Register Address
#define WDG_nREG8_WDTCSR 0x60
/// Define used for accessing WDP0 - Watchdog Timer Prescaler 0
#define WDG_nWDP0 0u
/// Define used for accessing WDP1 - Watchdog Timer Prescaler 1
#define WDG_nWDP1 1u
/// Define used for accessing WDP2 - Watchdog Timer Prescaler 2
#define WDG_nWDP2 2u
/// Define used for accessing WDE - Watchdog System Reset Enable
#define WDG_nWDE  3u
/// Define used for accessing WDCE - Watchdog Change Enable
#define WDG_nWDCE 4u
/// Define used for accessing WDP3 - Watchdog Timer Prescaler 3
#define WDG_nWDP3 5u
/// Define used for accessing WDIE - Watchdog Interrupt Enable
#define WDG_nWDIE 6u
/// Define used for accessing WDIF - Watchdog Interrupt Flag
#define WDG_nWDIF 7u

/// Mode for WatchDog module - Stopped, no action on Time-out
#define WDG_nWDT_MODE_STOPPED   (0u)
/// Mode for WatchDog module - Interrupt, interrupt generated on Time-out
#define WDG_nWDT_MODE_INTERRUP  (1u << WDG_nWDIE)
/// Mode for WatchDog module - Reset, MCU reset on Time-out
#define WDG_nWDT_MODE_RESET     (1u << WDG_nWDE)
/// Mode for WatchDog module - Interrupt and Reset, interrupt generated on firts Time-out then MCU reset performed on second Time-out
#define WDG_nWDT_MODE_INT_RESET ((1u << WDG_nWDIE) | (1u << WDG_nWDE))

/// Prescale for WatchDog module - prescale value for 16ms Time-out
#define WDG_nWDT_PRESCALE_16ms   (0u)
/// Prescale for WatchDog module - prescale value for 32ms Time-out
#define WDG_nWDT_PRESCALE_32ms   (1u << WDG_nWDP0)
/// Prescale for WatchDog module - prescale value for 64ms Time-out
#define WDG_nWDT_PRESCALE_64ms   (1u << WDG_nWDP1)
/// Prescale for WatchDog module - prescale value for 125ms Time-out
#define WDG_nWDT_PRESCALE_125ms  (1u << WDG_nWDP1) | (1u << WDG_nWDP0)
/// Prescale for WatchDog module - prescale value for 250ms Time-out
#define WDG_nWDT_PRESCALE_250ms  (1u << WDG_nWDP2)
/// Prescale for WatchDog module - prescale value for 500ms Time-out
#define WDG_nWDT_PRESCALE_500ms  (1u << WDG_nWDP2) | (1u << WDG_nWDP0)
/// Prescale for WatchDog module - prescale value for 1000ms Time-out
#define WDG_nWDT_PRESCALE_1000ms (1u << WDG_nWDP2) | (1u << WDG_nWDP1)
/// Prescale for WatchDog module - prescale value for 2000ms Time-out
#define WDG_nWDT_PRESCALE_2000ms (1u << WDG_nWDP2) | (1u << WDG_nWDP1) | (1u << WDG_nWDP0)
/// Prescale for WatchDog module - prescale value for 4000ms Time-out
#define WDG_nWDT_PRESCALE_4000ms (1u << WDG_nWDP3)
/// Prescale for WatchDog module - prescale value for 8000ms Time-out
#define WDG_nWDT_PRESCALE_8000ms (1u << WDG_nWDP3) | (1u << WDG_nWDP0)

/// Number of WatchDog configurations
#define WDG_nWDT_NUMBER_OF_CFG 3u

/// WatchDog configuration which is currently selected to be used
#define WDG_nWDT_SELECTED_CFG 2u

/// WatchDog time limit for initialization in microseconds
#define WDG_nWDT_INIT_TIME_LIMIT 100u

/// Structure used for configuring the WatchDog module
typedef struct 
{
  uint8_t u8Mode;     ///< Selects the mode for WatchDog module
  uint8_t u8Prescale; ///< Selects the prescale value for WatchDog module
} WDG_tstWatchDogConfig;

/// Pointer to WatchDog module configuration list
const WDG_tstWatchDogConfig * pWDG_stWatchDogConfig[WDG_nWDT_NUMBER_OF_CFG];

#endif //WDG_CFG_H