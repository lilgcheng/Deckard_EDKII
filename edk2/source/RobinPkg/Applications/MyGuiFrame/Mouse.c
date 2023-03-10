//member functions of mouse
/**
 * 《UEFI编程实践》随书代码
 * 更多的UEFI探索，可以参考笔者的博客和专栏：
 * CSDN: https://blog.csdn.net/luobing4365
 * 知乎: https://www.zhihu.com/column/c_1233025362843209728
 * **/
#include "Window.h"
#include "Pictures.h"
#include "Graphic.h"
#include "Mouse.h"


extern EFI_SIMPLE_POINTER_PROTOCOL *gMouse;

//============================ 鼠标图案在此处 begin ============================
#define gMouseWidth   18 //pcx图像的宽度 
#define gMouseHeight  25 //pcx图像的高度 
EFI_GRAPHICS_OUTPUT_BLT_PIXEL gMousePicColorTable[]={
  0x34,  0x0e,  0x0c,  0x00,      //000
  0x04,  0xfe,  0x04,  0x00,      //001		//掩码图案
  0x4c,  0x4e,  0x4c,  0x00,      //002
  0xfc,  0x8a,  0x84,  0x00,      //003
  0xfc,  0xc6,  0xc4,  0x00,      //004
  0x34,  0x2e,  0x2c,  0x00,      //005
  0xfc,  0xaa,  0xac,  0x00,      //006
  0xe4,  0x52,  0x54,  0x00,      //007
  0xfc,  0x6e,  0x6c,  0x00,      //008
  0xe4,  0x46,  0x44,  0x00,      //009
  0x34,  0x1e,  0x1c,  0x00,      //010
  0xfc,  0xe6,  0xe4,  0x00,      //011
  0x4c,  0x3e,  0x3c,  0x00,      //012
  0xfc,  0x9a,  0x9c,  0x00,      //013
  0xe4,  0xba,  0xbc,  0x00,      //014
  0xe4,  0xd6,  0xd4,  0x00,      //015
  0x34,  0x36,  0x34,  0x00,      //016
  0xfc,  0x7e,  0x7c,  0x00,      //017
  0x4c,  0x1e,  0x1c,  0x00,      //018
  0xfc,  0x66,  0x64,  0x00,      //019
  0xfc,  0x92,  0x94,  0x00,      //020
  0xfc,  0xb2,  0xac,  0x00,      //021
  0xe4,  0xa6,  0xa4,  0x00,      //022
  0xe4,  0xc2,  0xc4,  0x00,      //023
  0x44,  0x36,  0x34,  0x00,      //024
  0x34,  0x16,  0x14,  0x00,      //025
  0xfc,  0x5a,  0x5c,  0x00,      //026
  0xfc,  0x76,  0x74,  0x00,      //027
  0x34,  0x26,  0x24,  0x00,      //028
  0xfc,  0xfa,  0xfc,  0x00,      //029
  0x4c,  0x46,  0x44,  0x00,      //030
  0xfc,  0xd2,  0xcc,  0x00,      //031
  0xfc,  0x8a,  0x8c,  0x00,      //032
  0xfc,  0xce,  0xcc,  0x00,      //033
  0xfc,  0xba,  0xbc,  0x00,      //034
  0xfc,  0x86,  0x84,  0x00,      //035
  0x5c,  0x2a,  0x2c,  0x00,      //036
  0xfc,  0xb2,  0xb4,  0x00,      //037
  0xfc,  0xa2,  0xa4,  0x00,      //038
  0x44,  0x3a,  0x3c,  0x00,      //039
  0xfc,  0xd2,  0xd4,  0x00,      //040
  0x34,  0x12,  0x14,  0x00,      //041
  0xfc,  0xca,  0xcc,  0x00,      //042
  0x34,  0x32,  0x34,  0x00,      //043
  0xfc,  0xae,  0xac,  0x00,      //044
  0xfc,  0x52,  0x54,  0x00,      //045
  0xfc,  0x72,  0x74,  0x00,      //046
  0x34,  0x22,  0x24,  0x00,      //047
  0xfc,  0xf2,  0xf4,  0x00,      //048
  0x4c,  0x42,  0x44,  0x00,      //049
  0xfc,  0x9e,  0x9c,  0x00,      //050
  0x3c,  0x36,  0x34,  0x00,      //051
  0xfc,  0x82,  0x84,  0x00,      //052
  0x4c,  0x22,  0x24,  0x00,      //053
  0xfc,  0x6a,  0x6c,  0x00,      //054
  0xfc,  0x96,  0x94,  0x00,      //055
  0xfc,  0xc2,  0xc4,  0x00,      //056
  0x34,  0x1a,  0x1c,  0x00,      //057
  0xfc,  0x5e,  0x5c,  0x00,      //058
  0xfc,  0x7a,  0x7c,  0x00,      //059
  0x34,  0x2a,  0x2c,  0x00,      //060
  0xfc,  0xfe,  0xfc,  0x00,      //061
  0x4c,  0x4a,  0x4c,  0x00,      //062
  0xfc,  0x8e,  0x8c,  0x00,      //063
  0xfc,  0xbe,  0xbc,  0x00,      //064
  0xfc,  0xb6,  0xb4,  0x00,      //065
  0xfc,  0xa6,  0xa4,  0x00,      //066
  0x4c,  0x3a,  0x3c,  0x00,      //067
  0xfc,  0xd6,  0xd4,  0x00,      //068
  0x00,  0x00,  0x00,  0x00,      //069
};

