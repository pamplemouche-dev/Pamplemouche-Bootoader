#include "efi.h"
#include "bootargs.h"
#include "filesystem.h"

// Prototypes des modules qu'on a codés
extern EFI_STATUS LoadFileFromDisk(EFI_SYSTEM_TABLE *ST, CHAR16 *Path, void **Buffer, uint64_t *Size);
extern void SetupArchitecture(boot_args *args);
extern EFI_STATUS FinalBootStrap(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST, void* KernelEntry, boot_args *Args);

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST) {
    void *KernelBuffer = 0;
    uint64_t KernelSize = 0;
    boot_args Args;

    // 1. Charger le kernel de macOS Tahoe
    // Le chemin standard pour la récupération est celui-ci :
    LoadFileFromDisk(ST, L"\\com.apple.recovery.boot\\boot.efi", &KernelBuffer, &KernelSize);

    // 2. Préparer les arguments de boot
    for(int i=0; i<256; i++) Args.CommandLine[i] = 0;
    // On force le mode verbose pour voir ce qu'on fait
    char *cmd = "-v keepsyms=1 debug=0x100 -no_compat_check";
    for(int i=0; cmd[i] != 0; i++) Args.CommandLine[i] = cmd[i];

    // 3. Configurer l'identité du Mac
    SetupArchitecture(&Args);

    // 4. Lancer le système
    FinalBootStrap(ImageHandle, ST, KernelBuffer, &Args);

    return EFI_SUCCESS;
}
