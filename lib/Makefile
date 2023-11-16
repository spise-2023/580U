# As you are assigned each ADT, move the comment `#` to include its directory
SUBDIRS=vector #list stack queue tree

.PHONY: all clean check memcheck

all clean check memcheck:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
