#include <ti/screen.h>
#include "main.h"

uint8_t get_numeric(uint16_t key) {
    switch (key) {
        case k_0:
            return 0;
            break;
        case k_1:
            return 1;
            break;
        case k_2:
            return 2;
            break;
        case k_3:
            return 3;
            break;
        case k_4:
            return 4;
            break;
        case k_5:
            return 5;
            break;
        case k_6:
            return 6;
            break;
        case k_7:
            return 7;
            break;
        case k_8:
            return 8;
            break;
        case k_9:
            return 9;
            break;
    }

    return 255;
}

static uint16_t print_menu(void) {
    uint16_t key = 0;
    uint8_t m_item = 0;

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
    uint16_t ret = 0;
    /* Clear the homescreen */
    os_ClrHome();

    while ((ret = print_menu()) != k_Quit) {
        switch (ret) {
            case k_1:
                __menu_items[get_numeric(ret) - 1].cb(NULL);
                break;
            default:
                break;
        }
    }

    /* Return 0 for success */
    return 0;
}
