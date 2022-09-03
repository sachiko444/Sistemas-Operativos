#include <iostream>
#include <pthread.h>


//Hasta donde termina
//iteraciones de funcion
//la define el usuario
//basically numero de threads
long long THREAD_COUNT;


//variable global donde se guarda la suma del valor final de la serie
float sumaValor;


//Creacion de mutex lock
pthread_mutex_t lock;




void *serieG(void *nvoid) {

    //casting de n 
    long long n = (long long)nvoid;


    //operacion de serie individual
    float valor = (1/((float)n*((float)n+1)));

    
    //Guardar en variable global sumaValor la suma de todos los valores de cada thread
    pthread_mutex_lock(&lock);
    sumaValor += valor; 
    pthread_mutex_unlock(&lock); 

    
    return NULL; 
}





int main() {

    //inicializar la mutex
    pthread_mutex_init(&lock, NULL);

    //variable donde guarda creacion
    long long rc;
    long long n;

    //Define valor de thread_count
    std::cout << "Cuantas iteraciones de serie geometrica? ";
    std::cin >> THREAD_COUNT; 

    //Array de id de threads
	pthread_t threads[THREAD_COUNT];



    //Creacion de threads
    for(n=1; n<=(THREAD_COUNT); n++) {

        rc = pthread_create(&threads[n],NULL,serieG,(void *)n);
        if(rc)
		{
			std::cout<<">>>Error creating threads"<<std::endl;
			exit(-1);
		}
    }

    //Join de cada thread
    for(n=1; n<=(THREAD_COUNT); n++) {

        rc = pthread_join(threads[n],NULL);
        if(rc)
		{
			std::cout<<"No se pudo unir el hilo "<<n<<std::endl;
			exit(-1);
		}
    }


    //Imprimir resultado
    std::cout << "\n Resultado de suma geometrica: " << sumaValor << "\n";

    //destruir mutex
    pthread_mutex_destroy(&lock);
	return 0;

}