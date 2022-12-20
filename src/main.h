#ifndef SRC_MAIN_H
#define SRC_MAIN_H

#include <ti/getkey.h>
#include "callbacks.h"

#define ARRAY_SZ(x)         (sizeof(x) / sizeof(x[0]))

typedef struct {
    const char *name;
    void (*cb)(void *data);
} mItem;

static const mItem __menu_items[] = {
        {
                .name = "1. Dec->Hex",
                .cb = dec2hex
        },
        {
                .name = "2. Hex->Dec",
                .cb = hex2dec
        }
};

uint8_t get_numeric(uint16_t key);

#endif /* SRC_MAIN_H */
