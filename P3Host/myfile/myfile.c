//librer�as necesarias para trabajar con las funciones a bajo nivel
#include "myfile.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void setPathFile(char *path) {
	//declaramos las variables para guardar la ruta y el nombre del fichero
	char namefile[20], abspath[120];
	//en esta variable se guarda la preferencia del usuario sobre la ubicaci�n del fichero (s: ruta absoluta, otro valor: ruta relativa)
	char isAbs;

	//se pregunta al usuario por el nombre y ubicaci�n del fichero
	printf("Introduzca el nombre del fichero: ");
	fflush(stdin);
	scanf(" %s", namefile);
	printf("Quieres especificar una ruta absoluta (s/n)?: ");
	fflush(stdin);
	scanf(" %c", &isAbs);

	if (isAbs == 's') {
		//si el usuario indica una ruta absoluta, se solicita la ubicaci�n completa concaten�ndolo con el nombre del fichero
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


FILE* openFile(char *path, char *mode) {
	FILE *file;

	//r - lectura
	//w - escritura
	//a - a�adir al final del fichero
	if (mode == "r" | mode == "w" || mode == "a") {
		file = fopen(path, mode);
	}
	
	return file;
}


void closeFile(FILE *file) {
	fclose(file);
}


int removeFile(char *path) {
	return remove(path);
}


int readCharFile(FILE *file, char *charfile) {
	return fscanf(file, "%c", charfile);
}


void writeCharFile(FILE *file, char *c) {
	return fprintf(file, "%c", c);
}


char* readLineFile(FILE *file) {
	//se guarda el car�cter del fichero
	char *charfile = malloc(2);
	//se guarda toda la l�nea del fichero
	char *line = malloc(sizeof(char) * 120);
	//un flag para controlar que hemos llegado al final de una l�nea
	bool endLine = false;
	//un flag para controlar que no hay m�s caracteres en el fichero
	int res = 0;
	
	strcpy(line, "\0");

	//leemos caracteres hasta llegar al final del fichero o fin de linea
	do {
		res = readCharFile(file, charfile);

		//a�adimos el car�cter cadena vac�a dependiendo del 
		//estado de la lectura del fichero
		if (res > 0) {
			charfile[1] = '\0';
		} else {
			charfile[0] = '\0';
		}
		
		//se comprueba si hemos llegado al final de una l�nea
		if (strcmp(charfile, "\n") == 0) {
			endLine = true;
		}

		//a�adimos el car�cter a la cadena de caracteres donde
		//guardamos la l�nea completa.,M
		strcat(line, charfile);
	} while (res > 0 && !endLine);

	return line;
}


void writeBufferFile(char *buffer, FILE *file) {
	return fwrite(buffer, sizeof(char), strlen(buffer), file);
}