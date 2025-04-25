
#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void menu_principal(void)
{
printf( "                                                                                                                                 ,----,                                       \n");
printf( "                                                 ,----..                ____                                                   ,/   .`|     ,----..                           \n");
printf( "    ,---,     ,---,.      ,---,. ,-.----.       /   /                 ,'  , `.     ,---,.  ,--,     ,--,      .--.--.        ,`   .'  :    /   /   v   ,-.----.        ,---,. \n");
printf( " ,`--.' |   ,'  .'      ,'  .' |      /        /   .     :         ,-+-,.' _ |   ,'  .' |  |'. v   / .`|     /  /    '.    ;    ;     /   /   .     :  v    /  v     ,'  .' | \n");
printf( " |   :  : ,---.' .' | ,---.'   | ;   :        .   /   ;.        ,-+-. ;   , || ,---.'   |  ; v `v /' / ;    |  :  /`. /  .'___,/    ,'   .   /   ;.  v ;   :    v  ,---.'   | \n");
printf( " :   |  ' |   |  |: | |   |   .' |   | .  :  .   ;   /  ` ;    ,--.'|'   |  ;| |   |   .'  `. v  /  / .'    ;  |  |--`   |    :     |   .   ;   /  ` ; |   | .v :  |   |   .' \n");
printf( " |   :  | :   :  :  / :   :  |-, .   : |: |  ;   |  ;   ; |   |   |  ,', |  ': :   :  |-,   v  vv  / ./     |  :  ;_     ;    |.';  ;   ;   |  ; v ; | .   : |: |  :   :  |-, \n");
printf( " '   '  ; :   |    ;  :   |  ;/| |   |    :  |   :  | ; | '   |   | /  | |  || :   |  ;/|    v  vv'  /       v  v    `.  `----'  |  |   |   :  | ; | ' |   |  v :  :   |  ;/| \n");
printf( " |   |  | |   :       |   :   .' |   : .  /  .   |  ' ' ' :   '   | :  | :  |, |   :   .'     v  ;  ;         `----.   v     '   :  ;   .   |  ' ' ' : |   : .  /  |   :   .' \n");
printf( " '   :  ; |   |   . | |   |  |-, ;   | |     '   ;     /  |   ;   . |  ; |--'  |   |  |-,    / v  v  v        __ v  v  |     |   |  '   '   ;  vv /  | ;   | |  v  |   |  |-, \n");
printf( " |   |  ' '   :  '; | '   :  ;/| |   | ;             ',  /    |   : |  | ,     '   :  ;/|   ;  /v  v  v      /  /`--'  /     '   :  |    v   v  ',  /  |   | ;v  v '   :  ;/| \n");
printf( " '   :  | |   |  | ;  |   |      :   ' |   '   ;   :    /     |   : '  |/      |   |    v ./__;  v  ;  v    '--'.     /      ;   |.'      ;   :    /   :   ' | vv' |   |    v \n");
printf( " ;   |.'  |   :   /   |   :   .' :   : :-'            .'      ;   | |`-'       |   :   .' |   : / v  v  ;     `--'---'       '---'         v   v .'    :   : :-'   |   :   .' \n");
printf( " '---'    |   | ,'    |   | ,'   |   |.'         `---`        |   ;/           |   | ,'   ;   |/   v  ' |                                   `---`      |   |.'     |   | ,'   \n");
printf( "          `----'      `----'     `---'                        '---'            `----'     `---'     `--`                                               `---'       `----'     \n");

  printf("BIENVENID@  A NUESTRA TIENDA DEPARTAMENTAL!\n");
  printf("OPCIONES: \n");
  printf("1. Clientes que más han comprado\n");
  printf("2. Posibilidad de calcular la facturación total de un cliente en particular.\n");
  printf("3 Lista de los clientes que no han comprado ningún producto. \n");
  printf("4. Lista de todos los clientes que han comprado productos por más de una cantidad específica, proporcionada por el usuario.\n");
  printf("5. Lista de cada compra, nombre del cliente, número de productos y descripción de cada uno de los productos.\n");
  printf("6. Lista de asesores que han resuelto los problemas satisfactoriamente.\n");
  printf("7 Lista de asesores que tienen todavía casos abiertos.\n");
  printf("8 Lista de todos los productos de una categoría en particular, mostrando su nombre, descripción y comentarios (en su caso) de clientes que hayan opinado acerca de dicho producto. \n");
  printf("9. Cuántas cancelaciones y devoluciones se han hecho y cuál es el producto más devuelto.\n");
  printf("10. Lista de los clientes con su información completa para poder hacer una entrega.\n");
  printf("11. INSERT sobre la DB.\n");
  printf("12. DELETE sobre la DB.\n");
  printf("13. UPDATE sobre la DB (pendiente).\n");
  printf("0. Salir\n");
  printf("Elija una opción: ");
}

