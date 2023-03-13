
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/Smbios.h>
#include <IndustryStandard/SmBios.h>
#include <Guid/SmBios.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>


#include "LibSmbiosView.h"
#include "SmbiosView.h"
#include "PrintInfo.h"
#include "QueryTable.h"

STATIC UINT8                    m64Init       = 0;
STATIC SMBIOS_TABLE_3_0_ENTRY_POINT *mSmbios64BitTable = NULL;
STATIC SMBIOS_STRUCTURE_POINTER m_Smbios64BitStruct;
STATIC SMBIOS_STRUCTURE_POINTER *mSmbios64BitStruct = &m_Smbios64BitStruct;
UINTN  mSmbios64BitTableLength;
STATIC STRUCTURE_STATISTICS *mSmbios64BitStatisticsTable = NULL;
UINTN  mNumberOfSmbios64BitStructures;

/**
  Copy Length of Src buffer to Dest buffer,
  add a NULL termination to Dest buffer.

  @param[in, out] Dest  Destination buffer head.
  @param[in] Src        Source buffer head.
  @param[in] Length     Length of buffer to be copied.
**/
VOID
MemToString1 (
  IN OUT VOID   *Dest,
  IN VOID       *Src,
  IN UINTN      Length
  )
{
  UINT8 *SrcBuffer;
  UINT8 *DestBuffer;
  SrcBuffer   = (UINT8 *) Src;
  DestBuffer  = (UINT8 *) Dest;
  //
  // copy byte by byte
  //
  while ((Length--)!=0) {
    *DestBuffer++ = *SrcBuffer++;
  }
  //
  // append a NULL terminator
  //
  *DestBuffer = '\0';
}

/**
  Print the info of 64-bit EPS(Entry Point Structure).

  @param[in] SmbiosTable    Pointer to the SMBIOS table entry point.
  @param[in] Option         Display option.
**/
VOID
Smbios64BitPrintEPSInfo (
  IN  SMBIOS_TABLE_3_0_ENTRY_POINT  *SmbiosTable,
  IN  UINT8                         Option
  )
{
  UINT8 Anchor[5];

  // if (SmbiosTable == NULL) {
  //   ShellPrintHiiEx(-1,-1,NULL,STRING_TOKEN (STR_SMBIOSVIEW_PRINTINFO_SMBIOSTABLE_NULL), gShellDebug1HiiHandle);
  //   return ;
  // }

  // if (Option == SHOW_NONE) {
  //   return ;
  // }

  if (Option >= SHOW_NORMAL) {
    MemToString1 (Anchor, SmbiosTable->AnchorString, 5);
    Print((const CHAR16 *)L"Anchor String:        %a\r\n",Anchor);
    Print((const CHAR16 *)L"EPS Checksum:         0x%x\r\n",SmbiosTable->EntryPointStructureChecksum);
    Print((const CHAR16 *)L"Entry Point Len:      %d\r\n",SmbiosTable->EntryPointLength);
    Print((const CHAR16 *)L"Version:              %d.%d\r\n",SmbiosTable->MajorVersion,SmbiosTable->MinorVersion);
    Print((const CHAR16 *)L"SMBIOS Docrev:        0x%x\r\n",SmbiosTable->DocRev);
    Print((const CHAR16 *)L"Table Max Size:       %d\r\n",SmbiosTable->TableMaximumSize);
    Print((const CHAR16 *)L"Table Address:        0x%p\r\n",SmbiosTable->TableAddress);
  }
  //
  // If SHOW_ALL, also print followings.
  //
  if (Option >= SHOW_DETAIL) {

    Print((const CHAR16 *)L"Entry Point revision: 0x%x\r\n",SmbiosTable->EntryPointRevision);
  }
  Print (L"\n");
}


