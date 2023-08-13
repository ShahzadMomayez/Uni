
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#pragma warning(disable:4996)

//colors
#define RED 12
#define BLUE 3
#define GREEN 10
#define YELLOW 14
#define GRAY 8
#define PINK 13
#define WHITE 15
#define WAIT_TIME_MILI_SEC 100
//directions
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
// general
#define BOARD_SIZE 30
#define INITIAL_SNAKE_LENGTH 3
#define MINIMUM_SNAKE_LENGTH 2
#define MAX_LEN_SNAKES 30
#define NUMBER_OF_MOUSES 20
//board_characters
#define EMPTY '0'
#define MOUSE 'm'
#define PLAYER1_SNAKE_HEAD '1'
#define PLAYER2_SNAKE_HEAD '2'
#define PLAYER1_SNAKE_BODY 'a'
#define PLAYER2_SNAKE_BODY 'b'
//Bernard, Poison and golden star
#define BERNARD_CLOCK 'c' //on the board character
#define GOLDEN_STAR '*' //on the board character
#define POISON 'x' //on the board character
#define NUMBER_OF_POISONS 5
#define NUMBER_OF_GOLDEN_STARS 3
#define BERNARD_CLOCK_APPEARANCE_CHANCE_PERCENT 20
#define BERNARD_CLOCK_APPEARANCE_CHECK_PERIOD_MILI_SEC 2000
#define BERNARD_CLOCK_FROZEN_TIME_MILI_SEC 4000

CONSOLE_FONT_INFOEX former_cfi;
CONSOLE_CURSOR_INFO former_info;
COORD former_screen_size;

void reset_console() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(consoleHandle, CONSOLE_WINDOWED_MODE, &former_screen_size);
	SetCurrentConsoleFontEx(consoleHandle, FALSE, &former_cfi);
	SetConsoleCursorInfo(consoleHandle, &former_info);
}

void hidecursor(HANDLE consoleHandle)
{
	GetConsoleCursorInfo(consoleHandle, &former_info);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void set_console_font_and_font_size(HANDLE consoleHandle) {
	former_cfi.cbSize = sizeof(former_cfi);
	GetCurrentConsoleFontEx(consoleHandle, FALSE, &former_cfi);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 12;
	cfi.dwFontSize.Y = 12;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Courier");
	SetCurrentConsoleFontEx(consoleHandle, FALSE, &cfi);
}

void set_full_screen_mode(HANDLE consoleHandle) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	former_screen_size.X = csbi.dwSize.X; former_screen_size.Y = csbi.dwSize.Y;
	COORD coord;
	SetConsoleDisplayMode(consoleHandle, CONSOLE_FULLSCREEN_MODE, &coord);
}

void init_screen()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	set_full_screen_mode(consoleHandle);
	hidecursor(consoleHandle);
	set_console_font_and_font_size(consoleHandle);

}

void wait_and_get_direction(int* player1_snake_direction, int* player2_snake_direction) {
	DWORD64 start_time, check_time;
	start_time = GetTickCount64();
	check_time = start_time + WAIT_TIME_MILI_SEC; //GetTickCount returns time in miliseconds
	char key = 0;
	char player1_key_hit = 0;
	char player2_key_hit = 0;

	while (check_time > GetTickCount64()) {
		if (_kbhit()) {
			key = _getch();
			if (key == 0)
				key = _getch();
			if (key == 'w' || key == 'a' || key == 's' || key == 'd')
				player1_key_hit = key;
			if (key == 'i' || key == 'j' || key == 'k' || key == 'l')
				player2_key_hit = key;
		}
	}

	switch (player1_key_hit) {
	case 'w': if (*player1_snake_direction != DOWN) *player1_snake_direction = UP; break;
	case 'a': if (*player1_snake_direction != RIGHT) *player1_snake_direction = LEFT; break;
	case 's': if (*player1_snake_direction != UP) *player1_snake_direction = DOWN; break;
	case 'd': if (*player1_snake_direction != LEFT) *player1_snake_direction = RIGHT; break;
	default: break;
	}

	switch (player2_key_hit) {
	case 'i': if (*player2_snake_direction != DOWN) *player2_snake_direction = UP; break;
	case 'j': if (*player2_snake_direction != RIGHT) *player2_snake_direction = LEFT; break;
	case 'k': if (*player2_snake_direction != UP) *player2_snake_direction = DOWN; break;
	case 'l': if (*player2_snake_direction != LEFT) *player2_snake_direction = RIGHT; break;
	default: break;
	}
}

