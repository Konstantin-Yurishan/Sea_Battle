// TODO режимы игры
//человек - комп
//комп - комп
//Расстановка кораблей:
//игрок - сам
//комп за игрока
//комп играет в 2 режиммах:
// 1. случайный выстрел
//2. стратегия
// отображение тек состояния
// возможность паузы,завершения и новой игры
//TODO запись статистики по играм
// TODO цветная карта, звуковая индикация попадания
// TODO туман войны


#include <iostream>
#include <string>
#include <Windows.h>
#include <thread>
#include <conio.h>
#pragma comment(lib, "winmm.lib")

struct playerField {

	int ship1 = 0;
	int ship2 = 0;
	int ship3 = 0;
	int ship4 = 0;

	char** field;

};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
playerField createPlayerField();	//	создаёт и заполняет поля значениями по умолчанию
void showField(playerField, playerField);	//	показ игровых полей
void fillFieldManual(playerField*);	//	заполнение поля в ручном режиме
void fillFieldAutomatic(playerField*);	//	заполнение поля в автоматическом режиме
void intro();	//	интро в начале игры
void musicThread();	//	поток для проигрывания музыки в интро
void consoleSize();	//	изменение размера окна консоли
void mainMenu();	//	главное меню программы
void errorPrinter(int);	//	выводит ошибку согласно переданому числу
bool checkArea(playerField*, int, int);
void enemyShotEasy(playerField*);	//	выстрел компьютера
bool break_cond = false;

//TODO Fзаполнение поля кораблями в автоматическом режиме
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

	//intro();

	//mainMenu();

	playerField field1 = createPlayerField();
	playerField* ptrField1 = &field1;
	playerField field2 = createPlayerField();
	playerField* ptrField2 = &field2;

	fillFieldAutomatic(ptrField1);
	fillFieldAutomatic(ptrField2);
	
	showField(field1, field2);


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

// TODO сделать прерывание при нажатии любой клавиши
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

void mainMenu()
{

	int choice;
	bool exit = false;

	while (!exit) {
		std::cout << "1. Start new game." << std::endl;
		std::cout << "0. Exit." << std::endl;
		std::cin >> choice;
		system("CLS");

		switch (choice) {
		case 1:
			while (!exit) {
				std::cout << "1. Player_1 vs Player_2." << std::endl;
				std::cout << "2. Player vs PC." << std::endl;
				std::cout << "0. Exit." << std::endl;
				std::cin >> choice;
				system("CLS");
				//	автоматическая или ручная расстановка
				switch (choice) {
				case 1:
					//	start game
					break;
				case 2:
					while (!exit) {
						std::cout << "Choose difficult:" << std::endl;
						std::cout << "1. Easy." << std::endl;
						std::cout << "2. Hard." << std::endl;
						std::cout << "0. Exit." << std::endl;
						std::cin >> choice;

						switch (choice) {
						case 1:
							//	start easy game
							break;
						case 2:
							//	strat hard game
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