/**
  Query all structures Data from SMBIOS table and Display
  the information to users as required display option.

  @param[in] QueryType      Structure type to view.
  @param[in] QueryHandle    Structure handle to view.
  @param[in] Option         Display option: none,outline,normal,detail.
  @param[in] RandomView     Support for -h parameter.

  @retval EFI_SUCCESS           print is successful.
  @retval EFI_BAD_BUFFER_SIZE   structure is out of the range of SMBIOS table.
**/
EFI_STATUS
SMBios64View (
  IN  UINT8   QueryType,
  IN  UINT16  QueryHandle,
  IN  UINT8   Option,
  IN  BOOLEAN RandomView
  )
{
  UINT16                        Handle;
  UINT8                         *Buffer;
  UINT16                        Length;
  UINTN                         Index;
  SMBIOS_STRUCTURE_POINTER      SmbiosStruct;
  SMBIOS_TABLE_3_0_ENTRY_POINT  *SMBiosTable;

  SMBiosTable = NULL;
  LibSmbios64BitGetEPS (&SMBiosTable);
  if (SMBiosTable == NULL) {
    // ShellPrintHiiEx(-1,-1,NULL,STRING_TOKEN (STR_SMBIOSVIEW_SMBIOSVIEW_CANNOT_ACCESS_TABLE), gShellDebug1HiiHandle);
    Print((const CHAR16 *)L"SmbiosView: Cannot access SMBIOS table\r\n");
    return EFI_BAD_BUFFER_SIZE;
  }

  if (CompareMem (SMBiosTable->AnchorString, "_SM3_", 5) == 0) {
    //
    // Have got SMBIOS table
    //
    Smbios64BitPrintEPSInfo (SMBiosTable, Option);
  
  //   SmbiosMajorVersion = SMBiosTable->MajorVersion;
  //   SmbiosMinorVersion = SMBiosTable->MinorVersion;

  //   ShellPrintEx(-1,-1,L"=========================================================\n");
  //   ShellPrintHiiEx(-1,-1,NULL,STRING_TOKEN (STR_SMBIOSVIEW_SMBIOSVIEW_QUERY_STRUCT_COND), gShellDebug1HiiHandle);

  //   if (QueryType == STRUCTURE_TYPE_RANDOM) {
  //     ShellPrintHiiEx(-1,-1,NULL,STRING_TOKEN (STR_SMBIOSVIEW_SMBIOSVIEW_QUERYTYPE_RANDOM), gShellDebug1HiiHandle);
  //   } else {
  //     ShellPrintHiiEx(-1,-1,NULL,STRING_TOKEN (STR_SMBIOSVIEW_SMBIOSVIEW_QUERYTYPE), gShellDebug1HiiHandle, QueryType);
  //   }

  //   if (RandomView) {
  //     ShellPrintHiiEx(-1,-1,NULL,STRING_TOKEN (STR_SMBIOSVIEW_SMBIOSVIEW_QUERYHANDLE_RANDOM), gShellDebug1HiiHandle);
  //   } else {
  //     ShellPrintHiiEx(-1,-1,NULL,STRING_TOKEN (STR_SMBIOSVIEW_SMBIOSVIEW_QUERYHANDLE), gShellDebug1HiiHandle, QueryHandle);
  //   }

  //   ShellPrintHiiEx(-1,-1,NULL,STRING_TOKEN (STR_SMBIOSVIEW_SMBIOSVIEW_SHOWTYPE), gShellDebug1HiiHandle);
  //   ShellPrintEx(-1,-1,GetShowTypeString (gShowType));
  //   ShellPrintEx(-1,-1,L"\n\n");



    //
    // Searching and display structure info
    //
    Handle    = QueryHandle;
    for (Index = 0; Index < mNumberOfSmbios64BitStructures; Index++) {
      //
      // if reach the end of table, break..
      //
      if (Handle == INVALID_HANDLE) {
        break;
      }
      //
      // handle then point to the next!
      //
      if (LibGetSmbios64BitStructure (&Handle, &Buffer, &Length) != DMI_SUCCESS) {
        break;
      }

      SmbiosStruct.Raw = Buffer;

      //
      // if QueryType==Random, print this structure.
      // if QueryType!=Random, but Hdr->Type==QueryType, also print it.
      // only if QueryType != Random and Hdr->Type != QueryType, skiped it.
      //
      Print((const CHAR16 *)L"QueryType=%d,SmbiosStruct.Hdr->Type=0x%x,", QueryType, SmbiosStruct.Hdr->Type);
      if (QueryType != STRUCTURE_TYPE_RANDOM && SmbiosStruct.Hdr->Type != QueryType) {
        continue;
      }

    
      Print((const CHAR16 *)L"\n=========================================================\n");
      Print((const CHAR16 *)L"Type=%d, Handle=0x%x\r\nDump Structure as:\r\n",SmbiosStruct.Hdr->Type,SmbiosStruct.Hdr->Handle);
      Print((const CHAR16 *)L"Index=%d,Length=0x%x,", Index, Length);
      //
      // Addr of structure in structure in table
      //
      Print((const CHAR16 *)L"Addr=0x%p\r\n", (UINTN) Buffer);
      // DumpHex (0, 0, Length, Buffer);


      // if (gShowType != SHOW_NONE) {
      //   //
      //   // Print structure information
      //   //
      //   SmbiosPrintStructure (&SmbiosStruct, gShowType);
      //   Print((const CHAR16 *)L"\n", (UINTN) Buffer);
      

      // }
      // if (!RandomView) {
      //   break;
      // }
      // //
      // // Support Execution Interrupt.
      // //
      // if (ShellGetExecutionBreakFlag ()) {
      //   return EFI_ABORTED;
      // }
    }

    Print((const CHAR16 *)L"\n=========================================================\n");
    return EFI_SUCCESS;
  }

  return EFI_BAD_BUFFER_SIZE;
}


