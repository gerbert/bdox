#ifndef SRC_MAIN_H
#define SRC_MAIN_H

#include <ti/getkey.h>
#include "callbacks.h"

#define ARRAY_SZ(x)         (sizeof(x) / sizeof(x[0]))

typedef struct {
    const char *name;
    t_mode mode;
    void (*cb)(void *data);
} mItem;

static const mItem __menu_items[] = {
        {
                .name = "1. Dec->Hex",
                .mode = MODE_DEC_HEX,
                .cb = convert
        },
        {
                .name = "2. Dec->Bin",
                .mode = MODE_DEC_BIN,
                .cb = convert
        },
        {
                .name = "3. Dec->Oct",
                .mode = MODE_DEC_OCT,
                .cb = convert
        },
        {
                .name = "4. Hex->Dec",
                .mode = MODE_HEX_DEC,
                .cb = convert
        },
        {
                .name = "5. Hex->Bin",
                .mode = MODE_HEX_BIN,
                .cb = convert
        }
};

uint8_t get_numeric(uint16_t key);

#endif /* SRC_MAIN_H */
