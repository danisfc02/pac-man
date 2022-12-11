#include <iostream>
#include <conio.h>
// Definimos la variable de las filas para que tenga 29
#define rows 29
// Definimos la variable de las columnas para que haya 100
#define columns 100
// Definimos la variable de nuestro personaje para que se vea con una "0"
#define player 'O'
// Definimos los colores
#define AZUL "\x1b[34m";
#define AMARILLO "\x1b[37m";
// Definimos como se vería en el mapa "NOTHING" "WALL" y "SCORE"
enum TILES { NOTHING = ' ', WALL = '#', SCORE = '.' };
// Decimos que el mapa esta formado por filas y columnas
TILES map[rows][columns];
bool run = true;

// Definimos nombres a las acciones que usaremos
enum INPUT { QUIT, UP, DOWN, LEFT, RIGHT, UNKNOWN };
INPUT currentInput = INPUT::UNKNOWN;

// Creamos las variables para las posiciones del personaje y las puntuaciones
int player_x;
int player_y;
int current_score = 21;
int total_score;

void Setup() {
	// Colocamos a nuestro personaje en el medio de la pantalla
	player_x = columns / 2;
	player_y = rows / 2;
	// Asi logramos que la primera fila sea entera de "WALL" y que vaya recorriendo las demás para conseguir que si es la columna [0] o [j] también sea "WALL"
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			if (i == 0 || j == 0 || i == rows - 1 || j == columns - 1) {
				map[i][j] = TILES::WALL;
			}
			else {
				map[i][j] = TILES::NOTHING;
			}
		}
	}

	// Esta es la generación del mapa en la que ponemos lo que queramos que haya en cada punto quw indicamos

	map[13][0] = TILES::SCORE;
	map[14][0] = TILES::SCORE;
	map[15][0] = TILES::SCORE;
	map[16][0] = TILES::SCORE;
	map[17][0] = TILES::SCORE;

	map[0][32] = TILES::SCORE;
	map[0][33] = TILES::SCORE;
	map[0][34] = TILES::SCORE;
	map[0][67] = TILES::SCORE;
	map[0][68] = TILES::SCORE;
	map[0][69] = TILES::SCORE;

	map[rows - 1][32] = TILES::SCORE;
	map[rows - 1][33] = TILES::SCORE;
	map[rows - 1][34] = TILES::SCORE;
	map[rows - 1][67] = TILES::SCORE;
	map[rows - 1][68] = TILES::SCORE;
	map[rows - 1][69] = TILES::SCORE;

	map[13][columns - 1] = TILES::SCORE;
	map[14][columns - 1] = TILES::SCORE;
	map[15][columns - 1] = TILES::SCORE;
	map[16][columns - 1] = TILES::SCORE;
	map[17][columns - 1] = TILES::SCORE;

	map[11][0] = TILES::NOTHING;
	map[12][0] = TILES::NOTHING;
	map[18][0] = TILES::NOTHING;
	map[19][0] = TILES::NOTHING;

	map[0][31] = TILES::NOTHING;
	map[0][35] = TILES::NOTHING;
	map[0][66] = TILES::NOTHING;
	map[0][70] = TILES::NOTHING;

	map[rows - 1][31] = TILES::NOTHING;
	map[rows - 1][35] = TILES::NOTHING;
	map[rows - 1][66] = TILES::NOTHING;
	map[rows - 1][70] = TILES::NOTHING;

	map[11][columns - 1] = TILES::NOTHING;
	map[12][columns - 1] = TILES::NOTHING;
	map[18][columns - 1] = TILES::NOTHING;
	map[19][columns - 1] = TILES::NOTHING;

	// COn esto logramos que cada vez que consigamos un punto se nos sume 1 al score total
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			if (map[i][j] == TILES::SCORE) {
				total_score++;
			}
		}
	}
}

void Input() {
	// Aquí conseguimos que al pulsar una tecla se usen las funciones que creamos antes (linea 15)
	char input = _getch();   // Cambiamos el input para que instantaniamente al usar cualquier acción se cambie sin necesidad de pulsar enter
	switch (input)
	{
	case 'w':
	case 'W':
		currentInput = INPUT::UP;
		break;
	case 's':
	case 'S':
		currentInput = INPUT::DOWN;
		break;
	case 'a':
	case 'A':
		currentInput = INPUT::LEFT;
		break;
	case 'd':
	case 'D':
		currentInput = INPUT::RIGHT;
		break;
	case 'q':
	case 'Q':
		currentInput = INPUT::QUIT;
		break;
	default:
		currentInput = INPUT::UNKNOWN;
		break;
	}
}
void Logic() {
	// Creamos estas dos variables para poner las posiciones nuevas
	int player_y_new = player_y;
	int player_x_new = player_x;
	switch (currentInput)
	{
	// Si usamos la acción "QUIT" el juego se cierra
	case QUIT:
		run = false;
		break;
	// Dependiendo de que acción usemos subimos o bajamos en 1 el valor en "x" o "y" de nuestro personaje
	case UP:
		player_y_new--;
		break;
	case DOWN:
		player_y_new++;
		break;
	case LEFT:
		player_x_new--;
		break;
	case RIGHT:
		player_x_new++;
		break;
	// Aquí creamos la nueva dirección
	}
	if (player_x_new < 0) {
		player_x_new = columns - 1;
	}
	if (player_y_new < 0) {
		player_y_new = rows - 1;
	}

	player_y_new = player_y_new % rows;
	player_x_new = player_x_new % columns;

	switch (map[player_y_new][player_x_new])
	{
	// Ponemos que si al movernos hay un "WALL" no haga nada
	case TILES::WALL:
		break;
	// Si es un "SCORE" nos sume 1 punto y lo cambie por un "NOTHING"
	case TILES::SCORE:
		current_score++;
		map[player_y_new][player_x_new] = TILES::NOTHING;
	// Que ponga al personaje en su nueva localización
	default:
		player_y = player_y_new;
		player_x = player_x_new;
		break;
	}
}

void Draw() {
	// Aquí dibujamos el mapa usando "i" como "rows" y "j" como "columns"
	system("CLS");
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			if (i == player_y && j == player_x) {
				std::cout << "\033[1;31m" << player;
			}
			else if (TILES::SCORE == map[i][j]) {
				std::cout << AMARILLO; //Cambiamos el color de los puntos a amarillop
			}
			else {
				std::cout << AZUL; //Cambiamos el color de las paredes a azul al dibujarlos
			}
			std::cout << (char)map[i][j];
		}
		std::cout << std::endl;
	}
	// Con esto dibujamos la puntuación en la parte inferior de nuestro juego 

	//std::cout << "\x1b[34m";
	std::cout << "\x1b[34m" << current_score << '/' << total_score;
}

void Check() { 
	// Comprobamos que nuestra puntuación sea igual a la máxima
	if (current_score == total_score) {
	// Si es así ponemos el mensaje de "HAS GANADO" y el juego deja de funcionar
		std::cout << "\x1b[32m" << "\n \n \n \n \n HAS GANADO \n \n \n \n" << "\x1b[37m";
		run = false;
	}
}

int main()
{
// En el main ponemos que funciones estarán usandose. En este caso se usan siempre
	Setup();
	Draw();
	while (run) {
	// En este caso solo se usan las funciones cuando el juego arranque
		Input();
		Logic();
		Draw();
		Check();
	}	
}