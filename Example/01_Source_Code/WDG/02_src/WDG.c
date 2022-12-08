/// @file  WDG.c
/// @brief Source file of WatchDog module

#include "Std_Types.h"
#include "WDG.h"

static vWDGDisable()
{
    // Disable interrupts
    SYS_vDisableInterrupt();
    // Reset WatchDog timer
    __asm__ __volatile__ ("wdr");
    // Clear WDRF in MCUSR
    WDG_nREG8(WDG_nREG8_MCUSR) &= ~(1u << WDG_nWDRF);
    // Write logical one to WDCE and WDE
    WDG_nREG8(WDG_nREG8_WDTCSR) = (1u << WDG_nWDCE) | (1 << WDG_nWDE);
    // Turn off WDT 
    WDG_nREG8(WDG_nREG8_WDTCSR) = 0x0;
    // Enable interrupts
    SYS_vEnableInterruts();
}

static boolean boWDGSetupConfig()
{
    boolean boResult   = boFALSE;
    uint8   u8Settings = pWDG_stWatchDogConfig[WDG_nWDT_SELECTED_CFG]->u8Mode | pWDG_stWatchDogConfig[WDG_nWDT_SELECTED_CFG]->u8Prescale;

    // Disable interrupts
    SYS_vDisableInterrupt();
    // Reset WatchDog timer
    __asm__ __volatile__ ("wdr");
    // Clear WDRF in MCUSR
    WDG_nREG8(WDG_nREG8_MCUSR) &= ~(1u << WDG_nWDRF);
    // Write logical one to WDCE and WDE
    WDG_nREG8(WDG_nREG8_WDTCSR) = (1u << WDG_nWDCE) | (1 << WDG_nWDE);
    // Setup the WatchDog
    WDG_nREG8(WDG_nREG8_WDTCSR) = u8Settings;

    if(WDG_nREG8(WDG_nREG8_WDTCSR) == u8Settings)
    {
        boResult == boTRUE;
    }

    return boResult;
}

void WDG_vInit()
{
    boolean boSetupSuccess = boFALSE;
    uint32  u32CurrentTime;
    const uint32 u32StartTime = SYS_u32GetTimeCurrent();

    // Disable WatchDog at startup - recommended by manufacturer
    vWDGDisable();

    do
    {
        // Setup WatchDog module
        boSetupSuccess = boWDGSetupConfig();

        // Update time spent in the loop
        u32CurrentTime = SYS_u32GetTimeSince(u32StartTime);
    } while ((boSetupSuccess != boTRUE) | u32CurrentTime < WDG_nWDT_INIT_TIME_LIMIT);
    
    // If the setup was unsuccessful
    if(boSetupSuccess == boFALSE)
    {
        // Initiate hardware reset
        ResetMCU_vHardReset(ResetMCU_nWDG_INIT_FAILED);
    }
}