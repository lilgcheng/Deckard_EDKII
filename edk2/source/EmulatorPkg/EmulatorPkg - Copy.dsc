## @file
# UEFI/PI Emulation Platform with UEFI HII interface supported.
#
# The Emulation Platform can be used to debug individual modules, prior to creating
# a real platform. This also provides an example for how an DSC is created.
#
# Copyright (c) 2006 - 2021, Intel Corporation. All rights reserved.<BR>
# Portions copyright (c) 2010 - 2011, Apple Inc. All rights reserved.<BR>
# Copyright (c) Microsoft Corporation.
#
# SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

[Defines]
  PLATFORM_NAME                  = EmulatorPkg
  PLATFORM_GUID                  = 05FD064D-1073-E844-936C-A0E16317107D
  PLATFORM_VERSION               = 0.3
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/Emulator$(ARCH)

  SUPPORTED_ARCHITECTURES        = X64|IA32
  BUILD_TARGETS                  = DEBUG|RELEASE|NOOPT
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = EmulatorPkg/EmulatorPkg.fdf


  #
  # Network definition
  #
  DEFINE NETWORK_SNP_ENABLE       = FALSE
  DEFINE NETWORK_IP6_ENABLE       = FALSE
  DEFINE NETWORK_TLS_ENABLE       = FALSE
  DEFINE NETWORK_HTTP_BOOT_ENABLE = FALSE
  DEFINE NETWORK_HTTP_ENABLE      = FALSE
  DEFINE NETWORK_ISCSI_ENABLE     = FALSE
  DEFINE SECURE_BOOT_ENABLE       = FALSE

  #
  # Redfish definition
  #
  DEFINE REDFISH_ENABLE = FALSE

[SkuIds]
  0|DEFAULT

!include MdePkg/MdeLibs.dsc.inc

[LibraryClasses]
  #
  # Entry point
  #
  PeiCoreEntryPoint|MdePkg/Library/PeiCoreEntryPoint/PeiCoreEntryPoint.inf
  PeimEntryPoint|MdePkg/Library/PeimEntryPoint/PeimEntryPoint.inf
  DxeCoreEntryPoint|MdePkg/Library/DxeCoreEntryPoint/DxeCoreEntryPoint.inf
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  ShellCEntryLib|ShellPkg/Library/UefiShellCEntryLib/UefiShellCEntryLib.inf

  #
  # C Standard Libraries
  #
  LibC|StdLib/LibC/LibC.inf
  LibCType|StdLib/LibC/Ctype/Ctype.inf
  LibLocale|StdLib/LibC/Locale/Locale.inf
  LibMath|StdLib/LibC/Math/Math.inf
  LibSignal|StdLib/LibC/Signal/Signal.inf
  LibStdio|StdLib/LibC/Stdio/Stdio.inf
  LibStdLib|StdLib/LibC/StdLib/StdLib.inf
  LibString|StdLib/LibC/String/String.inf
  LibTime|StdLib/LibC/Time/Time.inf
  LibUefi|StdLib/LibC/Uefi/Uefi.inf
  LibWchar|StdLib/LibC/Wchar/Wchar.inf

# Common Utilities for Networking Libraries
  LibNetUtil|StdLib/LibC/NetUtil/NetUtil.inf

# Additional libraries for POSIX functionality.
  LibPosix|StdLib/PosixLib/PosixLib.inf   # Combines LibErr, LibGen, LibGlob, LibStringlist, GetPass into one library

  LibErr|StdLib/PosixLib/Err/LibErr.inf
  LibGen|StdLib/PosixLib/Gen/LibGen.inf
  LibGlob|StdLib/PosixLib/Glob/LibGlob.inf
  LibStringlist|StdLib/PosixLib/Stringlist/LibStringlist.inf
  LibIIO|StdLib/LibC/Uefi/InteractiveIO/IIO.inf

# Additional, non-standard, libraries
  LibContainer|StdLib/LibC/Containers/ContainerLib.inf

