CFLAGS=-O3 -pedantic -Wall -Wextra -std=c99
CC=gcc

OBJS=cromchy.o sha256.o
DEPS=$(OBJS:.o=.d)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.d: %.c
	@$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) > $@

cromchy: $(OBJS)
	$(CC) $(OBJS) -o $@

-include $(DEPS)

.PHONY: clean
	rm -f $(OBJS) cromchy