
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/PrintLib_External.h>
#include <Library/DebugLib.h>
#include <Library/DebugPrintErrorLevelLib.h>
#include <Library/PcdLib.h>

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
Uefi_Main_Use_PCD (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{

  // EFI_STATUS Status = EFI_SUCCESS;
  UINT8 FixPcdValue = 0;
  UINT16 DynamicPcdValue = 0;
  FixPcdValue = FixedPcdGet8(PcdSample1);
  DEBUG ((EFI_D_INFO, "[Deckard] FixPcdValue:%x \n",FixPcdValue));
  DynamicPcdValue = PcdGet16(PcdSample2);
  DEBUG ((EFI_D_INFO, "[Deckard] DynamicPcdValue:%x \n",DynamicPcdValue));

  return EFI_SUCCESS;
}
