#include "efi.h"

// GUID du protocole graphique
static const uint8_t gop_guid[16] = {0xde, 0xa9, 0x42, 0x90, 0x34, 0xdc, 0x4a, 0x4a, 0x9b, 0x9e, 0x2d, 0xb7, 0x35, 0x92, 0x31, 0x5c};

void DrawBackground(EFI_SYSTEM_TABLE *ST) {
    void *gop_ptr;
    // On localise la carte graphique
    ST->BootServices->LocateProtocol((void*)gop_guid, 0, &gop_ptr);
    
    // Ici on ajouterait la logique pour remplir l'écran en noir "Deep Black"
    // Pour l'instant on utilise le texte pour simuler l'UI
    ST->ConOut->OutputString(ST->ConOut, L"[ RadicalBoot UI Loaded ]\r\n");
}

void DrawMenu(EFI_SYSTEM_TABLE *ST) {
    ST->ConOut->OutputString(ST->ConOut, L"1. macOS Tahoe (Recovery)\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"2. NVRAM Reset\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"3. Shell\r\n");
}
