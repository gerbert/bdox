#ifndef SRC_CALLBACKS_H
#define SRC_CALLBACKS_H

#include <inttypes.h>

// KEEP THE ORDER!
typedef enum {
    MODE_DEC_HEX = 0,
    MODE_DEC_OCT,
    MODE_DEC_BIN,
    MODE_HEX_DEC,
    MODE_HEX_OCT,
    MODE_HEX_BIN,
    MODE_OCT_DEC
} t_mode;

void convert(void *value);

#endif /* SRC_CALLBACKS_H */
