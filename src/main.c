#include "efi.h"

// Déclarations
extern void SetDeepBlack(EFI_SYSTEM_TABLE *ST);
extern void PatchHardware(EFI_SYSTEM_TABLE *ST);

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST) {
    // 1. Graphismes
    SetDeepBlack(ST);
    
    // 2. Patch Ivy Bridge
    PatchHardware(ST);

    // 3. Texte Flow
    ST->ConOut->OutputString(ST->ConOut, L"RADICAL BOOT - FLOW UI\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"Ready for macOS Tahoe Recovery\r\n\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"Press any key to boot...\r\n");

    // Attente
    uint64_t index;
    ST->BootServices->WaitForEvent(1, &ST->ConIn->WaitForKey, &index);
    
    return EFI_SUCCESS;
}
