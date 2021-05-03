#include <iostream>
#include <string>
#include <Windows.h>
#include <thread>
#include <conio.h>
//#include "Header.h"
#pragma comment(lib, "winmm.lib")

struct playerField {

	int ship1 = 0;
	int ship2 = 0;
	int ship3 = 0;
	int ship4 = 0;
	int sumOfShipsDecks = 20;

	char** field;

};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

playerField createPlayerField();	//	создаёт и заполняет поля значениями по умолчанию
void showField(playerField*);         
void showFields(playerField, playerField);	//	показ игровых полей
void fillFieldManual(playerField*);	//	заполнение поля в ручном режиме
void fillFieldAutomatic(playerField*);	//	заполнение поля в автоматическом режиме
void intro();	//	интро в начале игры
void musicThread();	//	поток для проигрывания музыки в интро
void consoleSize();	//	изменение размера окна консоли
void mainMenu(playerField*, playerField*);	//	главное меню программы
void errorPrinter(int);	//	выводит ошибку согласно переданому числу
bool checkArea(playerField*, int, int);
bool enemyShotEasy(playerField*);	//	выстрел компьютера
bool enemyShotHard(playerField*);	//	выстрел компьютера тяжелый
bool checkEndOfGame(playerField*, playerField*);
bool checkShoot(playerField*, int, int);
void game(playerField*, playerField*, int, int);
void cursorPosition();
int* cursorPosition2();


//функция сильного ИИ
//подбитые корабли - красный, корабли - зелёный, область промаха - белый
//

int main()
{

	consoleSize();	//	изменение размера окна при запуске программы
	srand(time(NULL));

	playerField field1 = createPlayerField();
	playerField* ptrField1 = &field1;
	playerField field2 = createPlayerField();
	playerField* ptrField2 = &field2;

	//intro();

	//cursorPosition();
	//cursorPosition2();

	mainMenu(ptrField1, ptrField2);

	return 0;
}

playerField createPlayerField()
{
	playerField newField;

	newField.field = new char* [10];
	
	for (int i = 0; i < 10; i++) {
		newField.field[i] = new char[10];
	}

	for (int i = 0; i < 10; i++) {
		for (int c = 0; c < 10; c++) {
			newField.field[i][c] = '~';
		}
	}

	return newField;
}

void showField(playerField* field)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << "  A  B  C  D  E  F  G  H  I  J" << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << i + 1;
		if (i != 9) std::cout << " ";

		for (int c = 0; c < 10; c++) {
			if (field->field[i][c] == '#') {
				SetConsoleTextAttribute(hConsole, 150);
				std::cout << field->field[i][c];
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (field->field[i][c] == '~') {
				SetConsoleTextAttribute(hConsole, 3);
				std::cout << field->field[i][c];
				SetConsoleTextAttribute(hConsole, 7);
			}
			SetConsoleTextAttribute(hConsole, 7);
			std::cout << "  ";
		}
		std::cout << std::endl << std::endl;

		SetConsoleTextAttribute(hConsole, 7);
	}
}

//показ обоих полей
void showFields(playerField field1, playerField field2)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//для манип с конс выводом в данном случае раскраска

	std::cout << "\t  A  B  C  D  E  F  G  H  I  J \t\t\t  A  B  C  D  E  F  G  H  I  J " << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << "\t" << i + 1;
		if (i != 9) std::cout << " ";


		for (int c = 0; c < 10; c++) {
			if (field1.field[i][c] == '#') {
				SetConsoleTextAttribute(hConsole, 150);
				std::cout << field1.field[i][c];
			}
			else if (field1.field[i][c] == '~') {
				SetConsoleTextAttribute(hConsole, 3);
				std::cout << field1.field[i][c];
			}
			else if (field1.field[i][c] == 'X') {
				SetConsoleTextAttribute(hConsole, 3);
				std::cout << field1.field[i][c];
			}
			else if (field1.field[i][c] == '0') {
				SetConsoleTextAttribute(hConsole, 3);
				std::cout << '~';
			}
			SetConsoleTextAttribute(hConsole, 7);
			std::cout << "  ";
		}

		std::cout << "\t";
		std::cout << "\t" << i + 1;
		if (i != 9) std::cout << " ";

		for (int c = 0; c < 10; c++) {
			if (field2.field[i][c] == 'X') {
				SetConsoleTextAttribute(hConsole, 150);
				std::cout << field2.field[i][c];
			}
			else if (field2.field[i][c] == '0') {
				SetConsoleTextAttribute(hConsole, 3);
				std::cout << field2.field[i][c];
			}
			else if (field2.field[i][c] == '~' || field2.field[i][c] == '#') {
				SetConsoleTextAttribute(hConsole, 3);
				std::cout << '/';
			}
			
			SetConsoleTextAttribute(hConsole, 7);
			std::cout << "  ";
		}

		std::cout << std::endl << std::endl;

		SetConsoleTextAttribute(hConsole, 7);
	}

	//	TODO вывод информации по количеству кораблей
	//	TODO вывод информации с номером хода
	//	TODO вывод информации с временем игры ? (время нельзя показать в реальном времени)
	//	TODO вывод информации об очерёдности хода
	//	TODO вывод информации о горячих клавишах

}

