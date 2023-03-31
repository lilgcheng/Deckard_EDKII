#ifndef __DXE_SAMPLE_H__
#define __DXE_SAMPLE_H__

#include <Uefi.h>
#include <Library/UefiLib.h>

#define EFI_DECKARD_DATA_PROTOCOL_PROTOCOL_GUID \
    { 0x4583ff6, 0xcb36, 0x4940, { 0x94, 0x7e, 0xb9, 0xb3, 0x9f, 0x4a, 0xfa, 0xf7 }}
    
#define EFI_DECKARD_BMI_PROTOCOL_PROTOCOL_GUID \
    { 0x4663ff6, 0xcb36, 0x4940, { 0x94, 0x7e, 0xb9, 0xb3, 0x9f, 0x4a, 0xfa, 0xf7 }}

typedef struct _DECKARD_DATA_PROTOCOL_ DECKARD_DATA_PROTOCOL;

typedef struct _DECKARD_BMI_PROTOCOL_ DECKARD_BMI_PROTOCOL;


struct _DECKARD_DATA_PROTOCOL_ {
    CHAR8    *name;
    UINT8    high;    
    UINT8    weight;    
};

struct _DECKARD_BMI_PROTOCOL_ {
    UINT8    high;    
    UINT8    weight;    
};

extern EFI_GUID gEfiDXESampleProtocolGuid;
extern EFI_GUID gEfiDXESampleBMIProtocolGuid;
#endif // __DXE_SAMPLE_H__
