/*---------------------------------------------------------------------------
* UNIVERSIDAD DEL ISTMO
* FACULTAD DE INGENIERÍA
* INGENIERÍA EN SISTEMAS Y CIENCIA DE LA COMPUTACIÓN
*
* Curso: 2155 Sistemas Operativos
* Actividad: Ejemplo clase semana 04
* Descripción: Llamada al sistema para creación de procesos hijos y 
*              modificación de variables en Parent y Child
------------------------------------------------------------------------------*/
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

using std::cout; using std::endl;

int main() {
    pid_t num_pid;				
	num_pid = fork();
	
	int counter = 100 ; 
	

    if (num_pid == -1) {
        perror("fork not created");
        exit(EXIT_FAILURE);
    } else if (num_pid > 0) {
        cout << "Printed from Parent Num. Process: " << getpid() << endl;
		
		int i = 0;
		for (; i < 10 ; ++i) 
		{ 
			printf( "Parent: Counter value = %d\n" , ++counter); 
		} 	
		
        wait(nullptr);
    } else {
		cout << "Printed from Child Num. Process: " << getpid() << endl;
		//cout << "Printed from Child, Parent Num. Process: " << getppid() << endl;
		cout << "Printed from Child process: fork returned value (num_pid): " << num_pid << endl;
		
		int i = 0;			
		for (; i < 10 ; ++i) 
		{ 
			printf( "Child: Counter value = %d\n" , --counter); 
		} 	
		
        exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}