
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/PrintLib_External.h>
#include <Library/DebugLib.h>

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
Uefi_Main_Use_Library (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  // EFI_TIME curTime;
  Print(L"Hello,this is Entry of UefiMain!\n");
  EFI_STATUS Status  = EFI_SUCCESS;
  Status= PrintLibUse();

  return EFI_SUCCESS;
}