UINT8 gMousePicPicture[]={
 0x3e, 0xd1, 0x01, 0x2b, 0x43, 0xd0, 0x01, 0x2b, 0x0f, 0x0c, 0xcf, 0x01, 0x10, 0x3d, 0x16, 0x31, 0xce, 0x01, 0x10, 0x3d, 0x38, 0x0e, 0x1e, 0xcd, 0x01, 0x3c, 0xc2, 0x3d, 0x22, 0x17, 0x3e, 0xcc,
 0x01, 0x2f, 0xc2, 0x3d, 0x06, 0x04, 0x0e, 0x05, 0xcb, 0x01, 0x2f, 0xc2, 0x3d, 0x40, 0x2c, 0x38, 0x44, 0x05, 0xca, 0x01, 0x0a, 0x30, 0x3d, 0x28, 0x26, 0x2c, 0x40, 0x28, 0x05, 0xc9, 0x01, 0x0a,
 0x0b, 0x3d, 0x21, 0x0d, 0x26, 0x06, 0x40, 0x21, 0x27, 0xc8, 0x01, 0x0a, 0x28, 0x3d, 0x38, 0x37, 0x0d, 0x32, 0x06, 0x22, 0x21, 0x33, 0xc7, 0x01, 0x39, 0x2a, 0x3d, 0x22, 0x3f, 0x14, 0x0d, 0x32,
 0x06, 0x22, 0x2a, 0x0c, 0xc6, 0x01, 0x39, 0x22, 0x3d, 0x2c, 0x20, 0x3f, 0x14, 0x37, 0x0d, 0x42, 0x41, 0x2a, 0x43, 0xc5, 0x01, 0x39, 0x25, 0x1d, 0x42, 0x34, 0x03, 0x20, 0x3f, 0xc2, 0x37, 0x42,
 0x25, 0x2a, 0x18, 0xc4, 0x01, 0x19, 0x42, 0x0b, 0x0d, 0x11, 0x34, 0x23, 0x3f, 0x14, 0x37, 0x0d, 0x26, 0x25, 0x04, 0x05, 0xc3, 0x01, 0x19, 0x0d, 0x1f, 0x20, 0x3b, 0x34, 0x23, 0x3f, 0x37, 0x0d,
 0x26, 0x42, 0x06, 0x41, 0x2a, 0x3c, 0xc2, 0x01, 0x19, 0x3f, 0x25, 0x08, 0x1b, 0x34, 0x3f, 0x0d, 0x26, 0x06, 0x2c, 0x41, 0x22, 0x40, 0x04, 0x28, 0x3c, 0x01, 0x29, 0x34, 0x3f, 0x36, 0x3b, 0x20,
 0x32, 0x3c, 0x1c, 0xc6, 0x3c, 0x05, 0xc2, 0x3c, 0x29, 0x08, 0x13, 0x36, 0x11, 0x0d, 0x1c, 0xcb, 0x01, 0x00, 0x1a, 0x3a, 0x36, 0x20, 0x2f, 0xcc, 0x01, 0x29, 0x2d, 0x1a, 0x08, 0x39, 0xcd, 0x01,
 0x00, 0x2d, 0x07, 0x39, 0xce, 0x01, 0x00, 0x09, 0x35, 0xcf, 0x01, 0x00, 0x12, 0xd0, 0x01, 0x24, 0xd1, 0x01,
};

//====================  end ==============================

//Name: putMouseArrow
//Input: x,y,gMouse
//Output: None
//Description: 显示鼠标图案
UINT16 mouse_xres=0;		//鼠标全局位置，只有鼠标显示函数可以使用
UINT16 mouse_yres=0;
UINT16 mouse_xScale,mouse_yScale; //鼠标的位移比率，一般分辨率为65536，此时xScale=yScale=17

