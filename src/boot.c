#include "efi.h"
#include "bootargs.h"

EFI_STATUS FinalBootStrap(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST, void* KernelEntry, boot_args *Args) {
    uint64_t MapSize = 0;
    void* Map = 0;
    uint64_t MapKey, DescriptorSize;
    uint32_t DescriptorVersion;

    // 1. Récupérer la Memory Map finale
    ST->BootServices->LocateProtocol(0, 0, 0); // Placeholder pour s'assurer que tout est chargé
    ST->BootServices->GetMemoryMap(&MapSize, NULL, &MapKey, &DescriptorSize, &DescriptorVersion);
    
    // 2. Tuer les services UEFI
    EFI_STATUS Status = ST->BootServices->ExitBootServices(ImageHandle, MapKey);
    
    if (Status != EFI_SUCCESS) {
        // Si ça échoue, on a un problème de timing (souvent sur les vieux BIOS)
        return Status; 
    }

    // 3. Sauter dans le Kernel (Le point de non-retour)
    void (*EntryPoint)(boot_args*) = (void (*)(boot_args*))KernelEntry;
    EntryPoint(Args);

    return EFI_SUCCESS; // On n'arrive jamais ici si ça marche
}