void draw_point(char point_content) {
	switch (point_content) {
	case PLAYER1_SNAKE_HEAD: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED); printf("@"); break;
	case PLAYER2_SNAKE_HEAD: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);  printf("@"); break;
	case PLAYER1_SNAKE_BODY: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);  printf("o"); break;
	case PLAYER2_SNAKE_BODY: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);  printf("o"); break;
	case MOUSE: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY); printf("m"); break;
	case GOLDEN_STAR: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW); printf("*"); break;
	case POISON: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN); printf("x"); break;
	case BERNARD_CLOCK: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PINK); printf("c"); break;
	default: printf(" ");
	}
}

void draw_horizonatal_walls() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	for (int i = 0; i < BOARD_SIZE + 2; ++i)
		printf("-");
	printf("\n");
}

void draw_board(char board_content[BOARD_SIZE][BOARD_SIZE]) {
	system("cls");
	draw_horizonatal_walls();
	for (int i = 0; i < BOARD_SIZE; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		printf("|"); // vertical wall 
		for (int j = 0; j < BOARD_SIZE; j++)
			draw_point(board_content[i][j]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		printf("|\n"); // vertical wall
	}
	draw_horizonatal_walls();
}

// prototypes
void init_screen();
void reset_console();
void wait_and_get_direction(int* player1_snake_direction, int* player2_snake_direction);
void draw_board(char board_content[BOARD_SIZE][BOARD_SIZE]);

void INITIALIZE_BOARD(char board_content[BOARD_SIZE][BOARD_SIZE]) {  //har marhale safhe ro pak mikone
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
			board_content[i][j] = EMPTY;

	}
}
void Clear_Snake_Tail(char board_content[BOARD_SIZE][BOARD_SIZE]) {   //it deletes the tail of the snakes and also the head


	for (int i = 0; i < BOARD_SIZE; i++)           
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board_content[i][j] == PLAYER1_SNAKE_HEAD) board_content[i][j] = EMPTY;
			if (board_content[i][j] == PLAYER1_SNAKE_BODY) board_content[i][j] = EMPTY;
			if (board_content[i][j] == PLAYER2_SNAKE_BODY) board_content[i][j] = EMPTY;    //sar va body ro pak mikone
			if (board_content[i][j] == PLAYER2_SNAKE_HEAD) board_content[i][j] = EMPTY;

		}
	}

}






char Snake1_eat(char board_content[BOARD_SIZE][BOARD_SIZE], int player1_y[MAX_LEN_SNAKES], int player1_x[MAX_LEN_SNAKES], int* player1_length, int player1_snake_direction, int* player2_length) {

	int x = 0, y = 0;   
	if (player1_snake_direction == UP  && player1_y[0] == 0)                    //agar az bala raft az payin biad biron
		y = MAX_LEN_SNAKES - 1;
	else if (player1_snake_direction == UP && player1_y[0] != 0){
			y = (player1_y[0] - 1);
		x = player1_x[0];
	}



	else if (player1_snake_direction == DOWN  && player1_y[0] == (MAX_LEN_SNAKES - 1) )  x = 0;      //agar az payin raft az bala biad
	else if (player1_snake_direction == DOWN && player1_y[0] != (MAX_LEN_SNAKES - 1)) {	
		y = (player1_y[0] + 1);
		x = player1_x[0];
	}
		

	else if (player1_snake_direction == LEFT) {                              //agar az chap raft az bala rast
		if (player1_x[0] == 0)
			x = (MAX_LEN_SNAKES - 1);
		else
			x = (player1_x[0] - 1);
		y = player1_y[0];

	}
	else if (player1_snake_direction == RIGHT) {
		if (player1_x[0] == (MAX_LEN_SNAKES - 1))                       //agar az rast raft az bala chap
			x = 0;
		else
			x = (player1_x[0] + 1);
		y = player1_y[0];

	}


	if (board_content[y][x] == MOUSE && *player1_length < MAX_LEN_SNAKES)               //become longer if it eats mouse
	{
		(*player1_length)+=1;

	}
	else if (board_content[y][x] == GOLDEN_STAR && *player2_length > (MINIMUM_SNAKE_LENGTH -1) )    //other snake becomes smaller  when snake 1 eats golden star
	{
		(*player2_length)-=1;
	}
	else if (board_content[y][x] == POISON && *player1_length >( MINIMUM_SNAKE_LENGTH-1))          //become smaller if it eats poision
	{
		(*player1_length)-=1;
	}


	return board_content[y][x];
}


