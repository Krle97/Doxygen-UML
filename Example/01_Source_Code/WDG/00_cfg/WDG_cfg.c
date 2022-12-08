/// @file  WDG_cfg.c
/// @brief Source configuration file of WatchDog module

#include "WDG_cfg.h"

// WatchDog configuration: MODE - Interrupt, PRESCALE - 125ms
static const WDG_tstWatchDogConfig WDG_stWatchDogConfig_0 = 
{
    WDG_nWDT_MODE_INTERRUP,
    WDG_nWDT_PRESCALE_125ms
};

// WatchDog configuration: MODE - Reset, PRESCALE - 1000ms
static const WDG_tstWatchDogConfig WDG_stWatchDogConfig_1 = 
{
    WDG_nWDT_MODE_RESET,
    WDG_nWDT_PRESCALE_1000ms
};

// WatchDog configuration: MODE - Interrupt and Reset, PRESCALE - 16ms
static const WDG_tstWatchDogConfig WDG_stWatchDogConfig_2 = 
{
    WDG_nWDT_MODE_INT_RESET,
    WDG_nWDT_PRESCALE_16ms
};

// WatchDog module configuration list
const WDG_tstWatchDogConfig * pWDG_stWatchDogConfig[WDG_nWDT_NUMBER_OF_CFG] =
{
    &WDG_stWatchDogConfig_0,
    &WDG_stWatchDogConfig_1,
    &WDG_stWatchDogConfig_2
};