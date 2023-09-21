CC = gcc

CCOMFLAGS = -Wall -Wextra -std=c99 --pedantic
CRELFLAGS = -O3 
CDEVFLAGS = -g

SRC_FOLDER = .
# BUILD_FOLDER = build

SRC = *.c
OBJ = ${SRC:.c=.o}
EXE = main

.PHONY: clean

all: build-rel

run: build-rel exec

dev: build-dev exec

build-rel:
	$(CC) -o $(EXE) $(SRC_FOLDER)/$(SRC) $(CCOMFLAGS) $(CRELFLAGS)

build-dev:
	$(CC) -o $(EXE) $(SRC_FOLDER)/$(SRC) $(CCOMFLAGS) $(CDEVFLAGS)

exec:
	@echo '--------------------------------'
	./$(EXE) $(ARGS)
	@echo '--------------------------------'

clean:
	$(RM) $(EXE)
	$(RM) $(OBJ)
