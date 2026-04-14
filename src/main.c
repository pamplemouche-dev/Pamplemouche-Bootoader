#include "efi.h"

// Déclarations externes de nos fonctions graphiques
extern void DrawBackground(EFI_SYSTEM_TABLE *ST);
extern void DrawMenu(EFI_SYSTEM_TABLE *ST);

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    // 1. Reset de la console
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Starting RadicalBoot...\r\n");

    // 2. Lancement de l'interface "Flow"
    DrawBackground(SystemTable);
    DrawMenu(SystemTable);

    // 3. Boucle d'attente de sélection (Simulée)
    // Plus tard, on codera ici la lecture du clavier
    while(1) {
        // Halt CPU or wait for key
    }

    return 0;
}
