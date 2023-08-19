

#include "AppSMBIOS.h"

STATIC SMBIOS_STRUCTURE_POINTER  SmbiosStruct; //Smbios Type Struct;

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

//   ASSERT (Smbios != NULL);

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
    LibGetSmbiosString (&Smbios, (UINT16) (-1));
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

EFI_STATUS 
ShowSmbiosType0 (
	UINT8* SmbiosStructTableAddress
) 
{
	EFI_STATUS Status = EFI_SUCCESS;

	SmbiosStruct.Raw = SmbiosStructTableAddress;
	
	while (1) {
	
	//1. The max handle is 0xFEFF for SMBIOS 2.0 later, please see the SMBIOS spec.
		if (SmbiosStruct.Hdr->Handle == 0xFEFF) {

			Print (L"The Handle of SMBIOS TYPE Struct is over 0xFEFF.\n");
			Status = EFI_NOT_FOUND;
			break;
		}


		if (SmbiosStruct.Hdr->Type != 0x00) {
			LibGetSmbiosString(&SmbiosStruct, (UINT16)(-1));
			continue;
		} else {
			
			Print (L"04h|(string index:%d), Vendor:%a\n", SmbiosStruct.Type0->Vendor, LibGetSmbiosString(&SmbiosStruct, SmbiosStruct.Type0->Vendor));
			Print (L"05h|(string index:%d), BiosVersion:%a\n", SmbiosStruct.Type0->BiosVersion, LibGetSmbiosString(&SmbiosStruct, SmbiosStruct.Type0->BiosVersion));
			Print (L"06h|(string index:%d), BiosSegment:%a\n", SmbiosStruct.Type0->BiosSegment, LibGetSmbiosString(&SmbiosStruct, SmbiosStruct.Type0->BiosSegment));

			Status = EFI_SUCCESS;
			break;
		}


	}

	return Status;
}


EFI_STATUS 
ShowSmbiosType1 (
	UINT8* SmbiosStructTableAddress
) 
{
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_GUID Uuid;
	SmbiosStruct.Raw = SmbiosStructTableAddress;
	
	while (1) {
	
	//1. The max handle is 0xFEFF for SMBIOS 2.0 later, please see the SMBIOS spec.
		if (SmbiosStruct.Hdr->Handle == 0xFEFF) {

			Print (L"The Handle of SMBIOS TYPE Struct is over 0xFEFF.\n");
			Status = EFI_NOT_FOUND;
			break;
		}


		if (SmbiosStruct.Hdr->Type != 0x01) {
			LibGetSmbiosString(&SmbiosStruct, (UINT16)(-1));
			continue;
		} else {
			
			Print (L"05h|(string index:%d), ProductName:%a\n", SmbiosStruct.Type1->ProductName, LibGetSmbiosString(&SmbiosStruct, SmbiosStruct.Type1->ProductName));
			Print (L"06h|(string index:%d), Version:%a\n", SmbiosStruct.Type1->Version, LibGetSmbiosString(&SmbiosStruct, SmbiosStruct.Type1->Version));
			Print (L"07h|(string index:%d), SerialNumber:%a\n", SmbiosStruct.Type1->SerialNumber, LibGetSmbiosString(&SmbiosStruct, SmbiosStruct.Type1->SerialNumber));

			CopyMem (&Uuid, &SmbiosStruct.Type1->Uuid, sizeof (EFI_GUID));
			Print (L"08h|UUID:%g\n", Uuid);



			switch (SmbiosStruct.Type1->WakeUpType) {
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
			
			Print (L"19h|(string index:%d), SKUNumber:%a\n", SmbiosStruct.Type1->SKUNumber, LibGetSmbiosString(&SmbiosStruct, SmbiosStruct.Type1->SKUNumber));
			Print (L"1Ah|(string index:%d), Family:%a\n", SmbiosStruct.Type1->Family, LibGetSmbiosString(&SmbiosStruct, SmbiosStruct.Type1->Family));

			Status = EFI_SUCCESS;
			break;
		}


	}

	return Status;
}


EFI_STATUS
EFIAPI
AppSMBIOSMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  SMBIOS_TABLE_3_0_ENTRY_POINT* SmbiosTableEntryPtr = NULL;  //Smbios Entry Point Struct (EPS).
  UINT8* SmbiosStructTableAddress = NULL;

  //1. Get SMBIOS table from System configuration table.
  Status = EfiGetSystemConfigurationTable(&gEfiSmbios3TableGuid, (VOID **)&SmbiosTableEntryPtr);

  if (((Status != EFI_SUCCESS) || (SmbiosTableEntryPtr == NULL)) || \
	 (CompareMem(SmbiosTableEntryPtr->AnchorString, "_SM3_", 5) !=0)) {

	Print (L"SMBIOS Table is not found!!!\n");
	
	return Status;
  }
  

  Print (L"================================================================================\n");
  Print (L"SMBIOS TABLE:\n");
  Print (L"AnchorString:%c%c%c%c%c\n", \
  	SmbiosTableEntryPtr->AnchorString[0],\
  	SmbiosTableEntryPtr->AnchorString[1],\
  	SmbiosTableEntryPtr->AnchorString[2],\
  	SmbiosTableEntryPtr->AnchorString[3],\
  	SmbiosTableEntryPtr->AnchorString[4]\
  	); 
  Print (L"EntryPointStructureChecksum: 0x%x\n", SmbiosTableEntryPtr->EntryPointStructureChecksum);
  Print (L"EntryPointLength: 0x%x\n", SmbiosTableEntryPtr->EntryPointLength);
  Print (L"MajorVersion: 0x%x\n", SmbiosTableEntryPtr->MajorVersion);
  Print (L"MinorVersion: 0x%x\n", SmbiosTableEntryPtr->MinorVersion);
  Print (L"DocRev: 0x%x\n", SmbiosTableEntryPtr->DocRev);
  Print (L"EntryPointRevision: 0x%x\n", SmbiosTableEntryPtr->EntryPointRevision);
  Print (L"TableMaximumSize: 0x%x\n", SmbiosTableEntryPtr->TableMaximumSize);
  Print (L"TableAddress: 0x%x\n", SmbiosTableEntryPtr->TableAddress);
  
  Print (L"================================================================================\n");

  //2. Show SMBIOS TYPE1.
  
  SmbiosStructTableAddress = (UINT8*)(UINTN)SmbiosTableEntryPtr->TableAddress;
  Print (L"Show SMBIOS TYPE0 !!!\n");
  Print (L"================================================================================\n");
  Status = ShowSmbiosType0 (SmbiosStructTableAddress);	
  Print (L"Show SMBIOS TYPE1 !!!\n");
  
  Status = ShowSmbiosType1 (SmbiosStructTableAddress);	

  return Status;
}