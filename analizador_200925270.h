//analizador_200925270.h




inline void analizar_entrada ( char _entrada[], accion **_instruccion )
{
	//este metodo validar si es un comentario
	//salir del bucle (exit)
	//o un accion


	// int no_parametro = 0;
	// char buffer[128] = "";
	// parametro *lista = NULL;
	// char nombre_comando[64] = "";

	// int i = 0;
	// int estado = 0;
	// for ( ; i < _tamano_cadena; ++i ) 
	// {
	// 	switch(estado)
	// 	{
	// 		case 0: {
	// 			switch(_entrada[i]) {
	// 				case ' ': case '\n': case '\t': {
	// 					estado = 0;
	// 				} break;
	// 				case '#': {
	// 					estado = 3;
	// 					--i;
	// 				} break;
	// 				default: {
	// 					estado = (_entrada[i]=='\"'||_entrada[i]=='\'') ? 2 : 1;
	// 	 				strncat( buffer, &_entrada[i], 1 );
	// 				} break;
	// 			}
	// 		} break;
	// 		case 1: {
	// 			switch(_entrada[i]) {
	// 				case ' ': case '\n': case '\t': { // ARGUMENTO ACEPTADO
	// 					( no_parametro > 0) ? validar_parametro ( &lista, buffer ) : 
	// 						strcpy( nombre_comando, buffer );

	// 					strcpy( buffer, "" );
	// 					++no_parametro;
	// 					estado = 0;
	// 				} break;
	// 				case '#': {  // ARGUMENTO ACEPTADO
	// 					( no_parametro > 0) ? validar_parametro ( &lista, buffer ) : 
	// 						strcpy( nombre_comando, buffer );

	// 					strcpy( buffer, "" );
	// 					++no_parametro;
	// 					estado = 3;
	// 					--i;
	// 				} break;
	// 				default: {
	// 					estado = (_entrada[i]=='\"'||_entrada[i]=='\'') ? 2 : 1;
	// 	 				strncat( buffer, &_entrada[i], 1 );
	// 				} break;
	// 			}
	// 		} break;
	// 		case 2: {
	// 			estado = (_entrada[i]=='\"'||_entrada[i]=='\'') ? 1 : 2;
 // 				strncat( buffer, &_entrada[i], 1 );
	// 		} break;
	// 		case 3: {
 // 				// strncat( buffer, &_entrada[i], 1 );
	// 			estado = 3;
	// 		} break;
	// 	}
	// }

	// if ( strlen( buffer ) > 0 )
	// 	( no_parametro > 0) ? validar_parametro ( &lista, buffer ) : 
	// 		strcpy( nombre_comando, buffer );

	// pasar_cadena_minusculas ( nombre_comando, nombre_comando );
	// int opcion = validar_ejecutar_comando ( nombre_comando, &lista );
	// //free ( lista );
	// return opcion;
}

inline accion *parsear_cadena_entrada ( char _entrada[], int _longitud )
{
	int i = 0;
	int estado = 0;
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
						//--i;
					} break;
					default: {
						//estado = (_entrada[i]=='\"'||_entrada[i]=='\'') ? 2 : 1;
						estado = 2;
		 				//strncat( buffer, &_entrada[i], 1 );
					} break;
				}
			} break;
			case 1: {
				estado = 1;
				// concatenar si es posible...
			} break;
			case 2: {
				switch(_entrada[i]) {
					case ' ': case '\n': case '\t': {
						estado = 4;
					} break;
					case '#': {
						estado = 1;
					} break;
					case '\"': {
						estado = 3;
					} break;
					default: {
						//estado = (_entrada[i]=='\"'||_entrada[i]=='\'') ? 2 : 1;
						estado = 2;
		 				//strncat( buffer, &_entrada[i], 1 );
					} break;
				}
			} break;
			case 3: {
				switch(_entrada[i]) {
					case '\"': {
						estado = 2;
						//concateno
						--i;
					} break;
					default: {
						//estado = (_entrada[i]=='\"'||_entrada[i]=='\'') ? 2 : 1;
						estado = 3;
		 				//strncat( buffer, &_entrada[i], 1 );
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
					case '\"': {
						estado = 3;
					} break;
					default: {
						//estado = (_entrada[i]=='\"'||_entrada[i]=='\'') ? 2 : 1;
						estado = 2;
		 				//strncat( buffer, &_entrada[i], 1 );
					} break;
				}
			} break;
			default: {

			} break;
		}
	}









	int no_parametro = 0;
	char buffer[128] = "";
	parametro *lista = NULL;
	char nombre_comando[64] = "";

	int i = 0;
	int estado = 0;
	for ( ; i < _tamano_cadena; ++i ) 
	{
		switch(estado)
		{
			case 0: {
				switch(_entrada[i]) {
					case ' ': case '\n': case '\t': {
						estado = 0;
					} break;
					case '#': {
						estado = 3;
						--i;
					} break;
					default: {
						estado = (_entrada[i]=='\"'||_entrada[i]=='\'') ? 2 : 1;
		 				strncat( buffer, &_entrada[i], 1 );
					} break;
				}
			} break;
			case 1: {
				switch(_entrada[i]) {
					case ' ': case '\n': case '\t': { // ARGUMENTO ACEPTADO
						( no_parametro > 0) ? validar_parametro ( &lista, buffer ) : 
							strcpy( nombre_comando, buffer );

						strcpy( buffer, "" );
						++no_parametro;
						estado = 0;
					} break;
					case '#': {  // ARGUMENTO ACEPTADO
						( no_parametro > 0) ? validar_parametro ( &lista, buffer ) : 
							strcpy( nombre_comando, buffer );

						strcpy( buffer, "" );
						++no_parametro;
						estado = 3;
						--i;
					} break;
					default: {
						estado = (_entrada[i]=='\"'||_entrada[i]=='\'') ? 2 : 1;
		 				strncat( buffer, &_entrada[i], 1 );
					} break;
				}
			} break;
			case 2: {
				estado = (_entrada[i]=='\"'||_entrada[i]=='\'') ? 1 : 2;
 				strncat( buffer, &_entrada[i], 1 );
			} break;
			case 3: {
 				// strncat( buffer, &_entrada[i], 1 );
				estado = 3;
			} break;
		}
	}

	if ( strlen( buffer ) > 0 )
		( no_parametro > 0) ? validar_parametro ( &lista, buffer ) : 
			strcpy( nombre_comando, buffer );

	pasar_cadena_minusculas ( nombre_comando, nombre_comando );
	int opcion = validar_ejecutar_comando ( nombre_comando, &lista );
	//free ( lista );
	return opcion;
}