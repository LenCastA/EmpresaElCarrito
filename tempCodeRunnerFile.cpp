    do {
        cout << "Ingrese la cantidad de pedido: "; cin >> cantidadDePedido;
        cantidadDePedido = validarEnteroPosi(cantidadDePedido);
        
        if (cantidadDePedido != -1 && map1[tipoDePieza] < cantidadDePedido) {
            msgError("No hay suficiente stock para completar el pedido");
            cantidadDePedido = -1;
        }
    } while (cantidadDePedido == -1);

    map1[tipoDePieza] -= cantidadDePedido;