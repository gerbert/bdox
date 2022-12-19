#ifndef SRC_MENU_H
#define SRC_MENU_H

#include <ti/getkey.h>
#include "callbacks.h"

typedef struct {
    uint16_t key_code;
    const char *name;
    void (*cb)(void *data);
} mItem;

static const mItem __menu_items[] = {
        {
                .key_code = k_0,
                .name = "1. Dec->Hex",
                .cb = dec2hex
        },
        {
                .key_code = k_9,
                .name = "9. Quit"
        }
};

int16_t print_menu(void);

#endif /* SRC_MENU_H */
