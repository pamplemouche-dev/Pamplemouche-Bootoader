#include <efi.h>

// Signature pour le compilateur (Convention d'appel Microsoft x64)
EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    // 1. Initialisation de l'accès à la console
    SystemTable->ConOut->Reset(SystemTable->ConOut, FALSE);

    // 2. Message de test "Radical"
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"RadicalBoot v0.1 - Toshiba C850\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Initialisation du pont CPU... OK\r\n");

    // 3. Boucle infinie pour éviter de rebooter immédiatement
    while(1) { }

    return EFI_SUCCESS;
}
