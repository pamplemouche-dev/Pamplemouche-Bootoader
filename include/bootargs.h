#ifndef BOOTARGS_H
#define BOOTARGS_H

#include <stdint.h>

typedef struct {
    uint16_t Revision;
    uint16_t Version;
    char     CommandLine[256];
    uint64_t MemoryMap;
    uint32_t MemoryMapSize;
    uint32_t MemoryMapDescriptorSize;
    uint32_t MemoryMapDescriptorVersion;
    struct {
        uint64_t BaseAddr;
        uint64_t Size;
        uint32_t Width;
        uint32_t Height;
        uint32_t PixelsPerScanLine;
    } Video;
} boot_args;

#endif
