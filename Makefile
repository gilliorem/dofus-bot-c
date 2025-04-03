go: *.c
	gcc *.c -lX11 -lXtst -o go
clean:
	rm -f *.o go
