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
