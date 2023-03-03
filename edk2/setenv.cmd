@rem Auther: Justin_Mao 
@rem Contact information: Justin_Mao@compal.com
@rem CMD file for setting the build environment
@rem ==========================================
@rem ==========================================
@rem Environment Parameters
@rem The folder location depends on your system.
@rem ==========================================
set CURRENT_PATH=%~dp0
set SOURCE_DIR=%CURRENT_PATH%source
set WORKSPACE=%SOURCE_DIR%
set TOOLCHAIN_DIR=%CURRENT_PATH%toolchain\
set PYTHON_HOME=%TOOLCHAIN_DIR%\python27\
set NASM_DIR=%TOOLCHAIN_DIR%\nasm\
set IASL_DIR=%TOOLCHAIN_DIR%\iasl\
set BASE_TOOLS_PATH=%SOURCE_DIR%\BaseTools
set NASM_PREFIX=%NASM_DIR%
set IASL_PREFIX=%IASL_DIR%
set BUILD_FOLDER=%SOURCE_DIR%\Build
set BASETOOLS_BIN=%BASE_TOOLS_PATH%\BIN\Win32
set BASETOOLS_BINWRAP_WIN=%BASE_TOOLS_PATH%\BinWrappers\WindowsLike

@rem ==========================================
@rem EDK2 Build parameters
@rem build -a %ARCHITECTURE_PARAMETER% -p %PLATFORM_PARAMETER% -t %TOOL_PARAMETER% -b %BUILD_MODE%
@rem ex. build -p EmulatorPkg\EmulatorPkg.dsc -t VS2017
@rem ==========================================
set TOOL_PARAMETER=VS2019
set BUILD_MODE=DEBUG

@rem For EmulatorPkg.
set PLATFORM_PARAMETER=EmulatorPkg\EmulatorPkg.dsc
set ARCHITECTURE_PARAMETER=X64
set OTHER_PARAMETERS=-D ADD_SHELL_STRING

@rem For OVMF package.
@rem set PLATFORM_PARAMETER=OvmfPkg\OvmfPkgX64.dsc
@rem set ARCHITECTURE_PARAMETER=X64
@rem set OTHER_PARAMETERS=-D DEBUG_ON_SERIAL_PORT -D ADD_SHELL_STRING
@rem set OVMF_FD_FILES=%BUILD_FOLDER%\Ovmf%ARCHITECTURE_PARAMETER%\%BUILD_MODE%_%TOOL_PARAMETER%\FV\OVMF.fd

@rem ==========================================
@rem Simulator files of EmulatorPkg
@rem =========================================
set WIN_HOST_EXE=%BUILD_FOLDER%\Emulator%ARCHITECTURE_PARAMETER%\%BUILD_MODE%_%TOOL_PARAMETER%\%ARCHITECTURE_PARAMETER%\

@rem ==========================================
@rem Qemu parameters
@rem =========================================
set QEMU_EXE_FOLDER=C:\Program Files\qemu
set QEMU_EXE_FILE=qemu-system-x86_64.exe
set QEMU_PARAMETERS=-m 2G -smp 4 -bios %OVMF_FD_FILES% -machine q35 -serial mon:stdio -hda %CURRENT_PATH%virtualdisk\virtualdisk.img --net none


@rem ==========================================
@rem Import VS VARS to Env
@rem ==========================================
set PATH=C:\Windows\system32;C:\Windows
set BATCH_VCVARSALL_PATH=c:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat
call "%BATCH_VCVARSALL_PATH%" x86 10.0.17763.0
set PATH=%BASETOOLS_BIN%;%BASETOOLS_BINWRAP_WIN%;%PYTHON_HOME%;%NASM_PREFIX%;%IASL_PREFIX%;%PATH%



