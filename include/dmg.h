#ifndef DMG_H
#define DMG_H

#include "efi.h"

// macOS utilise souvent le format HFS+ ou APFS dans les DMG.
// On définit ici la signature pour localiser le début de l'image.
#define DMG_SIG 0x6b6f6c79 // 'koly' en ASCII

typedef struct {
    char     Signature[4];
    uint32_t Version;
    uint32_t HeaderSize;
    uint64_t DataForkOffset;
    uint64_t DataForkLength;
    // ... autres champs du header DMG
} dmg_header;

#endif