EFI_GRAPHICS_OUTPUT_BLT_PIXEL oldZone[gMouseWidth*gMouseHeight];
VOID putMouseArrow(UINTN x,UINTN y)
{
  // EFI_STATUS Status;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer;
	EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer1;
	UINT32                        BltBufferSize;
	
	if(x>=(SY_SCREEN_WIDTH-1-gMouseWidth))
		x=SY_SCREEN_WIDTH-1-gMouseWidth;
	if(y>=SY_SCREEN_HEIGHT-1-gMouseHeight)
		y=SY_SCREEN_HEIGHT-1-gMouseHeight;
	//0 还原鼠标覆盖的区域
	putRectImage(mouse_xres,mouse_yres,gMouseWidth,gMouseHeight,oldZone);
	mouse_xres=(UINT16)x;
	mouse_yres=(UINT16)y;
	//1 保存当前鼠标要覆盖的区域
	getRectImage(x,y,gMouseWidth,gMouseHeight,oldZone);
	//2 在当前位置显示鼠标
	//2-1 申请内存 再保存一份当前覆盖区域的内容
	BltBufferSize = ((UINT32)gMouseWidth *  (UINT32)gMouseHeight * (sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)));
  BltBuffer = AllocateZeroPool(BltBufferSize);
	// Status = gBS->AllocatePool (
  //                 EfiRuntimeServicesData,
  //                 BltBufferSize,
  //                 (VOID **) &BltBuffer
  //                 );//最大可以容纳2^30的256色pcx数据，即32678x32678的图，不会溢出
  BltBuffer1 = AllocateZeroPool(BltBufferSize);
  // Status = gBS->AllocatePool (
  //                 EfiRuntimeServicesData,
  //                 BltBufferSize,
  //                 (VOID **) &BltBuffer1
  //                 );//最大可以容纳2^30的256色pcx数据，即32678x32678的图，不会溢出
  //2-2  读取覆盖区域
	getRectImage(x,y,gMouseWidth,gMouseHeight,BltBuffer);  //BltBuffer包含要覆盖的图像 
	//2-3 解压
	decompressPCX256_special(gMouseWidth,gMouseHeight,gMousePicColorTable,gMousePicPicture,BltBuffer1,1);
	//2-4 透明处理
	MaskingTransparent(gMouseWidth,gMouseHeight,BltBuffer1,BltBuffer,10);
	//2-5 显示
	putRectImage(x,y,gMouseWidth,gMouseHeight,BltBuffer);
	
	FreePool(BltBuffer); 
  FreePool(BltBuffer1);
  // gBS->FreePool(BltBuffer);    
  // gBS->FreePool(BltBuffer1);              
}
//Name: initMouseArrow
//Input: x,y,gMouse
//Output: None
//Description: 初始化鼠标图案
//此函数只应该调用一次，以保证鼠标显示正常
VOID initMouseArrow(VOID)
{
  UINTN temp;
	mouse_xres=0;
	mouse_yres=0;
  mouse_xScale = 0;
  mouse_yScale = 0;
  
  temp = (UINTN)gMouse->Mode->ResolutionX;
  temp >>=1;
  while(temp!=0)
  {
    ++mouse_xScale;
    temp >>=1; 
  }
  temp = (UINTN)gMouse->Mode->ResolutionY;
  temp >>=1;
  while(temp!=0)
  {
    ++mouse_yScale;
    temp >>=1; 
  }
  // Print(L"xScale=0x%x,  yScale=0x%x\n",mouse_xScale,mouse_yScale);
	getRectImage(0,0,gMouseWidth,gMouseHeight,oldZone);	//存储鼠标覆盖区域
	putPCX256(0,0,gMouseWidth,gMouseHeight,gMousePicColorTable,gMousePicPicture,1);	//maskcolor=1
  // putMouseArrow(mouse_xres, mouse_yres);
}

//Function Name: GetMouseState
//Input: 
//Output: 
//Description: Get Mouse state when any mouse event was occur
//注意，此函数是等待事件发生时去获取鼠标消息
// typedef struct{
//	INT32 RelativeMovementX;
//	INT32 RelativeMovementY;
//	INT32 RelativeMovementZ;
//	BOOLEAN LeftButton;
//	BOOLEAN RightButton;
//}EFI_SIMPLE_POINTER_STATE
EFI_STATUS GetMouseState(EFI_SIMPLE_POINTER_STATE *State)
{
//	UINTN Index;
	
//	gBS->WaitForEvent( 1, &gMouse->WaitForInput, &Index );
  return gMouse->GetState(gMouse,State);  
}
//Function Name: CheckMouseEvent
//Input: 
//Output: EFI_SUCCESS: 发生
//				EFI_NOT_READY: 没有发生
//Description: 检测是否有鼠标事件发生
EFI_STATUS CheckMouseEvent(VOID)
{
	
	return gBS->CheckEvent( gMouse->WaitForInput);
}
//  ====== debug function ==============

//Name: DisplaySerialMode
//Input: gMouse
//Output: None
//Description:
EFI_STATUS DisplayMouseMode(void)
{
	Print(L"Print Current Mode of Mouse:\n");
	Print(L"::ResolutionX=0x%x\n",gMouse->Mode->ResolutionX);
	Print(L"::ResolutionY=%d\n",gMouse->Mode->ResolutionY);
	Print(L"::ResolutionZ=%d\n",gMouse->Mode->ResolutionZ);
	Print(L"::LeftButton=%d\n",gMouse->Mode->LeftButton);
	Print(L"::RightButton=%d\n",gMouse->Mode->RightButton);
	
	return EFI_SUCCESS;
}



