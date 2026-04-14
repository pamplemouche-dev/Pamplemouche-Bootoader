#include "efi.h"
#include "bootargs.h"
#include "filesystem.h"

extern EFI_STATUS LoadFileFromDisk(EFI_SYSTEM_TABLE *ST, CHAR16 *Path, void **Buffer, uint64_t *Size);
extern void SetDeepBlack(EFI_SYSTEM_TABLE *ST);
extern void DrawSelector(EFI_SYSTEM_TABLE *ST, int OptionIndex);

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST) {
    int SelectedOption = 0;
    EFI_INPUT_KEY Key;
    
    SetDeepBlack(ST);
    ST->ConOut->OutputString(ST->ConOut, L"RADICAL BOOT v1.0\r\n\r\n");

    // Boucle du Menu
    while (1) {
        DrawSelector(ST, SelectedOption);
        
        uint64_t index;
        ST->BootServices->WaitForEvent(1, &ST->ConIn->WaitForKey, &index);
        ST->ConIn->ReadKeyStroke(ST->ConIn, &Key);

        if (Key.ScanCode == 0x02) SelectedOption = (SelectedOption + 1) % 3; // Flèche Bas/Droite
        if (Key.UnicodeChar == L'\r') break; // Touche Entrée
    }

    // Exécution du choix
    if (SelectedOption == 0 || SelectedOption == 1) {
        ST->ConOut->OutputString(ST->ConOut, L"\nBooting macOS Tahoe 26...\r\n");
        // Appel aux fonctions de chargement DMG et Kernel qu'on a codées
    } else {
        ST->ConOut->OutputString(ST->ConOut, L"\nResetting NVRAM...\r\n");
        // ST->RuntimeServices->ResetSystem(...)
    }

    return 0;
}
