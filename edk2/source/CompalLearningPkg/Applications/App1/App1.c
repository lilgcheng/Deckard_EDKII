/** @file
    Name: App1.c
    Description: Print the string "Hello World!!!" when we execute 
                 the application.
**/

#include "App1.h"

EFI_STATUS
EFIAPI
App1Main (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  Print (L"Hello World !!!\n");
  
  return EFI_SUCCESS;
}