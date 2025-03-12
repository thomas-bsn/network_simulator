CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -Wvla

OBJ = \
    src/main.o \
    src/utils/logger.o \
    src/nodes/node.o \
    src/nodes/interfaces.o \
    src/links/links.o \
    src/utils/config_parser.o \
    src/protocols/arp.o \
    src/protocols/icmp.o \
    src/network/packet.o \
    src/core/event_loop.o

BIN = network_simulator

.PHONY: all clean check debug test

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

debug: CFLAGS += -g -DDEBUG
debug: clean $(BIN)
	@echo "Compilation en mode DEBUG terminée."

test: CFLAGS += -DTEST_MODE
test: clean $(BIN)
	@echo "Compilation en mode TEST terminée."

clean:
	$(RM) $(OBJ) $(BIN)
	clear
