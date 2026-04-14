#ifndef EFI_H
#define EFI_H

#include <stdint.h>
#include <stddef.h> // Utilise le NULL standard pour éviter les warnings

#define EFIAPI __attribute__((ms_abi))
typedef void* EFI_HANDLE;
typedef uint64_t EFI_STATUS;
typedef uint16_t CHAR16;
#define EFI_SUCCESS 0

// --- SYSTÈME DE SORTIE TEXTE ---
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    void* Reset;
    EFI_STATUS (EFIAPI *OutputString)(struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, const CHAR16 *String);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// --- TABLE DE CONFIGURATION ---
typedef struct {
    uint8_t  Guid[16];
    void    *VendorTable;
} EFI_CONFIGURATION_TABLE;

// --- SERVICES DE BOOT ---
typedef struct {
    char Sig[8]; uint32_t Rev; uint32_t Hdr; uint32_t CRC; uint32_t Res;
    void* _p1[2];
    void* AllocatePages;
    void* FreePages;
    void* GetMemoryMap;
    void* _p2[9];
    EFI_STATUS (EFIAPI *WaitForEvent)(uint32_t Num, void **Event, uint64_t *Index);
    void* _p3[13];
    EFI_STATUS (EFIAPI *LocateProtocol)(void *Protocol, void *Reg, void **Interface);
} EFI_BOOT_SERVICES;

// --- TABLE SYSTÈME ---
typedef struct {
    char Sig[8]; uint32_t Rev; uint32_t Hdr; uint32_t CRC; uint32_t Res;
    EFI_HANDLE ConsoleInHandle;
    void *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    void* RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    uint64_t NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE *ConfigurationTable; // Typé correctement ici
} EFI_SYSTEM_TABLE;

#endif
