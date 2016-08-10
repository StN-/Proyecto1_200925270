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
static inline int validar_parametro ( char [] );

/*
 *
 *
 *
 */

inline void analizar_entrada ( char _entrada[], accion **_instruccion )
{
	if(DEPURADOR)
		printf("\n\t(Cadena Entrada: %s)", _entrada);
	int longitud = strlen ( _entrada );
	(*_instruccion) = parsear_cadena_entrada ( _entrada, longitud );
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

	if (instruccion == NULL) {
		if(DEPURADOR)
			printf("\n\t(Accion: %s)", buffer);
		instruccion =  nueva_accion( validar_instruccion ( buffer ) );
	} else {
		if(DEPURADOR)
			printf("\n\t(Parametro: %s)", buffer);
		insertar_parametro ( &parametros, validar_formato_parametro ( buffer ) );
	}

	strcpy( buffer, "" );

	if (instruccion == NULL && parametros != NULL) {
		printf("\n\t Error: La entrada no concuerda con la sintaxis.");
	}

	instruccion->parametros = parametros;
	return instruccion;
}

static inline int validar_instruccion ( char _instruccion[] )
{
	convertir_minusculas ( _instruccion, _instruccion );
	if ( strcmp( _instruccion, "rep" ) == 0 )
		return 0;
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
		return 0;
	else if ( strcmp( _instruccion, "exit" ) == 0 )
		return 0;
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
		printf("\n\t(ERROR INSTRUCCION: %s)", _instruccion );
		return 0;
	}
}

static inline parametro *validar_formato_parametro ( char _argumento[] )
{
	char nombre_parametro[32];
	char valor_parametro[126];
	if ( sscanf( _argumento, "-%[^-:]::%[^:]", nombre_parametro, valor_parametro ) == 2 ) {
		sscanf( valor_parametro, "\"%[^\"]\"", valor_parametro );
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", nombre_parametro);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", valor_parametro);
		return nuevo_parametro ( validar_parametro ( nombre_parametro ), valor_parametro );
	} else if ( sscanf( _argumento, "–%[^–:]::%[^:]", nombre_parametro, valor_parametro ) == 2 ) {
		sscanf( valor_parametro, "\"%[^\"]\"", valor_parametro );
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", nombre_parametro);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", valor_parametro);
		return nuevo_parametro ( validar_parametro ( nombre_parametro ), valor_parametro );
	} else if ( sscanf( _argumento, "+%[^+:]::%[^:]", nombre_parametro, valor_parametro ) == 2 ) {
		sscanf( valor_parametro, "\"%[^\"]\"", valor_parametro );
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", nombre_parametro);
		if(DEPURADOR)
			printf("\n\t(Valor del Parametro: %s)", valor_parametro);
		return nuevo_parametro ( validar_parametro ( nombre_parametro ), valor_parametro );
	} else if ( sscanf( _argumento, "-%[^-]", nombre_parametro ) == 1 ) {
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", nombre_parametro);
		return nuevo_parametro ( validar_parametro ( nombre_parametro ), "" );
	} else if ( sscanf( _argumento, "–%[^–]", nombre_parametro ) == 1 ) {
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", nombre_parametro);
		return nuevo_parametro ( validar_parametro ( nombre_parametro ), "" );
	} else if ( sscanf( _argumento, "+%[^+]", nombre_parametro ) == 1 ) {
		if(DEPURADOR)
			printf("\n\t(Nombre Parametro: %s)", nombre_parametro);
		return nuevo_parametro ( validar_parametro ( nombre_parametro ), "" );
	} else {
		if(DEPURADOR)
			printf("\n\t(Error Parametro: %s)", _argumento);
		return nuevo_parametro ( validar_parametro ( "error" ), _argumento );
	}

	return NULL;
}

static inline int validar_parametro ( char _parametro[] )
{
	convertir_minusculas ( _parametro, _parametro );
	if ( strcmp( _parametro, "id" ) == 0 )
		return ID;
 	else if ( strcmp( _parametro, "fit" ) == 0 )
 		return FIT;
 	else if ( strcmp( _parametro, "add" ) == 0 )
 		return ADD;
 	else if ( strcmp( _parametro, "size" ) == 0 )
 		return SIZE;
	else if ( strcmp( _parametro, "unit" ) == 0 )
		return UNIT;
	else if ( strcmp( _parametro, "path" ) == 0 )
		return PATH;
	else if ( strcmp( _parametro, "type" ) == 0 )
		return TYPE;
	else if ( strcmp( _parametro, "name" ) == 0 )
		return NAME;
	else if ( strcmp( _parametro, "delete" ) == 0 )
		return DELETE;
	else
		return -1; // ERROR

	/*
	 *
	 * FalTA ID(n) : id1, id2, id3
	 *
	 */	

}


#endif // ANALIZADOR_H