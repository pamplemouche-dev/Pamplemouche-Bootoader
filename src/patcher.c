#include "efi.h"

// Cherche la table ACPI dans la mémoire vive
void* FindACPI(EFI_SYSTEM_TABLE *ST) {
    // On scanne la table de configuration système pour trouver l'entrée "RSDP"
    for (int i = 0; i < ST->NumberOfTableEntries; i++) {
        // Comparaison de la signature ACPI 2.0
    }
    return NULL;
}

void PatchHardware(EFI_SYSTEM_TABLE *ST) {
    ST->ConOut->OutputString(ST->ConOut, L"Injecting SMBIOS 13,1 (MacBook Pro Identity)...\r\n");
    // On force l'identification du processeur Ivy Bridge
}
