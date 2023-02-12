release:
	gcc -c main.c
	gcc -c users.c
	gcc -c telegram.c
	gcc main.o users.o telegram.o -lcurl -o watcher

debug:
	gcc -c -g main.c
	gcc -c -g users.c
	gcc -c -g telegram.c
	gcc main.o users.o telegram.o -lcurl -o watcher
	gdb ./watcher

clean:
	rm *.o watcher
