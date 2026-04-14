#include "efi.h"
#include "bootargs.h"

// GUID GOP pour l'affichage
static uint8_t gop_guid[16] = {0xde, 0xa9, 0x42, 0x90, 0x34, 0xdc, 0x4a, 0x4a, 0x9b, 0x9e, 0x2d, 0xb7, 0x35, 0x92, 0x31, 0x5c};

void WaitKey(EFI_SYSTEM_TABLE *ST) {
    uint64_t index;
    ST->BootServices->WaitForEvent(1, &ST->ConIn->WaitForKey, &index);
    EFI_INPUT_KEY key;
    ST->ConIn->ReadKeyStroke(ST->ConIn, &key);
}

void SetDeepBlack(EFI_SYSTEM_TABLE *ST) {
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
    ST->BootServices->LocateProtocol((void*)gop_guid, 0, (void**)&gop);
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL black = {0, 0, 0, 0};
    gop->Blt(gop, &black, EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
}

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST) {
    ST->ConOut->OutputString(ST->ConOut, L"RadicalBoot Loading...\r\n");
    
    // Activer l'UI Flow
    SetDeepBlack(ST);
    
    ST->ConOut->OutputString(ST->ConOut, L"====================================\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"   RADICAL BOOT - macOS TAHOE 26    \r\n");
    ST->ConOut->OutputString(ST->ConOut, L"====================================\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"[1] Boot macOS Tahoe\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"[2] Recovery Mode\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"[3] Reset NVRAM\r\n\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"Select an option to proceed...\r\n");

    WaitKey(ST);
    
    // Logique de boot à suivre...
    return EFI_SUCCESS;
}
