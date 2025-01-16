CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -Wvla
OBJ = src/main.o src/utils/logger.o src/nodes/node.o src/links/links.o
BIN = network_simulator

.PHONY: all clean check

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

clean:
	$(RM) $(OBJ) $(BIN)
	clear