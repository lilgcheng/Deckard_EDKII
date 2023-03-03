/** @file
    Name: Dxe5.c
    Description: Locate Compal Learning Sample Protocol 1.
**/

#include "Dxe5.h"

EFI_STATUS
Dxe5EntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  COMPAL_LEARNING_SAMPLE_PROTOCOL_1 *MyProfile = NULL;
  
  Status = gBS->LocateProtocol(&gCompalLearningSampleProtocol1, NULL,(VOID**) &MyProfile);
  
  if (Status == EFI_SUCCESS) {
      DEBUG ((EFI_D_ERROR, "\n ======My Profile=======: \n"));
      DEBUG ((EFI_D_ERROR, "\n Name: %a \n", MyProfile->Name));
      DEBUG ((EFI_D_ERROR, "\n Height: %d cm\n", MyProfile->Height));
      DEBUG ((EFI_D_ERROR, "\n Weight: %d kg\n", MyProfile->Weight));
      DEBUG ((EFI_D_ERROR, "\n Age: %d years old\n", MyProfile->Age));  
  }
  
  DEBUG ((EFI_D_ERROR, "\n [DEBUG] (%a, %d, %r): \n",__func__,__LINE__, Status));
  
  return Status;
}