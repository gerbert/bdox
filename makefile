# ----------------------------
# Makefile Options
# ----------------------------

NAME			= BDOX
ICON			= icon.png
DESCRIPTION		= "Bin-Dec-Oct-HeX calculator"
COMPRESSED		= YES
COMPRESSED_MODE = zx7
ARCHIVED		= NO

CFLAGS			= -Wall -Wextra -Oz
CXXFLAGS		= -Wall -Wextra -Oz
EXTRA_C_SOURCES = \
	src/callbacks.c

# ----------------------------

include $(shell cedev-config --makefile)
