#include "efi.h"

// Pas besoin d'extern compliqués si on veut juste que ça compile
void FakeSetDeepBlack(EFI_SYSTEM_TABLE *ST) {
    if (ST && ST->ConOut) {
        ST->ConOut->OutputString(ST->ConOut, L"[+] RadicalBoot: Flow UI Active\r\n");
    }
}

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST) {
    if (!ST || !ST->ConOut) return 1;

    FakeSetDeepBlack(ST);

    ST->ConOut->OutputString(ST->ConOut, L"-----------------------------------\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"  READY TO BOOT MACOS FROM USB\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"-----------------------------------\r\n");
    ST->ConOut->OutputString(ST->ConOut, L"Press any key to jump to kernel...\r\n");

    uint64_t index;
    // On utilise ConIn directement
    ST->BootServices->WaitForEvent(1, (void**)&ST->ConIn, &index);

    return EFI_SUCCESS;
}
