/*---------------------------------------
UNIVERSIDAD DEL VALLE DE GUATEMALA
CC3086 - Programacion de Microprocesadores
Modificado por: Kimberly Barrera
Fecha: 08/11/2020
Mod:   08/19/2022

retorno.cpp
Comparte desde subrutina argumento puntero
de tipo void, por medio de return.
---------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//Reto que sea float

void *calculos(void* argument){
	
    //variable float
	float input; 


	input = *(float*)&argument; // puntero a float y luego * te da el valor dentro de ese puntero que es de tipo float
	//puntero de tipo float guarda la direccion en memoria & del void argument
    //* permite acceder a lo que hay dentro de esa dirreccion en memoria

	float output; 
	output = input*2;

    //void *v2;
    //v2 = &output; 
    //return v2

	return *(void**)&output; //doble puntero tipo void con la direccion del float output
    //retorna la direccion del puntero que en realidad es el valor float
    //el doble puntero void guarda la direccion del float
    //al acceder dentro del puntero void se encuentra el valor del float y lo toma como si fuera dirreccion de void
}
int main(){

	printf("\n\n");
	pthread_t thread_id;
	pthread_attr_t attr;
	
	pthread_attr_init (&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	void *exit_value; //puntero void que guarda direccion float

	
	for(float i = 0.1; i < 100; i++){
		pthread_create(&thread_id, &attr, calculos, *(void**)&i); //doble puntero void que guarda el valor del float
		pthread_join(thread_id, &exit_value); //direccion de pointer exitvalue
		
		float result = *(float*) &exit_value; //convierte a puntero float el puntero void y accede a lo que hay dentro
		printf("Resultado multiplicaciÃ³n es: %f\n ", result);
	}
	
	pthread_attr_destroy(&attr);
	pthread_exit(NULL);
	return 0;
	
}