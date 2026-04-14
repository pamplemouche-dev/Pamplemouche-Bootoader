#include "efi.h"

// Liaison avec gui.c et patcher.c
extern void SetDeepBlack(EFI_SYSTEM_TABLE *ST);
extern void PatchHardware(EFI_SYSTEM_TABLE *ST);

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST) {
    // 1. Fond d'écran noir (Flow)
    SetDeepBlack(ST);

    // 2. Identification Hardware (Ivy Bridge)
    PatchHardware(ST);

    // 3. Message de succès
    ST->ConOut->OutputString(ST->ConOut, L"RADICAL BOOT 1.0 - STATUS: READY\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"Target: macOS Tahoe (Toshiba C850)\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"\r\nPress any key to jump to kernel...\r\n");

    // Attente utilisateur
    uint64_t index;
    ST->BootServices->WaitForEvent(1, &ST->ConIn->WaitForKey, &index);

    return EFI_SUCCESS;
}
