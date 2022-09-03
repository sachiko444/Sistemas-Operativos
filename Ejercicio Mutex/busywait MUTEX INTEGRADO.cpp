/*
 * UNIVERSIDAD DEL ISTMO
 * Sistemas Operativos
 * Date:	2022/08/25
 * Ver:		2.0 - 2022/08/19
 *
 * busywaitPI.cpp
 * Calculo de PI usando busy-waiting para proteger memoria compartida
 */
 
#include <iostream>
#include <stdio.h>		//printf
#include <cmath>		//pow
#include <pthread.h>	

using namespace std;

const long long N = pow(10,10);
//---- Cuidar que THREAD_COUNT sea factor de N
const int THREAD_COUNT = 10;

//---- suma y bandera globales
long double sum = 0.0;


//------------
// Serie para calculo de PI
//------------


//creacion e inicializacion de lock
pthread_mutex_t lock;
 


void *threadSum(void *thread_rank)
{
    
    
	long my_rank = (long)thread_rank;
    double factor, my_sum = 0.0;  //*** Suma local
	long long i;
	//---- Lote de datos de cada thread
	long long my_n = N/THREAD_COUNT;
	//---- Rango de datos para cada hilo
	long long my_first_i = my_n * my_rank;
	long long my_last_i = my_first_i + my_n;
	
	if(my_first_i % 2 == 0)		//Orden de dato inicial es para
		factor = 1.0;
	else
		factor = -1.0;
	
	//---- Magnitud de cada elemento de la serie
	for(i=my_first_i; i<my_last_i; i++, factor = -factor)
	{
	   
		my_sum += factor/(2 * i + 1); //*** Suma local
		
	}

	//---- Busy-waiting para actualizar variable y bandera global
pthread_mutex_lock(&lock);

	 
	sum += my_sum;  //Copia del resultado parcial del hilo a mem-global
		
	
pthread_mutex_unlock(&lock); 
//flag almacena que valor deberia estar activo en ese momento 

	
	return NULL;
}

int main()
{
    
    pthread_mutex_init(&lock, NULL);
    
	long long i, rc;
	pthread_t threads[THREAD_COUNT];
	

	
	
	for(i=0;i<THREAD_COUNT;i++)
	{
		rc = pthread_create(&threads[i],NULL,threadSum,(void *)i);
		if(rc)
		{
			cout<<">>>Error creating threads"<<endl;
			exit(-1);
		}
		/*
		rc = pthread_join(threads,NULL);
		if(rc)
		{
			cout<<"No se pudo unir el hilo "<<i<<endl;
			exit(-1);
		}*/
	}
	for(i=0;i<THREAD_COUNT;i++) {
		rc = pthread_join(threads[i],NULL);
		if(rc)
		{
			cout<<"No se pudo unir el hilo "<<i<<endl;
			exit(-1);
		}
	}
	printf("PI= %.10Lf\n",4.0*sum);
	pthread_mutex_destroy(&lock);
	return 0;
}