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
Uefi_Main_HandleProtocol (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{

  //1. implment HandleProtocol
  EFI_BOOT_SERVICES *gBS =NULL;
  gBS =  SystemTable->BootServices;
  // extern EFI_GUID gEfiLoadedImageProtocolGuid;
  EFI_LOADED_IMAGE_PROTOCOL         *LoadedImage;
  EFI_STATUS Status;

  Status = gBS->HandleProtocol(
    ImageHandle,
    &gEfiLoadedImageProtocolGuid,
    &LoadedImage
  );

  Print(L"Status: %r\n",Status);

  

  return EFI_SUCCESS;
}