# Libraries for device abstractions within the Standard C Library
# Applications should not directly access any functions defined in these libraries.
  LibGdtoa|StdLib/LibC/gdtoa/gdtoa.inf
  DevConsole|StdLib/LibC/Uefi/Devices/daConsole.inf
  DevShell|StdLib/LibC/Uefi/Devices/daShell.inf       # DEPRECATED!  Please use DevMedia for new code.
  DevMedia|StdLib/LibC/Uefi/Devices/daShell.inf
  DevUtility|StdLib/LibC/Uefi/Devices/daUtility.inf

  LuaLib|AppPkg/Applications/Lua/LuaLib.inf           # Lua language library
  #
  # Basic
  #
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  SynchronizationLib|MdePkg/Library/BaseSynchronizationLib/BaseSynchronizationLib.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  CacheMaintenanceLib|MdePkg/Library/BaseCacheMaintenanceLib/BaseCacheMaintenanceLib.inf
  PeCoffLib|MdePkg/Library/BasePeCoffLib/BasePeCoffLib.inf
  PeCoffGetEntryPointLib|MdePkg/Library/BasePeCoffGetEntryPointLib/BasePeCoffGetEntryPointLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  FrameBufferBltLib|MdeModulePkg/Library/FrameBufferBltLib/FrameBufferBltLib.inf

  #
  # UEFI & PI
  #
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  UefiRuntimeLib|MdePkg/Library/UefiRuntimeLib/UefiRuntimeLib.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  UefiDecompressLib|MdePkg/Library/BaseUefiDecompressLib/BaseUefiDecompressLib.inf

  PeiServicesLib|MdePkg/Library/PeiServicesLib/PeiServicesLib.inf
  DxeServicesLib|MdePkg/Library/DxeServicesLib/DxeServicesLib.inf
  DxeServicesTableLib|MdePkg/Library/DxeServicesTableLib/DxeServicesTableLib.inf
  SmbiosLib|EmulatorPkg/Library/SmbiosLib/SmbiosLib.inf

  #
  # Generic Modules
  #
  UefiScsiLib|MdePkg/Library/UefiScsiLib/UefiScsiLib.inf
  OemHookStatusCodeLib|MdeModulePkg/Library/OemHookStatusCodeLibNull/OemHookStatusCodeLibNull.inf
  BootLogoLib|MdeModulePkg/Library/BootLogoLib/BootLogoLib.inf
  FileExplorerLib|MdeModulePkg/Library/FileExplorerLib/FileExplorerLib.inf
  UefiBootManagerLib|MdeModulePkg/Library/UefiBootManagerLib/UefiBootManagerLib.inf
  BmpSupportLib|MdeModulePkg/Library/BaseBmpSupportLib/BaseBmpSupportLib.inf
  SafeIntLib|MdePkg/Library/BaseSafeIntLib/BaseSafeIntLib.inf
  CustomizedDisplayLib|MdeModulePkg/Library/CustomizedDisplayLib/CustomizedDisplayLib.inf
  SecurityManagementLib|MdeModulePkg/Library/DxeSecurityManagementLib/DxeSecurityManagementLib.inf
  TimerLib|MdePkg/Library/BaseTimerLibNullTemplate/BaseTimerLibNullTemplate.inf
  SerialPortLib|MdePkg/Library/BaseSerialPortLibNull/BaseSerialPortLibNull.inf
  CapsuleLib|MdeModulePkg/Library/DxeCapsuleLibNull/DxeCapsuleLibNull.inf
  #
  # Platform
  #
  PlatformBootManagerLib|EmulatorPkg/Library/PlatformBmLib/PlatformBmLib.inf
  KeyMapLib|EmulatorPkg/Library/KeyMapLibNull/KeyMapLibNull.inf
  !if $(REDFISH_ENABLE) == TRUE
    RedfishPlatformHostInterfaceLib|EmulatorPkg/Library/RedfishPlatformHostInterfaceLib/RedfishPlatformHostInterfaceLib.inf
    RedfishPlatformCredentialLib|EmulatorPkg/Library/RedfishPlatformCredentialLib/RedfishPlatformCredentialLib.inf
  !endif
  #
  # Misc
  #
  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
  PerformanceLib|MdePkg/Library/BasePerformanceLibNull/BasePerformanceLibNull.inf
  DebugAgentLib|MdeModulePkg/Library/DebugAgentLibNull/DebugAgentLibNull.inf
  PeiServicesTablePointerLib|EmulatorPkg/Library/PeiServicesTablePointerLibMagicPage/PeiServicesTablePointerLibMagicPage.inf
  DebugLib|MdeModulePkg/Library/PeiDxeDebugLibReportStatusCode/PeiDxeDebugLibReportStatusCode.inf
  LockBoxLib|MdeModulePkg/Library/LockBoxNullLib/LockBoxNullLib.inf
  CpuExceptionHandlerLib|MdeModulePkg/Library/CpuExceptionHandlerLibNull/CpuExceptionHandlerLibNull.inf
  TpmMeasurementLib|MdeModulePkg/Library/TpmMeasurementLibNull/TpmMeasurementLibNull.inf
  VarCheckLib|MdeModulePkg/Library/VarCheckLib/VarCheckLib.inf
  VariablePolicyLib|MdeModulePkg/Library/VariablePolicyLib/VariablePolicyLibRuntimeDxe.inf
  VariablePolicyHelperLib|MdeModulePkg/Library/VariablePolicyHelperLib/VariablePolicyHelperLib.inf
  SortLib|MdeModulePkg/Library/BaseSortLib/BaseSortLib.inf
  ShellLib|ShellPkg/Library/UefiShellLib/UefiShellLib.inf
  FileHandleLib|MdePkg/Library/UefiFileHandleLib/UefiFileHandleLib.inf