char Snake2_eat(char board_content[BOARD_SIZE][BOARD_SIZE], int player2_y[MAX_LEN_SNAKES], int player2_x[MAX_LEN_SNAKES], int* player2_length, int player2_snake_direction, int* player1_length) {

	int x = 0, y = 0;   
	if (player2_snake_direction == UP && player2_y[0] == 0) 
		y = MAX_LEN_SNAKES - 1;                                                     ////agar az bala raft az payin biad biron
		else if (player2_snake_direction == UP && player2_y[0] != 0){
			y = (player2_y[0] - 1);
		x = player2_x[0];
	}

	else if (player2_snake_direction == RIGHT) {            //agar az  rast raft az balachap
		if (player2_x[0] == (MAX_LEN_SNAKES - 1))
			x = 0;
		else
			x = (player2_x[0] + 1);
		y = player2_y[0];

	}

	else if (player2_snake_direction == DOWN) {
		if (player2_y[0] == (MAX_LEN_SNAKES - 1))     ////agar az payin raft az bala biad biron
			x = 0;
		else
			y = (player2_y[0] + 1);
		x = player2_x[0];
	}

	else if (player2_snake_direction == LEFT && player2_x[0] == 0)     //agar az chap raft az rast biad biron
			x = (MAX_LEN_SNAKES - 1);
	else if (player2_snake_direction == LEFT && player2_x[0] != 0)
	{
			x = (player2_x[0] - 1);
		y = player2_y[0];

	}



	if (board_content[y][x] == MOUSE && *player2_length < MAX_LEN_SNAKES)                   //taqir size mar2 based on eating mouse
	{
		(*player2_length)+=1;

	}
	else if (board_content[y][x] == GOLDEN_STAR && *player1_length > (MINIMUM_SNAKE_LENGTH -1) )              //taqir size mar2 based on eating golden star
	{
		(*player1_length)-=1;
	}
	else if (board_content[y][x] == POISON && *player2_length > (MINIMUM_SNAKE_LENGTH -1))          //taqir size mar2 based on eating stuff
	{
		(*player2_length)-=1;
	}
	

	return board_content[y][x];
}
void END_GAME_AND_CONDITIONS(char board_content[BOARD_SIZE][BOARD_SIZE], int  player1_length, int player2_length, int player1_x[MAX_LEN_SNAKES], int player1_y[MAX_LEN_SNAKES], int player2_x[MAX_LEN_SNAKES], int player2_y[MAX_LEN_SNAKES], int* condition)
{

	for (int i = 1; i < player1_length; i++)
	{
		if (player1_y[0] == player1_y[i] && player1_x[0] == player1_x[i])      //kale mar 1 be body khodesh bokhore , mar 1 mibaze
			*condition = 1; //player 1 lost the game
	}

	for (int i = 1; i < player1_length; i++)
	{
		if (player2_y[0] == player2_y[i] && player2_x[0] == player2_x[i])  //kale mar2 be body khodesh bokhore, mar 2 mibaze
			*condition = 2; //player 2 lost the game
	}


	for (int i = 1; i < player1_length; i++)
	{
		if (player1_y[0] == player2_y[i] && player1_x[0] == player2_x[i])   //kale mar 1 be body 2 bokhore, mar1 mibaze
			*condition = 1; //player 1 lost the game
	}

	for (int i = 1; i < player2_length; i++)
	{
		if (player2_y[0] == player1_y[i] && player2_x[0] == player1_x[i])   //kale mar 2 be body 1 bokhore, mar2 mibaze
			*condition = 2; //player 2 lost the game
	}

	if (player1_y[0] == player2_y[0] && player2_x[0] == player1_x[0])
	{
		if (player1_length > player2_length)
			*condition = 2; //player 2 lost the game
		else if (player1_length > player2_length)
			*condition = 1; //player 1 lost the game
		else if (player1_length == player2_length)
			*condition = 3; //tie


	}

	if (player1_length < MINIMUM_SNAKE_LENGTH)
		*condition = 1; //player 1 lost the game
	if (player2_length < MINIMUM_SNAKE_LENGTH)
		*condition = 2; //player 2 lost the game

}