//заполнение поля в ручном режиме
void fillFieldManual(playerField* field1)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int coordX, coordY, dir, finishX, finishY;
	//однопалубные
	while (field1->ship1 != 4) {
		system("CLS");
		std::cout << "Single-deck ship #" << field1->ship1 + 1 << std::endl;
		showField(field1);
		int * rep = { 0, };
		//rep = cursorPosition2();
		cursorPosition();
		coordX = rep[0];
		coordY = rep[1];
		/*std::cout << "Enter the first coordinate X: ";
		std::cin >> coordX;
		std::cout << "Enter the second coordinate Y: ";
		std::cin >> coordY;*/
		if (checkArea(field1, coordX, coordY)) {
			field1->field[coordX][coordY] = '#';
			field1->ship1++;
		}
		else {
			std::cout << "Input error!" << std::endl;
		}
	}
	

	//двухпалубные
	while (field1->ship2 != 3) {
		system("CLS");
		std::cout << "Double-deck ship #" << field1->ship2 + 1 << std::endl;
		showField(field1);
		std::cout << "Enter the start coordinate X: ";
		std::cin >> coordX;
		std::cout << "Enter the start coordinate Y: ";
		std::cin >> coordY;

		std::cout << "Enter the finish coordinate X: ";
		std::cin >> finishX;
		std::cout << "Enter the finish coordinate Y: ";
		std::cin >> finishY;

		if ((abs(coordX - finishX) == 1 || abs(coordY - finishY) == 1) && !(abs(coordX - finishX) == 1 && abs(coordY - finishY)==1)) {
			if (checkArea(field1, coordX, coordY) && checkArea(field1, finishX, finishY)) {
				field1->field[coordX][coordY] = '#';
				field1->field[finishX][finishY] = '#';
				field1->ship2++;
			}
			else {
				std::cout << "Point is not clear." << std::endl;
			}
		}
		else {
			std::cout << "Input error!" << std::endl;
		}
		
	}
	

	//трёхпалубные
	while (field1->ship3 != 2) {
		system("CLS");
		std::cout << "Triple-deck ship #" << field1->ship3 + 1 << std::endl;
		showField(field1);
		std::cout << "Enter the start coordinate X: ";
		std::cin >> coordX;
		std::cout << "Enter the start coordinate Y: ";
		std::cin >> coordY;

		std::cout << "Enter the finish coordinate X: ";
		std::cin >> finishX;
		std::cout << "Enter the finish coordinate Y: ";
		std::cin >> finishY;

		if ((abs(coordX - finishX) == 2 || abs(coordY - finishY) == 2) && !(abs(coordX - finishX) == 2 && abs(coordY - finishY) == 2)) {
			if (checkArea(field1, coordX, coordY) && checkArea(field1, finishX, finishY) && checkArea(field1, coordX + (abs(coordX - finishX) == 2 ? 1 : 0), coordY + (abs(coordX - finishX) == 2 ? 1 : 0))) {
				field1->field[coordX][coordY] = '#';
				field1->field[coordX + (abs(coordX - finishX) == 2 ? 1 : 0)][coordY + (abs(coordY - finishY) == 2 ? 1 : 0)] = '#';
				field1->field[finishX][finishY] = '#';
				field1->ship3++;
			}
			else {
				std::cout << "Point is not clear." << std::endl;
			}
		}
		else {
			std::cout << "Input error!" << std::endl;
		}

	}
	

	//четёрехпалубный
	while (field1->ship4 != 1) {
		system("CLS");
		std::cout << "Four-deck ship #" << field1->ship4 + 1 << std::endl;
		showField(field1);
		std::cout << "Enter the start coordinate X: ";
		std::cin >> coordX;
		std::cout << "Enter the start coordinate Y: ";
		std::cin >> coordY;

		std::cout << "Enter the finish coordinate X: ";
		std::cin >> finishX;
		std::cout << "Enter the finish coordinate Y: ";
		std::cin >> finishY;

		if ((abs(coordX - finishX) == 3 || abs(coordY - finishY) == 3) && !(abs(coordX - finishX) == 3 && abs(coordY - finishY) == 3)) {
			if (checkArea(field1, coordX, coordY) && checkArea(field1, finishX, finishY) && checkArea(field1, coordX + (abs(coordX - finishX) == 3 ? 1 : 0), coordY + (abs(coordX - finishX) == 3 ? 1 : 0)) && checkArea(field1, coordX + (abs(coordX - finishX) == 3 ? 2 : 1), coordY + (abs(coordX - finishX) == 3 ? 2 : 1))) {
				field1->field[coordX][coordY] = '#';
				field1->field[coordX + (abs(coordX - finishX) == 3 ? 2 : 0)][coordY + (abs(coordY - finishY) == 3 ? 2 : 0)] = '#';
				field1->field[coordX + (abs(coordX - finishX) == 3 ? 1 : 0)][coordY + (abs(coordY - finishY) == 3 ? 1 : 0)] = '#';
				field1->field[finishX][finishY] = '#';
				field1->ship4++;
			}
			else {
				std::cout << "Point is not clear." << std::endl;
			}
		}
		else {
			std::cout << "Input error!" << std::endl;
		}

	}

	showField(field1);
}

