#include "efi.h"

uint16_t GetKey(EFI_SYSTEM_TABLE *ST) {
    uint64_t index;
    EFI_INPUT_KEY key;
    
    // Attente de l'événement clavier
    ST->BootServices->WaitForEvent(1, (void**)&ST->ConIn->WaitForKey, &index);
    
    // Lecture de la touche
    ST->ConIn->ReadKeyStroke(ST->ConIn, &key);
    
    return key.ScanCode;
}