/**
  @param[in]  Smbios64EntryPoint          SMBIOS 64-bit entry point.
  @param[out] NumberOfSmbios64Structures  The number of structures in 64-bit SMBIOS table.
  @param[out] Smbios64TableLength         The total length of 64-bit SMBIOS table.

  @retval EFI_SUCCESS                     Calculation was successful.
**/
EFI_STATUS
CalculateSmbios64BitStructureCountAndLength (
  SMBIOS_TABLE_3_0_ENTRY_POINT    *Smbios64EntryPoint,
  UINTN                           *NumberOfSmbios64Structures,
  UINTN                           *Smbios64TableLength
)
{
  SMBIOS_STRUCTURE_POINTER        Smbios;
  UINT8                           *Raw;

  *Smbios64TableLength = 0;
  *NumberOfSmbios64Structures = 0;

  Smbios.Raw = (UINT8 *)(UINTN)(Smbios64EntryPoint->TableAddress);
  while (TRUE) {
    if (Smbios.Hdr->Type == 127) {
      //
      // Reach the end of table type 127
      //
      (*NumberOfSmbios64Structures)++;
      (*Smbios64TableLength) += sizeof (SMBIOS_STRUCTURE);
      return EFI_SUCCESS;
    }

    Raw = Smbios.Raw;
    //
    // Walk to next structure
    //

    Print((const CHAR16 *)L"this structure head = %p\r\n",Raw);
    LibGetSmbiosString (&Smbios, (UINT16) (-1));
    Print((const CHAR16 *)L"Next structure head= %p\r\n",Smbios.Raw);
   
    //
    // Length = Next structure head - this structure head
    //
    
    (*Smbios64TableLength) += ((UINTN) Smbios.Raw - (UINTN) Raw);
    if ((*Smbios64TableLength) > Smbios64EntryPoint->TableMaximumSize) {
      //
      // The actual table length exceeds maximum table size,
      // There should be something wrong with SMBIOS table.
      //
      return EFI_INVALID_PARAMETER;
    }
    (*NumberOfSmbios64Structures)++;
  }
}

/**
  Get the entry point structure for the table.

  @param[out] EntryPointStructure  The pointer to populate.
**/
VOID
LibSmbios64BitGetEPS (
  OUT SMBIOS_TABLE_3_0_ENTRY_POINT **EntryPointStructure
  )
{
  //
  // return SMBIOS Table address
  //
  *EntryPointStructure = mSmbios64BitTable;
}


