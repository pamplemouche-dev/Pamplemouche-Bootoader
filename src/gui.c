#include "efi.h"

// Définition des couleurs Radical (Noir, Blanc, Bleu Electrique)
#define COLOR_DEEP_BLACK  0x00000000
#define COLOR_PURE_WHITE  0xFFFFFFFF
#define COLOR_GLOW_BLUE   0x0000FFFF

void FillScreen(EFI_SYSTEM_TABLE *ST, uint32_t Color) {
    void *gop_ptr;
    ST->BootServices->LocateProtocol((void*)gop_guid, 0, &gop_ptr);
    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop = (EFI_GRAPHICS_OUTPUT_PROTOCOL*)gop_ptr;

    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Pixel;
    Pixel.Reserved = 0;
    Pixel.Red = (Color >> 16) & 0xFF;
    Pixel.Green = (Color >> 8) & 0xFF;
    Pixel.Blue = Color & 0xFF;

    gop->Blt(gop, &Pixel, EfiBltVideoFill, 0, 0, 0, 0, 
             gop->Mode->Info->HorizontalResolution, 
             gop->Mode->Info->VerticalResolution, 0);
}

void DrawButton(int x, int y, int w, int h, const uint16_t* Label) {
    // Logique pour dessiner un rectangle avec du texte au milieu
    // C'est ici qu'on injecte le "Flow" visuel
}
