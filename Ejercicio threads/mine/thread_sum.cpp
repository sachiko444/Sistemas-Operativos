#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h> 
#include <vector>
#include <numeric>
#include <string>
#include <functional>


#define NTHREADS 2


struct parameters
{
  int ini;
  int fin;
  int n;
  std::vector<int> listNum; 
};



void *say_sum(void *arg) {

//DECLARACION STRUCT

  parameters *ps;
	ps = (parameters *)arg;

//ini= donde comienza array
//fin= donde termina array
//n = tamaño de array >>cin
  int ini2 = ps -> ini;
  int fin2 = ps -> fin;
  int n2 = ps -> n;


//DECLARACION DE VARIABLES

//listNum2 =  vector con valores del parametro listNum    
  std::vector<int> listNum2;
  listNum2 = ps -> listNum;  


//ans =  resultado de la suma de cada thread 
  int ans = 0; 


//newlistNum: vector donde se guarda la parte de la lista correspondiente a cada thread
  std::vector<int> newlistNum; 
	  


//SUBFUNCIONES

//pasar la mitad de listNum a newlistNum  	
	for (int i = ini2; i<=fin2; i++) {
	    
    newlistNum.push_back(listNum2[i]);
	}


//suma valores en newlistNum
    for (int i = 0; i < (newlistNum.size()); i++) {
	    
      ans = ans + newlistNum[i];        
	}


//imprime valores
  std::cout << "\n Array:  ";

	for (int i = 0; i<(newlistNum.size()); i++) {
	    
    std::cout << newlistNum[i] << " "; 
	}

    
  std::cout << " \n Suma es: " << ans;
  std::cout << " \n Ini es: " << ini2 <<"   fin: " << fin2 << "\n";
    

//DONE
    pthread_exit(NULL);
    return 0;
}








int main(int argc, char *argv[]) {

//INICIALIZAR STRUCT
  parameters p;


//RANDOM

//numero dentro de array
  int num;
 


//Usuario pone tamaño de array
  std::cout << "Digite el tamaño del array:  ";
  std::cin >> p.n; 


//values[] array con los numeros random
  p.listNum[p.n]; 
  srand(time(NULL));
    
    for(int c = 0; c < p.n; c++)
    {
        num = 1 + rand() % (10 - 1);
        std::cout << num<< " ";
        p.listNum.push_back(num);
    }   
    
    std::cout << std::endl;
//end of random





//asignar a cada thread los valores del array

  int tamArray_cadaThread = p.n/NTHREADS;
  int residuo_tam = p.n%NTHREADS; 


    int rc; 
    long long i;
    
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    for (i=0; i<NTHREADS; i++) {
        
  //asignar a cada thread los valores del array  
  //si resultado no da numero entero
        if(i == (NTHREADS-1)) {
          p.ini = i * tamArray_cadaThread;
          p.fin = (p.ini+tamArray_cadaThread -1) + residuo_tam; 
        }
        else {
          p.ini = i * tamArray_cadaThread;
          p.fin = p.ini + tamArray_cadaThread -1;
        }
  

        rc = pthread_create(&tid, &attr, say_sum, (void *)&p);
        
        if (rc) {              
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }

    
    rc = pthread_join(tid, NULL);
    if (rc) {
      printf("ERROR; return code from pthread_join() is %d\n", rc);
      exit(-1);
    }
              
    }
    
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
    
}