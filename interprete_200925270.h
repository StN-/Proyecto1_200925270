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
	printf("\n\tValidando Instruccion a Ejecutar.");

	parametro *errores = NULL;
	switch (instrucciones->tipo)
	{
		case MKDISK: { 
			//mKdisk -path::"/home/wxqzsvtyk/Plantillas/disk.dk" -size::6 +unit::M
			validar_creacion_disco ( &(*_instrucciones)->parametros, &errores );
		} break;
		case RMDISK: { 
			// RmDisk -path::"/home/wxqzsvtyk/Plantillas/disk.dk"
			validar_eliminacion_disco ( &(*_instrucciones)->parametros, &errores );
		} break;
		case FDISK: { 
			// fdisk –Size::512 –path::"/home/wxqzsvtyk/Plantillas/disk.dk" –name::"Particion5" +unit::w +type::l
			// fdisk –delete::fast –path::"/home/wxqzsvtyk/Plantillas/disk.dk" –name::"Particion3" 
			validar_accion_particion ( &(*_instrucciones)->parametros, &errores );
		} break;
		case MOUNT: {
			// mount -y::z –path::"/home/wxqzsvtyk/Plantillas/disk.dk" –name::"Particion1"
			// mount –path::"/home/wxqzsvtyk/Plantillas/disk.dk" –name::"Particion7"
			validar_montar_disco ( &(*_instrucciones)->parametros, &errores );
		} break;
		// case UNMOUNT: {} break;
		case REP: {
			// rep -id::vda1 –path::"/home/wxqzsvtyk/Plantillas/mbr" -name::mbr
			// rep -id::vda1 –path::"/home/wxqzsvtyk/Plantillas/mbr.png" -name::disk
			validar_creacion_reportes ( &(*_instrucciones)->parametros, &errores );
		} break;
		case EXEC: {
			// exec -path::"/home/wxqzsvtyk/Plantillas/ArchivoScript.txt"
			validar_ejecucion_archivo ( &(*_instrucciones)->parametros, &errores );
		} break;
		case COMENTARIO: {
			return true;
		} break;
		case EXIT: {
			return false;
		} break;
		// case 6: {} break;
		// case 7: {} break;
		default: {} break;
	}

	printf("\n\t(ERRORES ENCONTRADOS:)");
	imprimir_parametros ( errores );
	printf("\n");
	printf("\n\t(PARAMETROS DEMAS:)");
	imprimir_parametros ( instrucciones->parametros );

	return true;
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
	char cadena[256] = "";

	int longitud = 0;	
	//accion *instrucciones = NULL;

	while ( fgets ( buffer, sizeof(buffer), *_archivo ) )
	{
		accion *lista = NULL;

		longitud = strlen( cadena );
		if ( validar_final_linea ( buffer ) )
		{
			longitud += strlen ( buffer ) + 1;
			if( longitud < 255 ) {
				concatenar ( cadena, 1, buffer );
			} else {
				printf("\n\t Error: La cadena es demasiado grande para procesar.");
			}			
			continue;
		} else {
			longitud += strlen ( buffer ) + 1;
			if( longitud < 255 ) {
				concatenar ( cadena, 1, buffer );
			} else {
				printf("\n\t Error: La cadena es demasiado grande para procesar.");
				continue;
			}
		}

		analizar_entrada ( cadena, &lista );
		//insertar_instruccion ( &instrucciones, lista );
		ejecutar_instrucciones ( &lista );
		strcpy ( cadena, "" );
	}

	
	printf(" Finalizando Ejecucion del Archivo Script.\n");
}

static inline void cargar_archivo_entrada () {}

#endif // INTERPRETE_H