#include <Uefi.h>

#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <PiPei.h>
#include <Guid/MemoryAllocationHob.h>
#include <Pi/PiHob.h>
#include <Include/HobDemo.h>


extern EFI_GUID gMyFirstHobGuid;

EFI_STATUS
EFIAPI
LocateMyHobEntry(
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
)
/**
  a Dxe Drier to locate my hob.

  @param ImageHandle     Image handle this driver.
  @param SystemTable     Pointer to SystemTable.

  @retval EFI_SUCESS     This function always complete successfully.

**/
{

  EFI_STATUS               Status;
  UINTN                    Temp;

  TEST_STR                 *PacketHeader;
  EFI_PEI_HOB_POINTERS      HobPointer;

  for(Temp = 0; Temp <= 5; Temp++) {
      DEBUG ((EFI_D_ERROR, "\n"));
  }

  DEBUG ((DEBUG_INFO, "dxe locate hob is start!..\n"));

  HobPointer.Raw = GetFirstGuidHob (&gMyFirstHobGuid);
  PacketHeader = (TEST_STR *) GET_GUID_HOB_DATA (HobPointer.Guid);
  PacketHeader->PrintMesg();
  DEBUG ((DEBUG_INFO, "Deckard PacketHeader->number=%d\n",PacketHeader->number));

  DEBUG ((DEBUG_INFO, "dxe locate hob is end!..\n"));
  Status=EFI_SUCCESS;

  return Status;
}
