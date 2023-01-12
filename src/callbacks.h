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
    MODE_OCT_DEC,
    MODE_OCT_HEX,
    MODE_OCT_BIN,
    MODE_BIN_DEC,
    MODE_BIN_HEX,
    MODE_BIN_OCT
} t_mode;

void convert(t_mode mode);
void convert_bin(t_mode mode);

#endif /* SRC_CALLBACKS_H */
