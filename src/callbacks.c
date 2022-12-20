#include <ti/screen.h>
#include <ti/getkey.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "callbacks.h"
#include "main.h"

void dec2hex(void __attribute__ ((unused)) *value) {
    /*
     * Even though the value is 64 bit unsigned integer, we're
     * going to operate only 32 bit unsigned integer. It's done
     * intentionally to protect ourselves from value overloading.
     */
    uint64_t ret = 0;
    char buffer[11];
    char *ptr = &buffer[0];
    uint8_t num = 0;
    uint16_t key = 0;

    os_ClrLCD();
    memset(buffer, '\0', ARRAY_SZ(buffer));
    os_SetCursorPos(0, 0);

    os_EnableCursor();
    while ((key = os_GetKey()) != k_Enter) {
        if (key == k_Quit) {
            os_DisableCursor();
            return;
        } else if (key == k_Clear) {
            os_ClrLCD();
            memset(buffer, '\0', ARRAY_SZ(buffer));
            os_SetCursorPos(0, 0);

            ptr = &buffer[0];
            continue;
        }

        if ((key >= k_0) && (key <= k_9)) {
            num = get_numeric(key);

            if ((size_t)(ptr - buffer) < ARRAY_SZ(buffer)) {
                printf("%c", num);
                memcpy((void *)(ptr++), (void *)&num, 1);
            } else {
                continue;
            }
        }
    }
    os_DisableCursor();

    os_SetCursorPos(1, 0);
    ptr = &buffer[0];
    ret = (uint64_t)strtoll(ptr, NULL, 10);
    if (ret <= UINT32_MAX)
        printf("0x%llX", ret);
    else
        printf("Error: Integer overflow");

    if (os_GetKey() == k_Quit)
        return;

    // Return back
    dec2hex(value);
}

void hex2dec(void __attribute__ ((unused)) *value) {
    return;
}