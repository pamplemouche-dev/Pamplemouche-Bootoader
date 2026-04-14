#ifndef EFI_H
#define EFI_H

#include <stdint.h>
#include <stddef.h>

#define EFIAPI __attribute__((ms_abi))
#define NULL ((void *)0)

typedef void* EFI_HANDLE;
typedef uint64_t EFI_STATUS;
typedef uint16_t CHAR16;
#define EFI_SUCCESS 0

// Clavier
typedef struct { uint16_t ScanCode; CHAR16 UnicodeChar; } EFI_INPUT_KEY;

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    void* Reset;
    EFI_STATUS (EFIAPI *ReadKeyStroke)(struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, EFI_INPUT_KEY *Key);
    void* WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

// Graphismes
typedef enum { EfiBltVideoFill } EFI_GRAPHICS_OUTPUT_BLT_OPERATION;
typedef struct { uint8_t B; uint8_t G; uint8_t R; uint8_t Reserved; } EFI_GRAPHICS_OUTPUT_BLT_PIXEL;
typedef struct { uint32_t Ver; uint32_t HorizontalResolution; uint32_t VerticalResolution; uint32_t Format; uint32_t Info[4]; uint32_t PixelsPerScanLine; } EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct {
    uint32_t MaxMode; uint32_t Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    uint64_t Size; uint64_t FrameBufferBase; uint64_t FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL {
    void* QueryMode; void* SetMode;
    EFI_STATUS (EFIAPI *Blt)(struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *This, EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Buffer, EFI_GRAPHICS_OUTPUT_BLT_OPERATION Operation, uint64_t SX, uint64_t SY, uint64_t DX, uint64_t DY, uint64_t W, uint64_t H, uint64_t Delta);
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;

// Boot Services
typedef struct {
    char Sig[8]; uint32_t Rev; uint32_t Hdr; uint32_t CRC; uint32_t Res;
    void* _p1[2];
    EFI_STATUS (EFIAPI *AllocatePages)(uint32_t, uint32_t, uint64_t, void**);
    void* _p2[2];
    EFI_STATUS (EFIAPI *GetMemoryMap)(uint64_t*, void*, uint64_t*, uint64_t*, uint32_t*);
    void* _p3[7];
    EFI_STATUS (EFIAPI *WaitForEvent)(uint32_t, void**, uint64_t*);
    void* _p4[12];
    EFI_STATUS (EFIAPI *ExitBootServices)(EFI_HANDLE, uint64_t);
    void* _p5[10];
    EFI_STATUS (EFIAPI *LocateProtocol)(void*, void*, void**);
} EFI_BOOT_SERVICES;

typedef struct {
    char Sig[8]; uint32_t Rev; uint32_t Hdr; uint32_t CRC; uint32_t Res;
    EFI_HANDLE InH; EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    EFI_HANDLE OutH; void* ConOut; // On peut simplifier ConOut pour le boot
    void* Runtime; EFI_BOOT_SERVICES *BootServices;
    uint64_t TableEntries; void* ConfigTable;
} EFI_SYSTEM_TABLE;

#endif
