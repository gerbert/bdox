#include <ti/screen.h>
#include <ti/getkey.h>
#include <ti/getcsc.h>
#include <string.h>
#include "main.h"

int16_t print_menu(void) {
    uint16_t ret = 0;
    uint8_t m_item = 0;

    os_ClrLCD();
    for (m_item = 0; m_item < ARRAY_SZ(__menu_items); m_item++) {
        os_SetCursorPos(m_item, 0);
        os_PutStrLine(__menu_items[m_item].name);
    }

    while ((ret = os_GetKey()) != k_Enter) {
        switch (ret) {
            case k_1:
                __menu_items[0].cb(NULL);
                break;
            case k_9:
            default:
                return k_Quit;
                break;
        }
    }

    return ret;
}
