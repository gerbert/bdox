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
                .name = "Dec->Hex",
                .mode = MODE_DEC_HEX,
                .cb = convert
        },
        {
                .name = "Dec->Bin",
                .mode = MODE_DEC_BIN,
                .cb = convert
        },
        {
                .name = "Dec->Oct",
                .mode = MODE_DEC_OCT,
                .cb = convert
        },
        {
                .name = "Hex->Dec",
                .mode = MODE_HEX_DEC,
                .cb = convert
        },
        {
                .name = "Hex->Bin",
                .mode = MODE_HEX_BIN,
                .cb = convert
        },
        {
                .name = "Hex->Oct",
                .mode = MODE_HEX_OCT,
                .cb = convert
        }
};

uint8_t get_numeric(uint16_t key);
void print_header(const char *text);
void print_t(const char *text, uint16_t col, uint8_t row);

#endif /* SRC_MAIN_H */
