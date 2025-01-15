CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -Wvla
OBJ = main.o
BIN = $(OBJ:.o=)

.PHONY: all clean check

all: $(BIN)

$(BIN): $(OBJ)

clean:
	$(RM) $(OBJ) $(BIN)