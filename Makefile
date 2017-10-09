ll :	sol_hilos sol_procesos sol_semaforos

sol_hilos : sol_hilos.o
		gcc -o sol_hilos sol_hilos.o -l pthread

sol_hilos.o : sol_hilos.c
		gcc -c sol_hilos.c -l pthread

sol_procesos : sol_procesos.o
		gcc -o sol_procesos sol_procesos.o 

sol_procesos.o : sol_procesos.c
		gcc -c sol_procesos.c

sol_semaforos : sol_semaforos.o
		gcc -o sol_semaforos sol_semaforos.o 

sol_semaforos.o : sol_semaforos.c
		gcc -c sol_semaforos.c

clean :
		rm sol_hilos.o sol_procesos.o sol_semaforos.o sol_hilos sol_procesos sol_semaforos