!if $(SECURE_BOOT_ENABLE) == TRUE
  RngLib|MdePkg/Library/BaseRngLibTimerLib/BaseRngLibTimerLib.inf
  IntrinsicLib|CryptoPkg/Library/IntrinsicLib/IntrinsicLib.inf
  OpensslLib|CryptoPkg/Library/OpensslLib/OpensslLibCrypto.inf
  PlatformSecureLib|SecurityPkg/Library/PlatformSecureLibNull/PlatformSecureLibNull.inf
  AuthVariableLib|SecurityPkg/Library/AuthVariableLib/AuthVariableLib.inf
!else
  AuthVariableLib|MdeModulePkg/Library/AuthVariableLibNull/AuthVariableLibNull.inf
!endif

[LibraryClasses.common.SEC]
  PeiServicesLib|EmulatorPkg/Library/SecPeiServicesLib/SecPeiServicesLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  PeCoffGetEntryPointLib|EmulatorPkg/Library/PeiEmuPeCoffGetEntryPointLib/PeiEmuPeCoffGetEntryPointLib.inf
  PeCoffExtraActionLib|EmulatorPkg/Library/PeiEmuPeCoffExtraActionLib/PeiEmuPeCoffExtraActionLib.inf
  SerialPortLib|EmulatorPkg/Library/PeiEmuSerialPortLib/PeiEmuSerialPortLib.inf
  PpiListLib|EmulatorPkg/Library/SecPpiListLib/SecPpiListLib.inf
  DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
  TimerLib|EmulatorPkg/Library/PeiTimerLib/PeiTimerLib.inf

[LibraryClasses.common.USER_DEFINED, LibraryClasses.common.BASE]
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  PeCoffExtraActionLib|MdePkg/Library/BasePeCoffExtraActionLibNull/BasePeCoffExtraActionLibNull.inf
  MemoryAllocationLib|MdePkg/Library/PeiMemoryAllocationLib/PeiMemoryAllocationLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  PpiListLib|EmulatorPkg/Library/SecPpiListLib/SecPpiListLib.inf
  ThunkPpiList|EmulatorPkg/Library/ThunkPpiList/ThunkPpiList.inf
  ThunkProtocolList|EmulatorPkg/Library/ThunkProtocolList/ThunkProtocolList.inf
  PeCoffGetEntryPointLib|MdePkg/Library/BasePeCoffGetEntryPointLib/BasePeCoffGetEntryPointLib.inf
  PpiListLib|EmulatorPkg/Library/SecPpiListLib/SecPpiListLib.inf
  PeiServicesLib|EmulatorPkg/Library/SecPeiServicesLib/SecPeiServicesLib.inf


[LibraryClasses.common.PEIM, LibraryClasses.common.PEI_CORE]
  HobLib|MdePkg/Library/PeiHobLib/PeiHobLib.inf
  MemoryAllocationLib|MdePkg/Library/PeiMemoryAllocationLib/PeiMemoryAllocationLib.inf
  ReportStatusCodeLib|MdeModulePkg/Library/PeiReportStatusCodeLib/PeiReportStatusCodeLib.inf
  PeCoffGetEntryPointLib|EmulatorPkg/Library/PeiEmuPeCoffGetEntryPointLib/PeiEmuPeCoffGetEntryPointLib.inf
  PeCoffExtraActionLib|EmulatorPkg/Library/PeiEmuPeCoffExtraActionLib/PeiEmuPeCoffExtraActionLib.inf
  ExtractGuidedSectionLib|MdePkg/Library/PeiExtractGuidedSectionLib/PeiExtractGuidedSectionLib.inf
  SerialPortLib|EmulatorPkg/Library/PeiEmuSerialPortLib/PeiEmuSerialPortLib.inf
  ReportStatusCodeLib|MdeModulePkg/Library/PeiReportStatusCodeLib/PeiReportStatusCodeLib.inf
  TimerLib|EmulatorPkg/Library/PeiTimerLib/PeiTimerLib.inf

