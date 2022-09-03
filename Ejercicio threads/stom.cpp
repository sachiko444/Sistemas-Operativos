/*---------------------------------------
UNIVERSIDAD DEL ISTMO
Sistemas Operativos
Modificado por: Kimberly Barrera
Fecha: 08/11/2019
Mod:   08/17/2022

argumentos_stom.cpp
Comparte desde subrutina argumentos en es-
tructura con elementos de mÃºltpiple 
tipo, hacia el main
---------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define num_th 100

struct parameters { 
	int id;
	float val1;
	float val2;
	float val3;
};

void *calculate(void *arg ) {
	parameters *ps;
	ps = (parameters *)arg;
	float res;
	
	
	res = ps -> val1*ps -> val2;
	printf("Thread %d ", ps->id); 
	printf(" resultado desde rutina %f \n", res);
	ps -> val3 = res;
	//usleep(1000);
	/*
	 * De forma implicita, el thread llama a exit() al terminar
	 * su ejecucion.
	 */
	pthread_exit(NULL);
}

int main() {
	pthread_t thread;
	int i;
	parameters p;
	
	
	for(i=1; i<num_th; i++){
		p.id = i;
		p.val1 = i;
		p.val2 = i-1;
		p.val3 = 0;
		pthread_create(&thread, NULL, calculate, ( void *)&p);
		pthread_join(thread, NULL);
		
		printf("Thread %d ", p.id);
		printf("resultado desde MAIN:  %f \n", p.val3);
		printf("\n");
	}
	printf ("\n --- Fin --- \n");
}