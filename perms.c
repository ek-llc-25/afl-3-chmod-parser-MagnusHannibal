#include "perms.h"
#include <stddef.h>

// TODO: Den her funktion virker kun for en utrolig begrænset mængde input (u-r)
//
// Den skulle også gerne virke for:
// - u, g, o
// - + og -
// - r, w, x, rw, rx, wx, rwx (eller en anden rækkefølge af dem)
bool chmod(const char *input, struct perms_t *perms) {
    if (input == NULL || perms == NULL) {
        return false;
    }

    char who = input[0];
    if (who != 'u' && who != 'g' && who != 'o' && who != 'a') {
        return false;
    }

    char op = input[1];
    if (op != '+' && op != '-') {
        return false;
    }

    int i = 2;
    bool has_r = false, has_w = false, has_x = false;

    if (input[i] == '\0') {
        return false;
    }

    while (input[i] != '\0') {
        if (input[i] == 'r') {
            has_r = true;
        } else if (input[i] == 'w') {
            has_w = true;
        } else if (input[i] == 'x') {
            has_x = true;
        } else {
            return false; // invalid character
        }
        i++;
    }
    // Når man AND'er med en maske med 0'er i, slukker man for enkelte bits
    // Når man OR'er med en maske med 1'er i, tænder man for enkelte bits

    // Hvis OTHER_READ er 0b000'000'100
    // så er ~OTHER_READ  0b111'111'011
    //
    // Eksempel:
    // 0644 og o-r giver 0640
    // og når man &'er med den maske, bliver den mindste bit sat til 0, og de resterende bits forbliver som de er.

    uint32_t mask = 0;

    if (who == 'u' || who == 'a') {
        if (has_r) mask |= USER_READ;
        if (has_w) mask |= USER_WRITE;
        if (has_x) mask |= USER_EXECUTE;
    }
    if (who == 'g' || who == 'a') {
        if (has_r) mask |= GROUP_READ;
        if (has_w) mask |= GROUP_WRITE;
        if (has_x) mask |= GROUP_EXECUTE;
    }
    if (who == 'o' || who == 'a') {
        if (has_r) mask |= OTHER_READ;
        if (has_w) mask |= OTHER_WRITE;
        if (has_x) mask |= OTHER_EXECUTE;
    }

    // Step 5: Apply operation
    if (op == '+') {
        perms->bits |= mask;  // Turn bits ON
    } else { // op == '-'
        perms->bits &= ~mask; // Turn bits OFF
    }

    return true;
}