[LibraryClasses.common.PEI_CORE]
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf

[LibraryClasses.common.PEIM]
  PcdLib|MdePkg/Library/PeiPcdLib/PeiPcdLib.inf

[LibraryClasses.common.DXE_CORE]
  HobLib|MdePkg/Library/DxeCoreHobLib/DxeCoreHobLib.inf
  MemoryAllocationLib|MdeModulePkg/Library/DxeCoreMemoryAllocationLib/DxeCoreMemoryAllocationLib.inf
  ReportStatusCodeLib|MdeModulePkg/Library/DxeReportStatusCodeLib/DxeReportStatusCodeLib.inf
  PeCoffExtraActionLib|EmulatorPkg/Library/DxeEmuPeCoffExtraActionLib/DxeEmuPeCoffExtraActionLib.inf
  ExtractGuidedSectionLib|MdePkg/Library/DxeExtractGuidedSectionLib/DxeExtractGuidedSectionLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  TimerLib|EmulatorPkg/Library/DxeCoreTimerLib/DxeCoreTimerLib.inf
  EmuThunkLib|EmulatorPkg/Library/DxeEmuLib/DxeEmuLib.inf

[LibraryClasses.common.DXE_DRIVER, LibraryClasses.common.UEFI_DRIVER, LibraryClasses.common.UEFI_APPLICATION]
!if $(SECURE_BOOT_ENABLE) == TRUE
  BaseCryptLib|CryptoPkg/Library/BaseCryptLib/BaseCryptLib.inf
!endif

[LibraryClasses.common.DXE_RUNTIME_DRIVER]
!if $(SECURE_BOOT_ENABLE) == TRUE
  BaseCryptLib|CryptoPkg/Library/BaseCryptLib/RuntimeCryptLib.inf
!endif

[LibraryClasses.common.DXE_RUNTIME_DRIVER, LibraryClasses.common.UEFI_DRIVER, LibraryClasses.common.DXE_DRIVER, LibraryClasses.common.UEFI_APPLICATION]
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
  PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  ReportStatusCodeLib|MdeModulePkg/Library/DxeReportStatusCodeLib/DxeReportStatusCodeLib.inf
  EmuThunkLib|EmulatorPkg/Library/DxeEmuLib/DxeEmuLib.inf
  PeCoffExtraActionLib|EmulatorPkg/Library/DxeEmuPeCoffExtraActionLib/DxeEmuPeCoffExtraActionLib.inf
  ReportStatusCodeLib|MdeModulePkg/Library/DxeReportStatusCodeLib/DxeReportStatusCodeLib.inf
  TimerLib|EmulatorPkg/Library/DxeTimerLib/DxeTimerLib.inf
##
## Compal Library
##
  Lib1|CompalLearningPkg/Library/Lib1/Lib1.inf

[PcdsFeatureFlag]
  gEfiMdeModulePkgTokenSpaceGuid.PcdDxeIplSwitchToLongMode|FALSE
  gEfiMdeModulePkgTokenSpaceGuid.PcdPeiCoreImageLoaderSearchTeSectionFirst|FALSE
  gEfiMdeModulePkgTokenSpaceGuid.PcdDxeIplBuildPageTables|FALSE

[PcdsFixedAtBuild]
  gEfiMdeModulePkgTokenSpaceGuid.PcdImageProtectionPolicy|0x00000000
  gEfiMdeModulePkgTokenSpaceGuid.PcdResetOnMemoryTypeInformationChange|FALSE
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80000040
  gEfiMdePkgTokenSpaceGuid.PcdReportStatusCodePropertyMask|0x0f
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x1f
  gEfiMdeModulePkgTokenSpaceGuid.PcdMaxSizeNonPopulateCapsule|0x0
  gEfiMdeModulePkgTokenSpaceGuid.PcdMaxSizePopulateCapsule|0x0
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeUseSerial|TRUE

  gEmulatorPkgTokenSpaceGuid.PcdEmuFirmwareFdSize|0x002a0000
  gEmulatorPkgTokenSpaceGuid.PcdEmuFirmwareBlockSize|0x10000
  gEmulatorPkgTokenSpaceGuid.PcdEmuFirmwareVolume|L"../FV/FV_RECOVERY.fd"
!if $(SECURE_BOOT_ENABLE) == TRUE
  gEfiMdeModulePkgTokenSpaceGuid.PcdMaxAuthVariableSize|0x2800
  gEfiSecurityPkgTokenSpaceGuid.PcdUserPhysicalPresence|TRUE