void  Show_Result(int *condition) {
	if (condition == 1)
		printf(" player 2(blue) won the game. \n player 1(red) lost the game.");   //i set some conditions to print the result

	else if (condition == 2)
		printf(" player 1(red) won the game. \n player 2(blue) lost the game.");

	else if (condition == 3)
		printf(" game tied \n  player1=0 \t player2=0");

}


void Move_Snake1(int player1_snake_direction, int* player1_length, int player1_x[MAX_LEN_SNAKES], int player1_y[MAX_LEN_SNAKES]) {
	int i = 0;
	for (i = *player1_length - 1; i > 0; --i) {
		player1_x[i] = player1_x[i - 1];
		player1_y[i] = player1_y[i - 1];
	}

	if (player1_snake_direction == LEFT) {
		if (player1_x[0] == 0)
			player1_x[0] = BOARD_SIZE - 1; 
		else
			*(player1_x) -= 1;
	}

	else if (player1_snake_direction == DOWN) {
		if (player1_y[0] == BOARD_SIZE)
			player1_y[0] = 0;
		else
			*(player1_y) += 1;
	}


	else if (player1_snake_direction == RIGHT) {
		if (player1_x[0] == BOARD_SIZE)
			player1_x[0] = 0;
		else
			*(player1_x) += 1;
	}

	else if (player1_snake_direction == UP) {
		if (player1_y[0] == 0)
			player1_y[0] = BOARD_SIZE - 1;
		else
			*(player1_y) -= 1;

	}


}
void Apear_Snake1_On_The_screan(int player1_length, char board_content[BOARD_SIZE][BOARD_SIZE], int player1_x[MAX_LEN_SNAKES], int player1_y[MAX_LEN_SNAKES])
{
	int i = 0;
	                                                                           
	for (i = player1_length - 1; i > 0; i--) {							/// Hame tikke haye badanesh ro mizarim sare jashoon
		board_content[player1_y[i]][player1_x[i]] = PLAYER1_SNAKE_BODY;
	}
																			/// Va Kalleye maar
	board_content[player1_y[0]][player1_x[0]] = PLAYER1_SNAKE_HEAD;
}
void Move_Snake2(int player2_snake_direction, int* player2_length, int player2_x[MAX_LEN_SNAKES], int player2_y[MAX_LEN_SNAKES]) {

	int j = 0;
	for (j = *player2_length - 1; j > 0; j--) {
		player2_x[j] = player2_x[j - 1];
		player2_y[j] = player2_y[j - 1];
	}

	if (player2_snake_direction == LEFT) {
		if (player2_x[0] == 0)
			player2_x[0] = BOARD_SIZE - 1; //taqiiiiir bede
		else
			*(player2_x) -= 1;
	}

	else if (player2_snake_direction == DOWN) {
		if (player2_y[0] == BOARD_SIZE-1)
			player2_y[0] = 0;
		else
			*(player2_y) += 1;
	}


	else if (player2_snake_direction == RIGHT) {
		if (player2_x[0] == BOARD_SIZE-1)
			player2_x[0] = 0;
		else
			*(player2_x) += 1;
	}

	else if (player2_snake_direction == UP) {
		if (player2_y[0] == 0)
			player2_y[0] = BOARD_SIZE - 1;
		else
			*(player2_y) -= 1;

	}


}



