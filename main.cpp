#include "validaciones.cpp"
#include <map>
#include <vector>
#include <algorithm>

float cantidadDePedido, tipoDePieza, opcion;
string tipoDeProveedor, nombreDelTaller;
map<int, int> map1;
map<string, int> map2;
vector<string> talleres;

int recepcionDePedidos()
{
    cout << "-----------------------------------" << endl;
    do{
        cout << "Ingrese la cantidad del pedido: "; cin >> cantidadDePedido;
        cantidadDePedido = validarNumPosi(cantidadDePedido);
        cantidadDePedido = validarEntero(cantidadDePedido);

        if (cantidadDePedido < 50 || cantidadDePedido > 100) {
            cerr << "\033[31m" << "Cantidad de pedido invalida" << "\033[0m" << endl;
            cantidadDePedido = -1;
        }
    } while(cantidadDePedido == -1);
    
    do {
        cout << "Ingrese el tipo de pieza: "; cin >> tipoDePieza;

        tipoDePieza = validarNumPosi(tipoDePieza);
        tipoDePieza = validarEntero(tipoDePieza);

        if (tipoDePieza > 5) {
            cerr << "\033[31m" << "Tipo de pieza invalido" << "\033[0m" << endl;
            tipoDePieza = -1;;
        }

    } while(tipoDePieza == -1);

    do{
        cout << "Ingrese el tipo de proveedor: "; cin >> tipoDeProveedor;

        if (tipoDeProveedor.length() > 1){
            cerr << "\033[31m" << "Ingrese un solo caracter" << "\033[0m" << endl;
            tipoDeProveedor = "";
            continue;
        }
        if (tipoDeProveedor != "A" && tipoDeProveedor != "B" && tipoDeProveedor != "C"){
            cerr << "\033[31m" << "Tipo de proveedor invalido" << "\033[0m" << endl;
            tipoDeProveedor = "";
        } else {
            tipoDeProveedor = toupper(tipoDeProveedor[0]);
        }

    } while(tipoDeProveedor == "");

    map1[tipoDePieza] += cantidadDePedido;
    map2[tipoDeProveedor] += cantidadDePedido;

    cout << "-----------------------------------" << endl;
    cout << "\tReporte" << endl;
    cout << "Tipo de pieza: " << tipoDePieza << endl;
    cout << "Tipo de proveedor: " << tipoDeProveedor << endl;
    cout << "Cantidad del pedido recibido: " << cantidadDePedido << endl;
    cout << "-----------------------------------" << endl;
}

int atencionDePedidos()
{
    cout << "-----------------------------------" << endl;
    cout << "\tAtencion de pedidos" << endl;

    do {
        cout << "Ingrese el tipo de pieza: "; cin >> tipoDePieza;
        tipoDePieza = validarNumPosi(tipoDePieza);
        tipoDePieza = validarEntero(tipoDePieza);

        if (tipoDePieza > 5) {
            cerr << "\033[31m" << "Tipo de pieza invalido" << "\033[0m" << endl;
            tipoDePieza = -1;;
        }

    } while(tipoDePieza == -1);
    
    do {
        cout << "Ingrese la cantidad de pedido: "; cin >> cantidadDePedido;
        cantidadDePedido = validarNumPosi(cantidadDePedido);
        cantidadDePedido = validarEntero(cantidadDePedido);
    } while (cantidadDePedido == -1);

    if (map1[tipoDePieza] < cantidadDePedido) {
        cerr << "\033[31m" << "No hay suficiente stock para completar el pedido" << "\033[0m" << endl;
        return 0;
    } else {
        map1[tipoDePieza] -= cantidadDePedido;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Ingrese el nombre del taller: ";
        getline(cin, nombreDelTaller);
        nombreDelTaller = validarStringAlfabetico(nombreDelTaller);
    } while(nombreDelTaller == "");

    if (find(talleres.begin(), talleres.end(), nombreDelTaller) == talleres.end()) {
        talleres.push_back(nombreDelTaller);
    }

    cout << "-----------------------------------" << endl;
    cout << "\tReporte" << endl;
    cout << "Nombre del taller: " << nombreDelTaller << endl;
    cout << "Tipo de pieza: " << tipoDePieza << endl;
    cout << "Cantidad de pedido: " << cantidadDePedido << endl;
    cout << "-----------------------------------" << endl;
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
            cerr << "\033[31m" << "Es necesario reponer el stock de las piezas " << i << "\033[0m" << endl;
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
    map1[1] = 100;
    map1[2] = 100;
    map1[3] = 7;
    map1[4] = 6;
    map1[5] = 100;
    map2["A"] = 0;
    map2["B"] = 0;
    map2["C"] = 0;


    while (true) {
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
            opcion = validarNumPosi(opcion);
            opcion = validarEntero(opcion);
        } while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 5);
        
        if (opcion == 1) {
            recepcionDePedidos();
            reporte();
            continue;
        } else if (opcion == 2) {
            atencionDePedidos();
            reporte();
            continue;
        } else if (opcion == 3) {
            reporte();
        } else if (opcion == 4) {
            talleresVendidos();
        } else if (opcion == 5) {
            break; 
        } else {
            cerr << "\033[31m" << "Opcion invalida" << "\033[0m" << endl;
            continue;
        }
}
}
