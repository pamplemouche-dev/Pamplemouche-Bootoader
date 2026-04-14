#include "efi.h"
#include "filesystem.h"

EFI_STATUS LoadFileFromDisk(EFI_SYSTEM_TABLE *ST, CHAR16 *Path, void **Buffer, uint64_t *Size) {
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem;
    EFI_FILE_PROTOCOL *Root, *File;
    EFI_STATUS Status;

    // 1. Localiser le système de fichiers sur la clé
    Status = ST->BootServices->LocateProtocol((void*)fs_guid, 0, (void**)&FileSystem);
    if (Status != EFI_SUCCESS) return Status;

    // 2. Ouvrir le volume racine
    FileSystem->OpenVolume(FileSystem, &Root);

    // 3. Ouvrir le fichier spécifié (ex: \com.apple.recovery.boot\boot.efi)
    Status = Root->Open(Root, &File, Path, 1, 0); // 1 = Mode Lecture
    if (Status != EFI_SUCCESS) return Status;

    // 4. Lire le fichier (Pour simplifier, on alloue 16Mo, à ajuster selon le Kernel)
    *Size = 16 * 1024 * 1024; 
    ST->BootServices->AllocatePages(0, 2, (*Size / 4096), Buffer); // AllocateAnyPages = 0
    Status = File->Read(File, Size, *Buffer);

    File->Close(File);
    Root->Close(Root);

    return Status;
}
