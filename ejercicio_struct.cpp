/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;

int main()
{
    struct pfpmaraton{
        char nombre[20];
        int edad;
        char sexo[20];
        char* categoria;
    } pfppersona[2];
    
    for(int i=0; i<2; i++) {
        cout << "\nDigite Nombre: " << endl;
        cin >> pfppersona[i].nombre;
        cout << "\nDigite su edad: " << endl;
        cin >> pfppersona[i].edad;        
        cout << "\nDigite su sexo: " << endl;
        cin >> pfppersona[i].sexo; 
        cout << "\n";
        
        if(pfppersona[i].edad <= 18) {
            pfppersona[i].categoria = "Juvenil"; 
        } else if(pfppersona[i].edad >= 41) {
            pfppersona[i].categoria = "Veterano";
        } else {
            pfppersona[i].categoria = "Señor";
        }
            
        
    }
    
    for(int i=0; i<2; i++){
        cout <<"\nNombre: "<<pfppersona[i].nombre<<endl;
        cout <<"Edad: "<<pfppersona[i].edad<<endl;
        cout <<"Sexo: "<<pfppersona[i].sexo<<endl;
        cout <<"Categoria: "<<pfppersona[i].categoria<<endl;
    }
    
    

    return 0;
}
