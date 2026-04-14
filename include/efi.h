#ifndef EFI_H
#define EFI_H

#include <stdint.h>

#define EFIAPI __attribute__((ms_abi))
#define NULL ((void *)0)

typedef void* EFI_HANDLE;
typedef uint64_t EFI_STATUS;
typedef uint16_t CHAR16;

#define EFI_SUCCESS 0

// --- STRUCTURES GRAPHIQUES (GOP) ---
typedef struct {
    uint32_t Version;
    uint32_t HorizontalResolution;
    uint32_t VerticalResolution;
    int      PixelFormat;
    uint32_t PixelInformation[4];
    uint32_t PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct {
    uint32_t MaxMode;
    uint32_t Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    uint64_t Size;
    uint64_t FrameBufferBase;
    uint64_t FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct {
    uint32_t Blue;
    uint32_t Green;
    uint32_t Red;
    uint32_t Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef enum { EfiBltVideoFill, EfiGraphicsOutputBltMax } EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL {
    void* QueryMode;
    void* SetMode;
    EFI_STATUS (EFIAPI *Blt)(struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *This, EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer, EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation, uint64_t SourceX, uint64_t SourceY, uint64_t DestinationX, uint64_t DestinationY, uint64_t Width, uint64_t Height, uint64_t Delta);
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;

// --- SERVICES DE BOOT ---
typedef struct {
    char Signature[8];
    uint32_t Revision;
    uint32_t HeaderSize;
    uint32_t CRC32;
    uint32_t Reserved;
    void* _pad[2]; 
    void* AllocatePages;
    void* FreePages;
    void* GetMemoryMap;
    void* _pad2[9];
    EFI_STATUS (EFIAPI *WaitForEvent)(uint32_t NumberOfEvents, void **Event, uint64_t *Index);
    void* _pad3[13];
    EFI_STATUS (EFIAPI *LocateProtocol)(void *Protocol, void *Registration, void **Interface);
} EFI_BOOT_SERVICES;

// --- TABLE SYSTÈME ---
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    void* Reset;
    EFI_STATUS (EFIAPI *OutputString)(struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, const CHAR16 *String);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct {
    char Signature[8];
    uint32_t Revision;
    uint32_t HeaderSize;
    uint32_t CRC32;
    uint32_t Reserved;
    EFI_HANDLE ConsoleInHandle;
    void *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    void* RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    uint64_t NumberOfTableEntries;
    void* ConfigurationTable;
} EFI_SYSTEM_TABLE;

#endif
