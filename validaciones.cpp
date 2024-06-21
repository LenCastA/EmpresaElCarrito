#include <iostream>
#include <cmath>
#include <string>
#include <limits>
#include <cctype>
using namespace std;

string msgError(string msg)
{
    cerr << "\033[31m" << msg << "\033[0m" << endl;
}

float validarEnteroPosi(float n){
    if(cin.fail()){
        msgError("Error: Tiene que colocar un valor correcto.");
        cin.clear();  
        cin.ignore(1024, '\n');
        return -1;
    } else if (cin.peek() != '\n' && cin.peek() != '.') {
        msgError("Error: Caracter no numerico encontrado despues del primer entero.");
        cin.ignore(1024, '\n');
        return -1;
	} else if (n <= 0){
        msgError("Error: El numero debe ser mayor que 0.");
        return -1;
    } else if (n != floor(n)){
        msgError("Error: El numero debe ser entero.");
        cin.clear();
        cin.ignore(1024, '\n');
        return -1;
    } else {
        return n;
    }
}

// Funcion para validar que la entrada sea un string alfabetico
string validarStringAlfabetico(string entrada) {
    for (char c : entrada) {
        if (!isalpha(c) && !isspace(c)) { // Verifica si el carácter es alfabetico o un espacio
            msgError("Error: La entrada debe contener solo letras y espacios.");
            return ""; // Retorna un string vacio como indicador de error
        }
    }

    return entrada; // Retorna la entrada validada
}