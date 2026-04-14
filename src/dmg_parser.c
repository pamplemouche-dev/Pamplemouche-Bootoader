#include "efi.h"
#include "dmg.h"

EFI_STATUS ParseDmgTrailer(void *DmgBuffer, uint64_t DmgSize, DMG_KOLY_HEADER **OutHeader) {
    // Le header koly est à la fin du fichier
    uint8_t *Ptr = (uint8_t *)DmgBuffer + DmgSize - 512;
    DMG_KOLY_HEADER *Header = (DMG_KOLY_HEADER *)Ptr;

    // Vérification de la signature 'koly'
    if (Header->Signature != 0x696c796b) { // koly en Little Endian pour x86
        return 1; // Erreur de signature
    }

    *OutHeader = Header;
    return 0; // EFI_SUCCESS
}
