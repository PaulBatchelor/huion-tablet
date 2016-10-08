default: huion.so probe

CFLAGS = -DSLACKWARE -fPIC

huion.so: huion.o plugin.o
	gcc $(CFLAGS) -shared huion.o plugin.o -o huion.so -lsporth -lsoundpipe -lpthread 

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $^

probe: probe.c huion.o
	gcc $(CFLAGS) probe.c huion.o -o probe

huion_osc: huion_osc.c
	gcc $^ -o $@ -llo

clean:
	rm -rf huion.so probe huion_osc *.o
