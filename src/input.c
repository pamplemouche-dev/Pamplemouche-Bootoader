#include "efi.h"

uint16_t GetKey(EFI_SYSTEM_TABLE *ST) {
    uint64_t index;
    EFI_INPUT_KEY key; // On déclare la structure locale
    
    // Attendre l'appui
    ST->BootServices->WaitForEvent(1, &ST->ConIn->WaitForKey, &index);
    
    // Lire la touche
    ST->ConIn->ReadKeyStroke(ST->ConIn, &key);
    
    return key.ScanCode;
}
