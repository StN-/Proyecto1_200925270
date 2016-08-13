//administrador_reporte_200925270.h
#ifndef ADMINISTRADOR_REPORTE_H
#define ADMINISTRADOR_REPORTE_H

/*
 *
 *
 *
 */

inline void validar_creacion_reportes ( parametro **, parametro ** );

 /*
 *
 *
 *
 */

inline void validar_creacion_reportes ( parametro **_parametros, parametro **_errores )
{
	if(DEPURADOR)
		printf("\n\t(Entrada Del Administrador de Reportes)");
	printf("\n\tValidando Parametros para la Generacion de Reportes.");

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

	int arg_type_rep = 0;
	char arg_name[32] = "";
	if ( !buscar_parametro ( _parametros, NAME, arg_name ) ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : No existe el parametro <<name>>" );
	} else {
		convertir_minusculas ( arg_name, arg_name );
		(strcmp(arg_name, "mbr") == 0) ? arg_type_rep = 1 :
		(strcmp(arg_name, "disk") == 0) ? arg_type_rep = 2 :
		// (strcmp(arg_name, "tree") == 0) ? arg_name_ = REPORTE_TIPO_TREE :
		// (strcmp(arg_name, "inode") == 0) ? arg_name_ = REPORTE_TIPO_INODE :
		// (strcmp(arg_name, "block") == 0) ? arg_name_ = REPORTE_TIPO_BLOCK :
		// (strcmp(arg_name, "sb") == 0) ? arg_name_ = REPORTE_TIPO_SUPER :
		// (strcmp(arg_name, "bm_inode") == 0) ? arg_name_ = REPORTE_TIPO_BM_INODE :
		// (strcmp(arg_name, "bm_block") == 0) ? arg_name_ = REPORTE_TIPO_BM_BLOCK :
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : El valor del paramatro <<name>>, debe ser <<mbr>>, <<disk>>, <<inode>>, <<super>>, <<block>> o <<tree>>." );
	}

	if(DEPURADOR)
		printf("\n\t(Buscando parametro: NAME)");

	/*
	 *  ARGUMENTO ID OBLIGATORIO
	 */

	char arg_id[12] = "";
	if ( !buscar_parametro ( _parametros, ID, arg_id ) ) {
		agregar_parametro ( &errores, ERROR, "\n\t[ERROR] : No existe el parametro <<id>>" );
	}

	if(DEPURADOR)
		printf("\n\t(Buscando parametro: ID)");

	if( cantidad_parametros ( errores ) > 0 ) {
		(*_errores) = errores;
		return;
	}

	if( cantidad_parametros ( (*_parametros) ) > 0 ) {
		return;
	}

	verificar_creacion_reporte ( arg_path, arg_type_rep, arg_id );
}

#endif // ADMINISTRADOR_REPORTE_H
