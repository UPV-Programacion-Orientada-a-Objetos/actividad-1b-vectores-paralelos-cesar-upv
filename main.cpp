#include <iostream>
#include <iomanip> // para hacer bonitos los mensajes

// cargar productos iniciales...
const int SIZE = 5;
const int codigos[SIZE] = {60, 61, 62, 63, 64};
const std::string nombres[SIZE] = {"Destornillador de Estrella", "Rotomartillo", "Bolsa de Clavos", "Llave inglesa", "Cinta metrica"};    
int stocks[SIZE] = {10, 20, 15, 25, 5};
const float precios[SIZE] = {71.92f, 1485.00f, 75.00f, 185.73f, 310.00f};

// funciones principales
void consultar_producto(void);
void actualizar_inventario(void);
void crear_reporte(void);
void buscar_producto_mas_caro(void);

// funciones auxiliares
int index_por_codigo(std::string busqueda);
void cambiar_stock(int index, int stock_cambio);

int main(int argc, char* argv[]) {
    // primero validar el máximo de productos que es 100
    if (SIZE > 100) {
        std::cout << "\nError: tamaño global SIZE es mayor a 100. \n\n";
        return 1;
    }

    // especificar que todos los floats se impriman SIN notación cientifica y con dos decimales
    std::cout << std::fixed << std::setprecision(2);

    // menú principal del programa
    std::string menu_string = "";
    while (menu_string != "0") {
        std::cout << "---- Ferretería \"El Martillo\" ---- \n";
        std::cout << "1 | Consulta de producto \n";
        std::cout << "2 | Actualización de inventario \n";
        std::cout << "3 | Reporte de inventario \n";
        std::cout << "4 | Buscar producto más caro \n";
        std::cout << "0 | Salir \n";
        std::cout << "OPCIÓN A REALIZAR: ";
        std::cin >> menu_string;
        
        // limitar la respuesta a un carácter
        if (menu_string.length() != 1) {
            std::cout << "\nError: ingrese solo un carácter. \n\n";
            continue;
        }

        try {
            // convertir el string a int...
            int menu_int = std::stoi(menu_string);

            // mandar a llamar las funciones...
            switch (menu_int) {
                case 1: consultar_producto(); break;
                case 2: actualizar_inventario(); break;
                case 3: crear_reporte(); break;
                case 4: buscar_producto_mas_caro(); break;
                case 0: std::cout << "\nSaliendo del programa... \n\n"; break;                                                  
                default: std::cout << "\nError: opción inválida. \n\n"; break;
            }
        } catch (const std::invalid_argument& e) { // si NO ingresa un número
            std::cout << "\nError: opción inválida. \n\n";
        }
    }

    return 0;
}

/**
 * func. principal que consulta e imprime de forma extensa la información de un producto. 
 */
void consultar_producto() {
    std::string busqueda;
    std::cout << "\nCódigo a buscar: ";
    std::cin >> busqueda;

    int index = index_por_codigo(busqueda);
    if (index == -1) {
        std::cout << "\nError: código no encontrado. \n\n";
        return;
    }

    std::cout << "\nInformación del Producto: \n";
    std::cout << std::left << std::setw(20) << "Código: " << codigos[index] << std::endl;
    std::cout << std::left << std::setw(19) << "Nombre: " << nombres[index] << std::endl;
    std::cout << std::left << std::setw(19) << "Cantidad en stock: " << stocks[index] << std::endl;
    std::cout << std::left << std::setw(19) << "Precio unitario: " << "$" << precios[index] << "\n\n";
}

/**
 * func. principal que actualiza el stock de un producto, primero obteniendo el producto, y luego
 * llama a otra función que evalua el nuevo stock, pidiendo una confirmación.
 */
