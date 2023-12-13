DIRNAME:=list
SRC:=list.c  # Replace this with the actual name of your source file
OBJ:=$(addsuffix .o,$(DIRNAME))
LOG:=$(addsuffix .log,$(DIRNAME))
TARGET:=test

CFLAGS=-g -Wall -std=c99 -I../../include
LDFLAGS=
LDLIBS=-lcunit
ARFLAGS=rcs
RMFLAGS=-f

# Default target
all: $(TARGET)

# This rule builds the CUnit executable, test
$(TARGET): test.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# This rule runs the CUnit unit testing executable
.PHONY: check
check: $(TARGET)
	./$(TARGET) --verbose

# This rule runs the CUnit test executable inside Valgrind
.PHONY: memcheck
memcheck: $(TARGET)
	valgrind --leak-check=summary --error-exitcode=1 --log-file=$(LOG) ./$(TARGET) --silent

# This rule removes all files created after running `make all`, `make check`, 
# or `make memcheck`, and any cruft in the directory like temp or lock files
.PHONY: clean
clean:
	$(RM) $(RMFLAGS) $(OBJ) $(TARGET) $(LOG)