/**
  Function to initialize the global mSmbios64BitStatisticsTable object.

  @retval EFI_SUCCESS           print is successful.
**/
EFI_STATUS
InitSmbios64BitTableStatistics (
  VOID
  )
{
  UINT16                    Handle;
  UINT8                     *Buffer;
  UINT16                    Length;
  UINT16                    Offset;
  UINT16                    Index;
  EFI_STATUS                Status;
  SMBIOS_STRUCTURE_POINTER      SmbiosStruct;
  SMBIOS_TABLE_3_0_ENTRY_POINT  *SMBiosTable;
  STRUCTURE_STATISTICS          *StatisticsPointer;

  SMBiosTable = NULL;
  LibSmbios64BitGetEPS (&SMBiosTable);
  if (SMBiosTable == NULL) {
    // ShellPrintHiiEx(-1,-1,NULL,STRING_TOKEN (STR_SMBIOSVIEW_SMBIOSVIEW_CANNOT_ACCESS_TABLE), gShellDebug1HiiHandle);
    Print((const CHAR16 *)L"SmbiosView: Cannot access SMBIOS table\r\n");
    return EFI_NOT_FOUND;
  }

  if (CompareMem (SMBiosTable->AnchorString, "_SM3_", 5) != 0) {
    // ShellPrintHiiEx(-1,-1,NULL,STRING_TOKEN (STR_SMBIOSVIEW_SMBIOSVIEW_SMBIOS_TABLE), gShellDebug1HiiHandle);
   
   Print((const CHAR16 *)L"SmbiosView: SMBIOS table damaged\r\n");
    return EFI_INVALID_PARAMETER;
  }
  //
  // Allocate memory to mSmbios64BitStatisticsTable
  //
  if (mSmbios64BitStatisticsTable != NULL) {
    FreePool (mSmbios64BitStatisticsTable);
    mSmbios64BitStatisticsTable = NULL;
  }
  //
  // Calculate number of smbios structures
  //
  Status = CalculateSmbios64BitStructureCountAndLength (SMBiosTable, &mNumberOfSmbios64BitStructures, &mSmbios64BitTableLength);
  if ((EFI_ERROR (Status)) || (mSmbios64BitTableLength > SMBiosTable->TableMaximumSize)) {
    return EFI_INVALID_PARAMETER;
  }

  mSmbios64BitStatisticsTable = (STRUCTURE_STATISTICS *) AllocateZeroPool (mNumberOfSmbios64BitStructures * sizeof (STRUCTURE_STATISTICS));

  if (mSmbios64BitStatisticsTable == NULL) {
    // ShellPrintHiiEx(-1,-1,NULL,STRING_TOKEN (STR_SMBIOSVIEW_SMBIOSVIEW_OUT_OF_MEM), gShellDebug1HiiHandle);
   
   Print((const CHAR16 *)L"SmbiosView: Out of memory\r\n");
    return EFI_OUT_OF_RESOURCES;
  }

  Offset      = 0;
  StatisticsPointer = mSmbios64BitStatisticsTable;

  //
  // search from the first one
  //
  Handle = INVALID_HANDLE;
  LibGetSmbios64BitStructure (&Handle, NULL, NULL);
  Print((const CHAR16 *)L"mNumberOfSmbios64BitStructures=%d\r\n",mNumberOfSmbios64BitStructures);
  for (Index = 1; Index <= mNumberOfSmbios64BitStructures; Index++) {
    //
    // If reach the end of table, break..
    //
    if (Handle == INVALID_HANDLE) {
      break;
    }
    //
    // After LibGetSmbios64BitStructure(), handle then point to the next!
    //
    if (LibGetSmbios64BitStructure (&Handle, &Buffer, &Length) != DMI_SUCCESS) {
      break;
    }

    SmbiosStruct.Raw = Buffer;

    //
    // general statistics
    //
    StatisticsPointer->Index  = Index;
    StatisticsPointer->Type   = SmbiosStruct.Hdr->Type;
    StatisticsPointer->Handle = SmbiosStruct.Hdr->Handle;
    StatisticsPointer->Length = Length;
    StatisticsPointer->Addr   = Offset;

    Offset = (UINT16) (Offset + Length);

    StatisticsPointer         = &mSmbios64BitStatisticsTable[Index];
  }

  return EFI_SUCCESS;
}


