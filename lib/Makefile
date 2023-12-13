# As you are assigned each ADT, move the comment `#` to include its directory
SUBDIRS=list stack queue vector 

.PHONY: all clean check memcheck

all clean check memcheck:
	for dir in $(SUBDIRS);  do \
		$(MAKE) -C $$dir $@; \
	done