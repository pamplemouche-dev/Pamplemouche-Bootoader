#include "efi.h"

int efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST) {
    // 1. Initialisation Hardware
    PatchHardware(ST);
    
    // 2. Initialisation UI (Le Flow)
    FillScreen(ST, COLOR_DEEP_BLACK);
    
    // 3. Boucle principale du menu
    ST->ConOut->OutputString(ST->ConOut, L"=== RADICAL BOOT SELECTOR ===\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"[1] Boot macOS Tahoe 26\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"[2] Recovery Mode\r\n");

    int choice = GetKey(ST);
    
    if (choice == 1) {
        // Logique pour charger le kernel /System/Library/Kernels/kernel
    }

    return 0;
}
