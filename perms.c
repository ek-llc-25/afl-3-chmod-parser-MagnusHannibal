#include "perms.h"

#include <stddef.h>

// TODO: Den her funktion virker kun for en utrolig begrænset mængde input (u-r)
//
// Den skulle også gerne virke for:
// - u, g, o
// - + og -
// - r, w, x, rw, rx, wx, rwx (eller en anden rækkefølge af dem)
bool chmod(const char *input, struct perms_t *perms) {
    if (input == NULL) {
        return false;
    }

    if (input[0] != 'o') {
        return false;
    }

    if (input[1] != '-') {
        return false;
    }

    if (input[2] != 'r') {
        return false;
    }

    // Når man AND'er med en maske med 0'er i, slukker man for enkelte bits
    // Når man OR'er med en maske med 1'er i, tænder man for enkelte bits

    // Hvis OTHER_READ er 0b000'000'100
    // så er ~OTHER_READ  0b111'111'011
    //
    // Eksempel:
    // 0644 og o-r giver 0640
    // og når man &'er med den maske, bliver den mindste bit sat til 0, og de resterende bits forbliver som de er.
    perms->bits &= ~OTHER_READ;
    return true;
}
