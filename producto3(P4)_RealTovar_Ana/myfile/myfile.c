//librerías necesarias para trabajar con las funciones a bajo nivel
#include "myfile.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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


FILE* openFile(char *path, char *mode) {
	FILE *file;

	//r - lectura
	//w - escritura
	//a - añadir al final del fichero
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
	//se guarda el carácter del fichero
	char *charfile = malloc(2);
	//se guarda toda la línea del fichero
	char *line = malloc(sizeof(char) * 120);
	//un flag para controlar que hemos llegado al final de una línea
	bool endLine = false;
	//un flag para controlar que no hay más caracteres en el fichero
	int res = 0;
	
	strcpy(line, "\0");

	//leemos caracteres hasta llegar al final del fichero o fin de linea
	do {
		res = readCharFile(file, charfile);

		//añadimos el carácter cadena vacía dependiendo del 
		//estado de la lectura del fichero
		if (res > 0) {
			charfile[1] = '\0';
		} else {
			charfile[0] = '\0';
		}
		
		//se comprueba si hemos llegado al final de una línea
		if (strcmp(charfile, "\n") == 0) {
			endLine = true;
		}

		//añadimos el carácter a la cadena de caracteres donde
		//guardamos la línea completa.,M
		strcat(line, charfile);
	} while (res > 0 && !endLine);

	return line;
}


void writeBufferFile(char *buffer, FILE *file) {
	return fwrite(buffer, sizeof(char), strlen(buffer), file);
}