GFLAGS = $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS = $(shell pkg-config --libs gtk+-3.0)

go: *.c
	gcc *.c -g3 -O0 -lX11 -lXtst $(GFLAGS) $(LDFLAGS) -o go
clean:
	rm -f *.o go
