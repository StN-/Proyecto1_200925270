//interprete_200925270.h
#ifndef INTERPRETE_H
#define INTERPRETE_H

/*
 *
 *
 *
 */

inline int ejecutar_instrucciones ( accion ** );

inline void validar_ejecucion_archivo ( parametro **, parametro ** );
static inline void verificar_ejecucion_archivo ( char [] );
static inline void ejecutar_archivo_entrada ( FILE ** );

 /*
  *
  *
  *
  */

inline int ejecutar_instrucciones ( accion **_instrucciones )
{
	accion *instrucciones = (*_instrucciones);
	if ( instrucciones == NULL )
		return true;

	if(DEPURADOR)
		printf("\n\t(Entrada Del Interprete)");

	parametro *errores = NULL;
	switch (instrucciones->tipo)
	{
		case MKDISK: { //mKdisk -path::"/home/wxqzsvtyk/Plantillas/disk.dk" -size::2 +unit::M
			validar_creacion_disco ( &(*_instrucciones)->parametros, &errores );
		} break;
		case RMDISK: { //RmDisk -path::"/home/wxqzsvtyk/Plantillas/disk.dk"
			validar_eliminacion_disco ( &(*_instrucciones)->parametros, &errores );
		} break;
		case FDISK: { 
			// fdisk –Size::256 –path::"/home/wxqzsvtyk/Plantillas/disk.dk" –name::"Particion2" +unit::k
			// fdisk –delete::fast –path::"/home/wxqzsvtyk/Plantillas/disk.dk" –name::"Particion2"
			validar_accion_particion ( &(*_instrucciones)->parametros, &errores );
		} break;
		case MOUNT: {
			// mount –path::"/home/wxqzsvtyk/Plantillas/disk.dk" –name::"Particion1"
			// mount –path::"/home/wxqzsvtyk/Plantillas/disk.dk" –name::"Particion2"
			validar_montar_disco ( &(*_instrucciones)->parametros, &errores );
		} break;
		// case UNMOUNT: {} break;
		case REP: {
			// rep -id::vda1 –path::"/home/wxqzsvtyk/Plantillas/mbr" -name::mbr
			validar_creacion_reportes ( &(*_instrucciones)->parametros, &errores );
		} break;
		case EXEC: {

		} break;
		case EXIT: {
			return false;
		} break;
		// case 6: {} break;
		// case 7: {} break;
		default: {} break;
	}

	accion *siguiente = obtener_siguiente_instruccion ( _instrucciones );
	int resultado = ejecutar_instrucciones ( &siguiente );
	free ( siguiente );
	return resultado;
}

inline void validar_ejecucion_archivo ( parametro **_parametros, parametro **_errores )
{
	if(DEPURADOR)
		printf("\n\t(Entrada De Ejecucion de Archivos)");

	parametro *errores = NULL;
	if( cantidad_parametros ( (*_parametros) ) == 0 ) {
		agregar_parametro ( &errores, ERROR, "Debe de ingresar al menos un parametro." );
	}

	/*
	 *  ARGUMENTO PATH OBLIGATORIO
	 */

	char arg_path[128] = "";
	if ( !buscar_parametro ( _parametros, PATH, arg_path ) ) {
		agregar_parametro ( &errores, ERROR, "No existe el parametro <<path>>" );
	}

	if( cantidad_parametros ( errores ) > 0 ) {
		(*_errores) = errores;
		return;
	}

	if( cantidad_parametros ( (*_parametros) ) > 0 ) {
		return;
	}

	if(DEPURADOR)
		printf("\n\t(Si cumple con todos los requisitos para crear un Disco)");

	verificar_ejecucion_archivo( arg_path );
}

static inline void verificar_ejecucion_archivo ( char _arg_path[] )
{
	// char *sub_string = strrchr ( _arg_path_dir, '/' );
	// reemplazar ( _arg_path_dir, sub_string, "", strlen(sub_string) );
	// if ( !validar_directorio ( _arg_path_dir ) ) {
	// 	printf( "   -Error : El direcotrio <<%s>> No exite.\n", _arg_path_dir );
	// 	return;
	// }

	// if ( !validar_archivo ( _arg_path ) ) {
	// 	printf( "   -Error : El archivo <<%s>> No exite.\n", _arg_path );
	// 	return;
	// }
	
	FILE *archivo_script = fopen ( _arg_path, "r" );
	if(!archivo_script) {
		printf( "   -Error : El archivo <<%s>> No tiene permisos de lectura.\n", _arg_path );
		return;
	}

	printf(" Ejecutando Archivo <<%s>>.\n", _arg_path );

	ejecutar_archivo_entrada ( &archivo_script );

	fclose (archivo_script);
}

static inline void ejecutar_archivo_entrada ( FILE **_archivo )
{
	int numero_linea = 0;
	char buffer[128] = "";
	char cadena[256] = ""
	
	accion *instrucciones = NULL;

	while ( fgets ( buffer, sizeof(buffer), *_archivo ) ) }
	{
		//printf("  Linea No: %d :", numero_linea );
		//parsear_entrada ( buffer, strlen(buffer) );
		//++numero_linea;
		//printf("\n");

		if ( !validar_final_linea ( buffer ) ) {
			strcpy ( cadena, "" );
		}

		

		char cadena[256];
		accion *lista = NULL;
		if( !leer_entrada_consola ( cadena ) ) {
			printf("\n\t Error: La cadena es demasiado grande para procesar.");
			continue;
		}

		analizar_entrada ( cadena, &lista );
		opcion = 

	}

	ejecutar_instrucciones ( &lista );

	printf(" Finalizando Ejecucion del Archivo Script.\n");
}

static inline void cargar_archivo_entrada () {}

#endif // INTERPRETE_H