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
                strcpy(query, "SELECT c.idCliente, c.nombre, c.apellido, COUNT(co.idCompra) AS total_compras "
                               "FROM clientes_p1 c LEFT JOIN compras_p1 co ON c.idCliente = co.idCliente "
                               "GROUP BY c.idCliente ORDER BY total_compras DESC;");
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
                    mes[strcspn(mes, "\n")] = 0; // Quitar salto de línea

                    snprintf(query, sizeof(query),
                        "SELECT c.idCliente, c.nombre, c.apellido, SUM(co.total) AS facturacion_total "
                        "FROM clientes_p1 c JOIN compras_p1 co ON c.idCliente = co.idCliente "
                        "WHERE c.idCliente = %d AND DATE_FORMAT(co.fecha, '%%Y-%%m') = '%s' "
                        "GROUP BY c.idCliente;", idCliente, mes);
                }
                break;
            case 3:
                // Lista de clientes que no han comprado ningún producto
                strcpy(query, "SELECT c.idCliente, c.nombre, c.apellido, c.correo "
                               "FROM clientes_p1 c LEFT JOIN compras_p1 co ON c.idCliente = co.idCliente "
                               "WHERE co.idCompra IS NULL;");
                break;
            case 4:
                {
                    // Lista de clientes que han comprado productos por más de una cantidad específica.
                    double monto;
                    printf("Ingrese el monto mínimo de compra: ");
                    scanf("%lf", &monto);
                    getchar();
                    snprintf(query, sizeof(query),
                        "SELECT c.idCliente, c.nombre, c.apellido, SUM(co.total) AS total_gastado "
                        "FROM clientes_p1 c JOIN compras_p1 co ON c.idCliente = co.idCliente "
                        "GROUP BY c.idCliente HAVING total_gastado > %.2lf ORDER BY total_gastado DESC;", monto);
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
                strcpy(query, "SELECT p.nombre, COUNT(d.idDevolucion) AS total_devoluciones "
                               "FROM devoluciones_p1 d "
                               "JOIN detalle_compras_p1 dc ON d.idDetalle = dc.idDetalle "
                               "JOIN productos_p1 p ON dc.idProducto = p.idProducto "
                               "GROUP BY p.idProducto ORDER BY total_devoluciones DESC;");
                break;
            case 10:
                // Lista de los clientes con su información completa para entrega
                strcpy(query, "SELECT idCliente, nombre, apellido, correo, telefono, direccion_envio, direccion_facturacion, categoria "
                               "FROM clientes_p1;");
                break;
            case 0:
                printf("Vuelva pronto!\n");
                mysql_close(&mysql);
                exit(0);
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

    // Cierre de conexión (nunca alcanzado en este ejemplo)
    mysql_close(&mysql);
    return 0;
}
