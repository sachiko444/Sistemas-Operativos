#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h> 
#include <vector>
#include <numeric>
#include <string>
#include <functional>
#include <unistd.h>


#define NTHREADS 3


struct parameters {
    int t = 0;
    float d =0 ;
    int v =0 ;
};


void *say_time(void *arg) {

    parameters *ps;
	ps = (parameters *)arg;
    int t2 = ps -> t;


    for(t2=1; t2 <= 50; t2++) {
        std::cout << "\nEl valor del hilo 1 es: " << (t2) << "segundos. \n";
        ps -> t = t2;
        sleep(1); 
    }

    pthread_exit(NULL);
    return 0;
}

void *say_distance(void *arg) {
       
    parameters *ps;
	ps = (parameters *)arg;
    
    int t2 = ps -> t;
    int d2 = ps -> d;
    int v2 = ps -> v; 


    for(int i=1; i <= 50; i++) {        
        t2 = ps -> t;
        d2 =  v2 * t2;
        if(t2==i) {
            std::cout << "En " << t2 << " segundos, la distancia recorrida es: " << d2 << "metros. \n";
        }
        ps -> d = d2;
        sleep(1);
                        
    }
    pthread_exit(NULL);
    return 0;
}


void *say_rec(void *arg) {

    parameters *ps;
	ps = (parameters *)arg;
    int d2 = ps -> d;
    int t2 = ps -> t;

    for(int i=1; i <= 50; i++) { 
        d2 = ps -> d;
        t2 = ps -> t;
        if(d2%2 == 0 && t2 == i) {
            std::cout << "Se ha recorrido " << d2 << " metros \n";
        } 
        sleep(1);
    }
    
    pthread_exit(NULL);
    return 0;

}


int main() {
    

    parameters p;
    std::cout << "Ingrese la velocidad en m/s: "; 
    std::cin >> p.v;
    
    int tc;
    int dc;  
    int rc; 

    
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    
    
    tc = pthread_create(&tid, &attr, say_time, (void *)&p);
    dc = pthread_create(&tid, &attr, say_distance, (void *)&p);
    rc = pthread_create(&tid, &attr, say_rec, (void *)&p);

    
        
    if (tc) {              
      printf("ERROR; return code from pthread_create() is %d\n", tc);
      exit(-1);
    }

//pthread_join permite que el hilo espere a que terminen los otros. 
    
    tc = pthread_join(tid, NULL);
    if (tc) {
      printf("ERROR; return code from pthread_join() is %d\n", tc);
      exit(-1);
    }


    dc = pthread_join(tid, NULL);
    if (dc) {
      printf("ERROR; return code from pthread_join() is %d\n", tc);
      exit(-1);
    }


    rc = pthread_join(tid, NULL);
    if (rc) {
      printf("ERROR; return code from pthread_join() is %d\n", tc);
      exit(-1);
    }
              
    
    
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
}


