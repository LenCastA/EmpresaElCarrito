#include "functionsImportant.cpp"
#include <algorithm>

int obtenerTipoDePieza()
{
    int tipoDePieza;
    do {
        std::cout << "Ingrese el tipo de pieza: "; std::cin >> tipoDePieza;
        tipoDePieza = validarNatural(tipoDePieza); //validamos que tipoDePieza sea un numero entero

        if (tipoDePieza > 5) { //validamos que tipoDePieza sea una de las 5 opciones posibles
            msgError("Tipo de pieza invalido");
            tipoDePieza = -1;
        }

    } while(tipoDePieza == -1);
    return tipoDePieza;
}

int obtenerCantidadDePiezas()
{
    int cantidadDePiezas;
    do {
        std::cout << "Ingrese la cantidad de piezas del pedido (Si desea volver al menu ingrese 0): "; std::cin >> cantidadDePiezas;
        cantidadDePiezas = validarNatural(cantidadDePiezas, true); //validamos que cantidadDePiezas sea un numero entero
        if (cantidadDePiezas == 0) {
            return -2;
        }
    } while (cantidadDePiezas == -1);
    return cantidadDePiezas;
}

string obtenerTipoDeProvedor()
{
    string tipoDeProveedor;
    do{
        std::cout << "Ingrese el tipo de proveedor (A, B o C): "; std::cin >> tipoDeProveedor;

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

    return tipoDeProveedor;
}

void PrintMap1(std::map<int, int>& m)
{
    for (auto& item : m) {
        std::cout << item.first << ":" << item.second << " || ";
    }
}

void PrintMap2(std::map<string, int>& m)
{
    for (auto& item : m) {
        std::cout << item.first << ":" << item.second << " || ";
    }
}

int recepcionDePedidos(std::map<int, int>& map1, std::map<string, int>& map2)
{
    std::cout << "-----------------------------------" << endl;
    std::cout << "\tRecepcion de pedidos" << endl;

    int cantidadDePiezas;
    do
    {
        cantidadDePiezas = obtenerCantidadDePiezas();
        if (cantidadDePiezas == -2) {
            return -2;
        }
        if (cantidadDePiezas < 50 || cantidadDePiezas > 100){
            msgError("El pedido debe estar comprendido entre 50 y 100 piezas.");
        }
    } while (cantidadDePiezas < 50 || cantidadDePiezas > 100);

    int tipoDePieza = obtenerTipoDePieza();
    string tipoDeProveedor = obtenerTipoDeProvedor();

    map1[tipoDePieza] += cantidadDePiezas;
    map2[tipoDeProveedor] += cantidadDePiezas;

    guardarDatosMap(map1, "inventario.txt");
    guardarDatosMap(map2, "proveedores.txt");

    std::cout << "-----------------------------------" << endl;
    std::cout << "\tReporte" << endl;
    std::cout << "Tipo de pieza: " << tipoDePieza << endl;
    std::cout << "Tipo de proveedor: " << tipoDeProveedor << endl;
    std::cout << "Cantidad del pedido recibido: " << cantidadDePiezas << endl;
    std::cout << "-----------------------------------" << endl;
    
    return 0;
}

int atencionDePedidos(std::map<int, int>& map1, std::map<string, int>& map2, vector<string>& talleres)
{
    std::cout << "-----------------------------------" << endl;
    std::cout << "\tAtencion de pedidos" << endl;

    int cantidadDePiezas = obtenerCantidadDePiezas();
    if (cantidadDePiezas == -2) {
        return -2;
    }
    int tipoDePieza = obtenerTipoDePieza();

    do {
        string opcion;
        cantidadDePiezas = obtenerCantidadDePiezas();
        if (map1[tipoDePieza] < cantidadDePiezas) {
            msgError("No hay suficientes piezas en el inventario");
            std::cout << "Cantidad de piezas en el inventario: " << map1[tipoDePieza] << endl;
            do {
                std::cout << "Desea continuar con el pedido? (s/n): "; std::cin >> opcion;
                if (opcion != "s" && opcion != "n") {
                    msgError("Opcion invalida");
                    continue;
                }
                if (opcion.length() > 1) {
                    msgError("Ingrese un solo caracter");
                    continue;
                } else {
                    opcion = tolower(opcion[0]);
                    if (opcion == "n") {
                        return 0;
                    } else if (opcion == "s") {
                        break;
                    }
                }
            } while(opcion != "S" && opcion != "N");
        }
    } while(map1[tipoDePieza] < cantidadDePiezas);

    map1[tipoDePieza] -= cantidadDePiezas;

    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string nombreDelTaller;
    do {
        std::cout << "Ingrese el nombre del taller: ";
        getline(std::cin, nombreDelTaller);
        nombreDelTaller = validarString(nombreDelTaller);
    } while(nombreDelTaller == "");

    if (find(talleres.begin(), talleres.end(), nombreDelTaller) == talleres.end()) {
        talleres.push_back(nombreDelTaller);
    }

    guardarDatosMap(map1, "inventario.txt");
    guardarDatosArray(talleres, "talleres.txt");

    std::cout << "-----------------------------------" << endl;
    std::cout << "\tReporte" << endl;
    std::cout << "Nombre del taller: " << nombreDelTaller << endl;
    std::cout << "Tipo de pieza: " << tipoDePieza << endl;
    std::cout << "Cantidad de pedido: " << cantidadDePiezas << endl;
    std::cout << "-----------------------------------" << endl;

    return 0;
}

int reporte(std::map<int, int> map1, std::map<string, int> map2)
{
    std::cout << "-----------------------------------" << endl;
    std::cout << "\tInventario" << endl;
    std::cout << "Piezas: "; PrintMap1(map1); std::cout << endl;
    std::cout << "Proveedeores: "; PrintMap2(map2); std::cout << endl;
    std::cout << "-----------------------------------" << endl;
}

int aviso(std::map<int, int> map1)
{
    for (int i = 1; i < 6; i++) {
        if (map1[i] < 8) {
            msgError("Es necesario reponer el stock de las piezas " + to_string(i));
        }
    }
    
}

int talleresVendidos(vector<string> talleres)
{
    std::cout << "-----------------------------------" << endl;
    std::cout << "\tTalleres vendidos" << endl;
    for (int i = 0; i < talleres.size(); i++) {
        std::cout << talleres[i] << endl;
    }
    std::cout << "-----------------------------------" << endl;
}
