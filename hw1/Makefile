# Makefile to use based off of the Sample C program compilation options

# CSPICE install to make sure I can link against the library
CSPICE_PATH = $(HOME)/Applications/NASA-SPICE/cspice

CC = gcc
CFLAGS = -I/$(CSPICE_PATH)/include
LDFLAGS = $(CSPICE_PATH)/lib/cspice.a

TARGET = main
SRC = script.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)