/**
    Get SMBIOS structure for the given Handle,
    Handle is changed to the next handle or 0xFFFF when the end is
    reached or the handle is not found.

    @param[in, out] Handle     0xFFFF: get the first structure
                               Others: get a structure according to this value.
    @param[out] Buffer         The pointer to the pointer to the structure.
    @param[out] Length         Length of the structure.

    @retval DMI_SUCCESS   Handle is updated with next structure handle or
                          0xFFFF(end-of-list).

    @retval DMI_INVALID_HANDLE  Handle is updated with first structure handle or
                                0xFFFF(end-of-list).
**/
EFI_STATUS
LibGetSmbios64BitStructure (
  IN  OUT UINT16  *Handle,
  OUT UINT8       **Buffer,
  OUT UINT16      *Length
  )
{
  SMBIOS_STRUCTURE_POINTER  Smbios;
  SMBIOS_STRUCTURE_POINTER  SmbiosEnd;
  UINT8                     *Raw;

  if (*Handle == INVALID_HANDLE) {
    *Handle = mSmbios64BitStruct->Hdr->Handle;
    return DMI_INVALID_HANDLE;
  }

  if ((Buffer == NULL) || (Length == NULL)) {
    Print((const CHAR16 *)L"Get SMBIOS Structure, no buffer or length specified!\r\n");
    return DMI_INVALID_HANDLE;
  }

  *Length     = 0;
  Smbios.Hdr  = mSmbios64BitStruct->Hdr;

  SmbiosEnd.Raw = Smbios.Raw + mSmbios64BitTableLength;
  while (Smbios.Raw < SmbiosEnd.Raw) {
    if (Smbios.Hdr->Handle == *Handle) {
      Raw = Smbios.Raw;
      //
      // Walk to next structure
      //
      LibGetSmbiosString (&Smbios, (UINT16) (-1));
      //
      // Length = Next structure head - this structure head
      //
      *Length = (UINT16) (Smbios.Raw - Raw);
      *Buffer = Raw;
      //
      // update with the next structure handle.
      //
      if (Smbios.Raw < SmbiosEnd.Raw) {
        *Handle = Smbios.Hdr->Handle;
      } else {
        *Handle = INVALID_HANDLE;
      }
      return DMI_SUCCESS;
    }
    //
    // Walk to next structure
    //
    LibGetSmbiosString (&Smbios, (UINT16) (-1));
  }

  *Handle = INVALID_HANDLE;
  return DMI_INVALID_HANDLE;
}



/**
  Return SMBIOS string for the given string number.

  @param[in] Smbios         Pointer to SMBIOS structure.
  @param[in] StringNumber   String number to return. -1 is used to skip all strings and
                            point to the next SMBIOS structure.

  @return Pointer to string, or pointer to next SMBIOS strcuture if StringNumber == -1
**/
CHAR8*
LibGetSmbiosString (
  IN  SMBIOS_STRUCTURE_POINTER    *Smbios,
  IN  UINT16                      StringNumber
  )
{
  UINT16  Index;
  CHAR8   *String;

  ASSERT (Smbios != NULL);

  //
  // Skip over formatted section
  //
  String = (CHAR8 *) (Smbios->Raw + Smbios->Hdr->Length);

  //
  // Look through unformated section
  //
  for (Index = 1; Index <= StringNumber; Index++) {
    if (StringNumber == Index) {
      return String;
    }
    //
    // Skip string
    //
    for (; *String != 0; String++);
    String++;

    if (*String == 0) {
      //
      // If double NULL then we are done.
      //  Return pointer to next structure in Smbios.
      //  if you pass in a -1 you will always get here
      //
      Smbios->Raw = (UINT8 *)++String;
      return NULL;
    }
  }

  return NULL;
}



