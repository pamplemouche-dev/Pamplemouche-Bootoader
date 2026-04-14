#include "efi.h"
#include "bootargs.h"

// Déclarations des fonctions dans les autres fichiers .c
extern void SetDeepBlack(EFI_SYSTEM_TABLE *ST);
extern void DrawSelector(EFI_SYSTEM_TABLE *ST, int OptionIndex);
extern EFI_STATUS LoadFileFromDisk(EFI_SYSTEM_TABLE *ST, CHAR16 *Path, void **Buffer, uint64_t *Size);
extern void SetupArchitecture(boot_args *args);
extern EFI_STATUS FinalBootStrap(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST, void* KernelEntry, boot_args *Args);

void WaitKey(EFI_SYSTEM_TABLE *ST) {
    uint64_t index;
    ST->BootServices->WaitForEvent(1, &ST->ConIn->WaitForKey, &index);
    EFI_INPUT_KEY key;
    ST->ConIn->ReadKeyStroke(ST->ConIn, &key);
}

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST) {
    // 1. Initialisation UI
    SetDeepBlack(ST);
    ST->ConOut->OutputString(ST->ConOut, L"RADICAL BOOT v1.0 - Flow Enabled\r\n");

    // 2. Menu simple pour tester le rendu
    ST->ConOut->OutputString(ST->ConOut, L"Press any key to boot macOS Tahoe 26...\r\n");
    WaitKey(ST);

    // 3. Suite du boot...
    return EFI_SUCCESS;
}
