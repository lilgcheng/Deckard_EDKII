/** @file
    Name: CompalLearningSampleProtocol1.h
    Description: Header File for exteranl module use.
**/
#ifndef _COMPAL_LEARNING_SAMPLE_PROTOCOL_1_H_
#define _COMPAL_LEARNING_SAMPLE_PROTOCOL_1_H_

#define COMPAL_LEARNING_SAMPLE_PROTOCOL_1_GUID {0x755B6596, 0x6896, 0x4BA3, { 0xB3, 0xDD, 0x1C, 0x62, 0x9F, 0xD1, 0xEA, 0x88}}

typedef struct _COMPAL_LEARNING_SAMPLE_PROTOCOL_1 COMPAL_LEARNING_SAMPLE_PROTOCOL_1;

struct _COMPAL_LEARNING_SAMPLE_PROTOCOL_1 {
    CHAR8 Name[50];
    UINT8 Age;
    UINT8 Height;
    UINT8 Weight;
};

extern EFI_GUID gCompalLearningSampleProtocol1;
#endif //_COMPAL_LEARNING_SAMPLE_PROTOCOL_1_H_