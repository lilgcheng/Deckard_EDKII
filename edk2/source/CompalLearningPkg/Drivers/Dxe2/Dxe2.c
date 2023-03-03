/** @file
    Name: Dxe2.c
    Description: Use Lib1 during POST
**/

#include "Dxe2.h"

EFI_STATUS
Dxe2EntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  
  Lib1ForUse();
  
  return Status;
}