tty := test-tty
pseudo-terminal := pseudo-terminal

main: ./target/$(tty) ./target/$(pseudo-terminal)

./target/$(tty): test-tty.c
	gcc -g -o ./target/$(tty) $(tty).c

./target/$(pseudo-terminal): pseudo-terminal.c
	gcc -g -o ./target/$(pseudo-terminal) $(pseudo-terminal).c

test: main
	./test.fish
