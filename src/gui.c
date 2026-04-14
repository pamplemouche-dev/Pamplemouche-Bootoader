#include "efi.h"

void DrawSelector(EFI_SYSTEM_TABLE *ST, int OptionIndex) {
    // On efface la zone précédente et on dessine un curseur ">"
    // Dans une version 2.0, on dessinerait un rectangle bleu translucide (GOP)
    ST->ConOut->OutputString(ST->ConOut, L"\rSelection: ");
    if (OptionIndex == 0) ST->ConOut->OutputString(ST->ConOut, L"[ > macOS Tahoe ]   Recovery     Reset  ");
    if (OptionIndex == 1) ST->ConOut->OutputString(ST->ConOut, L"[   macOS Tahoe ] > Recovery     Reset  ");
    if (OptionIndex == 2) ST->ConOut->OutputString(ST->ConOut, L"[   macOS Tahoe ]   Recovery   > Reset  ");
}
