#include "funcionesMenu.cpp"
#include <algorithm>

int main()
{
    int opcion = 0;

    leerDatosMap(map1, "inventario.txt");
    leerDatosMap(map2, "proveedores.txt");
    leerDatosArray(talleres, "talleres.txt");

    while (opcion != 5) {
        aviso();

        cout << "\tMenu" << endl;
        cout << "1. Recepcion de pedidos" << endl;
        cout << "2. Atencion de pedidos" << endl;
        cout << "3. Consultar inventario" << endl;
        cout << "4. Talleres vendidos" << endl;
        cout << "5. Salir" << endl;
        cout << "-----------------" << endl;

        do {
            cout << "Ingrese una opcion: "; cin >> opcion;
            opcion = validarEnteroPosi(opcion);
            if (opcion > 5) {
                opcion = -1;
                msgError("Opcion invalida");
            }
        } while (opcion == -1);

        switch (opcion){
            case 1:
                recepcionDePedidos();
                reporte();
                break;
            case 2:
                atencionDePedidos();
                reporte();
                break;
            case 3:
                reporte();
                break;
            case 4:
                talleresVendidos();
                break;
            case 5:
                break;
            default:
                break;
        }
// Nota: La opción 5 cortará el bucle automáticamente según la lógica del bucle while que lo contiene.
    }
}
