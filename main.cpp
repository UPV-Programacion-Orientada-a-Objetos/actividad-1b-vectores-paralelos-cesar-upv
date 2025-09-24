#include <iostream>
#include <iomanip> // para hacer bonitos los mensajes

// cargar productos iniciales...
const int SIZE = 5;
const int codigos[SIZE] = {60, 61, 62, 63, 64};
const std::string nombres[SIZE] = {"Destornillador de Estrella", "Rotomartillo", "Bolsa de Clavos", "Llave inglesa", "Cinta metrica"};
int stocks[SIZE] = {10, 20, 15, 25, 5};
const float precios[SIZE] = {71.92f, 1485.00f, 75.00f, 185.73f, 310.00f};

void consultar_producto(void); // funciones principales
void actualizar_inventario(void);
void crear_reporte(void);
void buscar_producto_mas_caro(void);

int index_por_codigo(int busqueda); // funciones auxiliares
void cambiar_stock(int index, int stock_cambio, bool necesita_confirmacion);
int preguntar_int(std::string pregunta);
int obtener_index_producto(std::string mensaje);
bool confirmar_accion(void);

int main(int argc, char *argv[])
{
    // primero validar el máximo de productos que es 100
    if (SIZE > 100)
    {
        std::cout << "\nError: tamaño global SIZE es mayor a 100. \n\n";
        return 1;
    }

    // especificar que todos los floats se impriman SIN notación cientifica y con dos decimales
    std::cout << std::fixed << std::setprecision(2);

    // menú principal del programa
    int menu_int = -1;
    while (menu_int != 0)
    {
        std::cout << "---- Ferretería \"El Martillo\" ---- \n";
        std::cout << "1 | Consulta de producto \n";
        std::cout << "2 | Actualización de inventario \n";
        std::cout << "3 | Reporte de inventario \n";
        std::cout << "4 | Buscar producto más caro \n";
        std::cout << "0 | Salir \n";
        menu_int = preguntar_int("OPCIÓN A REALIZAR: ");

        switch (menu_int)
        {
        case 1:
            consultar_producto();
            break;
        case 2:
            actualizar_inventario();
            break;
        case 3:
            crear_reporte();
            break;
        case 4:
            buscar_producto_mas_caro();
            break;
        case 0:
            std::cout << "\nSaliendo del programa... \n\n";
            break;
        default:
            std::cout << "\nError: opción inválida. \n\n";
            break;
        }
    }

    return 0;
}

/**
 * func. principal que consulta e imprime de forma extensa la información de un producto.
 */
void consultar_producto()
{
    std::cout << "\n- - CONSULTAR PRODUCTO\n";
    int index = obtener_index_producto("Código del producto a consultar: ");

    if (index != -1)
    {
        std::cout << "\nInformación del Producto: \n";
        std::cout << std::left << std::setw(20) << "Código: " << codigos[index] << std::endl;
        std::cout << std::left << std::setw(19) << "Nombre: " << nombres[index] << std::endl;
        std::cout << std::left << std::setw(19) << "Cantidad en stock: " << stocks[index] << std::endl;
        std::cout << std::left << std::setw(19) << "Precio unitario: " << "$" << precios[index] << "\n\n";
    }
}

/**
 * func. principal que actualiza el stock de un producto, primero obteniendo el producto, y luego
 * llama a otra función que evalua el nuevo stock, pidiendo una confirmación.
 */
void actualizar_inventario()
{
    std::cout << "\n- - ACTUALIZAR INVENTARIO\n";
    int index = obtener_index_producto("Código del producto a actualizar: ");

    if (index != -1)
    {
        std::string stock_cambio_string;
        std::cout << "\nNombre: " << nombres[index] << " | Stock actual: " << stocks[index] << "\n";
        int stock_cambio = preguntar_int("Ingresar nuevo stock, o stock a eliminar: ");
        cambiar_stock(index, stock_cambio, true);
    }
}

/**
 * func. principal que imprime un reporte de inventario con los detalles de
 * los productos disponibles.
 */
