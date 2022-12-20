#include <ti/screen.h>
#include <stdio.h>
#include "main.h"

uint8_t get_numeric(uint16_t key) {
    switch (key) {
        case k_0 ... k_9:
            return (48 + (key - k_0));
            break;
        case k_CapA ... k_CapF:
            return (65 + (key - k_CapA));
            break;
        default:
            break;
    }

    return 0;
}

static uint16_t print_menu(void) {
    uint16_t key;
    uint8_t m_item;

    os_ClrLCD();
    for (m_item = 0; m_item < ARRAY_SZ(__menu_items); m_item++) {
        os_SetCursorPos(m_item, 0);
        os_PutStrLine(__menu_items[m_item].name);
    }

    while ((key = os_GetKey()) != k_Enter) {
        if (key == k_Quit)
            break;

        if ((key >= k_0) && (key <= k_9))
            return key;
    }

    return k_Quit;
}

int main(void)
{
    uint16_t ret;
    uint8_t key;
    t_mode mode;

    os_ClrHome();
    while ((ret = print_menu()) != k_Quit) {
        // Allow numbers only
        if ((ret >= k_0) && (ret <= k_9)) {
            key = get_numeric(ret) - 48;
            switch (ret) {
                case k_1 ... k_5:
                    mode = __menu_items[key - 1].mode;
                    __menu_items[key - 1].cb((void *)&mode);
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}
