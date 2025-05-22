CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -O2

OBJ=src/main.o src/task.o src/file_ops.o
TARGET=todo_list

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
