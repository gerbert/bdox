#include <ti/screen.h>
#include "menu.h"

/* Main function, called first */
int main(void)
{
    /* Clear the homescreen */
    os_ClrHome();

    while (print_menu() != k_Quit);

    /* Return 0 for success */
    return 0;
}