//заполнение поля в автоматическом режиме
void fillFieldAutomatic(playerField* field1)
{
	
	int coordX, coordY, dir;

	//однопалубные
	while (field1->ship1 != 4) {

		coordX = rand() % 10;
		coordY = rand() % 10;
		
		if (checkArea(field1, coordX, coordY)) {
			field1->field[coordX][coordY] = '#';
			field1->ship1++;
		}
	}
	//двухпалубные
	while (field1->ship2 != 3) {
		coordX = rand() % 10;
		coordY = rand() % 10;

		dir = rand() % 4;

		if ((coordX == 0 && dir == 0) || (coordY == 0 && dir == 2) || (coordX == 9 && dir == 1) || (coordY == 9 && dir == 3)) {
			continue;
		}

		if (checkArea(field1, coordX, coordY)) {
			//	вверх
			if (dir == 0) {
				if (checkArea(field1, coordX - 1, coordY)) {
					field1->field[coordX - 1][coordY] = '#';
					field1->field[coordX][coordY] = '#';
					field1->ship2++;
				}
			}// низ
			else if (dir == 1) {
				if (checkArea(field1, coordX + 1, coordY)) {
					field1->field[coordX + 1][coordY] = '#';
					field1->field[coordX][coordY] = '#';
					field1->ship2++;
				}
			} //влево
			else if (dir == 2) {
				if (checkArea(field1, coordX, coordY - 1)) {
					field1->field[coordX][coordY - 1] = '#';
					field1->field[coordX][coordY] = '#';
					field1->ship2++;
				}
			} //вправо
			else {
				if (checkArea(field1, coordX, coordY + 1)) {
					field1->field[coordX][coordY + 1] = '#';
					field1->field[coordX][coordY] = '#';
					field1->ship2++;
				}
			}
		}
	}

	//трёхпалубные
	while (field1->ship3 != 2) {
		coordX = rand() % 10;
		coordY = rand() % 10;
		dir = rand() % 4;

		if ((coordX < 3 && dir == 0) || (coordY < 3 && dir == 2) || (coordX > 7 && dir == 1) || (coordY > 7 && dir == 3)) {
			continue;
		}

		if (checkArea(field1, coordX, coordY)) {
			if (dir == 0) {
				if (checkArea(field1, coordX - 1, coordY) && checkArea(field1, coordX - 2, coordY)) {
					field1->field[coordX - 1][coordY] = '#';
					field1->field[coordX - 2][coordY] = '#';
					field1->field[coordX][coordY] = '#';
					field1->ship3++;
				}
			}
			else if (dir == 1) {
				if (checkArea(field1, coordX + 1, coordY) && checkArea(field1, coordX + 2, coordY)) {
					field1->field[coordX + 1][coordY] = '#';
					field1->field[coordX + 2][coordY] = '#';
					field1->field[coordX][coordY] = '#';
					field1->ship3++;
				}
			}
			else if (dir == 2) {
				if (checkArea(field1, coordX, coordY - 1) && checkArea(field1, coordX, coordY - 2)) {
					field1->field[coordX][coordY - 1] = '#';
					field1->field[coordX][coordY - 2] = '#';
					field1->field[coordX][coordY] = '#';
					field1->ship3++;
				}
			}
			else {
				if (checkArea(field1, coordX, coordY + 1) && checkArea(field1, coordX, coordY + 2)) {
					field1->field[coordX][coordY + 1] = '#';
					field1->field[coordX][coordY + 2] = '#';
					field1->field[coordX][coordY] = '#';
					field1->ship3++;
				}
			}
		}
	}

	//четёрехпалубный
	while (field1->ship4 != 1) {
		coordX = rand() % 10;
		coordY = rand() % 10;
		dir = rand() % 4;

		if ((coordX < 4 && dir == 0) || (coordY < 4 && dir == 2) || (coordX > 6 && dir == 1) || (coordY > 6 && dir == 3)) {
			continue;
		}

		if (checkArea(field1, coordX, coordY)) {
			if (dir == 0) {
				if (checkArea(field1, coordX - 1, coordY) && checkArea(field1, coordX - 2, coordY) && checkArea(field1, coordX - 3, coordY)) {
					field1->field[coordX - 1][coordY] = '#';
					field1->field[coordX - 2][coordY] = '#';
					field1->field[coordX - 3][coordY] = '#';
					field1->field[coordX][coordY] = '#';
					field1->ship4++;
				}
			}
			else if (dir == 1) {
				if (checkArea(field1, coordX + 1, coordY) && checkArea(field1, coordX + 2, coordY) && checkArea(field1, coordX + 3, coordY)) {
					field1->field[coordX + 1][coordY] = '#';
					field1->field[coordX + 2][coordY] = '#';
					field1->field[coordX + 3][coordY] = '#';
					field1->field[coordX][coordY] = '#';
					field1->ship4++;
				}
			}
			else if (dir == 2) {
				if (checkArea(field1, coordX, coordY - 1) && checkArea(field1, coordX, coordY - 2) && checkArea(field1, coordX, coordY - 3)) {
					field1->field[coordX][coordY - 1] = '#';
					field1->field[coordX][coordY - 2] = '#';
					field1->field[coordX][coordY - 3] = '#';
					field1->field[coordX][coordY] = '#';
					field1->ship4++;
				}
			}
			else {
				if (checkArea(field1, coordX, coordY + 1) && checkArea(field1, coordX, coordY + 2) && checkArea(field1, coordX, coordY + 3)) {
					field1->field[coordX][coordY + 1] = '#';
					field1->field[coordX][coordY + 2] = '#';
					field1->field[coordX][coordY + 3] = '#';
					field1->field[coordX][coordY] = '#';
					field1->ship4++;
				}
			}
		}
	}
}

