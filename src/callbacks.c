#include <ti/screen.h>
#include <ti/getkey.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "callbacks.h"
#include "main.h"

typedef enum {
    MODE_DEC_HEX = 0,
    MODE_HEX_DEC,
    /* SENTINEL */
    MODE_MAX
} t_mode;

static char *get_input(t_mode mode, size_t sz) {
    uint8_t num = 0;
    uint16_t key = 0;

    if (sz > 33)
        return NULL;

    char *buffer = (char *) malloc(sizeof(char) * sz);
    if (buffer == NULL)
        return NULL;

    memset(buffer, 0, sizeof(char) * sz);
    char *ptr = &buffer[0];

    os_ClrLCD();
    os_SetCursorPos(0, 0);

    os_EnableCursor();
    while ((key = os_GetKey()) != k_Enter) {
        if (key == k_Quit) {
            os_DisableCursor();
            return NULL;
        } else if (key == k_Clear) {
            os_ClrLCD();
            memset(buffer, 0, sizeof(char) * sz);
            os_SetCursorPos(0, 0);

            ptr = &buffer[0];
            continue;
        }

        switch (mode) {
            case MODE_DEC_HEX:
                if ((key >= k_0) && (key <= k_9)) {
                    num = get_numeric(key);

                    if ((size_t)(ptr - buffer) < 11) {
                        printf("%c", num);
                        memcpy((void *)(ptr++), (void *)&num, 1);
                    } else {
                        continue;
                    }
                }
                break;
            default:
                break;
        }
    }
    os_DisableCursor();
    return buffer;
}

void dec2hex(void __attribute__ ((unused)) *value) {
    /*
     * Even though the value is 64 bit unsigned integer, we're
     * going to operate only 32 bit unsigned integer. It's done
     * intentionally to protect ourselves from value overloading.
     */
    uint64_t ret = 0;
    char *ptr = get_input(MODE_DEC_HEX, 11);
    os_SetCursorPos(1, 0);

    if (ptr == NULL) {
        printf("Failed to convert a value");
        return;
    }

    ret = (uint64_t)strtoll(ptr, NULL, 10);
    if (ret <= UINT32_MAX)
        printf("0x%llX", ret);
    else
        printf("Error: Integer overflow");

    if (os_GetKey() == k_Quit) {
        free(ptr);
        return;
    }

    free(ptr);
    // Return back
    dec2hex(value);
}

void hex2dec(void __attribute__ ((unused)) *value) {
    return;
}