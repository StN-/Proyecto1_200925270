//administrador_disco_200925270.h
#ifndef ADMINISTRADOR_DISCO_H
#define ADMINISTRADOR_DISCO_H

/*
 *
 *
 *
 */

inline void validar_eliminacion_disco ( parametro **, parametro ** );
inline void validar_desmontar_disco ( parametro **, parametro ** );
inline void validar_creacion_disco ( parametro **, parametro ** );
inline void validar_montar_disco ( parametro **, parametro ** );

 /*
  *
  *
  *
  */

inline void validar_creacion_disco ( parametro **_parametros, parametro **_errores )
{
	if(DEPURADOR)
		printf("\n\t(Entrada Del Administrador de Disco)");
	printf("\n\tValidando Parametros Para la creacion de Disco.");

	parametro *errores = NULL;
	if( cantidad_parametros ( (*_parametros) ) == 0 ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : Debe de ingresar al menos un parametro." );
	}

	/*
	 *  ARGUMENTO PATH OBLIGATORIO
	 */

	char arg_path[128] = "";
	if ( !buscar_parametro ( _parametros, PATH, arg_path ) ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : No existe el parametro <<path>>" );
	}

	if(DEPURADOR)
		printf("\n\t(Buscando parametro: PATH)");

	/*
	 *  ARGUMENTO SIZE OBLIGATORIO
	 */

	char arg_size[5] = "";
	if ( !buscar_parametro ( _parametros, SIZE, arg_size ) ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : No existe el parametro <<size>>" );
	}

	int valor_arg = 0;
	if ( !validar_convertir_decimal ( &valor_arg, arg_size ) ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : El valor del paramatro <<size>>, no es numerico." );
	}

	if( valor_arg <= 0) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : El valor del paramatro <<size>>, debe ser mayor a cero." );
	}

	if(DEPURADOR)
		printf("\n\t(Buscando parametro: SIZE)");

	/*
	 *  ARGUMENTO UNIT OPCIONAL
	 */

	int arg_unit_ = MiB;
	char arg_unit[3] = "";
	if ( buscar_parametro ( _parametros, UNIT, arg_unit ) ) {
		switch(arg_unit[0]) {
			case 'm': { arg_unit_ = MiB; } break;
			case 'k': { arg_unit_ = KiB; } break;
			default: {
				agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : El valor del paramatro <<unit>>, debe ser <<k>> o <<m>>." );
			} break;
		}
	}

	if(DEPURADOR)
		printf("\n\t(Buscando parametro: UNIT)");

	if( cantidad_parametros ( errores ) > 0 ) {
		(*_errores) = errores;
		return;
	}

	if( cantidad_parametros ( (*_parametros) ) > 0 ) {
		return;
	}

	if(DEPURADOR)
		printf("\n\t(Si cumple con todos los requisitos para crear un Disco)");


	verificar_creacion_disco_virtual ( arg_path, valor_arg, arg_unit_ );
}

inline void validar_eliminacion_disco ( parametro **_parametros, parametro **_errores )
{
	if(DEPURADOR)
		printf("\n\t(Entrada Del Administrador de Disco)");
	printf("\n\tValidando Parametros Para la eliminacion de Disco.");

	parametro *errores = NULL;
	if( cantidad_parametros ( (*_parametros) ) == 0 ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : Debe de ingresar al menos un parametro." );
	}

	/*
	 *  ARGUMENTO PATH OBLIGATORIO
	 */

	char arg_path[128] = "";
	if ( !buscar_parametro ( _parametros, PATH, arg_path ) ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : No existe el parametro <<path>>" );
	}

	if(DEPURADOR)
		printf("\n\t(Buscando parametro: PATH)");
    
	if( cantidad_parametros ( errores ) > 0 ) {
		(*_errores) = errores;
		return;
	}

	if( cantidad_parametros ( (*_parametros) ) > 0 ) {
		return;
	}

	if(DEPURADOR)
		printf("\n\t(Si cumple con todos los requisitos para eliminar un Disco)");

	verificar_eliminacion_disco_virtual ( arg_path );
}

inline void validar_montar_disco ( parametro **_parametros, parametro **_errores )
{
	if(DEPURADOR)
		printf("\n\t(Entrada Del Administrador de Disco)");
	printf("\n\tValidando Parametros Para montar particion.");

	parametro *errores = NULL;
	if( cantidad_parametros ( (*_parametros) ) == 0 ) {
		imprimir_particiones_montadas ( festplatten );
		return;
	}

	/*
	 *  ARGUMENTO PATH OBLIGATORIO
	 */

	char arg_path[128] = "";
	if ( !buscar_parametro ( _parametros, PATH, arg_path ) ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : No existe el parametro <<path>>" );
	}
    
	if(DEPURADOR)
		printf("\n\t(Buscando parametro: PATH)");

	/*
	 *  ARGUMENTO NAME OBLIGATORIO
	 */

	char arg_name[32] = "";
	if ( !buscar_parametro ( _parametros, NAME, arg_name ) ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : No existe el parametro <<name>>" );
	}

	if(DEPURADOR)
		printf("\n\t(Buscando parametro: NAME)");

	if( cantidad_parametros ( errores ) > 0 ) {
		(*_errores) = errores;
		return;
	}

	if( cantidad_parametros ( (*_parametros) ) > 0 ) {
		return;
	}

	if(DEPURADOR)
		printf("\n\t(Si cumple con todos los requisitos para montar una Particion)");

	verificar_montar_disco ( arg_path, arg_name );
}

inline void validar_desmontar_disco ( parametro **_parametros, parametro **_errores )
{
	if(DEPURADOR)
		printf("\n\t(Entrada Del Administrador de Disco)");
	printf("\n\tValidando Parametros Para desmontar particion.");

	parametro *errores = NULL;
	if( cantidad_parametros ( (*_parametros) ) == 0 ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : Debe de ingresar al menos un parametro." );
	}

	/*
	 *  ARGUMENTO ID OBLIGATORIO
	 */

	char arg_id[12] = "";
	if ( !buscar_parametro ( _parametros, ID, arg_id ) ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : No existe el parametro <<id>>" );
	}
    
	if(DEPURADOR)
		printf("\n\t(Buscando parametro: PATH)");

	if( cantidad_parametros ( errores ) > 0 ) {
		(*_errores) = errores;
		return;
	}

	if( cantidad_parametros ( (*_parametros) ) > 0 ) {
		return;
	}

	if(DEPURADOR)
		printf("\n\t(Si cumple con todos los requisitos para desmontar una Particion)");

	verificar_desmontar_disco ( arg_id );
}

#endif // ADMINISTRADOR_DISCO_H