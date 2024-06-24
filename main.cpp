#include "funcionesMenu.cpp"

int main()
{
    int cod_volver; //inicializando una variable para retroceder al menu
    int opcion = 0; //inicializando opcion del menu
    int num_opciones = 5: //declara numero de opciones del menu
    int minPiezasPedido = 50, maxPiezasPedido = 100;

    //variables persistentes (talleres, proveedores, inventario)
    map<int, int> map1;
    map<string, int> map2;
    vector<string> talleres;
    
    //asignando valores a las variables persistentes
    leerDatosMap(map1, "inventario.txt");
    leerDatosMap(map2, "proveedores.txt");
    leerDatosArray(talleres, "talleres.txt");

    while (opcion != num_opciones) { //opcion final termina el programa
        aviso(map1); //avisar sobre faltas en el inventario
-        
        //Imprimiendo menu
        cout << "\tMenu" << endl;
        cout << "1. Recepcion de pedidos" << endl;
        cout << "2. Atencion de pedidos" << endl;
        cout << "3. Consultar inventario" << endl;
        cout << "4. Talleres vendidos" << endl;
        cout << "5. Salir" << endl;
        cout << "-----------------" << endl;
        cout << "\033[34m" << "Presione 0 en cualquier caso para volver al menu principal" << "\033[0m" << endl;
        cout << "-----------------" << endl;

        do {
            cout << "Ingrese una opcion: "; cin >> opcion;
            opcion = validarNatural(opcion); //validando que opcion sea entero positivo
            if (opcion > num_opciones) {
                opcion = -1; // -1 utilizamos como codigo de error de datos
                msgError("Opcion invalida");
            }
        } while (opcion == -1); // se repite hasta que el codigo de error no exista

        switch (opcion){
            case 1:
                cod_volver = recepcionDePedidos(map1, map2, minPiezasPedido, maxPiezasPedido); //si todo funciona bien cod_volver = 0
                if (cod_volver == -2) { //si la funcion devuelve -2 se regresa al menu inicial (-2 codigo para volver a la accion anterior)
                    break;
                }
                reporte(map1, map2);
                break;
            case 2:
                cod_volver = atencionDePedidos(map1, map2, talleres);
                if (cod_volver == -2) {
                    break;
                }
                reporte(map1, map2);
                break;
            case 3:
                reporte(map1, map2);
                break;
            case 4:
                talleresVendidos(talleres);
                break;
            //se debe añadir la funcionalidad de cada opcion del menu(la ultima, opcion de salida, queda por default)
            default:
                break;
        }
// Nota: La opción 5 cortará el bucle automáticamente según la lógica del bucle while que lo contiene.
    }
}
