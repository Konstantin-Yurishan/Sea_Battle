#include <iostream>
#include <string>
#include <Windows.h>
#include <thread>
#include "Header.h"
#pragma comment(lib, "winmm.lib")

//TODO Fзаполнение поля кораблями в ручном режиме игроком
//TODO Fзапрос на выстрел
//TODO Fвыстрел компьютера в рандомном режиме
//TODO Fвыстрел компьютера в интеллектуальном режиме
//TODO Fпроверка очерёдности хода
//TODO Fпроверка результативности выстрела
//TODO Fструктура для полей (поле, количество кораблей по классам, количество потопленных)
//TODO Fглавное меню
//TODO Fвывод статистики? -> встраивание в показ полей


int main()
{
	consoleSize();	//	изменение размера окна при запуске программы
	srand(time(NULL));
	intro();

	playerField field1 = createPlayerField();
	playerField* ptrField1 = &field1;
	playerField field2 = createPlayerField();
	playerField* ptrField2 = &field2;

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

//показ обоих полей
void showField(playerField field1, playerField field2)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << "  A  B  C  D  E  F  G  H  I  J \t\t  A  B  C  D  E  F  G  H  I  J " << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << i + 1;
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
			SetConsoleTextAttribute(hConsole, 7);
			std::cout << "  ";
		}

		std::cout << "\t";
		std::cout << i + 1;
		if (i != 9) std::cout << " ";

		for (int c = 0; c < 10; c++) {
			if (field2.field[i][c] == '#') {
				SetConsoleTextAttribute(hConsole, 150);
				std::cout << field2.field[i][c];
			}
			else if (field2.field[i][c] == '~') {
				SetConsoleTextAttribute(hConsole, 3);
				std::cout << field2.field[i][c];
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

//	заполнение поля в ручном режиме
void fillFieldManual(playerField* field)
{

}

//	заполнение поля в автоматическом режиме
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


	for (int i = 0; i < 2; i++) {

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

// меняет размер окна консоли при запуске
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

	int choice;
	bool exit = false;

	while (!exit) {
		std::cout << "\n\n\n\n\n\t\t\t\t\t1. Start new game." << std::endl;
		std::cout << "\t\t\t\t\t0. Exit." << std::endl;
		std::cin >> choice;
		system("CLS");

		switch (choice) {
		case 1:
			while (!exit) {

				std::cout << "\n\n\n\n\n\t\t\t\t\t1. Player_1 vs Player_2." << std::endl;
				std::cout << "\t\t\t\t\t2. Player vs PC." << std::endl;
				std::cout << "\t\t\t\t\t0. Exit." << std::endl;
				std::cin >> choice;
				system("CLS");
				
				switch (choice) {
				case 1:
					gamePlayerPlayer(field1, field2);
					break;
				case 2:
					while (!exit) {

						std::cout << "\n\n\n\n\n\t\t\t\t\tChoose difficult:" << std::endl;
						std::cout << "\t\t\t\t\t1. Easy." << std::endl;
						std::cout << "\t\t\t\t\t2. Hard." << std::endl;
						std::cout << "\t\t\t\t\t0. Exit." << std::endl;
						std::cin >> choice;

						switch (choice) {
						case 1:
							gamePlayerPC(field1, field2, 1);
							break;
						case 2:
							gamePlayerPC(field1, field2, 2);
							break;
						case 0:
							exit = true;
							break;
						default:
							errorPrinter(1);
							break;
						}
					}
					break;
				case 0:
					exit = true;
					break;
				default:
					errorPrinter(1);
					break;
				}
			}
			break;
		case 0:
			exit = true;
			break;
		default:
			errorPrinter(1);
			break;
		}
	}

	/*
	while (!exit) {
		std::cout << "\n\n\n\n\n\t\t\t\t\t1. Start new game." << std::endl;
		std::cout << "\t\t\t\t\t0. Exit." << std::endl;
		std::cin >> choice;
		system("CLS");

		if (choice == 1) {
			std::cout << "\n\n\n\n\n\t\t\t\t\t1. Player_1 vs Player_2." << std::endl;
			std::cout << "\t\t\t\t\t2. Player vs PC." << std::endl;
			std::cout << "\t\t\t\t\t0. Exit." << std::endl;
			std::cin >> choice;
			system("CLS");

			if (choice == 1) {

			}
			else if (choice == 2) {
				std::cout << "\n\n\n\n\n\t\t\t\t\tChoose difficult:" << std::endl;
				std::cout << "\t\t\t\t\t1. Easy." << std::endl;
				std::cout << "\t\t\t\t\t2. Hard." << std::endl;
				std::cout << "\t\t\t\t\t0. Exit." << std::endl;
				std::cin >> choice;
				system("CLS");
			}
			else if (choice == 0) {

			}
			else {

			}

		}
		else if (choice == 0) {

		}
		else {

		}
	}
	*/
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

			if (i < 0 || c < 0 || i > 9 || c > 9 || field->field[i][c] == '~') {
				continue;
			} else {
				return false;
			}
		}
	}
	return true;
}

void enemyShotEasy(playerField* field)
{
	int x = rand() % 10;
	int y = rand() % 10;

	if (field->field[x][y] == '#') {
		field->field[x][y] = 'X';
		std::cout << "Nice shoot!" << std::endl;
	}
	else {
		std::cout << "Looser!" << std::endl;
	}
}

void gamePlayerPlayer(playerField* field1, playerField* field2)
{
	std::cout << "In gamePlayerPlayer" << std::endl;
}

void gamePlayerPC(playerField*, playerField*, short difficult)
{

	//автоматическая или ручная расстановка кораблей?
		//автоматическая - автоматически заполняет кораблями поле игрока
		//ручная - игрок расставляет корабли вручную

	//рандомно решается чей ход первый

	//цикл(пока не победит)
		//показ поля игрока и поле с туманом войны противника
		//чуть ниже полей информация о составе оставшегося флота
		//предложение о вводе координат
		//при удачном попадании сообщение попал или убит - продолжается ход игрока или компьютера
		//

	std::cout << "In gamePlayerPlayer. Difficult - " << difficult << std::endl;
}

bool winChecker(playerField* field1, playerField* field2, bool gameMode)
{
	if (field1->shipAmount == 0 && gameMode) {
		std::cout << "Player2 Win!";
		return true;
	}
	else if (field2->shipAmount == 0 && gameMode) {
		std::cout << "Player1 Win!";
		return true;
	}
	else {
		return false;
	}

	if (field1->shipAmount == 0 && !gameMode) {
		std::cout << "PC Win!";
		return true;
	}
	else if (field2->shipAmount == 0 && !gameMode) {
		std::cout << "Player1 Win!";
		return true;
	}
	else {
		return false;
	}
}






