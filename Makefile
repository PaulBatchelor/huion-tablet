huion.so: huion.c
	gcc -fPIC -shared huion.c -o huion.so -lsporth -lsoundpipe -lpthread 

probe: probe.c
	gcc probe.c -o probe

huion_osc: huion_osc.c
	gcc $^ -o $@ -llo

clean:
	rm -rf huion.so probe huion_osc
