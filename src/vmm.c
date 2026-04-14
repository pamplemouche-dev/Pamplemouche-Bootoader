#include "efi.h"

void PrepareMemoryMap(EFI_SYSTEM_TABLE *ST) {
    uint64_t MapSize = 0;
    void* Map = 0;
    uint64_t MapKey, DescriptorSize;
    uint32_t DescriptorVersion;

    // Récupérer la taille nécessaire
    ST->BootServices->GetMemoryMap(&MapSize, Map, &MapKey, &DescriptorSize, &DescriptorVersion);
    
    // On ajoute un peu de marge et on alloue
    MapSize += 2 * DescriptorSize;
    ST->BootServices->AllocatePages(0, 2, (MapSize / 4096) + 1, &Map);

    // Récupérer la vraie carte mémoire
    ST->BootServices->GetMemoryMap(&MapSize, Map, &MapKey, &DescriptorSize, &DescriptorVersion);

    // Ici on ferait le ExitBootServices pour couper les ponts avec le BIOS
}
