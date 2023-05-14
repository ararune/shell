main: main.o cd.o cdir.o exit.o fetch.o find.o ls.o mkdir.o rm.o rmdir.o touch.o
	gcc main.o cd.o cdir.o exit.o fetch.o find.o ls.o mkdir.o rm.o rmdir.o touch.o -o main

main.o: main.c
	gcc -c main.c

cd.o: cd.c cd.h
	gcc -c cd.c

cdir.o: cdir.c cdir.h
	gcc -c cdir.c

exit.o: exit.c exit.h
	gcc -c exit.c

fetch.o: fetch.c fetch.h
	gcc -c fetch.c

find.o: find.c find.h
	gcc -c find.c

ls.o: ls.c ls.h
	gcc -c ls.c

mkdir.o: mkdir.c mkdir.h
	gcc -c mkdir.c

rm.o: rm.c rm.h
	gcc -c rm.c

rmdir.o: rmdir.c rmdir.h
	gcc -c rmdir.c

touch.o: touch.c touch.h
	gcc -c touch.c
clean:
	rm *.o
