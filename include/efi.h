#ifndef EFI_H
#define EFI_H

#include <stdint.h>
#include <stddef.h>

#define EFIAPI __attribute__((ms_abi))
typedef void* EFI_HANDLE;
typedef uint64_t EFI_STATUS;
typedef uint16_t CHAR16;
#define EFI_SUCCESS 0

// --- TEXT OUT ---
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    void* Reset;
    EFI_STATUS (EFIAPI *OutputString)(struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, const CHAR16 *String);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// --- BOOT SERVICES ---
typedef struct {
    char Sig[8]; uint32_t Rev; uint32_t Hdr; uint32_t CRC; uint32_t Res;
    void* _p1[16]; // On saute les fonctions inutiles pour simplifier
    EFI_STATUS (EFIAPI *WaitForEvent)(uint32_t Num, void **Event, uint64_t *Index);
    void* _p2[13];
    EFI_STATUS (EFIAPI *LocateProtocol)(void *Protocol, void *Reg, void **Interface);
} EFI_BOOT_SERVICES;

// --- SYSTEM TABLE ---
typedef struct {
    char Sig[8]; uint32_t Rev; uint32_t Hdr; uint32_t CRC; uint32_t Res;
    EFI_HANDLE ConsoleInHandle;
    void* ConIn; // Simplifié en void* pour éviter les erreurs de structure
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    void* RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    uint64_t NumberOfTableEntries;
    void* ConfigurationTable;
} EFI_SYSTEM_TABLE;

#endif
