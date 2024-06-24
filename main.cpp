#include "funcionesMenu.cpp"
#include <algorithm>
//Declaracion de variables
string tipoDeProveedor, nombreDelTaller;
map<int, int> map1;
map<string, int> map2;
vector<string> talleres;

void PrintMap1(std::map<int, int>& m)
{
    for (auto& item : m) {
        cout << item.first << ":" << item.second << " || ";
    }
}

void PrintMap2(std::map<string, int>& m)
{
    for (auto& item : m) {
        cout << item.first << ":" << item.second << " || ";
    }
}

int recepcionDePedidos()
{
    cout << "-----------------------------------" << endl;
    cout << "\tRecepcion de pedidos" << endl;

    int cantidadDePiezas = obtenerCantidadDePiezas();
    int tipoDePieza = obtenerTipoDePieza();

    do{
        cout << "Ingrese el tipo de proveedor (A, B o C): "; cin >> tipoDeProveedor;

        if (tipoDeProveedor.length() > 1){
            msgError("Ingrese un solo caracter");
            tipoDeProveedor = "";
            continue;
        }

        tipoDeProveedor = toupper(tipoDeProveedor[0]);

        if (tipoDeProveedor != "A" && tipoDeProveedor != "B" && tipoDeProveedor != "C"){
            msgError("Tipo de proveedor invalido");
            tipoDeProveedor = "";
        }

    } while(tipoDeProveedor == "");

    map1[tipoDePieza] += cantidadDePiezas;
    map2[tipoDeProveedor] += cantidadDePiezas;

    guardarDatosMap(map1, "inventario.txt");
    guardarDatosMap(map2, "proveedores.txt");

    cout << "-----------------------------------" << endl;
    cout << "\tReporte" << endl;
    cout << "Tipo de pieza: " << tipoDePieza << endl;
    cout << "Tipo de proveedor: " << tipoDeProveedor << endl;
    cout << "Cantidad del pedido recibido: " << cantidadDePiezas << endl;
    cout << "-----------------------------------" << endl;
}

int atencionDePedidos()
{
    cout << "-----------------------------------" << endl;
    cout << "\tAtencion de pedidos" << endl;

    int tipoDePieza = obtenerTipoDePieza();
    
    int cantidadDePiezas = obtenerCantidadDePiezas();

    if (map1[tipoDePieza] < cantidadDePiezas) {
        msgError("No hay suficiente stock para completar el pedido");
        return 0;
    } else {
        map1[tipoDePieza] -= cantidadDePiezas;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Ingrese el nombre del taller: ";
        getline(cin, nombreDelTaller);
        nombreDelTaller = validarString(nombreDelTaller);
    } while(nombreDelTaller == "");

    if (find(talleres.begin(), talleres.end(), nombreDelTaller) == talleres.end()) {
        talleres.push_back(nombreDelTaller);
    }

    guardarDatosMap(map1, "inventario.txt");
    guardarDatosArray(talleres, "talleres.txt");

    cout << "-----------------------------------" << endl;
    cout << "\tReporte" << endl;
    cout << "Nombre del taller: " << nombreDelTaller << endl;
    cout << "Tipo de pieza: " << tipoDePieza << endl;
    cout << "Cantidad de pedido: " << cantidadDePiezas << endl;
    cout << "-----------------------------------" << endl;
}

int reporte()
{
    cout << "-----------------------------------" << endl;
    cout << "\tInventario" << endl;
    cout << "Piezas: "; PrintMap1(map1); cout << endl;
    cout << "Proveedeores: "; PrintMap2(map2); cout << endl;
    cout << "-----------------------------------" << endl;
}

int aviso()
{
    for (int i = 1; i < 6; i++) {
        if (map1[i] < 8) {
            msgError("Es necesario reponer el stock de las piezas " + to_string(i));
        }
    }
    
}

int talleresVendidos()
{
    cout << "-----------------------------------" << endl;
    cout << "\tTalleres vendidos" << endl;
    for (int i = 0; i < talleres.size(); i++) {
        cout << talleres[i] << endl;
    }
    cout << "-----------------------------------" << endl;
}

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