!endif

  gEmulatorPkgTokenSpaceGuid.PcdEmuMemorySize|L"64!64"

  # Change PcdBootManagerMenuFile to UiApp
  gEfiMdeModulePkgTokenSpaceGuid.PcdBootManagerMenuFile|{ 0x21, 0xaa, 0x2c, 0x46, 0x14, 0x76, 0x03, 0x45, 0x83, 0x6e, 0x8a, 0xb6, 0xf4, 0x66, 0x23, 0x31 }


#define BOOT_WITH_FULL_CONFIGURATION                  0x00
#define BOOT_WITH_MINIMAL_CONFIGURATION               0x01
#define BOOT_ASSUMING_NO_CONFIGURATION_CHANGES        0x02
#define BOOT_WITH_FULL_CONFIGURATION_PLUS_DIAGNOSTICS 0x03
#define BOOT_WITH_DEFAULT_SETTINGS                    0x04
#define BOOT_ON_S4_RESUME                             0x05
#define BOOT_ON_S5_RESUME                             0x06
#define BOOT_ON_S2_RESUME                             0x10
#define BOOT_ON_S3_RESUME                             0x11
#define BOOT_ON_FLASH_UPDATE                          0x12
#define BOOT_IN_RECOVERY_MODE                         0x20
  gEmulatorPkgTokenSpaceGuid.PcdEmuBootMode|0

  gEmulatorPkgTokenSpaceGuid.PcdEmuApCount|L"1"

  # For a CD-ROM/DVD use L"diag.dmg:RO:2048"
  gEmulatorPkgTokenSpaceGuid.PcdEmuVirtualDisk|L"disk.dmg:FW"
  gEmulatorPkgTokenSpaceGuid.PcdEmuGop|L"GOP Window"
  gEmulatorPkgTokenSpaceGuid.PcdEmuFileSystem|L"."
  gEmulatorPkgTokenSpaceGuid.PcdEmuSerialPort|L"/dev/ttyS0"
  gEmulatorPkgTokenSpaceGuid.PcdEmuNetworkInterface|L"en0"

  gEmulatorPkgTokenSpaceGuid.PcdEmuCpuModel|L"Intel(R) Processor Model"
  gEmulatorPkgTokenSpaceGuid.PcdEmuCpuSpeed|L"3000"

  #  0-PCANSI, 1-VT100, 2-VT00+, 3-UTF8, 4-TTYTERM
  gEfiMdePkgTokenSpaceGuid.PcdDefaultTerminalType|1

!if $(REDFISH_ENABLE) == TRUE
  gEfiRedfishPkgTokenSpaceGuid.PcdRedfishRestExServiceDevicePath.DevicePathMatchMode|DEVICE_PATH_MATCH_MAC_NODE
  gEfiRedfishPkgTokenSpaceGuid.PcdRedfishRestExServiceDevicePath.DevicePathNum|1
  #
  # Below is the MAC address of network adapter on EDK2 Emulator platform.
  # You can use ifconfig under EFI shell to get the MAC address of network adapter on EDK2 Emulator platform.
  #
  gEfiRedfishPkgTokenSpaceGuid.PcdRedfishRestExServiceDevicePath.DevicePath|{DEVICE_PATH("MAC(000000000000,0x1)")}
  gEfiRedfishPkgTokenSpaceGuid.PcdRedfishRestExServiceAccessModeInBand|False
  gEfiRedfishPkgTokenSpaceGuid.PcdRedfishDiscoverAccessModeInBand|False
!endif

##
## Compal Fixed PCD
##
  gCompalLearningPkgSpaceGuid.PcdCompalSample1|0xF

[PcdsDynamicDefault.common.DEFAULT]
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareBase64|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingBase64|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableBase64|0

##
## Compal Dynamice PCD
##
  gCompalLearningPkgSpaceGuid.PcdCompalSample2|0x200

[PcdsDynamicHii.common.DEFAULT]
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|L"Setup"|gEmuSystemConfigGuid|0x0|80
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|L"Setup"|gEmuSystemConfigGuid|0x4|25
  gEfiMdePkgTokenSpaceGuid.PcdPlatformBootTimeOut|L"Timeout"|gEfiGlobalVariableGuid|0x0|10

[Components]
  
  # MdeModulePkg/Application/LibSample/MyLibApp/MyLibApp.inf  {
  #  <LibraryClasses>
  #     MyLibraryLib|MdeModulePkg/Application/LibSample/MyLibrary/MyLibrary.inf
  # }
    MdeModulePkg/Application/Uefi_Main/Uefi_Main.inf
    MdeModulePkg/Application/ShellApp_Main/ShellApp_Main.inf
   MdeModulePkg/Application/Stdlib_Main/Stdlib_Main.inf
  
