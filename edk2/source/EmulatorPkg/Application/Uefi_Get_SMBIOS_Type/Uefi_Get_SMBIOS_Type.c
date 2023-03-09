
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/Smbios.h>
#include <IndustryStandard/SmBios.h>
#include <Guid/SmBios.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>

STATIC SMBIOS_STRUCTURE_POINTER mSmbios64BitStruct;

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


EFI_STATUS
ShowSMBIOSTYPE1( UINT8* SmbioStructTableAddress){
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_GUID Uuid;
  mSmbios64BitStruct.Raw = SmbioStructTableAddress; // get SMBIOS Entry point address
	while (1) {
	
	//1. The max handle is 0xFEFF for SMBIOS 2.0 later, please see the SMBIOS spec.
		if (mSmbios64BitStruct.Hdr->Handle == 0xFEFF) {

			Print (L"The Handle of SMBIOS TYPE Struct is over 0xFEFF.\n");
			Status = EFI_NOT_FOUND;
			break;
		}


		if (mSmbios64BitStruct.Hdr->Type != 0x01) {
			Print (L"TSmbiosStruct.Hdr->Type=%x\n",mSmbios64BitStruct.Hdr->Type);
			LibGetSmbiosString(&mSmbios64BitStruct, (UINT16)(-1));
			// continue;
		} else {
			
			Print (L"05h|(string index:%d), ProductName:%a\n", mSmbios64BitStruct.Type1->ProductName, LibGetSmbiosString(&mSmbios64BitStruct, mSmbios64BitStruct.Type1->ProductName));
			Print (L"06h|(string index:%d), Version:%a\n", mSmbios64BitStruct.Type1->Version, LibGetSmbiosString(&mSmbios64BitStruct, mSmbios64BitStruct.Type1->Version));
			Print (L"07h|(string index:%d), SerialNumber:%a\n", mSmbios64BitStruct.Type1->SerialNumber, LibGetSmbiosString(&mSmbios64BitStruct, mSmbios64BitStruct.Type1->SerialNumber));

			CopyMem (&Uuid, &mSmbios64BitStruct.Type1->Uuid, sizeof (EFI_GUID));
			Print (L"08h|UUID:%g\n", Uuid);



			switch (mSmbios64BitStruct.Type1->WakeUpType) {
				case 0x0:
					Print (L"18h|Wake-up Type: Reserved.\n");	
					break;
				case 0x1:
					Print (L"18h|Wake-up Type: Other.\n");	
					break;
				case 0x2:
					Print (L"18h|Wake-up Type: Unkown.\n");	
					break;
				case 0x3:
					Print (L"18h|Wake-up Type: APM Timer.\n");	
					break;
				case 0x4:
					Print (L"18h|Wake-up Type: Modem Ring.\n");	
					break;
				case 0x5:
					Print (L"18h|Wake-up Type: LAN Remote.\n");
				case 0x6:
					Print (L"18h|Wake-up Type: Power Switch.\n");					
					break;	
				case 0x7:
					Print (L"18h|Wake-up Type: PCI PME#.\n");	
					break;
				case 0x8:
					Print (L"18h|Wake-up Type: AC Power Restored.\n");	
					break;	
				default:
					break;
			}
			
			Print (L"19h|(string index:%d), SKUNumber:%a\n", mSmbios64BitStruct.Type1->SKUNumber, LibGetSmbiosString(&mSmbios64BitStruct, mSmbios64BitStruct.Type1->SKUNumber));
			Print (L"1Ah|(string index:%d), Family:%a\n", mSmbios64BitStruct.Type1->Family, LibGetSmbiosString(&mSmbios64BitStruct, mSmbios64BitStruct.Type1->Family));

			Status = EFI_SUCCESS;
			break;
		}


	}
	return Status;
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
Uefi_Get_SMBIOS_Type (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{

EFI_SMBIOS_PROTOCOL *mSmbios;
SMBIOS_TABLE_3_0_ENTRY_POINT      *Smbios3Table;
Smbios3Table = NULL;
EFI_STATUS Status;

Status = gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **) &mSmbios);
DEBUG ((EFI_D_INFO, "  mSmbios MajorVersion : %d\n", mSmbios->MajorVersion));

  if (mSmbios->MajorVersion >= 3) {
    Status = EfiGetSystemConfigurationTable (
               &gEfiSmbios3TableGuid,
               (VOID **) &Smbios3Table
               );
    if (!EFI_ERROR (Status)) {
      // DEBUG ((EFI_D_INFO, "Smbios3Table:\n"));
      // DEBUG ((EFI_D_INFO, "  AnchorString                - '%c%c%c%c%c'\n",
        // Smbios3Table->AnchorString[0],
        // Smbios3Table->AnchorString[1],
        // Smbios3Table->AnchorString[2],
        // Smbios3Table->AnchorString[3],
        // Smbios3Table->AnchorString[4]
        // ));
      Print((const CHAR16 *)L"Smbios3Table:\n");
      Print((const CHAR16 *)L"AnchorString                - '%c%c%c%c%c'\n",
        Smbios3Table->AnchorString[0],
        Smbios3Table->AnchorString[1],
        Smbios3Table->AnchorString[2],
        Smbios3Table->AnchorString[3],
        Smbios3Table->AnchorString[4]
        );
      // DEBUG ((EFI_D_INFO, "  EntryPointStructureChecksum - 0x%02x\n", Smbios3Table->EntryPointStructureChecksum));
      // DEBUG ((EFI_D_INFO, "  EntryPointLength            - 0x%02x\n", Smbios3Table->EntryPointLength));
      // DEBUG ((EFI_D_INFO, "  MajorVersion                - 0x%02x\n", Smbios3Table->MajorVersion));
      // DEBUG ((EFI_D_INFO, "  MinorVersion                - 0x%02x\n", Smbios3Table->MinorVersion));
      // DEBUG ((EFI_D_INFO, "  DocRev                      - 0x%02x\n", Smbios3Table->DocRev));
      // DEBUG ((EFI_D_INFO, "  EntryPointRevision          - 0x%02x\n", Smbios3Table->EntryPointRevision));
      // DEBUG ((EFI_D_INFO, "  TableMaximumSize            - 0x%08x\n", Smbios3Table->TableMaximumSize));
      // DEBUG ((EFI_D_INFO, "  TableAddress                - 0x%016lx\n", Smbios3Table->TableAddress));
      
      
      Print((const CHAR16 *)L"  EntryPointStructureChecksum - 0x%02x\n", Smbios3Table->EntryPointStructureChecksum);
      Print((const CHAR16 *)L"  EntryPointLength            - 0x%02x\n", Smbios3Table->EntryPointLength);
      Print((const CHAR16 *)L"  MajorVersion                - 0x%02x\n", Smbios3Table->MajorVersion);
      Print((const CHAR16 *)L"  MinorVersion                - 0x%02x\n", Smbios3Table->MinorVersion);
      Print((const CHAR16 *)L"  DocRev                      - 0x%02x\n", Smbios3Table->DocRev);
      Print((const CHAR16 *)L"  EntryPointRevision          - 0x%02x\n", Smbios3Table->EntryPointRevision);
      Print((const CHAR16 *)L"  TableMaximumSize            - 0x%08x\n", Smbios3Table->TableMaximumSize);
      Print((const CHAR16 *)L"  TableAddress                - 0x%016lx\n", Smbios3Table->TableAddress);
      
    }
  }
  UINT8* SmbiosStructTableAddress = NULL;
  SmbiosStructTableAddress  = (UINT8 *) (UINTN) (Smbios3Table->TableAddress);
  Status = ShowSMBIOSTYPE1(SmbiosStructTableAddress);
  return EFI_SUCCESS;
}
