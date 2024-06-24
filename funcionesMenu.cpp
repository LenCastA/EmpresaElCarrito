#include "functionsImportant.cpp"
#include <algorithm>

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

int obtenerCantidadDePiezas()
{
    int cantidadDePiezas;
    do {
        cout << "Ingrese la cantidad de pedido: "; cin >> cantidadDePiezas;
        cantidadDePiezas = validarEnteroPosi(cantidadDePiezas); //validamos que cantidadDePiezas sea un numero entero

    } while (cantidadDePiezas == -1);
    return cantidadDePiezas;
}

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

int recepcionDePedidos(std::map<int, int>& map1, std::map<string, int>& map2)
{
    string tipoDeProveedor;
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

int atencionDePedidos(std::map<int, int>& map1, std::map<string, int>& map2, vector<string>& talleres)
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

    string nombreDelTaller;
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

int reporte(std::map<int, int> map1, std::map<string, int> map2)
{
    cout << "-----------------------------------" << endl;
    cout << "\tInventario" << endl;
    cout << "Piezas: "; PrintMap1(map1); cout << endl;
    cout << "Proveedeores: "; PrintMap2(map2); cout << endl;
    cout << "-----------------------------------" << endl;
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
    cout << "-----------------------------------" << endl;
    cout << "\tTalleres vendidos" << endl;
    for (int i = 0; i < talleres.size(); i++) {
        cout << talleres[i] << endl;
    }
    cout << "-----------------------------------" << endl;
}
