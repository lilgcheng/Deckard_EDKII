#ifndef __HOB_DEMO_H__
#define __HOB_DEMO_H__

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

#endif 