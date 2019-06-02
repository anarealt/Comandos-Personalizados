#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../myfile/myfile.h"





/**************************************************************
* Se solicita al usuario la ubicación relativa o completa
* del fichero hosts
**************************************************************/
 char* getPathHostsFile() {
	//guarda la ruta del fichero
	char pathfile[120];

	//se guarda en la variable 'pathfile' la ruta del fichero
	printf("-- FICHERO HOSTS --\n");
	setPathFile(pathfile);

	return pathfile;
}

 /**************************************************************
 * Se solicita al usuario la ubicación relativa o completa
 * del fichero de pares (ip-url)
 **************************************************************/
 char* getPathPairFile() {
	 //guarda la ruta del fichero 
	 char pathfile[120];

	 //se guarda en la variable 'pathfile' la ruta del fichero
	 printf("\n\n-- FICHERO IP-URLS --\n");
	 setPathFile(pathfile);

	 return pathfile;
 }


/**************************************************************
* Muestra por pantalla el contenido de un fichero ubicado en 
* la variable path.
**************************************************************/
void showFile(char *path) {
	//declaramos una variable para referenciar el fichero
	FILE *file;
	//aquí se guarda cada una de las líneas leídas del fichero
	char *buffer = malloc(120);

	//se realiza la apertura del fichero en modo lectura
	file = openFile(path, "r");

	//se comprueba si la apertura es correcta
	if (file == NULL) {
		printf("Error en la apertura del archivo\n");
	} else {
		//vamos leyendo linea a línea hasta que nos indica que es una cadena vacía
		do {
			strcpy(buffer, readLineFile(file));
			//se muestra el contenido de la linea por pantalla
			printf("%s", buffer);
		} while (strcmp(buffer, "\0") != 0);

		//cerramos el fichero para liberar recursos
		closeFile(file);
	}
}

/**************************************************************
* Comprueba si la cadena introducida por el usuario existe
* dentro del fichero hosts.
**************************************************************/
bool matchOnHost(char *input, char *pathHost) {
	//contiene una referencia al fichero hosts
	FILE *file;
	//con esta variable se controla que la cadena existe dentro del fichero
	bool fullmatch;
	//estas dos variables se usan para controlar el matcheo y la longitud máxima 
	//de la cadena de entrada
	int posMatch, max;
	//aquí se guarda el contenido de una línea del fichero hosts
	char *buffer = malloc(120);


	//se realiza la apertura del fichero host en modo lectura
	file = openFile(pathHost, "r");

	//se comprueba si la apertura es correcta
	if (file == NULL) {
		printf("Error en la apertura del archivo\n");
	} else {
		posMatch = 0;
		fullmatch = false;
		max = strlen(input);

		//se van leyendo líneas del fichero hosts hasta llegar al final o encontrar la cadena
		//que viene como parámetro de entrada.
		do {
			//se copia en buffer la línea donde buscaremos
			strcpy(buffer, readLineFile(file));

			//detecta fin de fichero o el inicio de un comentario
			if (strcmp(buffer, "\0") != 0 && buffer[0] != '#') {
				for (int i = 0; i < strlen(buffer); ++i) {
					if (buffer[i] == input[posMatch]) {
						//avanzamos la posición que hace referencia al matching entre el texto del fichero y el del usuario
						posMatch++;
					} else {
						//reiniciamos la comparación
						posMatch = 0;
						if (buffer[i] == input[posMatch]) {
							posMatch++;
						}
					}

					//si la posición del matching tiene el tamaño del texto, hemos llegado al final.
					if (posMatch == max) {
						fullmatch = true;
					}
				}
			}

		} while (strcmp(buffer, "\0") != 0 && !fullmatch);


		//cerramos el fichero para liberar recursos
		closeFile(file);
	}

	return fullmatch;
}



/**************************************************************
* Lee el archivo de pares (ip-url) y comprueba si existe en el
* archivo host y en caso contrario, lo almacena en un fichero
* temporal.
**************************************************************/
void readPairAndCheckHost(char *pathHost) {
	//declaramos una variable para referenciar el fichero pares 
	// y el fichero temporal
	FILE *file, *filetmp;
	//guarda el contenido de un fichero
	char *buffer = malloc(120);
	//un flag para controlar que la ip-url leída esta en el fichero host
	bool foundHost = false;
	//guarda la ruta del fichero de pares
	char *path = malloc(120);

	//se realiza la apertura del fichero en modo lectura
	strcpy(path, getPathPairFile());
	file = openFile(path, "r");

	//se realiza la apertura del fichero temporal
	filetmp = openFile("hosttmp.txt", "w");

	//se comprueba si la apertura es correcta
	if (file == NULL || filetmp == NULL) {
		printf("Error en la apertura del archivo\n");
	} else {
		do {
			//vamos leyenda cada una de las lineas del fichero pares
			strcpy(buffer, readLineFile(file));
			//se comprueba que el fichero ip-url leído esta en el fichero host
			foundHost = matchOnHost(buffer, pathHost);

			//si no esta, el resultado se guarda en un fichero temporal
			if (!foundHost) {
				writeBufferFile(buffer, filetmp);
			}
		} while (strcmp(buffer, "\0") != 0);

		//cerramos el fichero para liberar recursos
		closeFile(file);
		closeFile(filetmp);
	}
}

/**************************************************************
* Añade los pares (ip-url) del archivo temporal al final del
* archivo host.
**************************************************************/
void addPairsToHost(char *pathHost) {
	//declaramos una variable para referenciar al fichero host y temporal
	FILE *filehost, *filetmp;
	//guarda la línea leído de un fichero
	char *buffer = malloc(120);
	//
	bool foundHost = false;
	//un flag que controla la primera escritura
	bool firstOnce = true;

	//abre el fichero host en modo escritura colocando el puntero al final del fichero para añadir
	filehost = openFile(pathHost, "a");
	filetmp = openFile("hosttmp.txt", "r");

	//se comprueba si la apertura es correcta
	if (filehost == NULL || filetmp == NULL) {
		printf("Error en la apertura del archivo\n");
	} else {
		//vamos leyendo cada línea (ip-url) y se escribe al final del fichero host.
		do {
			strcpy(buffer, readLineFile(filetmp));
				
			if (firstOnce) {
				firstOnce = false;
				writeBufferFile("\n", filehost);
			}
			//se escribe el contenido en el fichero host
			writeBufferFile(buffer, filehost);
		} while (strcmp(buffer, "\0") != 0);

		//cerramos el fichero para liberar recursos
		closeFile(filehost);
		closeFile(filetmp);
	}

	//se eliminar el fichero temporal del disco
	removeFile("hosttmp.txt");
}


/**************************************************************
* AQUÍ COMIENZA LA EJECUCIÓN DEL PROGRAMA
**************************************************************/
int main(void)
{
	char *pathHost = malloc(120);

	//se muestra el contenido del fichero host por pantalla
	strcpy(pathHost, getPathHostsFile());
	showFile(pathHost);

	//se leer las parejas (ip-url) y se guarda en un fichero temporal
	//los que no estén en el fichero host
	readPairAndCheckHost(pathHost);
	
	//se añaden al final del fichero host las nuevas parejas y se elimina
	//el fichero temporal
	addPairsToHost(pathHost);

	return EXIT_SUCCESS;
}