#ifndef EFI_H
#define EFI_H

#include <stdint.h>

#define EFIAPI __attribute__((ms_abi))
#define IN
#define OUT

typedef void* EFI_HANDLE;
typedef uint64_t EFI_STATUS;
typedef uint16_t CHAR16;

#define EFI_SUCCESS 0

// Protocole Sortie Texte
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    void* Reset;
    EFI_STATUS (EFIAPI *OutputString)(struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, const CHAR16 *String);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// Protocole Entrée Texte
typedef struct {
    uint16_t ScanCode;
    CHAR16   UnicodeChar;
} EFI_INPUT_KEY;

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    void* Reset;
    EFI_STATUS (EFIAPI *ReadKeyStroke)(struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, EFI_INPUT_KEY *Key);
    void* WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

// Protocole Graphique (GOP)
typedef struct {
    uint32_t Blue;
    uint32_t Green;
    uint32_t Red;
    uint32_t Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef enum { EfiBltVideoFill, EfiBltVideoToBltBuffer, EfiBltBufferToVideo, EfiBltVideoToVideo, EfiGraphicsOutputBltMax } EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL {
    void* QueryMode;
    void* SetMode;
    EFI_STATUS (EFIAPI *Blt)(struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *This, EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer, EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation, uint64_t SourceX, uint64_t SourceY, uint64_t DestinationX, uint64_t DestinationY, uint64_t Width, uint64_t Height, uint64_t Delta);
    struct { uint32_t MaxMode; uint32_t Mode; void* Info; uint64_t Size; uint64_t FrameBufferBase; uint64_t FrameBufferSize; } *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;

// Table Système
typedef struct {
    char Signature[8];
    uint32_t Revision;
    uint32_t HeaderSize;
    uint32_t CRC32;
    uint32_t Reserved;
    EFI_HANDLE ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    void* RuntimeServices;
    struct {
        char Signature[8];
        void* Reserved[22];
        EFI_STATUS (EFIAPI *WaitForEvent)(uint32_t NumberOfEvents, void **Event, uint64_t *Index);
        EFI_STATUS (EFIAPI *LocateProtocol)(void *Protocol, void *Registration, void **Interface);
    } *BootServices;
} EFI_SYSTEM_TABLE;

#endif
