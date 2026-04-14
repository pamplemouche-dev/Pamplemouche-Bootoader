#include "efi.h"

// Déclarations externes pour le Linker
extern void SetDeepBlack(EFI_SYSTEM_TABLE *ST);
extern void PatchHardware(EFI_SYSTEM_TABLE *ST);

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST) {
    // 1. Initialisation Graphique
    SetDeepBlack(ST);

    // 2. Patching ACPI / SMBIOS
    PatchHardware(ST);

    // 3. Interface Flow
    ST->ConOut->OutputString(ST->ConOut, L"====================================\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"   RADICAL BOOT - FLOW INTERFACE    \r\n");
    ST->ConOut->OutputString(ST->ConOut, L"====================================\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"Status: Ready for macOS Tahoe\r\n\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"Press any key to initiate kernel jump...\r\n");

    // Boucle d'attente
    uint64_t index;
    ST->BootServices->WaitForEvent(1, &ST->ConIn->WaitForKey, &index);

    return EFI_SUCCESS;
}
