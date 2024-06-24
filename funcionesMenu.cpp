#include "functionsImportant.cpp"
#include <algorithm>

int obtenerTipoDePieza()
{
    int tipoDePieza;
    do {
        std::cout << "Ingrese el tipo de pieza: "; std::cin >> tipoDePieza;
        tipoDePieza = validarNatural(tipoDePieza, true); //validamos que tipoDePieza sea un numero entero

        if (tipoDePieza > 5) { //validamos que tipoDePieza sea una de las 5 opciones posibles
            msgError("Tipo de pieza invalido");
            tipoDePieza = -1;
        } else if (tipoDePieza == 0) {
            return -2;
        }
    } while(tipoDePieza == -1);
    return tipoDePieza;
}

int obtenerCantidadDePiezas()
{
    int cantidadDePiezas;
    do{
        cout << "Ingrese la cantidad de piezas del pedido: "; cin >> cantidadDePiezas;
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
        if (tipoDeProveedor == "0"){
            return "-2";
        } else {
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
        }

    } while(tipoDeProveedor == "");

    return tipoDeProveedor;
}

void PrintInventario(std::map<int, int>& m)
{
    for (auto& item : m) {
        std::cout << item.first << ":" << item.second << " || ";
    }
}

void PrintProveedor(std::map<string, int>& m)
{
    for (auto& item : m) {
        std::cout << item.first << ":" << item.second << " || ";
    }
}

int recepcionDePedidos(std::map<int, int>& inventario, std::map<string, int>& proveedores)
{
    //Bienvenida al usuario
    std::cout << "-----------------------------------" << endl;
    std::cout << "\tRecepcion de pedidos" << endl;

    int cantidadDePiezas; //incializando cantidad de piezas del pedido
    do
    {
        cantidadDePiezas = obtenerCantidadDePiezas();
        if (cantidadDePiezas == -2) { //-2 es codigo para volver a la accion anterior
            msgMenu();
            return -2;
        }
        if (cantidadDePiezas < 50 || cantidadDePiezas > 100){
            msgError("El pedido debe estar comprendido entre 50 y 100 piezas.");
        }
    } while (cantidadDePiezas < 50 || cantidadDePiezas > 100);

    int tipoDePieza = obtenerTipoDePieza();
    if (tipoDePieza == -2) {
        msgMenu();
        return -2;
    }
    string tipoDeProveedor = obtenerTipoDeProvedor();
    if (tipoDeProveedor == "-2") {
        msgMenu();
        return -2;
    }

    inventario[tipoDePieza] += cantidadDePiezas;
    proveedores[tipoDeProveedor] += cantidadDePiezas;

    guardarDatosMap(inventario, "inventario.txt");
    guardarDatosMap(proveedores, "proveedores.txt");

    std::cout << "-----------------------------------" << endl;
    std::cout << "\tReporte" << endl;
    std::cout << "Tipo de pieza: " << tipoDePieza << endl;
    std::cout << "Tipo de proveedor: " << tipoDeProveedor << endl;
    std::cout << "Cantidad del pedido recibido: " << cantidadDePiezas << endl;
    std::cout << "-----------------------------------" << endl;
}

int atencionDePedidos(std::map<int, int>& inventario, std::map<string, int>& proveedores, vector<string>& talleres)
{
    std::cout << "-----------------------------------" << endl;
    std::cout << "\tAtencion de pedidos" << endl;

    int tipoDePieza = obtenerTipoDePieza();
    if (tipoDePieza == -2) {
        msgMenu();
        return -2;
    }

    if (inventario[tipoDePieza] == 0) {
        msgError("No hay piezas en el inventario");
        return -2;
    }

    int cantidadDePiezas;
    string opcion;

    do {
        cantidadDePiezas = obtenerCantidadDePiezas();
        if (cantidadDePiezas == 0) {
            msgMenu();
            return -2;
        } else {
            if (inventario[tipoDePieza] < cantidadDePiezas) {
                msgError("No hay suficientes piezas en el inventario");
                std::cout << "Cantidad de piezas en el inventario: " << inventario[tipoDePieza] << endl;
                do {
                    cout << "Desea continuar con el pedido? (s/n): "; std::cin >> opcion;
                    if (opcion != "s" && opcion != "n" && opcion.length() > 1){
                        msgError("Opcion invalida");
                        continue;
                    } else {
                        opcion = tolower(opcion[0]);
                        if (opcion == "n") {
                            return 0;
                        } else if (opcion == "s") {
                            break;
                        }
                    }
                } while(opcion != "s" && opcion != "n");
            }
        }
    } while(inventario[tipoDePieza] < cantidadDePiezas);

    inventario[tipoDePieza] -= cantidadDePiezas;

    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string nombreDelTaller;
    do {
        std::cout << "Ingrese el nombre del taller: ";
        getline(std::cin, nombreDelTaller);
        if (nombreDelTaller == "0") {
            msgMenu();
            return -2;
        }
        nombreDelTaller = validarString(nombreDelTaller);
    } while(nombreDelTaller == "");

    if (std::find(talleres.begin(), talleres.end(), nombreDelTaller) == talleres.end()) {
        talleres.push_back(nombreDelTaller);
    }

    guardarDatosMap(inventario, "inventario.txt");
    guardarDatosArray(talleres, "talleres.txt");

    std::cout << "-----------------------------------" << endl;
    std::cout << "\tReporte" << endl;
    std::cout << "Nombre del taller: " << nombreDelTaller << endl;
    std::cout << "Tipo de pieza: " << tipoDePieza << endl;
    std::cout << "Cantidad de pedido: " << cantidadDePiezas << endl;
    std::cout << "-----------------------------------" << endl;

    return 0;
}

int reporte(std::map<int, int> inventario, std::map<string, int> proveedores)
{
    std::cout << "-----------------------------------" << endl;
    std::cout << "\tInventario" << endl;
    std::cout << "Piezas: "; PrintInventario(inventario); std::cout << endl;
    std::cout << "Proveedeores: "; PrintProveedor(proveedores); std::cout << endl;
    std::cout << "-----------------------------------" << endl;
}

int aviso(std::map<int, int> inventario)
{
    for (int i = 1; i < 6; i++) {
        if (inventario[i] < 8) {
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