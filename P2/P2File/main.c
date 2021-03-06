#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../myfile/myfile.h"


/**************************************************************
* Muestra el menú al usuario y solicita una opción 
**************************************************************/
int menu() {
	//guarda la opción seleccionada por el usuario
	int option = NULL;

	//se muestra el menú principal con todas las opciones del programa
	printf("*****************************************************************\n");
	printf("**                                                             **\n");
	printf("**                    MENU PRINCIPAL                           **\n");
	printf("**                                                             **\n");
	printf("** 1. Mostrar el contenido de un archivo                       **\n");
	printf("** 2. Guardar un archivo                                       **\n");
	printf("** 3. Chequear archivo                                         **\n");
	printf("** 4. Salir                                                    **\n");
	printf("**                                                             **\n");
	printf("**                                                             **\n");
	printf("*****************************************************************\n");
	printf("Qu\202 opci\242n desea realizar?: ");

	//se guarda la opción introducida por teclado
	fflush(stdin);
	scanf("%d", &option);

	//se comprueba que la opción es correcta, en caso contrario, se solicita de nueva una opción
	while (option <= 0 || option > 4) {
		printf("Opci\242n incorrecta, introduzca de nuevo una opci\242n: ");
		fflush(stdin);
		scanf("%d", &option);
	}

	return option;
}




/**************************************************************
* Muestra por pantalla el contenido de un fichero
**************************************************************/
void showContent() {
	//declaramos una variable para referenciar el descriptor del fichero
	int fd;
	//guarda la ruta del fichero y el caracter leído del fichero
	char pathfile[120], c = NULL;

	//se guarda en la variable 'pathfile' la ruta del fichero
	setPathFile(pathfile);

	//se realiza la apertura del fichero en modo lectura
	fd = openFile(pathfile, 'r');

	//se comprueba si la apertura es correcta
	if (fd == -1) {
		printf("Error en la apertura del archivo\n");
	} else {
		//vamos leyendo cada uno de los caracterés del fichero cuyo contenido lo mostramos por pantalla.
		while (readCharFile(fd, &c) > 0) {
			printf("%c", c);
		}

		//cerramos el fichero para liberar recursos
		if (closeFile(fd) == -1) {
			printf("Error en el cierre del fichero\n");
		}
	}
}

/**************************************************************
* Realiza una copia de un fichero y se guarda en la ruta 
* indicada por el usuario.
**************************************************************/
void saveAs() {
	//declaramos dos variables que hacen referencia al fichero origen y destino
	int fdFrom, fdTo;
	//declaramos dos varaibles para guardar las ruta de los fichero así como el carácter leído del fichero origen
	char pathfileFrom[120], pathfileTo[120], c = NULL;

	//se guarda la ruta del fichero origen
	printf("-- FICHERO ORIGEN --\n");
	setPathFile(pathfileFrom);

	//se guarda la ruta del fichero destino
	printf("\n-- FICHERO DESTINO --\n");
	setPathFile(pathfileTo);

	//se realiza la apertura del fichero origen en modo lectura
	fdFrom = openFile(pathfileFrom, 'r');

	//se realiza la apertura del fichero destino en modo escritura
	fdTo = openFile(pathfileTo, 'w');

	//se comprueba si la apertura de los ficheros es correcta
	if (fdFrom == -1 || fdTo == -1) {
		if (fdFrom == -1) {
			printf("Error en la apertura del archivo origen\n");
		} else {
			printf("Error en la apertura del archivo destino\n");
		}
	} else {
		//se van leyendo caracteres y en cada interación se guarda el carácter en el fichero
		while (readCharFile(fdFrom, &c) > 0) {
			writeCharFile(fdTo, &c);
		}

		//cerramos el fichero para liberar recursos
		if (closeFile(fdFrom) == -1 || closeFile(fdTo) == -1) {
			printf("Error en el cierre del fichero\n");
		} else {
			printf("\nEl archivo se ha guardado correctamente \n");
		}
	}
}

/**************************************************************
* Comprueba si la cadena introducida por el usuario existe
* dentro del fichero.
**************************************************************/
void checkContent() {
	//con esta variable se controla que la cadena existe dentro del fichero
	bool fullmatch;
	//declaramos una variable que hace referencia al descriptor del fichero
	//y otras dos variables para controlar el matcheo y la longitud máximo de 
	//la cadena introducida por el usuario
	int fd, posMatch, max;
	//guarda la ruta del fichero y el caracter leído del fichero
	char pathfile[120], c = NULL, inputData[120];

	//se guarda en la variable 'pathfile' la ruta del fichero
	setPathFile(pathfile);

	//se realiza la apertura del fichero en modo lectura
	fd = openFile(pathfile, 'r');

	//se guarda en la variable inputData el texto solicitado al usuario por teclado
	printf("Introduza una cadena para comprobar si esta en el fichero: ");
	scanf("%s", inputData);

	//se comprueba si la apertura es correcta
	if (fd == -1) {
		printf("Error en la apertura del archivo\n");
	}
	else {
		posMatch = 0;
		fullmatch = false;
		max = strlen(inputData);

		while (readCharFile(fd, &c) > 0 && !fullmatch) {
			//comprueba si el caracter leído coincide con el siguiente carácter del texto introducido por el usuario
			if (c == inputData[posMatch]) {
				//avanzamos la posición que hace referencia al matching entre el texto del fichero y el del usuario
				posMatch++;
			}
			else {
				//reiniciamos la comparación
				posMatch = 0;
				if (c == inputData[posMatch]) {
					posMatch++;
				}
			}

			//si la posición del matching tiene el tamaño del texto, hemos llegado al final.
			if (posMatch == max) {
				fullmatch = true;
			}
		}

		if (fullmatch) {
			printf("El texto introducido se encuentra en el fichero\n");
		}
		else {
			printf("No se ha encontrado el texto introducido en el fichero\n");
		}

		//cerramos el fichero para liberar recursos
		if (closeFile(fd) == -1) {
			printf("Error en el cierre del fichero\n");
		}
	}
}

/**************************************************************
* Controla la ejecución del menú
**************************************************************/
void showMenu()
{
	int menuOption;

	do {
		//Limpia el contenido anterior
		system("cls");
		menuOption = menu();
		//Limpia el menu una vez elegida una opción
		system("cls");

		switch (menuOption) {
		case 1: {
			showContent();
			break;
		}

		case 2: {
			saveAs();
			break;
		}

		case 3: {
			checkContent();
			break;
		}

		default:
			break;
		}

		if (menuOption != 4) {
			printf("\n");
			system("PAUSE");
		}
	} while (menuOption >= 1 && menuOption <= 3);
}


/**************************************************************
* AQUÍ COMIENZA LA EJECUCIÓN DEL PROGRAMA
**************************************************************/
int main(void)
{
	showMenu();
	return EXIT_SUCCESS;
}