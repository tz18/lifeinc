CFLAGS:=-g --std=gnu99

run: life
	./life input.txt

life: life.c

clean:
	rm life