!if "IA32" in $(ARCH) || "X64" in $(ARCH)
  !if "MSFT" in $(FAMILY) || $(WIN_HOST_BUILD) == TRUE
    ##
    #  Emulator, OS WIN application
    #  CLANGPDB is cross OS tool chain. It depends on WIN_HOST_BUILD flag
    #  to build WinHost application.
    ##
    EmulatorPkg/Win/Host/WinHost.inf
  !else
    ##
    #  Emulator, OS POSIX application
    ##
    EmulatorPkg/Unix/Host/Host.inf
  !endif
!endif

!ifndef $(SKIP_MAIN_BUILD)
  #
  # Generic SEC
  #
  EmulatorPkg/Sec/Sec.inf

  ##
  #  PEI Phase modules
  ##
  MdeModulePkg/Core/Pei/PeiMain.inf
  MdeModulePkg/Universal/PCD/Pei/Pcd.inf  {
   <LibraryClasses>
      PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  }
  MdeModulePkg/Universal/ReportStatusCodeRouter/Pei/ReportStatusCodeRouterPei.inf
  MdeModulePkg/Universal/StatusCodeHandler/Pei/StatusCodeHandlerPei.inf

  EmulatorPkg/BootModePei/BootModePei.inf
  MdeModulePkg/Universal/FaultTolerantWritePei/FaultTolerantWritePei.inf
  MdeModulePkg/Universal/Variable/Pei/VariablePei.inf
  EmulatorPkg/AutoScanPei/AutoScanPei.inf



  EmulatorPkg/FirmwareVolumePei/FirmwareVolumePei.inf
  EmulatorPkg/FlashMapPei/FlashMapPei.inf
  EmulatorPkg/ThunkPpiToProtocolPei/ThunkPpiToProtocolPei.inf
  MdeModulePkg/Core/DxeIplPeim/DxeIpl.inf

  ##
  #  DXE Phase modules
  ##
  MdeModulePkg/Core/Dxe/DxeMain.inf {
    <LibraryClasses>
      DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
      SerialPortLib|EmulatorPkg/Library/DxeEmuStdErrSerialPortLib/DxeEmuStdErrSerialPortLib.inf
      DxeEmuLib|EmulatorPkg/Library/DxeEmuLib/DxeEmuLib.inf
      NULL|MdeModulePkg/Library/DxeCrc32GuidedSectionExtractLib/DxeCrc32GuidedSectionExtractLib.inf
      NULL|MdeModulePkg/Library/LzmaCustomDecompressLib/LzmaCustomDecompressLib.inf
  }
  MdeModulePkg/Universal/PCD/Dxe/Pcd.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  }

  MdeModulePkg/Universal/ReportStatusCodeRouter/RuntimeDxe/ReportStatusCodeRouterRuntimeDxe.inf
  MdeModulePkg/Universal/StatusCodeHandler/RuntimeDxe/StatusCodeHandlerRuntimeDxe.inf {
   <LibraryClasses>
      DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
      SerialPortLib|EmulatorPkg/Library/DxeEmuStdErrSerialPortLib/DxeEmuStdErrSerialPortLib.inf
  }

  MdeModulePkg/Universal/Metronome/Metronome.inf
  EmulatorPkg/RealTimeClockRuntimeDxe/RealTimeClock.inf
  EmulatorPkg/ResetRuntimeDxe/Reset.inf
  MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
  EmulatorPkg/FvbServicesRuntimeDxe/FvbServicesRuntimeDxe.inf

  MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf {
    <LibraryClasses>
!if $(SECURE_BOOT_ENABLE) == TRUE
      NULL|SecurityPkg/Library/DxeImageVerificationLib/DxeImageVerificationLib.inf
!endif
  }

  MdeModulePkg/Universal/EbcDxe/EbcDxe.inf
  MdeModulePkg/Universal/MemoryTest/NullMemoryTestDxe/NullMemoryTestDxe.inf
  EmulatorPkg/EmuThunkDxe/EmuThunk.inf
  EmulatorPkg/CpuRuntimeDxe/Cpu.inf
  MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteDxe.inf
  EmulatorPkg/PlatformSmbiosDxe/PlatformSmbiosDxe.inf
  EmulatorPkg/TimerDxe/Timer.inf

!if $(SECURE_BOOT_ENABLE) == TRUE
  SecurityPkg/VariableAuthenticated/SecureBootConfigDxe/SecureBootConfigDxe.inf
