#ifndef DMG_H
#define DMG_H

#include <stdint.h>

// Signature "koly" (0x6b6f6c79) en Big Endian
#define DMG_KOLY_SIGNATURE 0x6b6f6c79

#pragma pack(push, 1) // Force l'alignement strict pour la lecture binaire
typedef struct {
    uint32_t Signature;          // 'koly'
    uint32_t Version;            // Actuellement 4
    uint32_t HeaderSize;         // Taille de cette structure (120 octets)
    uint32_t Flags;
    uint64_t RunningDataForkOffset;
    uint64_t DataForkOffset;     // Début des données réelles
    uint64_t DataForkLength;     // Taille des données
    uint64_t RsrcForkOffset;     // Souvent 0
    uint64_t RsrcForkLength;
    uint32_t SegmentNumber;
    uint32_t SegmentCount;
    uint8_t  SegmentID[16];

    uint32_t DataChecksumType;
    uint32_t DataChecksumSize;
    uint32_t DataChecksum[32];

    uint64_t XMLOffset;          // Emplacement de la Plist (Description des blocs)
    uint64_t XMLLength;          // Taille de la Plist
    uint8_t  Reserved1[120];     // Espace réservé
} DMG_KOLY_HEADER;
#pragma pack(pop)

// Structure pour le "Block Chunk" (Si le DMG est compressé en UDZO)
typedef struct {
    uint32_t EntryType;
    uint32_t Comment;
    uint64_t SectorOffset;
    uint64_t SectorCount;
    uint64_t CompressedOffset;
    uint64_t CompressedLength;
} DMG_BLOCK_CHUNK;

#endif
