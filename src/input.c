#include "efi.h"

int GetKey(EFI_SYSTEM_TABLE *ST) {
    EFI_INPUT_KEY Key;
    unsigned long long index;
    
    // Attend qu'une touche soit pressée
    ST->BootServices->WaitForEvent(1, &ST->ConIn->WaitForKey, &index);
    ST->ConIn->ReadKeyStroke(ST->ConIn, &Key);
    
    return Key.ScanCode;
}
