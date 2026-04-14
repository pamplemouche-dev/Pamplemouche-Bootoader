#include "efi.h"

uint16_t GetKey(EFI_SYSTEM_TABLE *ST) {
    uint64_t index;
    EFI_INPUT_KEY key = {0};
    
    // Correction du cast pour WaitForEvent
    ST->BootServices->WaitForEvent(1, (void**)&ST->ConIn->WaitForKey, &index);
    ST->ConIn->ReadKeyStroke(ST->ConIn, &key);
    
    return key.ScanCode;
}