!endif

  MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf {
    <LibraryClasses>
      NULL|MdeModulePkg/Library/VarCheckUefiLib/VarCheckUefiLib.inf
  }
  MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
  MdeModulePkg/Universal/MonotonicCounterRuntimeDxe/MonotonicCounterRuntimeDxe.inf
  MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
  MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
  MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
  MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
  MdeModulePkg/Universal/SerialDxe/SerialDxe.inf {
   <LibraryClasses>
      DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
      SerialPortLib|EmulatorPkg/Library/DxeEmuSerialPortLib/DxeEmuSerialPortLib.inf
  }

  MdeModulePkg/Universal/Console/TerminalDxe/TerminalDxe.inf
  MdeModulePkg/Universal/BdsDxe/BdsDxe.inf
!if "XCODE5" not in $(TOOL_CHAIN_TAG)
  MdeModulePkg/Logo/LogoDxe.inf
!endif
  MdeModulePkg/Universal/LoadFileOnFv2/LoadFileOnFv2.inf
  MdeModulePkg/Application/UiApp/UiApp.inf {
   <LibraryClasses>
      NULL|MdeModulePkg/Library/DeviceManagerUiLib/DeviceManagerUiLib.inf
      NULL|MdeModulePkg/Library/BootManagerUiLib/BootManagerUiLib.inf
      NULL|MdeModulePkg/Library/BootMaintenanceManagerUiLib/BootMaintenanceManagerUiLib.inf
  }
  MdeModulePkg/Application/BootManagerMenuApp/BootManagerMenuApp.inf

  MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
  #{
  #  <LibraryClasses>
  #    NULL|EmulatorPkg/Library/DevicePathTextLib/DevicePathTextLib.inf
  #}

  MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
  MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
  MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf
  MdeModulePkg/Bus/Pci/PciBusDxe/PciBusDxe.inf
  MdeModulePkg/Bus/Scsi/ScsiBusDxe/ScsiBusDxe.inf
  MdeModulePkg/Bus/Scsi/ScsiDiskDxe/ScsiDiskDxe.inf

  EmulatorPkg/EmuBusDriverDxe/EmuBusDriverDxe.inf
  EmulatorPkg/EmuGopDxe/EmuGopDxe.inf
  EmulatorPkg/EmuSimpleFileSystemDxe/EmuSimpleFileSystemDxe.inf
  EmulatorPkg/EmuBlockIoDxe/EmuBlockIoDxe.inf
  EmulatorPkg/EmuSnpDxe/EmuSnpDxe.inf

  MdeModulePkg/Application/HelloWorld/HelloWorld.inf

  MdeModulePkg/Universal/SmbiosDxe/SmbiosDxe.inf
  MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf
  MdeModulePkg/Universal/DisplayEngineDxe/DisplayEngineDxe.inf
  MdeModulePkg/Universal/SetupBrowserDxe/SetupBrowserDxe.inf
  MdeModulePkg/Universal/PrintDxe/PrintDxe.inf
  MdeModulePkg/Universal/DriverSampleDxe/DriverSampleDxe.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  }

  FatPkg/EnhancedFatDxe/Fat.inf

!if "XCODE5" not in $(TOOL_CHAIN_TAG)
  ShellPkg/DynamicCommand/TftpDynamicCommand/TftpDynamicCommand.inf {
    <PcdsFixedAtBuild>
      gEfiShellPkgTokenSpaceGuid.PcdShellLibAutoInitialize|FALSE
  }
!endif
  ShellPkg/Application/Shell/Shell.inf {
    <LibraryClasses>
      ShellCommandLib|ShellPkg/Library/UefiShellCommandLib/UefiShellCommandLib.inf
      NULL|ShellPkg/Library/UefiShellLevel2CommandsLib/UefiShellLevel2CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellLevel1CommandsLib/UefiShellLevel1CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellLevel3CommandsLib/UefiShellLevel3CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellDriver1CommandsLib/UefiShellDriver1CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellDebug1CommandsLib/UefiShellDebug1CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellInstall1CommandsLib/UefiShellInstall1CommandsLib.inf
      NULL|ShellPkg/Library/UefiShellNetwork1CommandsLib/UefiShellNetwork1CommandsLib.inf
      HandleParsingLib|ShellPkg/Library/UefiHandleParsingLib/UefiHandleParsingLib.inf
      OrderedCollectionLib|MdePkg/Library/BaseOrderedCollectionRedBlackTreeLib/BaseOrderedCollectionRedBlackTreeLib.inf
      SortLib|MdeModulePkg/Library/UefiSortLib/UefiSortLib.inf
      PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
#      SafeBlockIoLib|ShellPkg/Library/SafeBlockIoLib/SafeBlockIoLib.inf
#      SafeOpenProtocolLib|ShellPkg/Library/SafeOpenProtocolLib/SafeOpenProtocolLib.inf
      BcfgCommandLib|ShellPkg/Library/UefiShellBcfgCommandLib/UefiShellBcfgCommandLib.inf
      IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf

    <PcdsFixedAtBuild>
      gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0xFF
      gEfiShellPkgTokenSpaceGuid.PcdShellLibAutoInitialize|FALSE
      gEfiMdePkgTokenSpaceGuid.PcdUefiLibMaxPrintBufferSize|8000
  }

