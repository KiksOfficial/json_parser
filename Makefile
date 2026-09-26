CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = json_parser

SRC = main.c \
      src/read_file.c \
      src/tokenizer.c

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
