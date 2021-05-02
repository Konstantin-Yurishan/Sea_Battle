#pragma once

struct playerField {
	int ship1 = 0;
	int ship2 = 0;
	int ship3 = 0;
	int ship4 = 0;
	int shipAmount = ship1 + ship2 + ship3 + ship3;
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
void mainMenu(playerField*, playerField*);	//	главное меню программы
void errorPrinter(int);	//	выводит ошибку согласно переданому числу
bool checkArea(playerField*, int, int);
void enemyShotEasy(playerField*);	//	выстрел компьютера лёгкий
void enemyShotHard(playerField*);	//	выстрел компьютера тяжелый
void gamePlayerPlayer(playerField*, playerField*);
void gamePlayerPC(playerField*, playerField*, short);
bool winChecker(playerField*, playerField*, bool);
bool shootChecker(playerField*, char, int);