!endif

!include NetworkPkg/Network.dsc.inc

!if $(REDFISH_ENABLE) == TRUE
  EmulatorPkg/Application/RedfishPlatformConfig/RedfishPlatformConfig.inf
!endif
!include RedfishPkg/Redfish.dsc.inc

##
## Compal Modules
##
  #CompalLearningPkg/Peims/Peim1/Peim1.inf
  #CompalLearningPkg/Drivers/Dxe1/Dxe1.inf {
  #  <LibraryClasses>
  #    DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
  #    SerialPortLib|EmulatorPkg/Library/DxeEmuStdErrSerialPortLib/DxeEmuStdErrSerialPortLib.inf
  #}
  #CompalLearningPkg/Drivers/Dxe2/Dxe2.inf {
  #  <LibraryClasses>
  #    DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
  #    SerialPortLib|EmulatorPkg/Library/DxeEmuStdErrSerialPortLib/DxeEmuStdErrSerialPortLib.inf
  #}  
  #CompalLearningPkg/Applications/App1/App1.inf
  CompalLearningPkg/Drivers/Dxe3/Dxe3.inf {
    <LibraryClasses>
      DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
      SerialPortLib|EmulatorPkg/Library/DxeEmuStdErrSerialPortLib/DxeEmuStdErrSerialPortLib.inf
  }
  CompalLearningPkg/Drivers/Dxe4/Dxe4.inf {
    <LibraryClasses>
      DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
      SerialPortLib|EmulatorPkg/Library/DxeEmuStdErrSerialPortLib/DxeEmuStdErrSerialPortLib.inf
  }  
  CompalLearningPkg/Drivers/Dxe5/Dxe5.inf {
    <LibraryClasses>
      DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
      SerialPortLib|EmulatorPkg/Library/DxeEmuStdErrSerialPortLib/DxeEmuStdErrSerialPortLib.inf
  }    
  
  
[BuildOptions]
  #
  # Disable deprecated APIs.
  #
  *_*_*_CC_FLAGS = -D DISABLE_NEW_DEPRECATED_INTERFACES

  MSFT:DEBUG_*_*_CC_FLAGS = /Od /Oy-
  MSFT:NOOPT_*_*_CC_FLAGS = /Od /Oy-
  GCC:DEBUG_CLANGPDB_*_CC_FLAGS =-O0 -Wno-unused-command-line-argument -Wno-incompatible-pointer-types -Wno-enum-conversion -Wno-incompatible-pointer-types -Wno-sometimes-uninitialized -Wno-constant-conversion -Wno-main-return-type

  MSFT:*_*_*_DLINK_FLAGS     = /ALIGN:4096 /FILEALIGN:4096 /SUBSYSTEM:CONSOLE
  MSFT:DEBUG_*_*_DLINK_FLAGS = /EXPORT:InitializeDriver=$(IMAGE_ENTRY_POINT) /BASE:0x10000
  MSFT:NOOPT_*_*_DLINK_FLAGS = /EXPORT:InitializeDriver=$(IMAGE_ENTRY_POINT) /BASE:0x10000

!if $(WIN_HOST_BUILD) == TRUE
  #
  # CLANGPDB tool chain depends on WIN_HOST_BUILD flag to generate the windows application.
  #
  GCC:*_CLANGPDB_*_DLINK_FLAGS     = /ALIGN:4096 /FILEALIGN:4096 /SUBSYSTEM:CONSOLE
  GCC:DEBUG_CLANGPDB_*_DLINK_FLAGS = /EXPORT:InitializeDriver=$(IMAGE_ENTRY_POINT) /BASE:0x10000
  GCC:NOOPT_CLANGPDB_*_DLINK_FLAGS = /EXPORT:InitializeDriver=$(IMAGE_ENTRY_POINT) /BASE:0x10000
!endif
