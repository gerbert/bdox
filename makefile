# ----------------------------
# Makefile Options
# ----------------------------

NAME			= BDOX
ICON			= icon.png
DESCRIPTION		= "Bin-Dec-Oct-HeX calculator"
COMPRESSED		= YES
COMPRESSED_MODE = zx7
ARCHIVED		= NO

CFLAGS			= 			\
	-Wall 					\
	-Wextra 				\
	-Oz 					\
	-fpack-struct 			\
	-fshort-enums			\
	-Wconversion			\
	-Wsign-conversion 		\
	-Wshadow 				\
	-Wfloat-equal 			\
	-Wconversion 			\
	-Wcast-qual 			\
	-Wcast-align 			\
	-Wmain 					\
	-Wreturn-type 			\
	-Wshift-overflow 		\
	-Wduplicate-enum 		\
	-Wnull-dereference 		\
	-fstack-protector
EXTRA_C_SOURCES = \
	src/callbacks.c

# ----------------------------

include $(shell cedev-config --makefile)
