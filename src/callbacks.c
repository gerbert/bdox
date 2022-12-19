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
    uint8_t buffer[11];

    os_ClrLCD();
    memset(buffer, 0, ARRAY_SZ(buffer));

    os_SetCursorPos(0, 0);
    os_GetStringInput("Decimal:", (char *)buffer, ARRAY_SZ(buffer));
    os_SetCursorPos(1, 0);

    ret = (uint64_t)strtoll((const char *)buffer, NULL, 10);
    if (ret <= UINT32_MAX)
        printf("Hexadecimal: 0x%llX", ret);
    else
        printf("Error: integer overflow");
}
