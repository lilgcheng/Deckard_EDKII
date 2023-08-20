

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
   DEBUG (( DEBUG_INFO, "%a call Create Event CHHEventTest 1 \n", __FUNCTION__));
}

STATIC
VOID
EFIAPI
CHHEventTest2(IN EFI_EVENT Event,IN VOID *Context){
   DEBUG (( DEBUG_INFO, "%a call Create Event CHHEventTest2 \n", __FUNCTION__));
}

EFI_STATUS
EFIAPI
Event_Demo_Entry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  // EFI_EVENT mCHHEvent;
  // EFI_STATUS Status;
  // Status = gBS->CreateEvent(
  //   EVT_TIMER | EVT_NOTIFY_SIGNAL,
  //   TPL_NOTIFY,
  //   CHHEventTest,
  //   NULL,
  //   &mCHHEvent
  // );
  // gBS->SetTimer(mCHHEvent,TimerPeriodic,1*10*1000);
  // DEBUG (( DEBUG_INFO, "%a  Create Event test \n", __FUNCTION__));

  EFI_EVENT mCHHEvent;
  EFI_EVENT mCHHEvent2;
  EFI_GUID gCHHEventExtestGuid  = { 0x0579257E, 0x1843, 0x45FB, { 0x83, 0x9D, 0x6B, 0x79, 0x09, 0x38, 0x29, 0xA9 } };

gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  CHHEventTest,
                  NULL,
                  &gCHHEventExtestGuid,
                  &mCHHEvent
                  );
  gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  CHHEventTest2,
                  NULL,
                  &gCHHEventExtestGuid,
                  &mCHHEvent2
                  );
  DEBUG ((EFI_D_INFO, "Charles SignalEvent mCHHEvent  ...\n"));
  gBS->SignalEvent (mCHHEvent);
  DEBUG ((EFI_D_INFO, "Charles SignalEvent mCHHEvent2  ...\n"));
  gBS->SignalEvent (mCHHEvent2);
  gBS->CloseEvent(mCHHEvent);
  gBS->CloseEvent(mCHHEvent2);
  return EFI_SUCCESS;
}