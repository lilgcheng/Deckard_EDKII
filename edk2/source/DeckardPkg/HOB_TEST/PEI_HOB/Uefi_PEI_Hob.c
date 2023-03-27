
#include "Uefi_PEI_Hob.h"

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
Uefi_PEI_Hob (
  IN       EFI_PEI_FILE_HANDLE       FileHandle,
  IN CONST EFI_PEI_SERVICES          **PeiServices
  )
{
  EFI_STATUS Status =EFI_SUCCESS;
  UEFI_PEI_HOB_TEST *test = NULL;
 
  Status = PeiServicesCreateHob(
    EFI_HOB_TYPE_GUID_EXTENSION,
    sizeof(UEFI_PEI_HOB_TEST),
    (VOID **)&test
  );
  test->Age = 29;
  test->name = L"Deckard";
  test->Header.Name = gDeckardHobGuid;//define on DeckardLearningPkg.dec


  DEBUG ((EFI_D_INFO, "============================================\n"));
  DEBUG ((EFI_D_INFO, "========[Deckard] create Hob test===========\n"));
  DEBUG ((EFI_D_INFO, "============================================\n"));

  return EFI_SUCCESS;
}
