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

	/*
	 *  ARGUMENTO SIZE OBLIGATORIO
	 */

	char arg_size[5] = "";
	if ( !buscar_parametro ( _parametros, SIZE, arg_size ) ) {
		agregar_parametro ( &errores, ERROR, "No existe el parametro <<size>>" );
	}

	int valor_arg = 0;
	if ( !validar_convertir_decimal ( &valor_arg, arg_size ) ) {
		agregar_parametro ( &errores, ERROR, "El valor del paramatro <<size>>, no es numerico." );
	}

	if( valor_arg <= 0) {
		agregar_parametro ( &errores, ERROR, "El valor del paramatro <<size>>, debe ser mayor a cero." );
	}

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
				agregar_parametro ( &errores, ERROR, "El valor del paramatro <<unit>>, debe ser <<k>> o <<m>>." );
			} break;
		}
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


	verificar_creacion_disco_virtual ( arg_path, valor_arg, arg_unit_ );
}

inline void validar_eliminacion_disco ( parametro **_parametros, parametro **_errores )
{
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

	verificar_eliminacion_disco_virtual ( arg_path );
}

inline void validar_montar_disco ( parametro **_parametros, parametro **_errores )
{
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
    
	/*
	 *  ARGUMENTO NAME OBLIGATORIO
	 */

	char arg_name[32] = "";
	if ( !buscar_parametro ( _parametros, NAME, arg_name ) ) {
		agregar_parametro ( &errores, ERROR, "No existe el parametro <<name>>" );
	}

	if( cantidad_parametros ( errores ) > 0 ) {
		(*_errores) = errores;
		return;
	}

	if( cantidad_parametros ( (*_parametros) ) > 0 ) {
		return;
	}

	//verificar_montar_disco ( arg_path, arg_name );
}

inline void validar_desmontar_disco ( parametro **_parametros, parametro **_errores )
{
	parametro *errores = NULL;
	if( cantidad_parametros ( (*_parametros) ) == 0 ) {
		agregar_parametro ( &errores, ERROR, "Debe de ingresar al menos un parametro." );
	}

	/*
	 *  ARGUMENTO ID OBLIGATORIO
	 */

	char arg_id[12] = "";
	if ( !buscar_parametro ( _parametros, ID, arg_id ) ) {
		agregar_parametro ( &errores, ERROR, "No existe el parametro <<id>>" );
	}
    
	if( cantidad_parametros ( errores ) > 0 ) {
		(*_errores) = errores;
		return;
	}

	if( cantidad_parametros ( (*_parametros) ) > 0 ) {
		return;
	}

	//verificar_desmontar_disco ( arg_id );
}

#endif // ADMINISTRADOR_DISCO_H