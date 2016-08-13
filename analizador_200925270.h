//analizador_200925270.h
#ifndef ANALIZADOR_H
#define ANALIZADOR_H

/*
 *
 *
 *
 */

inline void analizar_entrada ( char [], accion ** );
static inline accion *parsear_cadena_entrada ( char [], int );

static inline int validar_instruccion ( char [] );
static inline parametro *validar_formato_parametro ( char [] );
static inline parametro *validar_parametro ( char [], char [] );

/*
 *
 *
 *
 */

inline void analizar_entrada ( char _entrada[], accion **_instruccion )
{
	if(DEPURADOR)
		printf("\n\t(Entrada Del Analizador: %s)", _entrada);
	printf("\n\tAnalizando Cadena de Entrada.");

	int longitud = strlen ( _entrada );

	(*_instruccion) = parsear_cadena_entrada ( _entrada, longitud );

	if(DEPURADOR)
		printf("\n\t(Salida Del Analizador)");

	if ( (*_instruccion) == NULL )
		return;

	if(DEPURADOR)
		imprimir_instrucciones ( *_instruccion );
}

static inline accion *parsear_cadena_entrada ( char _entrada[], int _longitud )
{
	int i = 0;
	int estado = 0;

	char buffer[128] = "";
	accion *instruccion = NULL;
	parametro *parametros = NULL;

	for ( ; i < _longitud; ++i )
	{
		switch(estado)
		{
			case 0: {
				switch(_entrada[i]) {
					case ' ': case '\n': case '\t': {
						estado = 0;
					} break;
					case '#': {
						estado = 1;
						//generar accion como comentario
						instruccion = nueva_accion( COMENTARIO );
					} break;
					default: {
						strncat( buffer, &_entrada[i], 1 );
						estado = 2;
					} break;
				}
			} break;
			case 1: {
				strncat( buffer, &_entrada[i], 1 );
				estado = 1;
			} break;
			case 2: {
				switch(_entrada[i]) {
					case ' ': case '\n': case '\t': {
						if(DEPURADOR)
							printf("\n\t(Accion: %s)", buffer);
						instruccion =  nueva_accion( validar_instruccion ( buffer ) );
						strcpy( buffer, "" );
						estado = 4;
					} break;
					case '#': {
						if(DEPURADOR)
							printf("\n\t(Accion: %s)", buffer);
						instruccion =  nueva_accion( validar_instruccion ( buffer ) );
						strcpy( buffer, "" );
						estado = 1;
					} break;
					case '\"': {
						strncat( buffer, &_entrada[i], 1 );
						estado = 3;
					} break;
					default: {
						strncat( buffer, &_entrada[i], 1 );
						estado = 2;
					} break;
				}
			} break;
			case 3: {
				switch(_entrada[i]) {
					case '\"': {
						strncat( buffer, &_entrada[i], 1 );
						estado = 2;
					} break;
					default: {
						strncat( buffer, &_entrada[i], 1 );
						estado = 3;
					} break;
				}
			} break;
			case 4: {
				switch(_entrada[i]) {
					case ' ': case '\n': case '\t': {
						estado = 4;
					} break;
					case '#': {
						estado = 1;
					} break;
					default: {
						strncat( buffer, &_entrada[i], 1 );
						estado = 5;
					} break;
				}
			} break;
			case 5: {
				switch(_entrada[i]) {
					case ' ': case '\n': case '\t': {
						if(DEPURADOR)
							printf("\n\t(Parametro: %s)", buffer);
						insertar_parametro ( &parametros, validar_formato_parametro ( buffer ) );
						strcpy( buffer, "" );
						estado = 4;
					} break;
					case '#': {
						if(DEPURADOR)
							printf("\n\t(Parametro: %s)", buffer);
						insertar_parametro ( &parametros, validar_formato_parametro ( buffer ) );
						strcpy( buffer, "" );
						estado = 1;
					} break;
					case '\"': {
						strncat( buffer, &_entrada[i], 1 );
						estado = 6;
					} break;
					default: {
						strncat( buffer, &_entrada[i], 1 );
						estado = 5;
					} break;
				}
			} break;
			case 6: {
				switch(_entrada[i]) {
					case '\"': {
						strncat( buffer, &_entrada[i], 1 );
						estado = 5;
					} break;
					default: {
						strncat( buffer, &_entrada[i], 1 );
						estado = 6;
					} break;
				}
			} break;
			default: {
				estado = 0;
			} break;
		}
	}


	if ( strcmp ( buffer, "" ) != 0 ) 
	{
		if (instruccion == NULL) {
			if(DEPURADOR)
				printf("\n\t(Accion: %s)", buffer);
			instruccion =  nueva_accion( validar_instruccion ( buffer ) );
		} else {
			if(DEPURADOR)
				printf("\n\t(Parametro: %s)", buffer);
			insertar_parametro ( &parametros, validar_formato_parametro ( buffer ) );
		}
	}

	strcpy( buffer, "" );

	if (instruccion == NULL && parametros != NULL) {
		printf( "\n\t[ERROR] : La entrada no concuerda con la sintaxis.");
		return NULL;
	}

	if (instruccion == NULL && parametros == NULL) {
		return NULL;
	}

	instruccion->parametros = parametros;
	return instruccion;
}

