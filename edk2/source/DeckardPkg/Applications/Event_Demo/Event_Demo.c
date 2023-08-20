

// #include "Event_Demo.h"

#include <Uefi.h>

// #include <Library/BaseMemoryLib.h>
// #include <Library/DebugLib.h>
// #include <Library/PcdLib.h>
// #include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include <Uefi/UefiBaseType.h>
#include <Uefi/UefiSpec.h>
#include <Library/DebugLib.h>

// #include <PiPei.h>
// #include <Library/BaseLib.h>
// #include <Library/TimerLib.h>

// #include <Library/EmuThunkLib.h>


// #include <Protocol/Timer.h>

EFI_BOOT_SERVICES  *gBS         = NULL;

STATIC
VOID
EFIAPI
CHHEventTest(IN EFI_EVENT Event,IN VOID *Context){
   DEBUG (( DEBUG_INFO, "%a call Create Event test \n", __FUNCTION__));
}

EFI_STATUS
EFIAPI
Event_Demo_Entry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_EVENT mCHHEvent;
  EFI_STATUS Status;
  Status = gBS->CreateEvent(
    EVT_TIMER | EVT_NOTIFY_SIGNAL,
    TPL_NOTIFY,
    CHHEventTest,
    NULL,
    &mCHHEvent
  );
  gBS->SetTimer(mCHHEvent,TimerPeriodic,1*10*1000);
  DEBUG (( DEBUG_INFO, "%a  Create Event test \n", __FUNCTION__));

  return EFI_SUCCESS;
}