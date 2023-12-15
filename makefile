CC = gcc
CFLAGS = -Wall -Werror

SRC_FILES = main.c scanner.c parser.c staticSemantics.c codegen.c
TARGET = comp

all: $(TARGET)

$(TARGET): $(SRC_FILES)
        $(CC) $(CFLAGS) $(SRC_FILES) -o $(TARGET)

clean:
        rm -f $(TARGET)

.PHONY: all clean

