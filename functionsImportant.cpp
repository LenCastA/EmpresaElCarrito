#include <iostream>
#include <cmath>
#include <string>
#include <limits>
#include <cctype>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

string msgError(string msg)
{
    cerr << "\033[31m" << msg << "\033[0m" << endl;
}

template<typename K, typename V>
void leerDatosMap(map<K, V>& mapa, const string& nombreArchivo) {
    ifstream archivoEntrada(nombreArchivo);
    K clave;
    V valor;
    if (archivoEntrada.is_open()) {
        while (archivoEntrada >> clave >> valor) {
            mapa[clave] = valor;
        }
        archivoEntrada.close();
    } else {
        msgError("No se pudo abrir el archivo.");
    }
}

template<typename K, typename V>
void guardarDatosMap(const map<K, V>& mapa, const string& nombreArchivo) {
    ofstream archivoSalida(nombreArchivo);
    if (archivoSalida.is_open()) {
        for (const auto& par : mapa) {
            archivoSalida << par.first << " " << par.second << "\n";
        }
        archivoSalida.close();
    } else {
        msgError("Error al abrir el archivo para guardar.");
    }
}

void leerDatosArray(vector<string>& datos, const string& nombreArchivo) {
    ifstream archivoEntrada(nombreArchivo);
    string linea;
    if (archivoEntrada.is_open()) {
        while (getline(archivoEntrada, linea)) {
            datos.push_back(linea);
        }
        archivoEntrada.close();
    }
}

void guardarDatosArray(const vector<string>& datos, const string& nombreArchivo) {
    std::ofstream archivoSalida(nombreArchivo);
    if (archivoSalida.is_open()) {
        for (const auto& dato : datos) {
            archivoSalida << dato << std::endl;
        }
        archivoSalida.close();
    }
}

int validarNatural(int n, bool accept_0 = false){
    if(cin.fail()){
        msgError("Error: Tiene que colocar un valor correcto.");
        cin.clear();  
        cin.ignore(1024, '\n');
        return -1;
    } else if (cin.peek() != '\n') {
        msgError("Error: Caracter no numerico encontrado despues del primer entero.");
        cin.ignore(1024, '\n');
        return -1;
	} else if (n < 0){
        msgError("Error: El numero no puede ser negativo.");
        return -1;
    } else if (n == 0) {
        if (accept_0)
        {
            return 0;
        }else {
            msgError("Error: El numero debe ser mayor que 0.");
            return -1;
        }
    } else {
        return n;
    }
}


// Funcion para validar que la entrada sea un string alfabetico
string validarString(string entrada) {
    if (entrada.length() > 2) { // Verifica si la entrada esta vacia
        for (char c : entrada) {
            if (!isalpha(c) && !isspace(c) && c != '.') {
                msgError("Error: La entrada no debe tener caracteres no validos.");
                return ""; // Retorna un string vacio como indicador de error
            }
        }
        return entrada;
    } else {
        msgError("Error: La entrada debe contener al menos 3 caracteres.");
        return "";
    }

}
