/** @file
    Name: Dxe1.c
    Description: Print the string "Hello World!!!" during POST
**/

#include "Dxe1.h"

EFI_STATUS
Dxe1EntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  
  DEBUG ((EFI_D_ERROR, "\n [DEBUG] (%a, %d): \n",__func__,__LINE__));
  
  DEBUG ((EFI_D_ERROR, "\n DXE1: Hello World !!! \n"));
  
  return Status;
}