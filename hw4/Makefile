CC := gcc
override CFLAGS += -O3 -Wall

SOURCE := MemManager.c
BINARY := MemManager

GIT_HOOKS := .git/hooks/applied
all: $(GIT_HOOKS) $(BINARY)

debug: CFLAGS += -DDEBUG -g
debug: $(GIT_HOOKS) $(BINARY)

$(GIT_HOOKS):
	scripts/install-git-hooks

$(BINARY): $(SOURCE) $(patsubst %.c, %.h, $(SOURCE))
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
test:
	git pull
	gcc -o t MemManager.c
clean:
	rm -f *.o $(BINARY)