void crear_reporte()
{
    std::cout << "\n------------------ Reporte de Inventario ------------------\n";
    std::cout << std::left << std::setw(8) << "Código" << std::setw(32) << "| Nombre" << std::setw(9) << "| Stock" << std::setw(8) << "| Precio\n";
    std::cout << "-----------------------------------------------------------\n";
    for (int i = 0; i < SIZE; i++)
    {
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
void buscar_producto_mas_caro()
{
    // empezar con el primer elemento de la lista...
    float precio_mayor = precios[0];

    // recorrer los precios hasta encontrar el mayor de todos
    for (int i = 0; i < SIZE; i++)
    {
        if (precios[i] > precio_mayor)
        {
            precio_mayor = precios[i];
        }
    }

    // imprimir todos los productos que tengan este precio
    std::cout << "\nProducto(s) más caros: \n";
    for (int i = 0; i < SIZE; i++)
    {
        if (precio_mayor == precios[i])
        {
            std::cout << nombres[i] << " con un precio de $" << precios[i] << std::endl;
        }
    }
    std::cout << std::endl;
}

/**
 * func. auxiliar que recorre el array de códigos de acuerdo a un término de búsqueda y retorna un índice válido o de error (-1).
 * @param busqueda código a buscar.
 */
int index_por_codigo(int busqueda)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (codigos[i] == busqueda)
        {
            return i;
        }
    }

    return -1; // error, si no encuentra nada
}

/**
 * func. auxiliar que determina y confirma un cambio de stock.
 * @param index el indice del producto
 * @param stock_cambio el stock a eliminar/añadir
 * @param necesita_confirmacion booleano para determinar si se necesita confirmar la operación (para cambios individuales o masivos)
 */
void cambiar_stock(int index, int stock_cambio, bool necesita_confirmacion)
{
    // si el nuevo stock es inferior a 0...
    if (stocks[index] + stock_cambio < 0)
    {
        std::cout << "\nError: el nuevo stock es menor a 0. \n\n";
        return;
    }

    if (!necesita_confirmacion) {
        stocks[index] += stock_cambio;
    } else {
        // avisar al usuario..
        std::cout << "\nEl nuevo stock de [" << nombres[index] << "] será de: " << (stocks[index] + stock_cambio) << ".\n";

        if (confirmar_accion()) {
            stocks[index] += stock_cambio;
        }
    }
}

/**
 * func. auxiliar que pregunta al usuario repetidamente por un número entero negativo o positivo hasta que ingrese uno válido y lo retorna.
 * @param pregunta cadena de texto de la pregunta hacia el usuario.
 */
int preguntar_int(std::string pregunta)
{
    std::string input_usuario;
    bool es_valido = false;

    do
    {
        std::cout << pregunta;
        std::cin >> input_usuario;

        try
        { // convertir el string a int...
            return std::stoi(input_usuario); 
        }
        catch (const std::invalid_argument &e)
        { // si NO ingresa un número
            std::cout << "\nError: por favor, ingrese un número. \n\n";
        }
        catch (const std::out_of_range &e)
        { // si el número está fuera de los limites de un int
            std::cout << "\nError: valor ingresado fuera del rango. \n\n";
        }
    } while (!es_valido);

    return 0;
}

/**
 * func. auxiliar que le pide al usuario un código de producto y retorna el indice del producto, si es que lo encuentra.
 * @param mensaje la pregunta con la que se pedirá el código.
 */
int obtener_index_producto(std::string mensaje) {
    int busqueda = preguntar_int(mensaje);
    int index = index_por_codigo(busqueda);

    if (index == -1)
    {
        std::cout << "\nError: código no encontrado. \n\n";
    }

    return index;
}

/**
 * func. auxiliar confirmar una operacion al usuario hasta que ingrese una opcion correcta.
 */
bool confirmar_accion() {
    std::string confirmar_cambio;
    std::cout << "Está seguro que desea continuar? [Y/N]: ";
    std::cin >> confirmar_cambio;
    
    while (confirmar_cambio != "y" && confirmar_cambio != "Y" && confirmar_cambio != "n" && confirmar_cambio != "N")
    {
        std::cout << "\nError: opción inválida. Desea continuar? [Y/N]: ";
        std::cin >> confirmar_cambio;
    }

    // terminar operación
    if (confirmar_cambio == "y" || confirmar_cambio == "Y")
    {
        std::cout << "\nAcción realizada con éxito. \n\n";
        return true;
    }
    else
    {
        std::cout << "\nAcción cancelada exitosamente. \n\n";
        return false;
    }
}