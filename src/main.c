#include "efi.h"

extern void SetDeepBlack(EFI_SYSTEM_TABLE *ST);
extern void PatchHardware(EFI_SYSTEM_TABLE *ST);

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST) {
    if (!ST || !ST->ConOut) return 1;

    SetDeepBlack(ST);

    ST->ConOut->OutputString(ST->ConOut, L"RADICAL BOOT - FLOW UI\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"Ready for macOS Tahoe Recovery\r\n");

    // Attente simple
    uint64_t index;
    ST->BootServices->WaitForEvent(1, &ST->ConIn, &index);

    return EFI_SUCCESS;
}
