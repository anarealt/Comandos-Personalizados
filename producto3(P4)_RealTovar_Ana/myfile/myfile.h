#include <stdlib.h>
#include <stdio.h>

/**************************************************************
* Se solicita al usuario la ubicaci�n del fichero.
*
* Recibe un par�metro de entrada:
* - path: se guarda la ruta absoluta/completa junto al nombre
* del fichero.
**************************************************************/
void setPathFile(char *path);

/**************************************************************
* Realiza la apertura del fichero.
*
* Recibe dos par�metros de entrada:
* - path: contiene la ubicaci�n abosoluta/relativa del fichero
* - mode: modo apertura del fichero (r: s�lo lectura, 
* w: escritura, a: a�adir).
*
* Devuelve un tipo FILE con la referencia al fichero,
* si el valor es NULL significa que hay un error en la apertura.
**************************************************************/
FILE* openFile(char *path, char mode);

/**************************************************************
* Realiza el cierre del fichero.
*
* Recibe un par�metro de entrada:
* - file: es la referencia al fichero
**************************************************************/
void closeFile(FILE *file);

/**************************************************************
* Elimina el fichero.
*
* Recibe un par�metro de entrada:
* - path: contiene la ubicaci�n abosoluta/relativa del fichero
*
* Devuelve un entero con el resultado de la operaci�n,
* si el valor es 0 significa que hay un error en la cierre.
**************************************************************/
int removeFile(char *path);


/**************************************************************
* Leer el siguiente car�cter del fichero
*
* Recibe dos par�metros de entrada:
* - file: es la referencia al fichero
* - c: es una variable donde se almacena el car�cter le�do
*
* Devuelve un entero que indica el estado de la operaci�n (1: ok,
* 0: fin de fichero)
**************************************************************/
int readCharFile(FILE *file, char *charfile);


/**************************************************************
* Escribe un car�cter en la siguiente posici�n del curso del
* fichero
*
* Recibe dos par�metros de entrada:
* - file: es la referencia al descriptor del fichero
* - c: contiene el caracter a copiar en el fichero
*
**************************************************************/
void writeCharFile(FILE *file, char *c);


/**************************************************************
* Lee la siguiente l�nea de caracteres del fichero
*
* Recibe un par�metro de entrada:
* - file: es la referencia al fichero
*
* Devuelve una cadena de caracteres terminada en 
* "\n" (fin de l�nea), si es una cadena vac�a ("\0") significa
* que no hay m�s l�neas para leer.
**************************************************************/
char* readLineFile(FILE *file);


/**************************************************************
* Escribe una l�nea de caracteres en el fichero
*
* Recibe dos par�metros de entrada:
* - file: es la referencia al fichero
* - buffer: es la cadena que se guarda en el fichero
**************************************************************/
void writeBufferFile(char *buffer, FILE *file);