//TODO сделать прерывание при нажатии любой клавиши
void intro()
{
	std::thread thr(musicThread);
	thr.join();
	


	std::string logo[19] = { "\n\n                               $$$$$$$$\\ $$$$$$$\\ $$$$$$\\  $$$$$$\\                              ",
							"                               $$  _____|$$  __$$\\\\_$$  _|$$  __$$\\                             ",
							"                               $$ |      $$ |  $$ | $$ |  $$ /  \\__|                            ",
							"                               $$$$$\\    $$$$$$$  | $$ |  $$ |                                  ",
							"                               $$  __|   $$  ____/  $$ |  $$ |                                  ",
							"                               $$ |      $$ |       $$ |  $$ |  $$\\                             ",
							"                               $$$$$$$$\\ $$ |     $$$$$$\\ \\$$$$$$  |                            ",
							"                               \\________|\\__|     \\______| \\______/                             ",
							"",
							"",
							"",
							"  $$$$$$\\  $$$$$$$$\\  $$$$$$\\        $$$$$$$\\   $$$$$$\\ $$$$$$$$\\ $$$$$$$$\\ $$\\       $$$$$$$$\\ ",
							" $$  __$$\\ $$  _____|$$  __$$\\       $$  __$$\\ $$  __$$\\\\__$$  __|\\__$$  __|$$ |      $$  _____|",
							" $$ /  \\__|$$ |      $$ /  $$ |      $$ |  $$ |$$ /  $$ |  $$ |      $$ |   $$ |      $$ |      ",
							" \\$$$$$$\\  $$$$$\\    $$$$$$$$ |      $$$$$$$\\ |$$$$$$$$ |  $$ |      $$ |   $$ |      $$$$$\\    ",
							"  \\____$$\\ $$  __|   $$  __$$ |      $$  __$$\\ $$  __$$ |  $$ |      $$ |   $$ |      $$  __|   ",
							" $$\\   $$ |$$ |      $$ |  $$ |      $$ |  $$ |$$ |  $$ |  $$ |      $$ |   $$ |      $$ |      ",
							" \\$$$$$$  |$$$$$$$$\\ $$ |  $$ |      $$$$$$$  |$$ |  $$ |  $$ |      $$ |   $$$$$$$$\\ $$$$$$$$\\ ",
							"  \\______/ \\________|\\__|  \\__|      \\_______/ \\__|  \\__|  \\__|      \\__|   \\________|\\________|" };


	for (int i = 0; i < 10; i++) {

		for (auto str : logo) {

			SetConsoleTextAttribute(hConsole, rand() % 15 + 1);

			std::cout << str << std::endl;
		}

		SetConsoleTextAttribute(hConsole, 7);

		std::cout << "\n\n\t\t\t\tGame will start untill " << 10 - i << " sec.";  // всё ещё работаю над этим
		

		Sleep(1000);
		system("CLS");

	}
	return;
}