static inline int validar_instruccion ( char _instruccion[] )
{
	convertir_minusculas ( _instruccion, _instruccion );
	if ( strcmp( _instruccion, "rep" ) == 0 )
		return REP;
	else if ( strcmp( _instruccion, "ren" ) == 0 )
		return 0;
	else if ( strcmp( _instruccion, "rem" ) == 0 )
		return 0;
	else if ( strcmp( _instruccion, "cat" ) == 0 )
		return 0;
	else if ( strcmp( _instruccion, "edit" ) == 0 )
		return 0;
	else if ( strcmp( _instruccion, "mkfs" ) == 0 )
		return 0;
	else if ( strcmp( _instruccion, "exec" ) == 0 )
		return EXEC;
	else if ( strcmp( _instruccion, "exit" ) == 0 )
		return EXIT;
	else if ( strcmp( _instruccion, "mkgrp" ) == 0 )
		return 0;
	else if ( strcmp( _instruccion, "mkusr" ) == 0 )
		return 0;
	else if ( strcmp( _instruccion, "rmgrp" ) == 0 )
		return 0;
	else if ( strcmp( _instruccion, "rmusr" ) == 0 )
		return 0;
	else if ( strcmp( _instruccion, "mkdir" ) == 0 )
		return 0;
	else if ( strcmp( _instruccion, "fdisk" ) == 0 )
		return FDISK;
	else if ( strcmp( _instruccion, "mount" ) == 0 )
		return MOUNT;
	else if ( strcmp( _instruccion, "login" ) == 0 )
		return 0;
	else if ( strcmp( _instruccion, "logout" ) == 0 )
		return 0;
	else if ( strcmp( _instruccion, "mkfile" ) == 0 )
		return 0;
	else if ( strcmp( _instruccion, "mkdisk" ) == 0 )
		return MKDISK;
	else if ( strcmp( _instruccion, "rmdisk" ) == 0 )
		return RMDISK;
	else if ( strcmp( _instruccion, "unmount" ) == 0 )
		return UNMOUNT;
	else if ( strcmp( _instruccion, "" ) == 0 ) { 
    	printf("   (Omitido)\n");
    	return 0;
    } else {
		printf( "\n\t[ERROR] : INSTRUCCION NO RECONOCIDA: %s.", _instruccion );
		return 0;
	}
}

static inline parametro *validar_formato_parametro ( char _argumento[] )
{
	char nombre_parametro[32];
	char valor_parametro[126];
	if ( sscanf( _argumento, "-%[^-:]::%[^:]", nombre_parametro, valor_parametro ) == 2 ) {
		return validar_parametro ( nombre_parametro, valor_parametro );
	} else if ( sscanf( _argumento, "–%[^–:]::%[^:]", nombre_parametro, valor_parametro ) == 2 ) {
		return validar_parametro ( nombre_parametro, valor_parametro );
	} else if ( sscanf( _argumento, "+%[^+:]::%[^:]", nombre_parametro, valor_parametro ) == 2 ) {
		return validar_parametro ( nombre_parametro, valor_parametro );
	} else if ( sscanf( _argumento, "-%[^-]", nombre_parametro ) == 1 ) {
		return validar_parametro ( nombre_parametro, "" );
	} else if ( sscanf( _argumento, "–%[^–]", nombre_parametro ) == 1 ) {
		return validar_parametro ( nombre_parametro, "" );
	} else if ( sscanf( _argumento, "+%[^+]", nombre_parametro ) == 1 ) {
		return validar_parametro ( nombre_parametro, "" );
	} else {
		return validar_parametro ( "error", _argumento );
	}
	return NULL;
}

static inline parametro *validar_parametro ( char _nombre[], char _valor[] )
{
	convertir_minusculas ( _nombre, _nombre );
	if ( strcmp( _nombre, "fit" ) == 0 )
	{
		convertir_minusculas ( _valor, _valor );
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", _nombre);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", _valor);
		return nuevo_parametro ( FIT, _valor );
 	} 
 	else if ( strcmp( _nombre, "add" ) == 0 )
 	{
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", _nombre);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", _valor);
 		return nuevo_parametro ( ADD, _valor );
 	} 
 	else if ( strcmp( _nombre, "size" ) == 0 )
 	{
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", _nombre);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", _valor);
 		return nuevo_parametro ( SIZE, _valor );
 	} 
 	else if ( strcmp( _nombre, "unit" ) == 0 )
 	{
 		convertir_minusculas ( _valor, _valor );
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", _nombre);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", _valor);
		return nuevo_parametro ( UNIT, _valor );
	} 
	else if ( strcmp( _nombre, "path" ) == 0 )
	{
		sscanf( _valor, "\"%[^\"]\"", _valor );
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", _nombre);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", _valor);
		return nuevo_parametro ( PATH, _valor );
	} 
	else if ( strcmp( _nombre, "type" ) == 0 )
	{
		convertir_minusculas ( _valor, _valor );
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", _nombre);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", _valor);
		return nuevo_parametro ( TYPE, _valor );
	} 
	else if ( strcmp( _nombre, "name" ) == 0 )
	{
		sscanf( _valor, "\"%[^\"]\"", _valor );
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", _nombre);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", _valor);
		return nuevo_parametro ( NAME, _valor );
	} 
	else if ( strcmp( _nombre, "delete" ) == 0 )
	{
		convertir_minusculas ( _valor, _valor );
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", _nombre);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", _valor);
		return nuevo_parametro ( DELETE, _valor );
	} 
	else if ( strcmp( _nombre, "id" ) == 0 )
	{
		// convertir_minusculas ( _valor, _valor );
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", _nombre);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", _valor);
		return nuevo_parametro ( ID, _valor );
	} 
	else if ( strcmp( _nombre, "error" ) == 0 )
	{
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", _nombre);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", _valor);
		return nuevo_parametro ( -1, _valor );
	}
	else
	{
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", _nombre);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", _valor);
		return nuevo_parametro ( -1, _valor );
	}

	// if ( strcmp( _parametro, "id" ) == 0 )
	// 	return ID;
 // 	else 

	/*
	 *
	 * FalTA ID(n) : id1, id2, id3
	 *
	 */	
}


#endif // ANALIZADOR_H