//librerías necesarias para trabajar con las funciones a bajo nivel
#include "myfile.h"

#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void setPathFile(char *path) {
	//declaramos las variables para guardar la ruta y el nombre del fichero
	char namefile[20], abspath[120];
	//en esta variable se guarda la preferencia del usuario sobre la ubicación del fichero (s: ruta absoluta, otro valor: ruta relativa)
	char isAbs;

	//se pregunta al usuario por el nombre y ubicación del fichero
	printf("Introduzca el nombre del fichero: ");
	fflush(stdin);
	scanf(" %s", namefile);
	printf("Quieres especificar una ruta absoluta (s/n)?: ");
	fflush(stdin);
	scanf(" %c", &isAbs);

	if (isAbs == 's') {
		//si el usuario indica una ruta absoluta, se solicita la ubicación completa concatenándolo con el nombre del fichero
		printf("Introduzca la ruta completa del fichero: ");
		fflush(stdin);
		scanf("%s", abspath);

		strcat(abspath, "\\");
		strcat(abspath, namefile);
		strcpy(path, abspath);
	} else {
		//si la ruta es relativa, se devuelve directamente el nombre del fichero
		strcpy(path, namefile);
	}
}


int openFile(char *path, char mode) {
	if (mode == 'r') {
		//se abre el archivo en modo lectura
		return _open(path, O_RDONLY);
	} else if (mode == 'w') {
		//se abre el archivo en modo lectura/escritura y se crea en caso de no existir
		return _open(path, O_CREAT | O_RDWR);
	} else {
		return -1;
	}
}

int closeFile(int fd) {
	//se usa la función de bajo nivel para cerrar el fichero
	return _close(fd);
}


int readCharFile(int fd, char *c) {
	//se usa la función de bajo nivel para leer un fichero
	return _read(fd, c, 1);
}


void writeCharFile(int fd, char *c) {
	//se usa la función de bajo nivel para escribir un carácter
	return _write(fd, c, 1);
}
