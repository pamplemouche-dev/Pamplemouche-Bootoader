#include <stdint.h>
#include <stddef.h>

// Cette fonction permet d'initialiser la mémoire manuellement
void *memset(void *s, int c, size_t n) {
    unsigned char *p = s;
    while (n--)
        *p++ = (unsigned char)c;
    return s;
}
