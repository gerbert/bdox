#include <ti/screen.h>
#include <ti/getkey.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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

/**
 * Get the number of characters for a particular mode.
 *
 * @param mode system mode
 * @return maximum number of input characters
 */
static uint8_t get_length(t_mode mode) {
    switch (mode) {
        case MODE_DEC_HEX ... MODE_DEC_BIN:
        case MODE_OCT_DEC ... MODE_OCT_BIN:
            return 10;
            break;
        case MODE_HEX_DEC ... MODE_HEX_BIN:
            return 8;
            break;
        default:
            return 0;
            break;
    }
}

/**
 * Print header based on selected numerical system mode
 *
 * @param mode system mode
 */
static void p_header(t_mode mode) {
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
        case MODE_HEX_OCT:
            print_header("16 > 8");
            break;
        case MODE_OCT_DEC:
            print_header("8 > 10");
            break;
        case MODE_OCT_HEX:
            print_header("8 > 16");
            break;
        case MODE_OCT_BIN:
            print_header("8 > 2");
            break;
    }
}

/**
 * Allocate a memory region for a particular conversion mode
 *
 * @param length a number of characters
 * @return a pointer to allocated memory region or NULL
 */
static char *p_alloc(uint8_t length) {
    if (length > UINT32_WIDTH)
        return NULL;

    char *p = (char *)malloc(sizeof(char) * length);
    if (p == NULL) {
        printf("Memory allocation error");
        return NULL;
    }

    memset(p, 0, sizeof(char) * length);
    return p;
}

/**
 * Get user input and parse it in accordance to the selected conversion mode
 *
 * @param mode system mode
 * @return input buffer
 */
static char *get_input(t_mode mode) {
    uint8_t num = 0;
    uint16_t key;
    uint8_t length = get_length(mode);
    bool k_valid = false;

    char *buffer = p_alloc(length);
    if (buffer == NULL)
        return NULL;
    char *ptr = &buffer[0];

    os_ClrLCD();
    p_header(mode);
    os_SetCursorPos(0, 0);

    os_EnableCursor();
    while ((key = os_GetKey()) != k_Enter) {
        if (key == k_Quit) {
            os_DisableCursor();
            free(buffer);
            return NULL;
        } else if (key == k_Clear) {
            os_ClrLCD();
            memset(buffer, 0, sizeof(char) * length);
            os_SetCursorPos(0, 0);

            ptr = &buffer[0];
            continue;
        }

        switch (mode) {
            case MODE_DEC_HEX ... MODE_DEC_BIN:
                if ((key >= k_0) && (key <= k_9)) {
                    num = get_numeric(key);
                    k_valid = true;
                }
                break;
            case MODE_HEX_DEC ... MODE_HEX_BIN:
                if (((key >= k_0) && (key <= k_9)) ||
                    ((key >= k_CapA) && (key <= k_CapF))) {
                    num = get_numeric(key);
                    k_valid = true;
                }
                break;
            case MODE_OCT_DEC ... MODE_OCT_BIN:
                if ((key >= k_0) && (key <= k_7)) {
                    num = get_numeric(key);
                    k_valid = true;
                }
                break;
            default:
                break;
        }

        if (k_valid) {
            if ((size_t)(ptr - buffer) < length) {
                printf("%c", num);
                memcpy((void *)(ptr++), (void *)&num, 1);
            }

            k_valid = false;
        }
    }
    os_DisableCursor();
    return buffer;
}

/**
 * Perform the conversion and print the result
 * @param value
 */
void convert(t_mode mode) {
    /*
     * Even though the value is 64 bit unsigned integer, we're
     * going to operate only 32 bit unsigned integer. It's done
     * intentionally to protect ourselves from value overloading.
     */
    uint64_t ret;
    char *ptr;

    ptr = get_input(mode);
    os_SetCursorPos(1, 0);
    if (ptr == NULL)
        return;

    switch (mode) {
        case MODE_DEC_HEX ... MODE_DEC_BIN:
            ret = (uint64_t)strtoll(ptr, NULL, 10);
            break;
        case MODE_HEX_DEC ... MODE_HEX_BIN:
            ret = (uint64_t)strtoll(ptr, NULL, 16);
            break;
        case MODE_OCT_DEC ... MODE_OCT_BIN:
            ret = (uint64_t)strtoll(ptr, NULL, 8);
            break;
    }

    free(ptr);

    if (ret <= UINT32_MAX) {
        switch (mode) {
            case MODE_DEC_HEX:
            case MODE_OCT_HEX:
                printf("0x%llX", ret);
                break;
            case MODE_DEC_BIN:
            case MODE_HEX_BIN:
            case MODE_OCT_BIN:
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
            case MODE_HEX_OCT:
                printf("%llo", ret);
                break;
            case MODE_HEX_DEC:
            case MODE_OCT_DEC:
                printf("%lld", ret);
                break;
        }
    } else {
        printf("Error: Integer overflow");
    }

    if (os_GetKey() == k_Quit)
        return;

    // Return back
    convert(mode);
}
