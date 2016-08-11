//librerias_200925270.h
#ifndef LIBRERIA_H
#define LIBRERIA_H

/*
 *
 *
 *
 */

#define true 1
#define false 0
#define KiB 1024
#define MiB 1024*KiB
#define DEPURADOR true
#define ERROR -1

/*
 *
 *
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include <sys/types.h>
#include <dirent.h>
#include <stdarg.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 *
 *
 *
 */

#include "io_200925270.h"
#include "funciones_200925270.h"
#include "buffer_entrada_200925270.h"

#include "parametro_200925270.h"
#include "instruccion_200925270.h"

#include "particion_200925270.h"
#include "administrador_particiones_200925270.h"


#include "unidad_disco_200925270.h"
#include "manejador_disco_200925270.h"
#include "administrador_disco_200925270.h"








#include "analizador_200925270.h"
#include "interprete_200925270.h"

/*
 *
 *
 *
 */

#endif // LIBRERIA_H