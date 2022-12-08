/// @file  WDG.h
/// @brief Header file of WatchDog module

#ifndef WDG_H
#define WDG_H

#include "WDG_cfg.h"

/// This function performs complete configuration for the WatchDog module
///
/// @pre
/// - This function must be called at the startup of the ECU only once.
/// @post
/// - WatchDog counter must be reseted periodically in order to avoid time-out
/// @param
/// - None
/// @return
/// - None
/// @globals
/// - None
/// @callsequence
///   @startuml "WDG_vInit.png"
///   title "Sequence diagram for function WDG_vInit"
///   ->WDG: WDG_vInit function call
///   WDG ++
///   WDG -> SYS: SYS_u32GetTimeCurrent()
///   WDG --
///   SYS ++
///   rnote over SYS #Cyan: Get current system time
///   SYS -> WDG: //u32StartTime//
///   SYS --
///   WDG ++
///   rnote over WDG: Disable WatchDog module\nFollowing manufacturers advice:
///   WDG -> WDG: vWDGDisable()
///   loop While setup isn't successful and the time limit isn't breached:
///     rnote over WDG: Call WatchDog setup routine:
///     WDG -> WDG: boWatchDogSetupConfig():\nreturns success status
///     WDG -> SYS: SYS_u32GetTimeSince(u_StartTime)
///     WDG --
///     SYS ++
///     rnote over SYS #Cyan: Update time spent in the loop
///     SYS -> WDG: //u32CurrentTime//
///     SYS --
///     WDG ++
///   end loop
///   opt If setup wasn't successful:
///     WDG++
///     WDG -> ResetMCU: ResetMCU_vHardReset(ResetMCU_nWDG_INIT_FAILED)
///     WDG --
///     ResetMCU ++
///     rnote over ResetMCU #Yellow: Initiate hardware reset
///     ResetMCU -> WDG
///     ResetMCU --
///     WDG ++
///   end opt
///   @enduml
///
void WDG_vInit();

#endif //WDG_H

