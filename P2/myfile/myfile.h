
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
* - mode: modo apertura del fichero (r: s�lo lectura, w: escritura).
*
* Devuelve un entero que hace referencia al descriptor del fichero,
* si el valor es -1 significa que hay un error en la apertura.
**************************************************************/
int openFile(char *path, char mode);

/**************************************************************
* Realiza el cierre del fichero. 
*
* Recibe un par�metro de entrada:
* - fd: es la referencia al descriptor del fichero

* Devuelve un entero con el resultado de la operaci�n,
* en caso de error, su valor ser� -1.
**************************************************************/
int closeFile(int fd);


/**************************************************************
* Leer el siguiente car�cter del fichero
*
* Recibe dos par�metros de entrada: 
* - fd: es la referencia al descriptor del fichero
* - c: es una variable donde se almacena el car�cter le�do
*
* Devuelve un entero que indica el estado de la operaci�n (1: ok,
* 0: fin de fichero)
**************************************************************/
int readCharFile(int fd, char *c);


/**************************************************************
* Escribe un car�cter en la siguiente posici�n del curso del 
* fichero
*
* Recibe dos par�metros de entrada:
* - fd: es la referencia al descriptor del fichero
* - c: contiene el caracter a copiar en el fichero
*
**************************************************************/
void writeCharFile(int fd, char *c);
