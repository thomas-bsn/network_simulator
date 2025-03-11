CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -Wvla
OBJ = src/main.o src/utils/logger.o src/nodes/node.o src/nodes/interfaces.o src/links/links.o src/utils/config_parser.o
BIN = network_simulator

.PHONY: all clean check debug

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

debug: CFLAGS += -g -DDEBUG
debug: clean $(BIN)
	@echo "Compilation en mode DEBUG terminée."

clean:
	$(RM) $(OBJ) $(BIN)
	clear
