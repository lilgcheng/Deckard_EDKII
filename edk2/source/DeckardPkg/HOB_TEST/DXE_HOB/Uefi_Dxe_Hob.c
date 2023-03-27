
/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiRuntimeLib.h>
#include <Library/UefiBootServicesTableLib.h>


#include <Pi/PiHob.h>
#include <Hob/Include_PEI_Hob.h>
#include <Library/HobLib.h>

EFI_STATUS
Uefi_Dxe_Hob (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_HOB_GUID_TYPE *HobList = NULL;
  UEFI_PEI_HOB_TEST *pei_hob_test;
  HobList = GetHobList(); //hind Hob header
  pei_hob_test = GetNextGuidHob(&gDeckardHobGuid,HobList);

  DEBUG ((EFI_D_INFO, "\n ####################### \n"));
  DEBUG ((EFI_D_INFO, "\n Deckard DXE get HOB \n"));
  DEBUG ((EFI_D_INFO, "\n ####################### \n"));
  ASSERT_EFI_ERROR(Status);
  DEBUG ((EFI_D_INFO, "\n ####################### \n"));
  DEBUG ((EFI_D_INFO, "\n ####################### \n"));
  DEBUG ((EFI_D_INFO, "\n ####################### \n"));
  DEBUG ((EFI_D_INFO, "\n Name %s \n",pei_hob_test->name));
  DEBUG ((EFI_D_INFO, "\n age %d \n",pei_hob_test->Age));

  DEBUG ((EFI_D_INFO, "\n ####################### \n"));
  DEBUG ((EFI_D_INFO, "\n ####################### \n"));
  DEBUG ((EFI_D_INFO, "\n ####################### \n"));
  return EFI_SUCCESS;
}