void Apear_Snake2_On_The_screan(int player2_length, char board_content[BOARD_SIZE][BOARD_SIZE], int player2_x[MAX_LEN_SNAKES], int player2_y[MAX_LEN_SNAKES])
{
	int j;
															/// Hame tikke haye badanesh ro mizarim sare jashoon
	for (j = player2_length - 1; j > 0; j--) {
		board_content[player2_y[j]][player2_x[j]] = PLAYER2_SNAKE_BODY;
	}

																				/// Va Kalleye maar
	board_content[player2_y[0]][player2_x[0]] = PLAYER2_SNAKE_HEAD;
	


}



void MICE_POISION_AND_GOLDEN_STAR(char board_content[BOARD_SIZE][BOARD_SIZE]) {
	int current_number_of_mice = 0;
	int x, j; int y_mice; int x_mice;


	for (x = 0; x < BOARD_SIZE; x++) {            //moteqayer taarif mikonim k teedad mouse ha ro beshmare
		for (j = 0; j < BOARD_SIZE; j++) {
			if (board_content[x][j] == MOUSE)
				current_number_of_mice = current_number_of_mice + 1;
		}



	}

	while (current_number_of_mice < NUMBER_OF_MOUSES) {
		x_mice = rand() % BOARD_SIZE;
		y_mice = rand() % BOARD_SIZE;
		if (board_content[x_mice][y_mice] == EMPTY && current_number_of_mice < NUMBER_OF_MOUSES)   //agar teedad mouse ha kam shod behesh ezafe kone
		{
			current_number_of_mice = current_number_of_mice + 1;
			board_content[x_mice][y_mice] = MOUSE;

		}

	}



	int current_number_of_poisions = 0;
	int y_poision; int x_poision;


	
	


	for (x = 0; x < BOARD_SIZE; x++) {            //moteqayer taarif mikonim k teedad poision ha ro beshmare
		for (j = 0; j < BOARD_SIZE; j++) {
			if (board_content[x][j] == POISON)
			{
				current_number_of_poisions = current_number_of_poisions + 1;
			}
		}



	}

	while (current_number_of_poisions < NUMBER_OF_POISONS) {
		x_poision = rand() % BOARD_SIZE;
		y_poision = rand() % BOARD_SIZE;
		if (board_content[x_poision][y_poision] == EMPTY && current_number_of_poisions < NUMBER_OF_POISONS)  //agar teedad poision ha kam shod behesh ezafe kone
		{
			current_number_of_poisions = current_number_of_poisions + 1;
			board_content[x_poision][y_poision] = POISON;

		}

	}

	int x_golden_star, y_golden_star, current_number_of_golden_stars = 0;
	


	for (x = 0; x < BOARD_SIZE; x++) {            //moteqayer taarif mikonim k teedad golden star ha ro beshmare
		for (j = 0; j < BOARD_SIZE; j++) {
			if (board_content[x][j] == GOLDEN_STAR)
			{
				current_number_of_golden_stars = current_number_of_golden_stars + 1;
			}
		}



	}

	while (current_number_of_golden_stars < NUMBER_OF_GOLDEN_STARS) {
		x_golden_star = rand() % BOARD_SIZE;
		y_golden_star = rand() % BOARD_SIZE;
		if (board_content[x_golden_star][y_golden_star] == EMPTY && current_number_of_golden_stars < NUMBER_OF_GOLDEN_STARS)
		{
			current_number_of_golden_stars = current_number_of_golden_stars + 1;   //agar teedad golden star ha kam shod behesh ezafe kone
			board_content[x_golden_star][y_golden_star] = GOLDEN_STAR;

		}

	}


	/*for (int i = 0; i < NUMBER_OF_POISONS; i++)
	{
		x_poision = rand() % BOARD_SIZE;
		y_poision = rand() % BOARD_SIZE;
		if (board_content[y_poision][x_poision] = POISON) {
			++current_number_of_poisions;
		}
	}

	while (current_number_of_poisions < NUMBER_OF_POISONS) {   ///taqir bede
		x_poision = rand() % BOARD_SIZE;
		y_poision = rand() % BOARD_SIZE;
		if (board_content[y_poision][x_poision] == EMPTY)
		{
			board_content[y_poision][y_poision] = POISON;
			++current_number_of_poisions;
		}
	}*/

}







