CFLAGS=-g -Wall -std=c99
LDFLAGS=
LDLIBS=-lcunit
ARFLAGS=rcs
RMFLAGS=-f

.PHONY: all clean check memcheck

all check memcheck:
	$(MAKE) -C lib $@

compile_commands.json:
	bear -- $(MAKE)

clean:
	$(RM) $(RMFLAGS) compile_commands.json
	$(MAKE) -C lib clean
