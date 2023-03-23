#include <ti/screen.h>
#include <ti/ui.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define LEFT_COL_PATTERN        ("%1d %s")
#define LEFT_COL_INDEX          (0)
#define RIGHT_COL_PATTERN       ("%2d %s")
#define RIGHT_COL_INDEX         (11)

uint8_t get_numeric(uint16_t key) {
    switch (key) {
        case k_0 ... k_9:
            return (uint8_t)(48 + (key - k_0));
        case k_CapA ... k_CapF:
            return (uint8_t)(65 + (key - k_CapA));
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

static uint8_t print_menu(void) {
    uint16_t key;
    uint8_t m_item;
    char *ptr;
    char menu_number[2] = {0};

    os_ClrLCD();
    print_header("MENU");

    for (m_item = 0; m_item < ARRAY_SZ(menu_items); m_item++) {
        if (m_item > 5) {
            os_SetCursorPos(m_item - 6, RIGHT_COL_INDEX);
            ptr = RIGHT_COL_PATTERN;
        } else {
            os_SetCursorPos(m_item, LEFT_COL_INDEX);
            ptr = LEFT_COL_PATTERN;
        }

        printf((const char *)ptr, (m_item + 1), menu_items[m_item].name);
    }

    ptr = &menu_number[0];
    os_SetCursorPos(252, 0);
    os_EnableCursor();
    printf("Choice (0/quit): ");
    while ((key = os_GetKey()) != k_Enter) {
        if (key == k_Quit) {
            os_DisableCursor();
            printf("quit");
            return 0;
        }

        if (key == k_Clear)
            return print_menu();

        if ((key >= k_0) && (key <= k_9)) {
            if ((size_t)(ptr - menu_number) < ARRAY_SZ(menu_number)) {
                m_item = get_numeric(key);
                *ptr = (char)m_item;
                ptr++;
                printf("%c", m_item);
            } else {
                break;
            }
        }
    }

    os_DisableCursor();
    return (uint8_t)strtoul(menu_number, NULL, 10);
}

int main(void)
{
    uint8_t m_item;
    t_mode mode;

    os_ClrHome();
    while ((m_item = print_menu()) != 0) {
        if (m_item <= ARRAY_SZ(menu_items)) {
            mode = menu_items[m_item - 1].mode;
            menu_items[m_item - 1].cb(mode);
        } else {
            os_ClrLCD();
            os_SetCursorPos(252, 0);
            printf("Wrong menu item!");
            os_GetKey();
        }
    }

    return 0;
}
