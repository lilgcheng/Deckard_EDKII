/** @file
  This is Sample of UEFI aplication. 
**/
/**
 * 《UEFI编程实践》随书代码
 * 更多的UEFI探索，可以参考笔者的博客和专栏：
 * CSDN: https://blog.csdn.net/luobing4365
 * 知乎: https://www.zhihu.com/column/c_1233025362843209728
 * **/
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/SerialIo.h>
#include <Library/BaseMemoryLib.h>//<-memory relevation

#include <Library/UefiBootServicesTableLib.h>
/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
Uefi_Main_LocateHandleBuffer (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{

  // EFI_BOOT_SERVICES *gBS =NULL;
  EFI_STATUS Status;
  EFI_HANDLE *SerialHandleBuffer = NULL;
  UINTN HandleIndex = 0;
  UINTN HandleCount = 0;
  EFI_SERIAL_IO_PROTOCOL *gSerialIOArray[256];

  // get support gEfiSerialIoProtocolGuid handle
  Status = gBS->LocateHandleBuffer(
    ByProtocol,
    &gEfiSerialIoProtocolGuid,
    NULL,
    &HandleCount,
    &SerialHandleBuffer
  );
  if(EFI_ERROR(Status)) 
    return Status;
   Print(L"HandleCount: %d\n",HandleCount);
  for (HandleIndex  = 0; HandleIndex < HandleCount; HandleIndex++)
  {
    //thorugh handle find protocol
    Status = gBS->HandleProtocol(
      SerialHandleBuffer[HandleIndex],
      &gEfiSerialIoProtocolGuid,
      (VOID**)&(gSerialIOArray[HandleIndex])
    );
    Print(L"Status: %r\n",Status);
    Print(L"HandleIndex: %d\n",HandleIndex);
    Print(L"gSerialIOArray: %p\n",&(gSerialIOArray[HandleIndex]));
    if(EFI_ERROR(Status)) continue;
  }
  if(SerialHandleBuffer!=NULL){
    Status = gBS->FreePool(SerialHandleBuffer);
  }
  // Print(L"Status: %r\n",Status);

  

  return EFI_SUCCESS;
}
