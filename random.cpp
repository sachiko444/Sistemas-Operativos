/*---------------------------------------------------------------------------
* UNIVERSIDAD DEL ISTMO
* FACULTAD DE INGENIERÃA
*
* Curso:       Sistemas Operativos  Ciclo II - 2022
* DescripciÃ³n: Generar 10 nÃºmeros aleatoriamiente
* Autor:       Martin Cruz 09/2012. Obtener numeros aleatorios en C++ 
------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <time.h>
#include<iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int num, c, d, n, s;
    int values[n];
    srand(time(NULL));
    
    for(c = 1; c <= 10; c++)
    {
        num = 1 + rand() % (11 - 1);
        cout << num<< " ";
    }   
    
    cout << endl;
    n = 5;
    for(d = 0; d <= n; d++)
    {
        values[d] = 1;
        cout << values[d] << " Array "<< endl;
    }  

    

    return 0;
}