// Función que ejecuta una consulta SQL y muestra los resultados
void ejecutarConsulta(MYSQL *conn, const char *query) {
    char buffer[1024];
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i, num_fields;

    if(mysql_query(conn, query)) {
        fprintf(stderr, "Error procesando consulta \"%s\": %s\n", query, mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if(!res) {
        fprintf(stderr, "Error para almacenar resultados: %s\n", mysql_error(conn));
        return;
    }

    num_fields = mysql_num_fields(res);
    while((row = mysql_fetch_row(res))) {
        for(i = 0; i < num_fields; i++) {
            printf("%s\t", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
    mysql_free_result(res);
}

int obtenerIdValido(const char *mensaje) {
    int id;
    char entrada[50];
    
    while(1) {
        printf("%s", mensaje);
        fgets(entrada, sizeof(entrada), stdin);
        
        if(sscanf(entrada, "%d", &id) == 1 && id > 0) {
            return id;
        }
        printf("ID inválido. \n");
    }
}

int main(void) {
    MYSQL mysql;
    char query[1024];
    int opcion;
    char buffer[1024];
    
    // Datos de conexión a la base de datos
    char *server = "localhost";
    char *user = "ict23amn";
    char *passwd = "258927";
    char *db = "ict23amn";

    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)) {
        fprintf(stderr, "Error al conectar: %s\n", mysql_error(&mysql));
        exit(1);
    }

    do {
        menu_principal();
        if(scanf("%d", &opcion) != 1) {
            fprintf(stderr, "Entrada inválida\n");
            exit(1);
        }
        getchar(); // Limpiar el buffer de entrada

        switch(opcion) {
            case 1:
                // Clientes que más han comprado
                // (Contar número de compras por cliente)
                    strcpy(query, "SELECT idCliente, nombre, apellido, COUNT(idCompra) AS total_compras FROM clientes_p1 LEFT JOIN compras_p1 USING(idCliente) GROUP BY idCliente ORDER BY total_compras DESC;");
                break;
            case 2:
                {
                    // Calcular facturación total de un cliente en un mes específico.
                    // Se solicita ingresar idCliente y mes (formato 'YYYY-MM')
                    int idCliente;
                    char mes[8];
                    printf("Ingrese el ID del cliente: ");
                    scanf("%d", &idCliente);
                    getchar();
                    printf("Ingrese el mes (formato YYYY-MM): ");
                    fgets(mes, sizeof(mes), stdin);
                    mes[strcspn(mes, "\n")] = 0; // Quitar \n

                    snprintf(query, sizeof(query),
                            "SELECT idCliente, nombre, apellido, SUM(total) AS fact_total FROM clientes_p1 " 
                        "JOIN compras_p1 USING(idCliente) WHERE idCliente = %d " 
                        "AND DATE_FORMAT(fecha, '%%Y-%%m') = '%s' GROUP BY idCliente;", idCliente, mes);
                }
                break;
            case 3:
                // Lista de clientes que no han comprado ningún producto
                strcpy(query, "SELECT idCliente, nombre, apellido, correo FROM clientes_p1 LEFT JOIN compras_p1 USING(idCliente) WHERE idCompra IS NULL;");
                break;
            case 4:
                {
                    // Lista de clientes que han comprado productos por más de una cantidad específica.
                    double monto;
                    printf("Ingrese el monto mínimo de compra: ");
                    scanf("%lf", &monto);
                    getchar();
                    snprintf(query, sizeof(query),
                        "SELECT idCliente, nombre, apellido, SUM(total) AS total_gastado FROM clientes_p1 " 
                            "JOIN compras_p1 USING(idCliente) GROUP BY idCliente "
                        "HAVING total_gastado > %.2lf ORDER BY total_gastado DESC;", monto);
                
                }
                break;
            case 5:
                // Lista de cada compra, nombre del cliente, número de productos y descripción de cada uno
                  strcpy(query, "SELECT co.idCompra, c.nombre, c.apellido, COUNT(dc.idDetalle) AS num_productos, GROUP_CONCAT(p.descripcion SEPARATOR '; ') AS productos "
                                        "FROM compras_p1 co "
                               "JOIN clientes_p1 c ON co.idCliente = c.idCliente "
                                    "JOIN detalle_compras_p1 dc ON co.idCompra = dc.idCompra "
                                        "JOIN productos_p1 p ON dc.idProducto = p.idProducto "
                                    "GROUP BY co.idCompra;");
                break;
            case 6:
                // Lista de asesores que han resuelto los problemas satisfactoriamente.
                strcpy(query, "SELECT DISTINCT a.idAsesor, a.nombre, a.correo "
                               "FROM asesores_p1 a JOIN tickets_p1 t ON a.idAsesor = t.idAsesor "
                               "WHERE t.estado = 'Resuelto';");
                break;
            case 7:
                // Lista de asesores que tienen todavía casos abiertos.
                strcpy(query, "SELECT DISTINCT a.idAsesor, a.nombre, a.correo "
                               "FROM asesores_p1 a JOIN tickets_p1 t ON a.idAsesor = t.idAsesor "
                               "WHERE t.estado = 'Pendiente';");
                break;
            case 8:
                {
                    // Lista de todos los productos de una categoría en particular,
                    // mostrando nombre, descripción y comentarios (si existen) de clientes
                     int idCategoria;
                    printf("Ingrese el ID de la categoría: ");
                    scanf("%d", &idCategoria);
                    getchar();
                    snprintf(query, sizeof(query),
                        "SELECT p.idProducto, p.nombre, p.descripcion, IFNULL(GROUP_CONCAT(t.descripcion SEPARATOR '; '), 'Sin comentarios') AS comentarios "
                        "FROM productos_p1 p LEFT JOIN tickets_p1 t ON p.idProducto = t.idTicket " // Nota: ajusta esta relación según tu modelo de datos real
                            "WHERE p.idCategoria = %d "
                        "GROUP BY p.idProducto;", idCategoria);
                }
                break;
            case 9:
                // Número de cancelaciones y devoluciones, y producto más devuelto
                strcpy(query, "SELECT nombre, COUNT(idDevolucion) AS total_devoluciones "
                               "FROM devoluciones_p1 "
                               "JOIN detalle_compras_p1 USING(idDetalle) "
                               "JOIN productos_p1 USING(idProducto) "
                               "GROUP BY idProducto ORDER BY total_devoluciones DESC;");
                break;
            case 10:
                // Lista de los clientes con su información completa para entrega
                strcpy(query, "SELECT idCliente, nombre, apellido, telefono, direccion_envio AS direccion_entrega, CASE WHEN categoria = 'Oro' THEN 'Prioritario' WHEN categoria = 'Plata' THEN 'Express' ELSE 'Estándar' END AS prioridad_envio FROM clientes_p1;");
                break;
            case 0:
                printf("Vuelva pronto!\n");
                mysql_close(&mysql);
                exit(0);

            case 11: 
            {
                printf("\n--- INSERTAR NUEVO REGISTRO ---\n");
                printf("Seleccione la tabla:\n");
                printf("1. Clientes\n");
                printf("2. Productos\n");
                printf("3. Compras\n");
                printf("4. Asesores\n");
                printf("Opción: ");
                
                int opc;
                scanf("%d", &opc);
                getchar();
                
                switch(opc) {
                    case 1:
                    {
                        char nombre[50], apellido[50], correo[100], telefono[20], direccion[200], categoria[20], direccion_facturacion[50], contrasenia[50];
                        
                        printf("\nIngrese los datos del nuevo cliente:\n");
                        printf("Nombre: "); fgets(nombre, sizeof(nombre), stdin);
                        printf("Apellido: "); fgets(apellido, sizeof(apellido), stdin);
                        printf("Correo: "); fgets(correo, sizeof(correo), stdin);
                        printf("Teléfono: "); fgets(telefono, sizeof(telefono), stdin);
                        printf("Dirección: "); fgets(direccion, sizeof(direccion), stdin);
                        printf("Categoría (Oro/Plata/Bronze): "); fgets(categoria, sizeof(categoria), stdin);
                        printf("Dirección de facturación: "); fgets(direccion_facturacion, sizeof(direccion_facturacion), stdin);
                        printf("Contraseña: "); fgets(contrasenia, sizeof(contrasenia), stdin);
                        
                        nombre[strcspn(nombre, "\n")] = 0;
                        apellido[strcspn(apellido, "\n")] = 0;
                        correo[strcspn(correo, "\n")] = 0;
                        telefono[strcspn(telefono, "\n")] = 0;
                        direccion[strcspn(direccion, "\n")] = 0;
                        categoria[strcspn(categoria, "\n")] = 0;
                        direccion_facturacion[strcspn(direccion_facturacion, "\n")] = 0;
                        contrasenia[strcspn(contrasenia, "\n")] = 0;
                        
                        sprintf(query, "INSERT INTO clientes_p1(nombre, apellido, correo, telefono, direccion_envio, categoria, direccion_facturacion, contrasenia) VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", 
                                nombre, apellido, correo, telefono, direccion, categoria, direccion_facturacion, contrasenia);
                        break;
                    }
                    case 2: 
                    {
                        char nombre[100], descripcion[500];
                        int cantidad, idCategoria;
                        float precio;
                        
                        printf("\nIngrese los datos del nuevo producto:\n");
                        printf("Nombre: "); fgets(nombre, sizeof(nombre), stdin);
                        printf("Descripción: "); fgets(descripcion, sizeof(descripcion), stdin);
                        printf("Cantidad: "); scanf("%d", &cantidad);
                        printf("Precio: "); scanf("%f", &precio);
                        printf("ID Cateogoria: "); scanf("%d", &idCategoria);
                        getchar();
                        
                        nombre[strcspn(nombre, "\n")] = 0;
                        descripcion[strcspn(descripcion, "\n")] = 0;
                        
                        sprintf(query, "INSERT INTO productos_p1 (nombre, descripcion, cantidad, precio, idCategoria) VALUES ('%s', '%s', '%d', %.2f, '%d')", 
                                nombre, descripcion, cantidad, precio, idCategoria);
                        break;
                    }
                    
                    default:
                        printf("Opción no válida.\n");
                       
                }
                break;
            }

            case 12: 
            {
                printf("\n--- ELIMINAR REGISTRO ---\n");
                printf("Seleccione la tabla:\n");
                printf("1. Categoría\n");
                printf("2. Productos\n");
                printf("3. Clientes\n");
                printf("4. Compras\n");
                printf("5. Tickets\n");
                printf("6. Devoluciones\n");
                printf("Opción: ");
                
                int tabla;
                scanf("%d", &tabla);
                getchar();
                
                switch(tabla) {
                    case 1:                     {
                        int idCategoria = obtenerIdValido("ID de la categoría a eliminar: ");
                        
                        printf("¿Está seguro de eliminar esta categoría? (s/n): ");
                        char confirmacion = getchar(); 
                        
                        if(confirmacion == 's' || confirmacion == 'S') {
                            sprintf(query, "DELETE FROM categoria_p1 WHERE idCategoria = %d", idCategoria);
                        } else {
                            printf("Operación cancelada.\n");
                            continue;
                        }
                        break;
                    }
                    case 2:                     {
                        int idProducto =obtenerIdValido("ID del producto a eliminar: ");
                        
                        printf("¿Está seguro de eliminar este producto? (s/n): ");
                        char confirmacion = getchar();                         
                        if(confirmacion == 's' || confirmacion == 'S') {
                            sprintf(query, "DELETE FROM productos_p1 WHERE idProducto = %d", idProducto);
                        } else {
                            printf("Operación cancelada.\n");
                            continue;
                        }
                        break;
                    }
                    case 3:                     {
                        int idCliente =obtenerIdValido("ID del cliente a eliminar: ");
                        
                        printf("ADVERTENCIA: Esto eliminará también todas sus compras, tickets y pagos relacionados.\n");
                        printf("¿Está seguro de eliminar este cliente? (s/n): ");
                        char confirmacion = getchar();                         
                        if(confirmacion == 's' || confirmacion == 'S') {
                            sprintf(query, "DELETE FROM clientes_p1 WHERE idCliente = %d", idCliente);
                        } else {
                            printf("Operación cancelada.\n");
                            continue;
                        }
                        break;
                    }
                    case 4: 
                    {
                        int idCompra =obtenerIdValido("ID de la compra a eliminar: ");
                        
                        printf("ADVERTENCIA: Esto eliminará también todos los detalles de compra y pagos relacionados.\n");
                        printf("¿Está seguro de eliminar esta compra? (s/n): ");
                        char confirmacion = getchar(); 
                        
                        if(confirmacion == 's' || confirmacion == 'S') {
                            sprintf(query, "DELETE FROM compras_p1 WHERE idCompra = %d", idCompra);
                        } else {
                            printf("Operación cancelada.\n");
                            continue;
                        }
                        break;
                    }
                    case 5:                     {
                        int idTicket =obtenerIdValido("ID del ticket a eliminar: ");
                        
                        printf("ADVERTENCIA: Esto eliminará también las devoluciones relacionadas.\n");
                        printf("¿Está seguro de eliminar este ticket? (s/n): ");
                        char confirmacion = getchar();                         
                        if(confirmacion == 's' || confirmacion == 'S') {
                            sprintf(query, "DELETE FROM tickets_p1 WHERE idTicket = %d", idTicket);
                        } else {
                            printf("Operación cancelada.\n");
                            continue;
                        }
                        break;
                    }
                    case 6:                     {
                        int idDevolucion =obtenerIdValido("ID de la devolución a eliminar: ");
                        
                        printf("¿Está seguro de eliminar esta devolución? (s/n): ");
                        char confirmacion = getchar(); 
                        
                        if(confirmacion == 's' || confirmacion == 'S') {
                            sprintf(query, "DELETE FROM devoluciones_p1 WHERE idDevolucion = %d", idDevolucion);
                        } else {
                            printf("Operación cancelada.\n");
                            continue;
                        }
                        break;
                    }
                    default:
                        printf("Opción no válida.\n");
                        continue;
                }
                break;
            }

            default:
                printf("Opción inválida, por favor intente de nuevo.\n");
                continue;

        }

        // Ejecuta la consulta y muestra los resultados
        system("clear");
        ejecutarConsulta(&mysql, query);

        printf("\nPresiona Enter -> ");
        fgets(buffer, sizeof(buffer), stdin);
    } while(1); // Equivalente a while True en Java

    // Cierre de conexión 
    mysql_close(&mysql);
    return 0;
}