#include "Uefi_DXE_Main_Located_Protocol.h"


EFI_STATUS
EFIAPI
Uefi_DXE_Main_Located_Protocol (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{

  
  DEBUG ((EFI_D_INFO, "\n [DEBUG] (%a, %d): \n",__func__,__LINE__));
  DEBUG ((EFI_D_INFO, "\n Uefi_DXE_Main_Located_Protocol:  \n"));
  DEBUG ((EFI_D_INFO, "Hello,this is Uefi_DXE_Main_Located_Protocol!\n"));

  EFI_STATUS Status ;  
  DECKARD_DATA_PROTOCOL *gDeckardDataProtocol = NULL;
  
  Status = gBS->LocateProtocol(&gEfiDXESampleProtocolGuid,NULL,(VOID **)&gDeckardDataProtocol);
  if(EFI_ERROR(Status)){
   DEBUG ((EFI_D_INFO, "[Deckard] Uefi_DXE_Main_Located_Protocol FAIL !\n"));
  }else{
   DEBUG ((EFI_D_INFO, "[Deckard] Uefi_DXE_Main_Located_Protocol SUCCESS!\n"));
  }
  DEBUG ((EFI_D_INFO, "[Deckard] name:%a \n",gDeckardDataProtocol->name));
  DEBUG ((EFI_D_INFO, "[Deckard] high:%d \n",gDeckardDataProtocol->high));
  DEBUG ((EFI_D_INFO, "[Deckard] weight:%d \n",gDeckardDataProtocol->weight));

  DECKARD_BMI_PROTOCOL *gDeckardBMIProtocol = NULL;
  
  Status = gBS->LocateProtocol(&gEfiDXESampleProtocolGuid,NULL,(VOID **)&gDeckardBMIProtocol);
  if(EFI_ERROR(Status)){
   DEBUG ((EFI_D_INFO, "[Deckard] Uefi_DXE_Main_Located_Protocol FAIL !\n"));
  }else{
   DEBUG ((EFI_D_INFO, "[Deckard] Uefi_DXE_Main_Located_Protocol SUCCESS!\n"));
  }
 
  DEBUG ((EFI_D_INFO, "[Deckard] BMI high:%d \n",gDeckardBMIProtocol->high));
  DEBUG ((EFI_D_INFO, "[Deckard] BMI weight:%d \n",gDeckardBMIProtocol->weight));



  return Status;
}
