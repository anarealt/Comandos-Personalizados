
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
* - mode: modo apertura del fichero (r: sólo lectura, w: escritura).
*
* Devuelve un entero que hace referencia al descriptor del fichero,
* si el valor es -1 significa que hay un error en la apertura.
**************************************************************/
int openFile(char *path, char mode);

/**************************************************************
* Realiza el cierre del fichero. 
*
* Recibe un parámetro de entrada:
* - fd: es la referencia al descriptor del fichero

* Devuelve un entero con el resultado de la operación,
* en caso de error, su valor será -1.
**************************************************************/
int closeFile(int fd);


/**************************************************************
* Leer el siguiente carácter del fichero
*
* Recibe dos parámetros de entrada: 
* - fd: es la referencia al descriptor del fichero
* - c: es una variable donde se almacena el carácter leído
*
* Devuelve un entero que indica el estado de la operación (1: ok,
* 0: fin de fichero)
**************************************************************/
int readCharFile(int fd, char *c);


/**************************************************************
* Escribe un carácter en la siguiente posición del curso del 
* fichero
*
* Recibe dos parámetros de entrada:
* - fd: es la referencia al descriptor del fichero
* - c: contiene el caracter a copiar en el fichero
*
**************************************************************/
void writeCharFile(int fd, char *c);
