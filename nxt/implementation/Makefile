# Target specific macros
TARGET = IMPL
TARGET_SOURCES = \
	$(wildcard ../common/*.c) \
	nxt.c
TOPPERS_OSEK_OIL_SOURCE = ./nxt.oil

# Custom include paths, space separated
USER_INC_PATH = /home/nxt/code/inc/

# Only build programs using the enhanced NXT standard firmware
BUILD_MODE = RXE_ONLY

# Don't modify below part
O_PATH ?= build
include ${NXTOSEK}/ecrobot/ecrobot.mak
