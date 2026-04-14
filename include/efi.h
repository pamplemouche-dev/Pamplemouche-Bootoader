#ifndef EFI_H
#define EFI_H

#include <stdint.h>

#define EFIAPI __attribute__((ms_abi))
#define NULL ((void *)0)
#define EFI_SUCCESS 0

typedef void* EFI_HANDLE;
typedef uint64_t EFI_STATUS;
typedef uint16_t CHAR16;

// --- INPUT ---
typedef struct {
    uint16_t ScanCode;
    CHAR16   UnicodeChar;
} EFI_INPUT_KEY;

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    void* Reset;
    EFI_STATUS (EFIAPI *ReadKeyStroke)(struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, EFI_INPUT_KEY *Key);
    void* WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

// --- OUTPUT ---
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    void* Reset;
    EFI_STATUS (EFIAPI *OutputString)(struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, const CHAR16 *String);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// --- GRAPHICS (GOP) ---
typedef enum {
    EfiBltVideoFill,
    EfiBltVideoToBltBuffer,
    EfiBltBufferToVideo,
    EfiBltVideoToVideo,
    EfiGraphicsOutputBltMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

typedef struct {
    uint8_t Blue; uint8_t Green; uint8_t Red; uint8_t Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef struct {
    uint32_t Version; uint32_t HorizontalResolution; uint32_t VerticalResolution;
    uint32_t PixelFormat; uint32_t PixelInformation[4]; uint32_t PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct {
    uint32_t MaxMode; uint32_t Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    uint64_t Size; uint64_t FrameBufferBase; uint64_t FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL {
    void* QueryMode;
    void* SetMode;
    EFI_STATUS (EFIAPI *Blt)(struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *This, EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer, EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation, uint64_t SX, uint64_t SY, uint64_t DX, uint64_t DY, uint64_t W, uint64_t H, uint64_t Delta);
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;

// --- BOOT SERVICES ---
typedef struct {
    char Signature[8]; uint32_t Revision; uint32_t HeaderSize; uint32_t CRC32; uint32_t Reserved;
    void* _pad[2];
    EFI_STATUS (EFIAPI *AllocatePages)(uint32_t Type, uint32_t MemoryType, uint64_t Pages, void **Memory);
    void* FreePages;
    EFI_STATUS (EFIAPI *GetMemoryMap)(uint64_t *Size, void *Map, uint64_t *Key, uint64_t *DescSize, uint32_t *DescVer);
    void* _pad2[2];
    void* _pad3[5];
    EFI_STATUS (EFIAPI *WaitForEvent)(uint32_t Num, void **Event, uint64_t *Index);
    void* _pad4[8];
    void* _pad5[4];
    EFI_STATUS (EFIAPI *ExitBootServices)(EFI_HANDLE Image, uint64_t Key);
    void* _pad6[10];
    EFI_STATUS (EFIAPI *LocateProtocol)(void *Protocol, void *Reg, void **Interface);
} EFI_BOOT_SERVICES;

// --- SYSTEM TABLE ---
typedef struct {
    char Signature[8]; uint32_t Revision; uint32_t HeaderSize; uint32_t CRC32; uint32_t Reserved;
    EFI_HANDLE ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    void* RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    uint64_t NumberOfTableEntries;
    void* ConfigurationTable;
} EFI_SYSTEM_TABLE;

#endif