void musicThread()
{
	PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

//меняет размер окна консоли при запуске
void consoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFOEX consolesize;

	consolesize.cbSize = sizeof(consolesize);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfoEx(hConsole, &consolesize);

	COORD c;
	c.X = 100;
	c.Y = 30;
	consolesize.dwSize = c;

	consolesize.srWindow.Left = 0;
	consolesize.srWindow.Right = 100;
	consolesize.srWindow.Top = 0;
	consolesize.srWindow.Bottom = 30;

	SetConsoleScreenBufferInfoEx(hConsole, &consolesize);
}

void mainMenu(playerField* field1, playerField* field2)
{

	char choice;
	bool exit = false;

	while (!exit) {
		std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t1. Start new game." << std::endl;
		std::cout << "\t\t\t\t\t0. Exit." << std::endl;
		choice = _getch();
		system("CLS");

		switch (choice) {
		case '1':
			while (!exit) {
				std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t1. Player_1 vs Player_2." << std::endl;
				std::cout << "\t\t\t\t\t2. Player vs PC." << std::endl;
				std::cout << "\t\t\t\t\t0. Exit." << std::endl;
				choice = _getch();
				system("CLS");
				
				switch (choice) {
				case '1':
					while (true) {
						char g;
						std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t1. Manual." << std::endl;
						std::cout << "\t\t\t\t\t2. Auto." << std::endl;
						g = _getch();

						if (g == '1') {
							game(field1, field2, 1, 1);
						}
						else if (g == '2') {
							game(field1, field2, 1, 2);
						}
						else {
							std::cout << "Enter correct value" << std::endl;
						}
					}
					break;
				case '2':
					while (!exit) {
						std::cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t    Choose difficult:" << std::endl;
						std::cout << "\t\t\t\t\t1. Easy." << std::endl;
						std::cout << "\t\t\t\t\t2. Hard." << std::endl;
						std::cout << "\t\t\t\t\t0. Exit." << std::endl;
						choice = _getch();

						switch (choice) {
						case '1':
							game(field1, field2, 2, 0);
							break;
						case '2':
							game(field1, field2, 3, 0);
							break;
						case '0':
							exit = true;
							break;
						default:
							errorPrinter(1);
							break;
						}
					}
					break;
				case '0':
					exit = true;
					break;
				default:
					errorPrinter(1);
					break;
				}
			}
			break;
		case '0':
			exit = true;
			break;
		default:
			errorPrinter(1);
			break;
		}
	}

}

