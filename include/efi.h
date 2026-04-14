#ifndef EFI_H
#define EFI_H

#include <stdint.h>

#define EFIAPI __attribute__((ms_abi)) // Convention d'appel Windows/UEFI

typedef void* EFI_HANDLE;
typedef uint64_t EFI_STATUS;

typedef struct {
    uint32_t Blue;
    uint32_t Green;
    uint32_t Red;
    uint32_t Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    void* Reset;
    EFI_STATUS (EFIAPI *OutputString)(struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, const uint16_t *String);
    void* TestString;
    // ... on ajoute les autres selon les besoins
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct {
    EFI_HANDLE ConsoleInHandle;
    void* ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    void* RuntimeServices;
    struct EFI_BOOT_SERVICES *BootServices;
} EFI_SYSTEM_TABLE;

typedef struct EFI_BOOT_SERVICES {
    char Signature[8];
    // On définit ici les fonctions pour localiser le protocole graphique (GOP)
    void* Reserved[22]; 
    EFI_STATUS (EFIAPI *LocateProtocol)(void *Protocol, void *Registration, void **Interface);
} EFI_BOOT_SERVICES;

#endif
