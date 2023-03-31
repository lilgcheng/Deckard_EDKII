#include "Uefi_DXE_Main_Insatll_Protocol.h"

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

DECKARD_DATA_PROTOCOL ptr;
DECKARD_DATA_PROTOCOL *data2=&ptr;

DECKARD_BMI_PROTOCOL ptr2;
DECKARD_BMI_PROTOCOL *data3=&ptr2;

VOID StrCpy(IN CHAR8 *Dest, IN CHAR8 *Src);
VOID StrCpy(IN CHAR8 *Dest, IN CHAR8 *Src){
  while ((*Src))
  {
    *(Dest++)=*(Src++);
  }
  *Dest = 0;
}
EFI_STATUS
EFIAPI
Uefi_DXE_Main_Insatll_Protocol (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{

  
  DEBUG ((EFI_D_INFO, "\n [DEBUG] (%a, %d): \n",__func__,__LINE__));
  DEBUG ((EFI_D_INFO, "Hello,this is Uefi_DXE_Main_Protocol!\n"));

  EFI_STATUS Status ;

  // 1.
  // DECKARD_DATA_PROTOCOL data1 = {
  //   "Deckard",
  //   172,
  //   67
  // };

  // 2.
  // CHAR8 str[]="Dekcard";  
  // data2->name = (CHAR8*)AllocatePool(sizeof(char)*8);
  // StrCpy(data2->name,str);  

  data2->name = "Deckard";
  data2->high=167;
  data2->weight=66;

  Status = gBS->InstallProtocolInterface(
    &ImageHandle,
    &gEfiDXESampleProtocolGuid,
    EFI_NATIVE_INTERFACE,
    &ptr);
  if(EFI_ERROR(Status)){
   DEBUG ((EFI_D_INFO, "[Deckard] InstallProtocolInterface FAIL !\n"));
  }else{
   DEBUG ((EFI_D_INFO, "[Deckard] InstallProtocolInterface SUCCESS!\n"));
  }

 
  data3->high=167;
  data3->weight=66;

  Status = gBS->InstallProtocolInterface(
    &ImageHandle,
    &gEfiDXESampleBMIProtocolGuid,
    EFI_NATIVE_INTERFACE,
    &ptr2);
  if(EFI_ERROR(Status)){
   DEBUG ((EFI_D_INFO, "[Deckard] BMI InstallProtocolInterface FAIL !\n"));
  }else{
   DEBUG ((EFI_D_INFO, "[Deckard] BMI InstallProtocolInterface SUCCESS!\n"));
  }
  return Status;
}