void errorPrinter(int e)
{

	SetConsoleTextAttribute(hConsole, 4);

	switch (e) {
	case 1:
		std::cout << "Enter the correct menu point." << std::endl;
		break;
	default:
		std::cout << "Unknown error code." << std::endl;
		break;
	}

	SetConsoleTextAttribute(hConsole, 7);
}

bool checkArea(playerField* field, int X, int Y)
{
	for (int i = X - 1; i <= X + 1; i++) {
		for (int c = Y - 1; c <= Y + 1; c++) {

			if (i < 0 || c < 0 || i > 9 || c > 9 || field->field[i][c] == '~' || field->field[i][c] != '#') {
				continue;
			} else {
				return false;
			}
		}
	}
	return true;
}

bool enemyShotEasy(playerField* field)
{
	int x = rand() % 10;
	int y = rand() % 10;

	if (field->field[x][y] == '#') {
		field->field[x][y] = 'X';
		std::cout << "Nice shoot!" << std::endl;
		field->sumOfShipsDecks--;
		return true;
	}
	else {
		field->field[x][y] = '0';
		std::cout << "Looser!" << std::endl;
		return false;
	}

	Sleep(1000);
	system("CLS");

}

bool enemyShotHard(playerField* field)
{

	int x, y;

	while (true) {

		x = rand() % 10;
		y = rand() % 10;

		if (field->field[x][y] == '0') {
			continue;
		}
		else if (!checkArea(field, x, y)) {
			if (checkShoot(field, x, y))
			{
				return true;
			}
			else {
				return false;
			}
		}
		else {
			continue;
		}
	}
	return false;
}

bool checkEndOfGame(playerField* field1, playerField* field2)
{
	if (field1->sumOfShipsDecks == 0) {
		std::cout << "Player2 win!";
		return true;
	}
	else if (field2->sumOfShipsDecks == 0) {
		std::cout << "Player1 win!";
		return true;
	}
	else {
		false;
	}

}

bool checkShoot(playerField* field, int x, int y)
{
	if (field->field[x][y] == '#') {
		field->field[x][y] = 'X';
		field->sumOfShipsDecks--;
		return true;
	}
	else {
		return false;
	}
}

