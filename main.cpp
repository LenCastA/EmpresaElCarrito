#include "validaciones.cpp"
#include <map>
#include <vector>
#include <algorithm>

float cantidadDePedido, tipoDePieza, opcion;
string tipoDeProveedor, nombreDelTaller;
map<int, int> map1;
map<string, int> map2;
vector<string> talleres;

float validarTipoDePieza(float tipoDePieza)
{
    do {
        cout << "Ingrese el tipo de pieza: "; cin >> tipoDePieza;
        tipoDePieza = validarEnteroPosi(tipoDePieza);

        if (tipoDePieza > 5) {
            msgError("Tipo de pieza invalido");
            tipoDePieza = -1;
        }

    } while(tipoDePieza == -1);
    return tipoDePieza;
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

int recepcionDePedidos()
{
    cout << "-----------------------------------" << endl;
    cout << "\tRecepcion de pedidos" << endl;

    do{
        cout << "Ingrese la cantidad del pedido: "; cin >> cantidadDePedido;
        cantidadDePedido = validarEnteroPosi(cantidadDePedido);

        if (cantidadDePedido < 50 || cantidadDePedido > 100) {
            msgError("Cantidad de pedido invalida");
            cantidadDePedido = -1;
        }
    } while(cantidadDePedido == -1);

    tipoDePieza = validarTipoDePieza(tipoDePieza);

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

    tipoDePieza = validarTipoDePieza(tipoDePieza);
    
    do {
        cout << "Ingrese la cantidad de pedido: "; cin >> cantidadDePedido;
        cantidadDePedido = validarEnteroPosi(cantidadDePedido);
    } while (cantidadDePedido == -1);

    if (map1[tipoDePieza] < cantidadDePedido) {
        msgError("No hay suficiente stock para completar el pedido");
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
    int opcion_valida = 0;
    
    map1[1] = 100;
    map1[2] = 100;
    map1[3] = 7;
    map1[4] = 6;
    map1[5] = 100;
    map2["A"] = 0;
    map2["B"] = 0;
    map2["C"] = 0;

    while (opcion_valida != 5) {
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
            opcion_valida = int(opcion);
            if (opcion_valida > 5) {
                opcion = -1;
                msgError("Opcion invalida");
            }
        } while (opcion == -1);

        switch (opcion_valida){
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