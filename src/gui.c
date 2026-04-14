#include "efi.h"

static uint8_t gop_guid[16] = {0xde, 0xa9, 0x42, 0x90, 0x34, 0xdc, 0x4a, 0x4a, 0x9b, 0x9e, 0x2d, 0xb7, 0x35, 0x92, 0x31, 0x5c};

void SetDeepBlack(EFI_SYSTEM_TABLE *ST) {
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop = NULL;
    ST->BootServices->LocateProtocol((void*)gop_guid, NULL, (void**)&gop);
    
    if (gop && gop->Mode && gop->Mode->Info) {
        EFI_GRAPHICS_OUTPUT_BLT_PIXEL black = {0, 0, 0, 0};
        gop->Blt(gop, &black, EfiBltVideoFill, 0, 0, 0, 0, 
                 gop->Mode->Info->HorizontalResolution, 
                 gop->Mode->Info->VerticalResolution, 0);
    }
}
