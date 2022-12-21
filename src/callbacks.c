#include <ti/screen.h>
#include <ti/getkey.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "callbacks.h"
#include "main.h"

#define DEC_TO_BINARY_PATTERN   "%c%c%c%c%c%c%c%c"
#define DEC_TO_BINARY(x)        \
    ((x & 0x80) ? '1' : '0'),   \
    ((x & 0x40) ? '1' : '0'),   \
    ((x & 0x20) ? '1' : '0'),   \
    ((x & 0x10) ? '1' : '0'),   \
    ((x & 0x08) ? '1' : '0'),   \
    ((x & 0x04) ? '1' : '0'),   \
    ((x & 0x02) ? '1' : '0'),   \
    ((x & 0x01) ? '1' : '0')

static char *get_input(t_mode mode, size_t sz) {
    uint8_t num = 0;
    uint16_t key;

    if (sz > UINT32_WIDTH)
        return NULL;

    char *buffer = (char *) malloc(sizeof(char) * sz);
    if (buffer == NULL)
        return NULL;

    memset(buffer, 0, sizeof(char) * sz);
    char *ptr = &buffer[0];

    os_ClrLCD();

    switch (mode) {
        case MODE_DEC_HEX:
            print_header("10 > 16");
            break;
        case MODE_DEC_BIN:
            print_header("10 > 2");
            break;
        case MODE_DEC_OCT:
            print_header("10 > 8");
            break;
        case MODE_HEX_DEC:
            print_header("16 > 10");
            break;
        case MODE_HEX_BIN:
            print_header("16 > 2");
            break;
    }

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
            case MODE_DEC_HEX ... MODE_DEC_BIN:
                if ((key >= k_0) && (key <= k_9)) {
                    num = get_numeric(key);

                    if ((size_t)(ptr - buffer) < sz) {
                        printf("%c", num);
                        memcpy((void *)(ptr++), (void *)&num, 1);
                    } else {
                        continue;
                    }
                }
                break;
            case MODE_HEX_DEC:
            case MODE_HEX_BIN:
                if (((key >= k_0) && (key <= k_9)) ||
                    ((key >= k_CapA) && (key <= k_CapF))) {
                    num = get_numeric(key);

                    if ((size_t)(ptr - buffer) < sz) {
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

void convert(void *value) {
    /*
     * Even though the value is 64 bit unsigned integer, we're
     * going to operate only 32 bit unsigned integer. It's done
     * intentionally to protect ourselves from value overloading.
     */
    uint64_t ret;
    t_mode mode = *(t_mode *)value;
    size_t sz = 0;
    char *ptr;

    switch (mode) {
        case MODE_DEC_HEX ... MODE_DEC_BIN:
            sz = 10;
            break;
        case MODE_HEX_DEC ... MODE_HEX_BIN:
            sz = 8;
            break;
    }

    ptr = get_input(mode, sz);
    os_SetCursorPos(1, 0);
    if (ptr == NULL) {
        printf("Failed to convert a value");
        return;
    }

    switch (mode) {
        case MODE_DEC_HEX:
        case MODE_DEC_BIN:
        case MODE_DEC_OCT:
            ret = (uint64_t)strtoll(ptr, NULL, 10);
            break;
        case MODE_HEX_DEC:
        case MODE_HEX_BIN:
            ret = (uint64_t)strtoll(ptr, NULL, 16);
            break;
    }

    if (ret <= UINT32_MAX) {
        switch (mode) {
            case MODE_DEC_HEX:
                printf("0x%llX", ret);
                break;
            case MODE_DEC_BIN:
            case MODE_HEX_BIN:
                print_t("31                                              23", 1, 63);
                os_SetCursorPos(2, 0);
                printf(DEC_TO_BINARY_PATTERN, DEC_TO_BINARY((ret >> 24) & 0xFF));
                printf(" ");
                printf(DEC_TO_BINARY_PATTERN, DEC_TO_BINARY((ret >> 16) & 0xFF));
                printf(" ");
                os_SetCursorPos(3, 0);
                print_t("15                                              7", 1, 103);
                os_SetCursorPos(4, 0);
                printf(DEC_TO_BINARY_PATTERN, DEC_TO_BINARY((ret >> 8) & 0xFF));
                printf(" ");
                printf(DEC_TO_BINARY_PATTERN, DEC_TO_BINARY(ret & 0xFF));

                break;
            case MODE_DEC_OCT:
                printf("%llo", ret);
                break;
            case MODE_HEX_DEC:
                printf("%lld", ret);
                break;
        }
    } else {
        printf("Error: Integer overflow");
    }

    if (os_GetKey() == k_Quit) {
        free(ptr);
        return;
    }

    free(ptr);
    // Return back
    convert(value);
}
