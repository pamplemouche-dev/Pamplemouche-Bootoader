#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "efi.h"

// GUID pour le protocole File System
static uint8_t fs_guid[16] = {0xad, 0xbb, 0x22, 0x96, 0x27, 0x21, 0x11, 0xd2, 0x8e, 0x35, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b};

typedef struct _EFI_FILE_PROTOCOL {
    uint64_t Revision;
    EFI_STATUS (EFIAPI *Open)(struct _EFI_FILE_PROTOCOL *This, struct _EFI_FILE_PROTOCOL **NewHandle, CHAR16 *FileName, uint64_t OpenMode, uint64_t Attributes);
    EFI_STATUS (EFIAPI *Close)(struct _EFI_FILE_PROTOCOL *This);
    void* Delete;
    EFI_STATUS (EFIAPI *Read)(struct _EFI_FILE_PROTOCOL *This, uint64_t *BufferSize, void *Buffer);
    void* Write;
    void* GetPosition;
    void* SetPosition;
    void* GetInfo;
    void* SetInfo;
    void* Flush;
} EFI_FILE_PROTOCOL;

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
    uint64_t Revision;
    EFI_STATUS (EFIAPI *OpenVolume)(struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This, EFI_FILE_PROTOCOL **Root);
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

#endif
