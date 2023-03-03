@rem Auther: Justin_Mao 
@rem Contact information: Justin_Mao@compal.com
@rem Batch file for EDK2 built.
@rem ==========================================

@echo off

call setenv.cmd

pushd . > nul 2>&1
cd /d %SOURCE_DIR%
call edksetup.bat rebuild
popd . > nul 2>&1

@rem ==========================================
@rem Entry 
@rem ==========================================
echo (1) Build Package.
echo (2) Clean Package.
echo (3) Run simulator of EmulatorPkg.
echo (4) Run Qemu Simulator.

echo Please enter your selection:
set /p var=

if "%var%" == "1" (
    call :BuildPackage
) else if "%var%" == "2" (
    call :CleanPackage
) else if "%var%" == "3" (
    call :RunSimofEmulatorPkg
) else if "%var%" == "4" (
    call :RunQemuSimulator
) else (
    echo Opps!! There's an error, please eneter a correct information.
)
exit /b 0

@rem ==========================================
@rem Build Package
@rem ==========================================
:BuildPackage
echo Build Package.
pushd . > nul 2>&1
cd /d %SOURCE_DIR%
call edksetup.bat
call build -a %ARCHITECTURE_PARAMETER% -p %PLATFORM_PARAMETER% -t %TOOL_PARAMETER% -b %BUILD_MODE% %OTHER_PARAMETERS%
popd . > nul 2>&1
exit /b 0
:EndBuildPackage

@rem ==========================================
@rem Clean Package
@rem ==========================================
:CleanPackage
echo Clean Package.
pushd . > nul 2>&1
cd /d %SOURCE_DIR%
call edksetup.bat
call build -a %ARCHITECTURE_PARAMETER% -p %PLATFORM_PARAMETER% -t %TOOL_PARAMETER% -b %BUILD_MODE% %OTHER_PARAMETERS% cleanall
rmdir /S /Q %BUILD_FOLDER%
popd . > nul 2>&1
exit /b 0
:EndCleanPackage

@rem ==========================================
@rem Run the simulator of EmulatorPkg
@rem ==========================================
:RunSimofEmulatorPkg
echo Run the simulator of EmulatorPkg.
pushd . > nul 2>&1
cd /d %WIN_HOST_EXE%
call WinHost.exe
popd . > nul 2>&1
exit /b 0
:EndRunSimofEmulatorPkg

@rem ==========================================
@rem Run Qemu Simulator
@rem ==========================================
:RunQemuSimulator
echo Run Qemusimulator.
pushd . > nul 2>&1
cd /d %QEMU_EXE_FOLDER%
call %QEMU_EXE_FILE% %QEMU_PARAMETERS%
popd . > nul 2>&1
exit /b 0
:EndRunQemuSimulator

