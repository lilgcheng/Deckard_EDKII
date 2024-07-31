/*++ @file

Copyright (c) 2006 - 2018, Intel Corporation. All rights reserved.<BR>
Portions copyright (c) 2011, Apple Inc. All rights reserved.

**/
#include <Uefi.h>
#include <Uefi/UefiBaseType.h>
#include <Pi/PiPeiCis.h>
#include <Ppi/MemoryDiscovered.h>

#include <Library/DebugLib.h>
#include <Library/PeimEntryPoint.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/MemoryAllocationLib.h>


/**
  This funtion is  printf  str in debug

  @return status
**/
EFI_STATUS
EFIAPI
PrintMesg (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "Mesg for in pei hob!\n"));

  return EFI_SUCCESS;
}

/**
  This funtion is  printf  str in debug

  @return status
**/
typedef 
EFI_STATUS 
(EFIAPI *PEI_HOB_MESSG) (
  VOID
  );

typedef struct {
  INT32  number;
  PEI_HOB_MESSG  PrintMesg
  ;
}TEST_STR;

extern EFI_GUID gMyFirstHobGuid;

EFI_STATUS
EFIAPI
MyFirstHobEntry(
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
)

{
  EFI_STATUS                     Status;
 // EFI_HOB_MEMORY_ALLOCATION      *Hob; 
  IN UINTN                       DataLength;
  TEST_STR                       *Data;
  TEST_STR                       *HobData;
  UINTN                           Temp;
  
  for(Temp = 0; Temp <= 5; Temp++) {
    DEBUG ((DEBUG_INFO, "\n"));
  }
  DEBUG ((DEBUG_INFO, "Peim creat hob is start!..\n"));


  DataLength = sizeof(TEST_STR);
  Status = (*PeiServices)->AllocatePool (PeiServices, DataLength, (VOID **)&Data);
  ASSERT (!EFI_ERROR (Status));

  Data->number=123;
  Data->PrintMesg=PrintMesg;

  HobData = BuildGuidHob (&gMyFirstHobGuid, DataLength);
  ASSERT (HobData != NULL);
  
  CopyMem (HobData, Data, DataLength);

  DEBUG ((DEBUG_INFO, "Peim creat hob is end!..\n"));
  return Status;
}
