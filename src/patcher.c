#include "efi.h"

typedef struct {
    uint8_t  Guid[16];
    void    *VendorTable;
} EFI_CONFIGURATION_TABLE;

void PatchHardware(EFI_SYSTEM_TABLE *ST) {
    if (ST == NULL) return;
    
    static uint8_t acpi_guid[16] = {0x71, 0xe8, 0x68, 0x88, 0xf1, 0xe4, 0xd3, 0x11, 0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81};
    EFI_CONFIGURATION_TABLE *Table = (EFI_CONFIGURATION_TABLE *)ST->ConfigurationTable;

    for (uint64_t i = 0; i < ST->NumberOfTableEntries; i++) {
        int match = 1;
        for (int j = 0; j < 16; j++) {
            if (((uint8_t*)&Table[i].Guid)[j] != acpi_guid[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            ST->ConOut->OutputString(ST->ConOut, L"ACPI RSDP Located.\r\n");
            return;
        }
    }
}
