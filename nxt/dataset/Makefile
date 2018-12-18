# Target specific macros
TARGET = DATASET
TARGET_SOURCES = \
	nxt.c
TOPPERS_OSEK_OIL_SOURCE = ./nxt.oil

# Define custom libraries. Requires USER_INC_PATH.
# USER_LIB = FOO

# Custom include paths, space separated
USER_INC_PATH = /home/nxt/code/inc/

# Only build programs using the enhanced NXT standard firmware
BUILD_MODE = RXE_ONLY

# Don't modify below part
O_PATH ?= build
include ${NXTOSEK}/ecrobot/ecrobot.mak
