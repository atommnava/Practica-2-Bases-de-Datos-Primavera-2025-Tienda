#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void menu_principal()
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
}

int main (int argc, char **argv)
{
    unsigned int i = 0;
    char     buffer[1024];
    unsigned int num_fields;

	// Se cambian los valores de estas variables dependiendo
	// del usuario que se conectará
	
    char *server = "localhost";
    char *user = "cusuario";
    char *passwd = "password";
    char *db = "usuario";

    char nombre[10];
    char apellido[10];
    char fecha[11];

    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD *fields;


    if( argc != 3 ){
      fputs("Usage: mysql <dataBase> <\"query\">\n", stderr);
      menu_principal();
      return 1;
    }

    mysql_init(&mysql); // Prepara la conexion al servidor de bases de datos

    // Se conecta al servidor de base de datos y verifica que no haya error
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
      fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
      return(0);
    }

    // Se conecta a la base de datos deseada
    if( mysql_select_db(&mysql,argv[1]) ){
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Ejecuta el query
    strcpy(buffer,argv[2]);
    if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    while( (row = mysql_fetch_row(res)) ){
        i = 0;

        for( i=0 ; i < mysql_num_fields(res); i++ ){
	  if(row[i] != NULL){
            printf("%s ",row[i]);
	  }
	  else{
	    printf(" \n");
	  }
        }
        fputc('\n',stdout);
    }

    mysql_free_result(res);
    
    // cierra la conexion con al servidor
    mysql_close(&mysql);

    return 0;
}