void actualizar_inventario() {
    std::string busqueda;
    std::cout << "\nCódigo del producto a actualizar: ";
    std::cin >> busqueda;

    int index = index_por_codigo(busqueda);
    if (index == -1) {
        std::cout << "\nError: código no encontrado. \n\n";
        return;
    }

    std::string stock_cambio_string;
    std::cout << "\n"<< nombres[index] << " | Stock actual: " << stocks[index] << "\n";    
    std::cout << "Ingresar nuevo stock, o stock a eliminar: ";
    std::cin >> stock_cambio_string;

    try {
        // convertir el string a int...
        int stock_cambio_int = std::stoi(stock_cambio_string);
        cambiar_stock(index, stock_cambio_int); // llamar a la función de cambiar stock
    } catch (const std::invalid_argument& e) { // si NO ingresa un número
        std::cout << "\nError: el stock ingresado es inválido. \n\n";
        return;
    } catch (const std::out_of_range& e) { // si el número está fuera del valor
        std::cout << "\nError: valor fuera del rango. \n\n";
        return;
    }
}

/**
 * func. principal que imprime un reporte de inventario con los detalles de
 * los productos disponibles.
 */
void crear_reporte() {
    std::cout << "\n------------------ Reporte de Inventario ------------------\n";
    std::cout << std::left << std::setw(8) << "Código" << std::setw(32) << "| Nombre" << std::setw(9) << "| Stock" << std::setw(8) << "| Precio\n";
    std::cout << "-----------------------------------------------------------\n";
    for (int i = 0; i < SIZE; i++) {
        std::cout << std::left << std::setw(7) << codigos[i];
        std::cout << std::left << "| " << std::setw(30) << nombres[i];
        std::cout << std::left << "| " << std::setw(7) << stocks[i];
        std::cout << std::left << "| " << "$" << precios[i] << std::endl;
    }
    std::cout << "-----------------------------------------------------------\n\n";    
}

/**
 * func. principal que recorre todos los productos en el inventario e imprime el más caro,
 * o varios si comparten el mismo precio.
 */
void buscar_producto_mas_caro() {
    // empezar con el primer elemento de la lista...
    float precio_mayor = precios[0];

    // recorrer los precios hasta encontrar el mayor de todos
    for (int i = 0; i < SIZE; i++) {
        if (precios[i] > precio_mayor) {
            precio_mayor = precios[i];
        }
    }

    // imprimir todos los productos que tengan este precio
    std::cout << "\nProducto(s) más caros: \n";
    for (int i = 0; i < SIZE; i++) {
        if (precio_mayor == precios[i]) {
            std::cout << nombres[i] << " con un precio de $" << precios[i] << std::endl;
        }
    }
    std::cout << std::endl;
}

/**
 * func. auxiliar que retorna el índice de un código de producto, de acuerdo a una búsqueda
 * @param busqueda código a buscar
 */
int index_por_codigo(std::string busqueda) {
    for (int i = 0; i < SIZE; i++) {
        std::string codigo_actual = std::to_string(codigos[i]);
        if (codigo_actual == busqueda) {
            return i;
        }
    }
    
    return -1; // error, si no encuentra nada
}

/**
 * func. auxiliar que determina y confirma un cambio de stock.
 * @param index el indice del producto
 * @param stock_cambio el stock a eliminar/añadir
 */
void cambiar_stock(int index, int stock_cambio) {
    // si el nuevo stock es inferior a 0...
    if (stocks[index] + stock_cambio < 0) {
        std::cout << "\nError: el nuevo stock es menor a 0. \n\n";
        return;
    }

    // avisar al usuario..
    std::string confirmar_cambio;
    std::cout << "El nuevo stock será: " << (stocks[index] + stock_cambio) << ", está seguro que desea continuar? [Y/N]: ";
    std::cin >> confirmar_cambio;

    // validar confirmación
    while (confirmar_cambio != "y" && confirmar_cambio != "Y" && confirmar_cambio != "n" && confirmar_cambio != "N") {
        std::cout << "\nError: opción inválida. Desea continuar? [Y/N]: ";
        std::cin >> confirmar_cambio;
    }

    // terminar operación
    if (confirmar_cambio == "y" || confirmar_cambio == "Y") {
        stocks[index] += stock_cambio;
        std::cout << "\nStock actualizado con exito. \n\n";
    } else {
        std::cout << "\nActualización de stock cancelada. \n\n";
    }
}