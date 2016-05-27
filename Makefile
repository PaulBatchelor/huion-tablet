huion.so: huion.c
	gcc -fPIC -shared huion.c -o huion.so -lsporth -lsoundpipe -lpthread 

clean:
	rm -rf huion.so probe
