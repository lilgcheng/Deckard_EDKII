/** @file
  This is Sample of UEFI aplication. 
**/
/**
 * 《UEFI编程实践》随书代码
 * 更多的UEFI探索，可以参考笔者的博客和专栏：
 * CSDN: https://blog.csdn.net/luobing4365
 * 知乎: https://www.zhihu.com/column/c_1233025362843209728
 * **/
#include  <Uefi.h>
#include  <Library/UefiLib.h>

#include <Library/UefiBootServicesTableLib.h>  //gST,gBs
#include <Library/UefiRuntimeServicesTableLib.h> //gRT

#include <Guid/Acpi.h>
#include <Library/BaseMemoryLib.h>

#include <Pi/PiFirmwareFile.h>
#include  <Library/BaseLib.h>  //字符串转换
#include <IndustryStandard/Acpi10.h>
#include <IndustryStandard/Acpi30.h>
#include <IndustryStandard/Acpi20.h>
#include <IndustryStandard/Acpi50.h>
// #include <Library/AcpiLib.h>
#include <Protocol/AcpiTable.h>


EFI_ACPI_TABLE_PROTOCOL *mAcpiTableProtocol = NULL;

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

VOID ST_Guid_List(VOID){
  UINTN i;
  EFI_CONFIGURATION_TABLE *ConfigTable = NULL;

  Print(L"NUmber of configuration Tables: %d\n",gST->NumberOfTableEntries);
  ConfigTable = gST->ConfigurationTable;
  for ( i = 0; i < gST->NumberOfTableEntries; i++)
  {
    Print(L"No %d . %g\n",i+1,&ConfigTable->VendorGuid);
    ConfigTable++;
  }
  
}

VOID ListAcpiTable(VOID){
  EFI_ACPI_3_0_ROOT_SYSTEM_DESCRIPTION_POINTER *Rsdp;
  EFI_ACPI_3_0_FIXED_ACPI_DESCRIPTION_TABLE *Fadt;
  EFI_ACPI_DESCRIPTION_HEADER *Entry,*XSDT;
  EFI_STATUS Status;
  // UINT32 *Entry32;
  UINT64 *Entry64;
  UINTN Entry64Num;
  UINTN i;
  UINT32 *Signature;


  Status = gBS->LocateProtocol(&gEfiAcpiTableProtocolGuid,NULL,(VOID **)&mAcpiTableProtocol);
  if(EFI_ERROR(Status)){
   Print(L"LocateProtocol -> gEfiAcpiTableProtocolGuid Fail\n");
  }

  //
  // Find ACPI table RSD_PTR from the system table.
  //
  Status = EfiGetSystemConfigurationTable(&gEfiAcpiTableGuid,(VOID **)&Rsdp);
  if(EFI_ERROR(Status)){
   Status = EfiGetSystemConfigurationTable(&gEfiAcpi10TableGuid,(VOID **)&Rsdp);
  }
  if(EFI_ERROR(Status)||(Rsdp==NULL)){
    Print(L"Can't find RSD_PTR form System table\n");
    // return NULL;
  }else if(Rsdp->Revision >= EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER_REVISION && Rsdp->XsdtAddress!=0) {
    Entry=(EFI_ACPI_DESCRIPTION_HEADER*)(UINTN)Rsdp->XsdtAddress;
    Print(L"Rsdp->XsdtAddres[XSDT]: 0x%p\n",Entry);
    XSDT = (EFI_ACPI_DESCRIPTION_HEADER*)(UINTN)Rsdp->XsdtAddress;
  }else if(Rsdp->RsdtAddress!=0){
    Entry = (EFI_ACPI_DESCRIPTION_HEADER*)(UINTN)Rsdp->RsdtAddress;
    Print(L"Rsdp->RsdtAddress: 0x%p\n",Entry);
  }

  if(XSDT != NULL){
    Entry64 = (UINT64*)(XSDT+1);
    Entry64Num = (XSDT->Length - sizeof(EFI_ACPI_DESCRIPTION_HEADER))>>3;
    for ( i = 0; i < Entry64Num; i++)
    {
      Signature = (UINT32*)(UINTN)Entry64[i];
      if(*Signature == EFI_ACPI_3_0_FIXED_ACPI_DESCRIPTION_TABLE_SIGNATURE){
        Fadt = (EFI_ACPI_3_0_FIXED_ACPI_DESCRIPTION_TABLE *)Signature;
        Print(L"[Fadt]: 0x%p\n",Fadt);
      }
    }
    
  }

  
}

EFI_STATUS
EFIAPI
Uefi_Main_ACPI_Dump (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  ST_Guid_List();
  ListAcpiTable();
  return EFI_SUCCESS;
}
