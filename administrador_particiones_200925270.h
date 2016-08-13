//administrador_particiones_200925270.h
#ifndef ADMINISTRADOR_PARTICIONES_H
#define ADMINISTRADOR_PARTICIONES_H

/*
 *
 *
 *
 */

inline void validar_accion_particion ( parametro **, parametro ** );

/*
 *
 *
 *
 */

inline void validar_accion_particion ( parametro **_parametros, parametro **_errores )
{
	if(DEPURADOR)
		printf("\n\t(Entrada Del Administrador de Particion)");
	printf("\n\tValidando Parametros para la intruccion de Particion.");

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
	 *  ARGUMENTO NAME OBLIGATORIO
	 */

	char arg_name[32] = "";
	if ( !buscar_parametro ( _parametros, NAME, arg_name ) ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : No existe el parametro <<name>>" );
	}

	if(DEPURADOR)
		printf("\n\t(Buscando parametro: NAME)");

	/*
	 *  ARGUMENTO DELETE OPCIONAL
	 */

	char arg_delete_ = '0';
	char arg_delete[8] = "";
	if ( buscar_parametro ( _parametros, DELETE, arg_delete ) ) 
	{
		(strcmp(arg_delete, "fast") == 0) ? arg_delete_ = 'R' :
			(strcmp(arg_delete, "full") == 0) ? arg_delete_ = 'C' : 
				agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : El valor del paramatro <<delete>>, debe ser <<fast>> o <<full>>." );

		if(DEPURADOR)
			printf("\n\t(Buscando parametro: DELETE)");

		if( cantidad_parametros ( errores ) > 0 ) {
			(*_errores) = errores;
			return;
		}

		if( cantidad_parametros ( (*_parametros) ) > 0 ) {
			return;
		}

		if(DEPURADOR)
			printf("\n\t(Si cumple con todos los requisitos para eliminar una Particion)");

		verificar_eliminacion_particion ( arg_path, arg_name, arg_delete_ );
		if(DEPURADOR)
			imprimir_mbr ( arg_path );
		return;
	}

	/*
	 *  ARGUMENTO UNIT OPCIONAL
	 */

	int arg_unit_ = KiB;
	char arg_unit[3] = "";
	if ( buscar_parametro ( _parametros, UNIT, arg_unit ) )
	{
		switch(arg_unit[0]) {
			case 'm': { arg_unit_ = MiB; } break;
			case 'k': { arg_unit_ = KiB; } break;
			case 'b': { arg_unit_ = 1; } break;
			default: {
				agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : El valor del paramatro <<unit>>, debe ser <<k>>, <<m>> o <<b>>." );
			} break;
		}
	}

	if(DEPURADOR)
		printf("\n\t(Buscando parametro: UNIT)");

	/*
	 *  ARGUMENTO ADD OPCIONAL
	 */

	char arg_add[8] = "";
	if ( buscar_parametro ( _parametros, ADD, arg_add ) )
	{
		int valor_arg = 0;
		if (! validar_convertir_decimal ( &valor_arg, arg_add ) ) {
			agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : El valor del paramatro <<add>>, no es numerico." );
		}

		if(DEPURADOR)
			printf("\n\t(Buscando parametro: ADD)");

		if( cantidad_parametros ( errores ) > 0 ) {
			(*_errores) = errores;
			return;
		}

		if( cantidad_parametros ( (*_parametros) ) > 0 ) {
			return;
		}

		if(DEPURADOR)
			printf("\n\t(Si cumple con todos los requisitos para modificar una Particion)");
		// llamar al controlador del particiones...
		if(DEPURADOR)
			imprimir_mbr ( arg_path );
		return;
	}

	/*
	 *  ARGUMENTO SIZE OBLIGATORIO
	 */

	char arg_size[5] = "";
	if ( !buscar_parametro ( _parametros, SIZE, arg_size ) ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : No existe el parametro <<size>>" );
	}

	if(DEPURADOR)
		printf("\n\t(Buscando parametro: SIZE)");

	int valor_arg = 0;
	if (! validar_convertir_decimal ( &valor_arg, arg_size ) ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : El valor del paramatro <<size>>, no es numerico." );
	}

	if( valor_arg <= 0) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : El valor del paramatro <<size>>, debe ser mayor a cero." );
	}

	/*
	 *  ARGUMENTO FIT OPCIONAL
	 */

	char arg_fit_ = 'f';
	char arg_fit[3] = "";	
	if ( buscar_parametro ( _parametros, FIT, arg_fit ) )
	{
		(strcmp(arg_fit, "bf") == 0) ? arg_fit_ = 'b' :
			(strcmp(arg_fit, "ff") == 0) ? arg_fit_ = 'f' :
				(strcmp(arg_fit, "wf") == 0) ? arg_fit_ = 'w' :
					agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : El valor del paramatro <<fit>>, debe ser <<bf>>, <<ff>> o <<wf>>." );
	}

	if(DEPURADOR)
		printf("\n\t(Buscando parametro: FIT)");

	/*
	 *  ARGUMENTO TYPE OPCIONAL
	 */

	char arg_type_ = 'P';
	char arg_type[3] = "";
	if ( buscar_parametro ( _parametros, TYPE, arg_type ) )
	{
		switch(arg_type[0]) {
			case 'p': { arg_type_ = 'P'; } break;
			case 'e': { arg_type_ = 'E'; } break;
			case 'l': { arg_type_ = 'L'; } break;
			default: {
				agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : El valor del paramatro <<type>>, debe ser <<p>>, <<e>> o <<l>>." );
			} break;
		}
	}

	if(DEPURADOR)
		printf("\n\t(Buscando parametro: TYPE)");

	if( cantidad_parametros ( errores ) > 0 ) {
		(*_errores) = errores;
		return;
	}

	if( cantidad_parametros ( (*_parametros) ) > 0 ) {
		return;
	}

	if(DEPURADOR)
		printf("\n\t(Si cumple con todos los requisitos para crear una Particion)");

	verificar_creacion_particion ( arg_path, arg_name, valor_arg*arg_unit_, arg_type_, arg_fit_ );

	if(DEPURADOR)
		imprimir_mbr ( arg_path );
}

#endif // ADMINISTRADOR_PARTICIONES_H