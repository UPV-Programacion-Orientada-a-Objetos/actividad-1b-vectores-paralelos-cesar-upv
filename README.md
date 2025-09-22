[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/NCwY-w0V)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=20630544)

# Actividad - Vectores Paralelos

## Sistema de Gestión de Inventario para una Ferretería

### Definición del Problema

La ferretería "El Martillo" necesita un sistema de gestión de inventario simple para sus productos más vendidos. El sistema debe ser capaz de almacenar, gestionar y consultar información clave sobre un número fijo de artículos. Debido a las limitaciones de hardware y la necesidad de un rendimiento predecible sin sobrecarga de memoria dinámica, se ha decidido utilizar arreglos paralelos.

El sistema deberá gestionar los siguientes datos para cada producto:

  * Código de Producto: Un número entero único que identifica al producto.

  * Nombre del Producto: Una cadena de caracteres que describe el artículo.

  * Cantidad en Stock: Un número entero que representa el inventario actual.

  * Precio Unitario: Un número de punto flotante que indica el precio de venta de cada unidad.

Todos estos datos deberán almacenarse en arreglos estáticos paralelos, donde el índice de cada arreglo se corresponde con el mismo producto. El tamaño máximo (y total) de estos arreglos se establece en 100 productos, lo que corresponde al número máximo de productos que el sistema deberá gestionar.

---

### Requisitos Funcionales y No Funcionales

#### Requisitos Funcionales

  1. **Carga de Datos Iniciales**: El programa debe inicializar los arreglos con un conjunto de datos de al menos 5 productos predefinidos al arrancar.

  2. **Consulta de Productos**: El usuario podrá ingresar un código de producto para ver toda la información asociada: nombre, cantidad en stock y precio. Si el producto no existe, se deberá mostrar un mensaje de error claro.

  3. **Actualización de Inventario**: El usuario podrá ingresar un código de producto y una cantidad para actualizar el stock. La cantidad puede ser positiva (sumar al stock) o negativa (restar del stock). No se permitirá que la cantidad en stock sea inferior a cero.

  4. **Generación de Reporte**: El programa deberá mostrar un reporte completo de todos los productos en el inventario, listando el código, nombre, cantidad y precio de cada uno.

  5. **Búsqueda del Producto Más Caro**: El sistema deberá identificar y mostrar el nombre y el precio del producto con el precio unitario más alto.


#### Requisitos No Funcionales

  1. **Tecnología**: El programa debe ser desarrollado en lenguaje de programación C++.

  2. **Estructura de Datos**: El almacenamiento de datos debe realizarse exclusivamente con arreglos estáticos de tamaño fijo (std::string, int, float), sin usar std::vector o std::array.

  3. **Rendimiento**: El programa debe tener un tiempo de respuesta rápido y predecible, dado que el tamaño del conjunto de datos es fijo y conocido.

  4. **Robustez**: El sistema debe manejar entradas inválidas del usuario (como letras en campos numéricos o códigos de producto que no existen) mostrando mensajes de error apropiados sin terminar la ejecución abruptamente.

  5. **Interfaz de Usuario (CLI)**: La interacción con el usuario se realizará a través de la línea de comandos (consola).

---

### Entregables

* Un único archivo `.cpp` que contenga la implementación completa del programa.

* El código debe estar comentado para explicar la lógica de las funciones principales.

* El código debe ser compilable con un compilador estándar de C++ (ej. g++).

---

### Ejemplo de Salida del Sistema

```bash
--- Bienvenido al Sistema de Inventario de "El Martillo" ---

Seleccione una opción:
1. Consultar un producto
2. Actualizar inventario
3. Generar reporte completo
4. Encontrar el producto más caro
5. Salir

Opción seleccionada: 1

Ingrese el código del producto a consultar: 101

Información del Producto:
Código: 101
Nombre: Martillo de bola
Cantidad en stock: 50
Precio unitario: $15.50

--- Menú principal ---

Seleccione una opción:
1. Consultar un producto
2. Actualizar inventario
3. Generar reporte completo
4. Encontrar el producto más caro
5. Salir

Opción seleccionada: 3

--- Reporte de Inventario ---
Código    | Nombre             | Stock | Precio
-------------------------------------------------
101       | Martillo de bola   | 50    | $15.50
102       | Destornillador     | 120   | $8.75
103       | Cinta métrica      | 75    | $20.00
104       | Llave inglesa      | 45    | $25.99
105       | Taladro inalámbrico| 10    | $120.00
... y así sucesivamente para todos los productos.
-------------------------------------------------

--- Fin del Reporte ---

--- Menú principal ---

Seleccione una opción:
1. Consultar un producto
2. Actualizar inventario
3. Generar reporte completo
4. Encontrar el producto más caro
5. Salir

Opción seleccionada: 4

El producto más caro es: Taladro inalámbrico con un precio de $120.00
```