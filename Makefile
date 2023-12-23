cc ?= gcc
cflags ?= -g
target := ./target
test-script := ./test.fish

pseudo-src := pseudo-terminal.c
pseudo := $(target)/pseudo-terminal
	
test-tty-src := test-tty.c
test-tty := $(target)/test-tty

echoing-src := turn-off-echoing.c
echoing := $(target)/turn-off-echoing

winsize-src := ./window-size.c
winsize := $(target)/window-size



main: $(pseudo) $(test-tty) $(echoing) $(winsize)

$(pseudo): $(pseudo-src) $(target)
	$(cc) -o $(pseudo) $(pseudo-src) $(cflags)


$(test-tty): $(test-tty-src) $(target)
	$(cc) -o $(test-tty) $(test-tty-src) $(cflags)

$(echoing): $(echoing-src) $(target)
	$(cc) -o $(echoing) $(echoing-src) $(cflags)

$(winsize): $(winsize-src) $(target)
	$(cc) -o $(winsize) $(winsize-src) $(cflags)

$(target):
	mkdir $(target)

test: main $(test-script)
	$(test-script)

clean: $(target)
	rm -rf $(target)
