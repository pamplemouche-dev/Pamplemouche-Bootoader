#ifndef EFI_H
#define EFI_H

#include <stdint.h>

#define EFIAPI __attribute__((ms_abi))
#define NULL ((void *)0)

typedef void* EFI_HANDLE;
typedef uint64_t EFI_STATUS;
typedef uint16_t CHAR16;
#define EFI_SUCCESS 0

// --- STRUCTURES DE BASE ---
typedef struct {
    uint16_t ScanCode;
    CHAR16   UnicodeChar;
} EFI_INPUT_KEY;

// --- PROTOCOLES ---
typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    void* Reset;
    EFI_STATUS (EFIAPI *ReadKeyStroke)(struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, EFI_INPUT_KEY *Key);
    void* WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    void* Reset;
    EFI_STATUS (EFIAPI *OutputString)(struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, const CHAR16 *String);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// --- GRAPHISMES (GOP) ---
typedef struct {
    uint32_t Blue; uint32_t Green; uint32_t Red; uint32_t Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef struct {
    uint32_t Version; uint32_t HorizontalResolution; uint32_t VerticalResolution;
    int PixelFormat; uint32_t PixelInformation[4]; uint32_t PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct {
    uint32_t MaxMode; uint32_t Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    uint64_t Size; uint64_t FrameBufferBase; uint64_t FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL {
    void* QueryMode;
    void* SetMode;
    EFI_STATUS (EFIAPI *Blt)(struct _EFI_GRAPHICS_OUTPUT_PROTOCOL *This, EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer, uint32_t Operation, uint64_t SX, uint64_t SY, uint64_t DX, uint64_t DY, uint64_t W, uint64_t H, uint64_t Delta);
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;

// --- BOOT SERVICES (L'endroit où ça bloquait) ---
typedef struct {
    char Signature[8]; uint32_t Revision; uint32_t HeaderSize; uint32_t CRC32; uint32_t Reserved;
    void* RaiseTPL; void* RestoreTPL;
    
    // Services de mémoire
    EFI_STATUS (EFIAPI *AllocatePages)(uint32_t Type, uint32_t MemoryType, uint64_t Pages, void **Memory);
    void* FreePages;
    EFI_STATUS (EFIAPI *GetMemoryMap)(uint64_t *Size, void *Map, uint64_t *Key, uint64_t *DescSize, uint32_t *DescVer);
    void* AllocatePool; void* FreePool;

    // Services d'événements
    void* CreateEvent; void* SetTimer;
    EFI_STATUS (EFIAPI *WaitForEvent)(uint32_t Num, void **Event, uint64_t *Index);
    void* SignalEvent; void* CloseEvent; void* CheckEvent;

    // Services de protocoles
    void* InstallProtocol; void* ReinstallProtocol; void* UninstallProtocol;
    void* HandleProtocol; void* PHandleProtocol; void* RegisterProtocolNotify;
    void* LocateHandle; void* LocateDevicePath; void* InstallConfigTable;

    // Services d'image
    void* LoadImage; void* StartImage; void* Exit; void* UnloadImage;
    EFI_STATUS (EFIAPI *ExitBootServices)(EFI_HANDLE Image, uint64_t Key);

    // Services divers
    void* GetNextMonotonicCount; void* Stall; void* SetWatchdogTimer;
    void* ConnectController; void* DisconnectController; void* OpenProtocol;
    void* CloseProtocol; void* OpenProtocolInfo; void* ProtocolsPerHandle;
    void* LocateHandleBuffer;
    EFI_STATUS (EFIAPI *LocateProtocol)(void *Protocol, void *Registration, void **Interface);
} EFI_BOOT_SERVICES;

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
