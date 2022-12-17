# ----------------------------
# Makefile Options
# ----------------------------

NAME = BDOX
ICON = icon.png
DESCRIPTION = "Bin-Dec-Oct-HeX calculator"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)

