#include <ti/screen.h>
#include <ti/ui.h>
#include <stdio.h>
#include "main.h"

#define LEFT_COL_PATTERN        ("%1d %s")
#define LEFT_COL_INDEX          (0)
#define RIGHT_COL_PATTERN       ("%2d %s")
#define RIGHT_COL_INDEX         (11)

uint8_t get_numeric(uint16_t key) {
    switch (key) {
        case k_0 ... k_9:
            return (uint8_t)(48 + (key - k_0));
            break;
        case k_CapA ... k_CapF:
            return (uint8_t)(65 + (key - k_CapA));
            break;
        default:
            break;
    }

    return 0;
}

void print_t(const char *text, uint16_t col, uint8_t row) {
    os_SetDrawBGColor(0xFFFF);
    os_SetDrawFGColor(0x0000);
    os_FontSelect(os_SmallFont);
    os_FontDrawText(text, col, row);
}

void print_header(const char *text) {
    // Redraw the status bar to reset the text
    os_DrawStatusBar();
    // Set text box back/foreground color
    os_SetDrawBGColor(0x52AA);
    os_SetDrawFGColor(0xFFFF);
    // The font should be tiny to fit into the status bar without overlapping
    os_FontSelect(os_SmallFont);
    os_FontDrawText(text, 1, 15);
}

static uint16_t print_menu(void) {
    uint16_t key;
    uint8_t m_item;
    char *ptr;

    os_ClrLCD();
    print_header("MENU");

    for (m_item = 0; m_item < ARRAY_SZ(__menu_items); m_item++) {
        if (m_item > 5) {
            os_SetCursorPos(m_item - 6, RIGHT_COL_INDEX);
            ptr = RIGHT_COL_PATTERN;
        } else {
            os_SetCursorPos(m_item, LEFT_COL_INDEX);
            ptr = LEFT_COL_PATTERN;
        }

        printf((const char *)ptr, (m_item + 1), __menu_items[m_item].name);
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
                case k_1 ... k_7:
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