/**
  Init the SMBIOS VIEW API's environment.

  @retval EFI_SUCCESS  Successful to init the SMBIOS VIEW Lib.
**/
EFI_STATUS
LibSmbios64BitInit (
  VOID
  )
{
  EFI_STATUS  Status;

  //
  // Init only once
  //
  if (m64Init == 1) {
    return EFI_SUCCESS;
  }
  //
  // Get SMBIOS table from System Configure table
  //
  Status = EfiGetSystemConfigurationTable (&gEfiSmbios3TableGuid, (VOID**)&mSmbios64BitTable);

  if (mSmbios64BitTable == NULL) {
    return EFI_NOT_FOUND;
  }

  if (!EFI_ERROR (Status)) {
        
        Print((const CHAR16 *)L"Smbios3Table:\n");
        Print((const CHAR16 *)L"AnchorString                - '%c%c%c%c%c'\n",
          mSmbios64BitTable->AnchorString[0],
          mSmbios64BitTable->AnchorString[1],
          mSmbios64BitTable->AnchorString[2],
          mSmbios64BitTable->AnchorString[3],
          mSmbios64BitTable->AnchorString[4]
          );
        
        Print((const CHAR16 *)L"  EntryPointStructureChecksum - 0x%02x\n", mSmbios64BitTable->EntryPointStructureChecksum);
        Print((const CHAR16 *)L"  EntryPointLength            - 0x%02x\n", mSmbios64BitTable->EntryPointLength);
        Print((const CHAR16 *)L"  MajorVersion                - 0x%02x\n", mSmbios64BitTable->MajorVersion);
        Print((const CHAR16 *)L"  MinorVersion                - 0x%02x\n", mSmbios64BitTable->MinorVersion);
        Print((const CHAR16 *)L"  DocRev                      - 0x%02x\n", mSmbios64BitTable->DocRev);
        Print((const CHAR16 *)L"  EntryPointRevision          - 0x%02x\n", mSmbios64BitTable->EntryPointRevision);
        Print((const CHAR16 *)L"  TableMaximumSize            - 0x%08x\n", mSmbios64BitTable->TableMaximumSize);
        Print((const CHAR16 *)L"  TableAddress                - 0x%016lx\n", mSmbios64BitTable->TableAddress);
  }
  //
  // Init SMBIOS structure table address
  //
  mSmbios64BitStruct->Raw  = (UINT8 *) (UINTN) (mSmbios64BitTable->TableAddress);

  m64Init               = 1;
  return EFI_SUCCESS;
}


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
Uefi_Get_SMBIOS_Dump (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
EFI_STATUS          Status;
Status = LibSmbios64BitInit();

if (EFI_ERROR (Status)){
  Print((const CHAR16 *)L" LibSmbios64BitInit fail\n");
}

UINT16              StructHandle;


if (!EFI_ERROR (Status)) {
    //
    // Initialize the StructHandle to be the first handle
    //
    StructHandle  = INVALID_HANDLE;
    Print((const CHAR16 *)L" LibGetSmbiosStructure Success1\n");
    LibGetSmbios64BitStructure (&StructHandle, NULL, NULL);
    Print((const CHAR16 *)L" LibGetSmbiosStructure Success2\n");
}

//
// build statistics table
//
Status = InitSmbios64BitTableStatistics ();
Print((const CHAR16 *)L" InitSmbios64BitTableStatistics Success2\n");

//
// Initialize the StructHandle to be the first handle
//
StructHandle  = INVALID_HANDLE;
LibGetSmbios64BitStructure (&StructHandle, NULL, NULL);

//
// Show SMBIOS structure information
//
Status = SMBios64View (0xFE, StructHandle, 0x03, TRUE);//-<scan smbio  0xFE



  return EFI_SUCCESS;
}
