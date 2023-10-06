BINARY=./bin/bin
ROOT=./src
LIB=./lib/libmath.a
CODEDIRS=$(shell find $(ROOT) -type d)
INCDIRS=. ./include

CC=gcc
OPT=-O0
# generate files that encode make rules for the .h dependencies
DEPFLAGS=-lm
# automatically add the -I onto each include directory
CFLAGS=-Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS)

LINKFLAGS= $(foreach D,$(INCDIRS),-L$(D)) $(DEPFLAGS)

# for-style iteration (foreach) and regular expression completions (wildcard)
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))
# regular expression replacement
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(LINKFLAGS)

# only want the .c file dependency here, thus $< instead of $^.
#
%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

library:
	ar -r $(LIB) $(OBJECTS)

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES) $(LIB)

# shell commands are a set of keystrokes away
distribute: clean
	tar zcvf dist.tgz *

# @ silences the printing of the command
# $(info ...) prints output
diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat

# include the dependencies
-include $(DEPFILES)

# add .PHONY so that the non-targetfile - rules work even if a file with the same name exists.
.PHONY: all clean distribute diff
