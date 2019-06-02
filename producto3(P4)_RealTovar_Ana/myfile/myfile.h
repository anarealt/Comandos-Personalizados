#include <stdlib.h>
#include <stdio.h>

/**************************************************************
* Se solicita al usuario la ubicación del fichero.
*
* Recibe un parámetro de entrada:
* - path: se guarda la ruta absoluta/completa junto al nombre
* del fichero.
**************************************************************/
void setPathFile(char *path);

/**************************************************************
* Realiza la apertura del fichero.
*
* Recibe dos parámetros de entrada:
* - path: contiene la ubicación abosoluta/relativa del fichero
* - mode: modo apertura del fichero (r: sólo lectura, 
* w: escritura, a: añadir).
*
* Devuelve un tipo FILE con la referencia al fichero,
* si el valor es NULL significa que hay un error en la apertura.
**************************************************************/
FILE* openFile(char *path, char mode);

/**************************************************************
* Realiza el cierre del fichero.
*
* Recibe un parámetro de entrada:
* - file: es la referencia al fichero
**************************************************************/
void closeFile(FILE *file);

/**************************************************************
* Elimina el fichero.
*
* Recibe un parámetro de entrada:
* - path: contiene la ubicación abosoluta/relativa del fichero
*
* Devuelve un entero con el resultado de la operación,
* si el valor es 0 significa que hay un error en la cierre.
**************************************************************/
int removeFile(char *path);


/**************************************************************
* Leer el siguiente carácter del fichero
*
* Recibe dos parámetros de entrada:
* - file: es la referencia al fichero
* - c: es una variable donde se almacena el carácter leído
*
* Devuelve un entero que indica el estado de la operación (1: ok,
* 0: fin de fichero)
**************************************************************/
int readCharFile(FILE *file, char *charfile);


/**************************************************************
* Escribe un carácter en la siguiente posición del curso del
* fichero
*
* Recibe dos parámetros de entrada:
* - file: es la referencia al descriptor del fichero
* - c: contiene el caracter a copiar en el fichero
*
**************************************************************/
void writeCharFile(FILE *file, char *c);


/**************************************************************
* Lee la siguiente línea de caracteres del fichero
*
* Recibe un parámetro de entrada:
* - file: es la referencia al fichero
*
* Devuelve una cadena de caracteres terminada en 
* "\n" (fin de línea), si es una cadena vacía ("\0") significa
* que no hay más líneas para leer.
**************************************************************/
char* readLineFile(FILE *file);


/**************************************************************
* Escribe una línea de caracteres en el fichero
*
* Recibe dos parámetros de entrada:
* - file: es la referencia al fichero
* - buffer: es la cadena que se guarda en el fichero
**************************************************************/
void writeBufferFile(char *buffer, FILE *file);