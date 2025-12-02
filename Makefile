CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
LDFLAGS = 
SRC = src/main.c src/filesystem.c
OBJ = $(SRC:.c=.o)
TARGET = mini_fs.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q src\*.o $(TARGET) 2>nul || rm -f $(OBJ) $(TARGET) 2>/dev/null || true

run: $(TARGET)
	.\$(TARGET)

.PHONY: all clean run