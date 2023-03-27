#ifndef _INCLUDE_PEI_HOB_H_
#define _INCLUDE_PEI_HOB_H_
#define DECKARD_PEI_HOB_GUID {0x755B6596, 0x68A6, 0x4BA3, { 0xB3, 0xAD, 0x2C, 0x62, 0x9F, 0xD1, 0xEA, 0x98}}

typedef struct _Uefi_PEI_Hob_test_ UEFI_PEI_HOB_TEST;
struct _Uefi_PEI_Hob_test_
{
    EFI_HOB_GUID_TYPE Header;
    CHAR16 *name;
    UINT8 Age;
};

extern EFI_GUID gDeckardHobGuid;

#endif