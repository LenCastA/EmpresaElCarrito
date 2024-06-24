#include "functionsImportant.cpp"


int obtenerTipoDePieza()
{
    int tipoDePieza;
    do {
        cout << "Ingrese el tipo de pieza: "; cin >> tipoDePieza;
        tipoDePieza = validarEnteroPosi(tipoDePieza); //validamos que tipoDePieza sea un numero entero

        if (tipoDePieza > 5) { //validamos que tipoDePieza sea una de las 5 opciones posibles
            msgError("Tipo de pieza invalido");
            tipoDePieza = -1;
        }

    } while(tipoDePieza == -1);
    return tipoDePieza;
}