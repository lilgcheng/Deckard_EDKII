/** @file
    Name: Dxe4.c
    Description: Install Compal Learning Sample Protocol 1.
**/

#include "Dxe4.h"

COMPAL_LEARNING_SAMPLE_PROTOCOL_1 CompalLearningSampleProtocol1 = {
    "Justin Mao",
    41,
    183,
    102
};

EFI_STATUS
Dxe4EntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  
  Status = gBS->InstallProtocolInterface(
                &ImageHandle,
                &gCompalLearningSampleProtocol1,
                EFI_NATIVE_INTERFACE,
                &CompalLearningSampleProtocol1);
                
  DEBUG ((EFI_D_ERROR, "\n [DEBUG] (%a, %d, %r): \n",__func__,__LINE__, Status));
   
  return Status;
}