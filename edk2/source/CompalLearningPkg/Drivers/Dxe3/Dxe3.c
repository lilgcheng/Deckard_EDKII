/** @file
    Name: Dxe3.c
    Description: Practice how to use a PCD (platform configuration database) 
**/

#include "Dxe3.h"

EFI_STATUS
Dxe3EntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  RETURN_STATUS PcdStatus = 0;
  UINT8 FixedPcdValue = 0;
  UINT16 DynamicPcdValue = 0;
  
  DEBUG ((EFI_D_ERROR, "\n [DEBUG] (%a, %d): \n",__func__,__LINE__));
  
  FixedPcdValue = FixedPcdGet8(PcdCompalSample1);
  
  DEBUG ((EFI_D_ERROR, "\n FixedPcdValue = 0x%x \n", FixedPcdValue));
  
  DynamicPcdValue = PcdGet16(PcdCompalSample2);
  
  DEBUG ((EFI_D_ERROR, "\n Original DynamicPcdValue = 0x%x \n", DynamicPcdValue));
  
  DEBUG ((EFI_D_ERROR, "\n Change the DynamicPcdValue \n"));
  
  PcdStatus = PcdSet16S (PcdCompalSample2, 0xFFFF);
  
  ASSERT_RETURN_ERROR (PcdStatus);
  
  DynamicPcdValue = PcdGet16(PcdCompalSample2);
  
  DynamicPcdValue = PcdGet16(PcdCompalSample2);
  
  DEBUG ((EFI_D_ERROR, "\n After DynamicPcdValue = 0x%x \n", DynamicPcdValue));
  
  return Status;
}