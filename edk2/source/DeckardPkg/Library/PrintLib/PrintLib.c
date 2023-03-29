#include "PrintLib_Internal.h"

EFI_STATUS PrintLibUse(VOID)
{
  EFI_STATUS  Status = EFI_SUCCESS;
  Print(L"Hello,this is PrintLib function()!\n");

  return Status;
}