void game(playerField* field1, playerField* field2, int gameMode, int fill)
{
	system("CLS");
	//1 - игрок против игрока
	//2 - игрок против ИИ простой
	//3 - игрок протв ИИ сложный
	//1 - manual
	//2 - auto

	int x, y;

	if (fill == 1) {
		fillFieldManual(field1);

		if (gameMode != 1) {
			fillFieldAutomatic(field2);
		}
		else {
			fillFieldManual(field2);
		}
	}
	else {

		fillFieldAutomatic(field1);
		fillFieldAutomatic(field2);
		
	}




	if (gameMode == 1) {

		while (checkEndOfGame(field1, field2)) {
			while (true) {

				std::cout << "\n\n\t\t    Player 1\t\t\t\t\t    Player 2" << std::endl << std::endl;
				showFields(*(field1), *(field2));

				std::cout << "Enter the x:";
				std::cin >> x;
				std::cout << "Enter the y:";
				std::cin >> y;

				system("CLS");

				if (checkShoot(field2, x, y)) {
					system("CLS");
					std::cout << "Nice shoot!" << std::endl;
					showFields(*(field1), *(field2));
				}
				else {
					if (field2->field[x][y] == '~') {
						field2->field[x][y] = '0';
						std::cout << "Looser!" << std::endl;
						break;
					}
				}
			}

			system("CLS");

			while (true) {

				std::cout << "\n\n\t\t    Player 2\t\t\t\t\t    Player 1" << std::endl << std::endl;
				showFields(*(field2), *(field1));

				std::cout << "Enter the x:";
				std::cin >> x;
				std::cout << "Enter the y:";
				std::cin >> y;

				system("CLS");

				if (checkShoot(field1, x, y)) {
					system("CLS");
					std::cout << "Nice shoot!" << std::endl;
					showFields(*(field2), *(field1));
				}
				else {
					if (field1->field[x][y] == '~') {
						field1->field[x][y] = '0';
						std::cout << "Looser!" << std::endl;
						break;
					}
				}
			}

		}

	}
	else if (gameMode == 2) {

		std::cout << "\n\n\t\t    Player 1\t\t\t\t\t    Player 2" << std::endl << std::endl;
		while (checkEndOfGame(field1, field2)) {
			while (true) {
				showFields(*(field1), *(field2));
				std::cout << "Enter the x:";
				std::cin >> x;
				std::cout << "Enter the y:";
				std::cin >> y;

				system("CLS");

				if (checkShoot(field2, x, y)) {
					system("CLS");
					std::cout << "Nice shoot!" << std::endl;
					showFields(*(field1), *(field2));
				}
				else {
					if (field2->field[x][y] == '~' || field2->field[x][y] == 'X') {
						field2->field[x][y] = '0';
						std::cout << "Looser!" << std::endl;
						break;
					}
				}
				showFields(*(field1), *(field2));
			}

			system("CLS");

			std::cout << "\n\n\t\t    Player 2\t\t\t\t\t    Player 1" << std::endl << std::endl;
			while (enemyShotEasy(field1)) {
				showFields(*(field1), *(field2));
			}
		}
	}
	else if (gameMode == 3) {
		std::cout << "\n\n\t\t    Player 1\t\t\t\t\t    Player 2" << std::endl << std::endl;
		while (checkEndOfGame(field1, field2)) {
			while (true) {
				showFields(*(field1), *(field2));
				std::cout << "Enter the x:";
				std::cin >> x;
				std::cout << "Enter the y:";
				std::cin >> y;

				system("CLS");

				if (checkShoot(field2, x, y)) {
					system("CLS");
					std::cout << "Nice shoot!" << std::endl;
					showFields(*(field1), *(field2));
				}
				else {
					if (field2->field[x][y] == '~' || field2->field[x][y] == 'X') {
						field2->field[x][y] = '0';
						std::cout << "Looser!" << std::endl;
						break;
					}
				}
				showFields(*(field1), *(field2));
			}

			system("CLS");
			std::cout << "\n\n\t\t    Player 2\t\t\t\t\t    Player 1" << std::endl << std::endl;
			while (enemyShotHard(field1)) {
				showFields(*(field1), *(field2));
			}
		}
	}
	else {
		std::cout << "Eternal error!";
	}

}

void cursorPosition()
{
	POINT p;
	RECT r;
	int rep[2];
	bool chrt = true;
	while (chrt) {
		GetWindowRect(GetConsoleWindow(), &r);
		GetCursorPos(&p);

		
			
			rep[0] = (p.x - r.left) / 10;
			rep[1] = (p.y - r.top - 31) / 15;
			if (GetAsyncKeyState(VK_LBUTTON))
			{
				chrt = false;
				std::cout << p.x << "   " << p.y;
			}
			/*std::cout << "RIGHT: " << (GetAsyncKeyState(VK_RBUTTON) ? "YES" : "NO")
				<< "\tLEFT: " << (GetAsyncKeyState(VK_LBUTTON) ? "YES" : "NO")
				<< "\t[" << p.x << ";" << p.y << "]" << std::endl;*/
		
	}


	
}


int* cursorPosition2()
{
	RECT r;
	POINT p;
	HWND wh = GetConsoleWindow();
	COORD c = { 1,1 };
	int rep[2];
	bool chrt = true;
	while (chrt) {
		GetWindowRect(wh, &r);
		GetCursorPos(&p);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		std::cout << p.x - r.left << ":" << p.y - r.top - 31 << "    ";
		
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000 != 0)) {
			chrt = false;
			rep[0] = (p.x - r.left) / 10;
			rep[1] = (p.y - r.top - 31) / 15;
			
		}
	}


	return rep;

}






