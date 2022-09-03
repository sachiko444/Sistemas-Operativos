/*---------------------------------------------------------------------------
* UNIVERSIDAD DEL ISTMO
* FACULTAD DE INGENIERÍA
* INGENIERÍA EN SISTEMAS Y CIENCIA DE LA COMPUTACIÓN
*
* Curso: 2155 Sistemas Operativos
* Actividad: Ejemplo clase semana 04
* Descripción: Llamada al sistema para creación de procesos hijos
------------------------------------------------------------------------------*/
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

using std::cout; 
using std::endl;

int main() {
    pid_t num_pid;				
	num_pid = fork();			//num_pid--valor de retorno generado por fork()

    if (num_pid == -1) {
        perror("fork not created");	//NUEVO
        exit(EXIT_FAILURE);
    } else if (num_pid > 0) {
        //cout << "Printed from Parent Num. Process: " << getpid() << endl;  							//NUEVOGETPID
		//cout << "Printed from Parent, Parent Num. Process: " << getppid() << endl;
        wait(nullptr);																				//NUEVO
    } else { // == 0
		cout << "Printed from Child Num. Process: " << getpid() << endl;
		//cout << "Printed from Child, Parent Num. Process: " << getppid() << endl;
		//cout << "Printed from Child process: fork **returned value** (num_pid): " << num_pid << endl;
        exit(EXIT_SUCCESS);  																			//NUEVO
    }

    return EXIT_SUCCESS;
}