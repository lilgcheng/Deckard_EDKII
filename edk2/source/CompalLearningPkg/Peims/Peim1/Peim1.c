/** @file
    Name: Peim1.c
    Description: Print the string "Hello World!!!" during POST
**/

#include "Peim1.h"
#include "../EmulatorPkg/Include/test.h"

EFI_STATUS
Peim1EntryPoint (
  IN       EFI_PEI_FILE_HANDLE        FileHandle,
  IN CONST EFI_PEI_SERVICES           **PeiServices
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  
  DEBUG ((EFI_D_ERROR, "\n [DEBUG] (%a, %d): \n",__func__,__LINE__));
  
  DEBUG ((EFI_D_ERROR, "\n PEIM1: Hello World !!! \n"));
  DEBUG ((EFI_D_ERROR, "\n [a]= (=%d): \n",a));
  return Status;
}