.PHONY: run

run: a.out
	./a.out

a.out: main.c
	$(CC) $< -o $@
