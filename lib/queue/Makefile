DIRNAME:=queue
SRC:=queue.c  # Replace this with the actual name of your source file
OBJ:=$(addsuffix .o,$(DIRNAME))
LOG:=$(addsuffix .log,$(DIRNAME))
TARGET:=test

CFLAGS=-g -Wall -std=c99 -I../../include
LDFLAGS=
LDLIBS=-lcunit
ARFLAGS= rcs
RMFLAGS=-f

all: $(OBJ) $(TARGET)

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

# This rule removes all files created after running `make all`, `make check` 
# or `make memcheck`, and any cruft in the directory like temp or lock files
.PHONY: clean
clean:
	$(RM) $(RMFLAGS) $(OBJ) $(TARGET) $(LOG)


# DIRNAME:=queue
# SRC:=$(addsuffix .c,$(DIRNAME))
# OBJ:=$(addsuffix .o,$(DIRNAME))
# LOG:=$(addsuffix .log,$(DIRNAME))

# CFLAGS=-g -Wall -std=c99 -I../../include
# LDFLAGS=
# LDLIBS=-lcunit
# ARFLAGS= rcs
# RMFLAGS=-f

# all: $(OBJ) test

# # This rule builds the CUnit executable, test
# test: $(SRC) test.c
# 	$(warning $(DIR) $@ rule not implemented)

# # This rule runs the CUnit unit testing executable
# .PHONY: check
# check: test
# 	./test --verbose

# # This rule runs the CUnit test executable inside Valgrind
# .PHONY: memcheck
# memcheck: test
# 	valgrind --leak-check=summary --error-exitcode=1 --log-file=$(LOG) ./test --silent

# # This rule removes all files created after running `make all`, `make check` 
# # or `make memcheck`, and any cruft in the directory like temp or lock files
# .PHONY: clean
# clean:
# 	$(warning $(DIR) $@ rule not implemented)