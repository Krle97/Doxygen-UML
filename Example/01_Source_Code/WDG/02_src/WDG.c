/// @file  WDG.c
/// @brief Source file of WatchDog module

#include "Std_Types.h"
#include "WDG.h"

/// Function disables WatchDog module
///
/// @pre
///   None
/// @post
///   None
/// @param 
///   None
/// @return 
///   None
/// @globals
///   None
/// @callsequence
///   @startuml "vWDGDisable.png"
///     title "Sequence diagram for function vWDGDisable"
///     ->WDG: vWDGDisable() function call
///     WDG ++
///     WDG -> SYS: SYS_vDisableInterrupt()
///     WDG --
///     SYS ++
///     rnote over SYS: Disable global interrupts
///     SYS -> WDG: //none//
///     SYS --
///     WDG ++
///     rnote over WDG: Reset WatchDog timer
///     rnote over WDG: Clear WDRF in MCUSR
///     rnote over WDG: Write logical one to WDCE and WDE
///     rnote over WDG: Turn off WDT
///     WDG -> SYS: SYS_vEnableInterruts()
///     WDG --
///     SYS ++
///     rnote over SYS: Enable global interrupts
///     SYS -> WDG: //none//
///     SYS --
///     WDG ++
///     <- WDG: //none//
///     WDG --
///   @enduml
static vWDGDisable();

/// Function disables WatchDog module
///
/// @pre
///   None
/// @post
///   Implement safety check based on return status
/// @param 
///   None
/// @return 
///   boResult : Returns bo_TRUE if the setup is successful, otherwise returns bo_FLASE
/// @globals
///   @ref pWDG_stWatchDogConfig : structure contains setting which need to be applied 
/// @callsequence
///   @startuml
///     title "Sequence diagram for function boWDGSetupConfig"
///     ->WDG: boWDGSetupConfig()
///     WDG ++
///     rnote over WDG: Fetch data from global structure pWDG_stWatchDogConfig
///     WDG -> SYS: SYS_vDisableInterrupt()
///     WDG --
///     SYS ++
///     rnote over SYS: Disable global interrupts
///     SYS -> WDG: //none//
///     SYS --
///     WDG ++
///     rnote over WDG: Reset WatchDog timer
///     rnote over WDG: Clear WDRF in MCUSR
///     rnote over WDG: Write logical one to WDCE and WDE
///     rnote over WDG: Setup the WatchDog
///     opt If the value of WDTCSR is the same as the one from configuration:
///       rnote over WDG: boResult = boTRUE
///     end 
///     WDG -> SYS: SYS_vEnableInterruts()
///     WDG --
///     SYS ++
///     rnote over SYS: Enable global interrupts
///     SYS -> WDG: //none//
///     SYS --
///     WDG ++
///     <- WDG: //boResult//
///     WDG --
///   @enduml
static boolean boWDGSetupConfig();

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
    // Enable interrupts
    SYS_vEnableInterruts();
	
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