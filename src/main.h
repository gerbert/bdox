#ifndef SRC_MAIN_H
#define SRC_MAIN_H

#include <ti/getkey.h>
#include "callbacks.h"

#define ARRAY_SZ(x)         (uint8_t)(sizeof(x) / sizeof(x[0]))

typedef struct {
    const char *name;
    t_mode mode;
    void (*cb)(void *data);
} mItem;

static const mItem menu_items[] = {
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
        },
        {
                .name = "Oct->Dec",
                .mode = MODE_OCT_DEC,
                .cb = convert
        },
        {
                .name = "Oct->Hex",
                .mode = MODE_OCT_HEX,
                .cb = convert
        },
        {
                .name = "Oct->Bin",
                .mode = MODE_OCT_BIN,
                .cb = convert
        }
};

uint8_t get_numeric(uint16_t key);
void print_header(const char *text);
void print_t(const char *text, uint16_t col, uint8_t row);

#endif /* SRC_MAIN_H */
