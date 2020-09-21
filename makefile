e1p: Processo/ep1.c
	clear
	gcc -Wall -std=c11 -o Processo/ep1 Processo/ep1.c
	./Processo/ep1

e2p: Processo/ep2.c
	clear
	gcc -Wall -std=c11 -o Processo/ep2  Processo/ep2.c
	./Processo/ep2

e3p: Processo/ep3.c
	clear
	gcc -Wall -std=c11 -o Processo/ep3  Processo/ep3.c
	./Processo/ep3

e4p: Processo/ep4.c
	clear
	gcc -Wall -std=c11 -o Processo/ep4  Processo/ep4.c
	./Processo/ep4 5

e5p: Processo/ep5.c
	clear
	gcc -Wall -std=c11 -o Processo/ep5  Processo/ep5.c -lpthread
	./Processo/ep5 5

e1t: Threads/et1.c
	clear
	gcc -Wall -std=c11 -o Threads/et1 Threads/et1.c -lpthread
	./Threads/et1

e2t: Threads/et2.c
	clear
	gcc -Wall -std=c11 -o Threads/et2 Threads/et2.c -lpthread
	./Threads/et2 10

e3t: Threads/et3.c
	clear
	gcc -Wall -std=c11 -o Threads/et3 Threads/et3.c -lpthread
	./Threads/et3 128

e4t: Threads/et4.c
	clear
	gcc -Wall -std=c11 -o Threads/et4 Threads/et4.c -lpthread
	./Threads/et4 128

e5t: Threads/et5.c
	clear
	gcc -Wall -std=c11 -o Threads/et5 Threads/et5.c -lpthread
	./Threads/et5 128

e6t: Threads/et6.c
	clear
	gcc -Wall -std=c11 -o Threads/et6 Threads/et6.c -lpthread
	./Threads/et6 2