int main() {
	int player1_y[MAX_LEN_SNAKES] = { BOARD_SIZE - 3 ,BOARD_SIZE - 2,BOARD_SIZE - 1 }; //arraye 1 boodi bara x va y player1 taarif mikonim
	int player1_x[MAX_LEN_SNAKES] = { 0,0,0 };
	char board_content[BOARD_SIZE][BOARD_SIZE];
	int player1_length = INITIAL_SNAKE_LENGTH;           //meqdar dahi avalie lengthe mar ha
	int player2_length = INITIAL_SNAKE_LENGTH;
	int player1_snake_direction = UP;                                                    // give the snakes by default direction
	int player2_snake_direction = DOWN;
	int player2_x[MAX_LEN_SNAKES] = { BOARD_SIZE - 1 ,BOARD_SIZE - 1,BOARD_SIZE - 1 };//arraye 1 boodi bara x va y player2 taarif mikonim
	int player2_y[MAX_LEN_SNAKES] = { 2,1,0 };
	int condition; int  x_mice, y_mice, current_number_of_mice = 0;
	INITIALIZE_BOARD(board_content);         //to clear the screan each time
	srand(time(NULL));



	init_screen(); //call this to make window adjustments


	board_content[player1_y[0]][player1_x[0]] = PLAYER1_SNAKE_HEAD;     
	board_content[player1_y[1]][player1_x[1]] = PLAYER1_SNAKE_BODY;     //kale va body snake 1 ro chap mikone
	board_content[player1_y[2]][player1_x[2]] = PLAYER1_SNAKE_BODY;

	board_content[player2_y[0]][player2_x[0]] = PLAYER2_SNAKE_HEAD;
	board_content[player2_y[1]][player2_x[1]] = PLAYER2_SNAKE_BODY;          //kale va body snake 1 ro chap mikone
	board_content[player2_y[2]][player2_x[2]] = PLAYER2_SNAKE_BODY;



	
	
		

	while (TRUE) {

		draw_board(board_content);
		wait_and_get_direction(&player1_snake_direction, &player2_snake_direction);          //in order to get the directions based on the pressed keys
		Clear_Snake_Tail(board_content);                                                    //in order to clear the end of the snake
		MICE_POISION_AND_GOLDEN_STAR(board_content); //code for apearing the golden_star//code for apearing the POISION//code for apearing the mice 

		Snake1_eat(board_content, player1_y, player1_x, &player1_length, player1_snake_direction, &player2_length);   //in order to manage the next step of the snake 1 and manage what it eats
		Snake2_eat(board_content, player2_y, player2_x, &player2_length, player2_snake_direction, &player1_length);     //in order to manage the next step of the snake 2 and manage what it eats
		Move_Snake1(player1_snake_direction, &player1_length, player1_x, player1_y);               //in order to manage the movement of snake 1
		Apear_Snake1_On_The_screan(player1_length, board_content, player1_x, player1_y);         //chap mikone sar va body snake 1 ro
		Move_Snake2(player2_snake_direction, &player2_length, player2_x, player2_y);  //in order to manage the movement of snake 2
		Apear_Snake2_On_The_screan(player2_length, board_content, player2_x, player2_y);  
	    //chap mikone sar va body snake 2 ro
		END_GAME_AND_CONDITIONS(board_content, player1_length, player2_length, player1_x, player1_y, player2_x, player2_y, &condition);
		// I set some conditions in order to stop the game
		
		if (condition == 2) break;    if (condition == 1) break; if (condition == 3)  break;      //to break from while and be preoared for showing the result

	}
	reset_console();
	Show_Result(condition);                                  //show the result and print them
	return 0;
}




//The Game is Finished, Show the result

