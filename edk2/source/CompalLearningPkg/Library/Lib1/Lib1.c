/** @file
    Name: Lib1.c
    Description: Create a Library that be cosumed by other drive or application.
**/

#include "Lib1.h"

EFI_STATUS
Lib1ForUse (
  VOID
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  
  DEBUG ((EFI_D_ERROR, "\n [DEBUG] (%a, %d): \n",__func__,__LINE__));
  
  DEBUG ((EFI_D_ERROR, "\n LIB1: It's a library !!!\n"));
  
  return Status;
}