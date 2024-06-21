#include <iostream>
#include <cmath>
#include <string>
#include <limits>
#include <cctype>
using namespace std;

//Creamos una funcion para validar que un numero sea entero
float validarEntero(float n){
    if (n != floor(n)){ //Si el numero no es igual a su valor redondeado inferiormente, no es entero
        cerr << "\033[31m" << "Error: Introduzca un numero entero." << "\033[0m" << endl;
        cin.clear();    //Usamos este metodo para restablecer el estado del cin luego del error
        cin.ignore(1024, '\n'); //Usamos este metodo para ignorar lo restante del buffer
        return -1;
    } else {
        return n;
    }
}

//Creamos una funcion que verifica que la entrada sea numero positivo
float validarNumPosi(float n){
    if(cin.fail()){     //Verifica si la entrada fallo, por ejemplo si ingreso una cadena de texto
        cerr << "\033[31m" << "Error: Tiene que colocar un valor correcto." << "\033[0m" << endl;
        cin.clear();  
        cin.ignore(1024, '\n');
        return -1;
    } else if (cin.peek() != '\n' && cin.peek() != '.') { //Verifica si hay un caracter diferente al salto de linea o el punto decimal
        cerr << "\033[31m" << "Error: Caracter no numerico encontrado despues del primer entero." << "\033[0m" << endl;
        cin.ignore(1024, '\n');
        return -1;
	} else if (n <= 0){ //Verifica la posibilidad de que el numero sea menor o igual a 0
        cerr << "\033[31m" << "Error: El numero debe ser mayor que 0." << "\033[0m" << endl;
        return -1; //Devuelve -1 para indicar que la entrada fue un numero invalido
    } else {
        return n; //Si n es un numero valido y positivo (valor correcto), la funcion devuelve n
    }
}

// Función para validar que la entrada sea un string alfabético
string validarStringAlfabetico(string entrada) {
    for (char c : entrada) {
        if (!isalpha(c) && !isspace(c)) { // Verifica si el carácter es alfabético o un espacio
            cerr << "\033[31m" << "Error: La entrada debe contener solo letras y espacios." << "\033[0m" << endl;
            return ""; // Retorna un string vacío como indicador de error
        }
    }

    return entrada; // Retorna la entrada validada
}