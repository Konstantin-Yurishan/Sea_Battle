//+заполнение вражеского поля кораблями
//меню для ввода информации с подсказками
//заполнение поля игрока кораблями путём ввода координат кораблей
//проверка корректности ввода координат и размещения кораблей игроком 
//реализация ии для хода компьютера
//реализация хода игрока и компьютера поочерёдно
//реализация режима тумана войны
//проверка попал или нет игрок или компютер
//сигнализация попадания цветом и звуком
//включение бегущей строки с докладом боевой обстановки
//проверка состояния игры (выйграл/проиграл)
//реализация таймера хода игрока 

#include <iostream>
#include <string>
#include <Windows.h>
#include <random>

void TextRunner();
void CreateField();
void ShowField();
void AIShipConstructor();
bool ClearShipFieldChecker(int, int);
bool menu();
void playerShipPlacer();

char mineField[12][12] = { 0, };
char enemyField[12][12] = { 0, };

int main() {
	setlocale(LC_ALL, "Russian");

	srand(time(NULL));
	//TextRunner();
	if (menu()) {
		system("CLS");
		CreateField();
		AIShipConstructor();
		ShowField();
		playerShipPlacer();
	}
	return 0;
}


void TextRunner() {

	std::string str = "Sea Battle   ";

	while (true) {//бесконечный цикл
		for (int i = 0; i < str.length(); i++) {//задаем начальную позицию для части бег строки
			for (int c = i; c <= i + 5; c++) {//задаем с какого до какого символа выводим в единицу frame
				std::cout << str.at(c % str.length());//вывод символа по индексу равному c ,в том момент когда индекс выходит за пределы массива она пропадает
			}
			Sleep(100);//frame
			system("CLS");

		}

	}

}

void CreateField() {

	for (int i = 0; i < 12; i++) {
		for (int c = 0; c < 12; c++) {
            if (c == 0 || c == 11 || i == 0 || i == 11) {
				mineField[i][c] = '#';
				enemyField[i][c] = '#';
			} else {
				mineField[i][c] = ' ';
				enemyField[i][c] = ' ';
			}
		}
	}
}

void ShowField() {

	std::cout << "   ABCDEFGHIJ \t\t   ABCDEFGHIJ" << std::endl;

	for (int i = 0, g = -1; i < 12; i++, g++) {
		if (i != 0 && g < 10) {
			std::cout << g << " ";
		}
		if (i == 0 || i == 11) {
			std::cout << "  ";
		}

		for (int c = 0; c < 12; c++) {
			std::cout << mineField[i][c];
		}

		std::cout << "\t\t";

		if (i != 0 && g < 10) {
			std::cout << g << " ";
		}
		if (i == 0 || i == 11) {
			std::cout << "  ";
		}

		for (int c = 0; c < 12; c++) {
			std::cout << enemyField[i][c];
		}

		std::cout << std::endl;
	}
}

void AIShipConstructor() {

	//однопалубные
	char ship1_1[2];
	char ship1_2[2];
	char ship1_3[2];
	char ship1_4[2];

	//двухпалубные
	char ship2_1[4];
	char ship2_2[4];
	char ship2_3[4];

	//трехпалубные
	char ship3_1[6];
	char ship3_2[6];

	//4палубный
	char ship4_1[8];


	int ship = 0;
	int coordI = 0;
	int coordC = 0;
	int direction = 0;

	//заполняем поле однопалубниками

	while (ship < 4) {
		coordI = rand() % 10 + 1;
		coordC = rand() % 10 + 1;

		if (ClearShipFieldChecker(coordI, coordC)) {
			enemyField[coordI][coordC] = '*';
			ship++;
		}
	}

	//заполняем поле двухпалубниками
	ship = 0;
	
	while (ship < 3) {
		coordI = rand() % 10 + 1;
		coordC = rand() % 10 + 1;

		if (ClearShipFieldChecker(coordI, coordC)) {
			direction = rand() % 4;

			if (direction == 0) { //вверх
				if (enemyField[coordI - 1][coordC] != '#' && ClearShipFieldChecker(coordI - 1, coordC)) {
					enemyField[coordI - 1][coordC] = '*';
					enemyField[coordI][coordC] = '*';
					ship++;
				}
			}
			else if (direction == 1) { //вниз
				if (enemyField[coordI + 1][coordC] != '#' && ClearShipFieldChecker(coordI + 1, coordC)) {
					enemyField[coordI + 1][coordC] = '*';
					enemyField[coordI][coordC] = '*';
					ship++;
				}
			}
			else if (direction == 2) { //влево
				if (enemyField[coordI][coordC - 1] != '#' && ClearShipFieldChecker(coordI, coordC - 1)) {
					enemyField[coordI][coordC - 1] = '*';
					enemyField[coordI][coordC] = '*';
					ship++;
				}
			}
			else { //вправо
				if (enemyField[coordI][coordC + 1] != '#' && ClearShipFieldChecker(coordI, coordC + 1)) {
					enemyField[coordI][coordC + 1] = '*';
					enemyField[coordI][coordC] = '*';
					ship++;
				}
			}
		}
	}

	//заполняем поле трёхпалубниками
	ship = 0;

	while (ship < 2) {
		coordI = rand() % 10 + 1;
		coordC = rand() % 10 + 1;

		if (ClearShipFieldChecker(coordI, coordC)) {
			direction = rand() % 4;

			if (direction == 0) { //вверх
				if (enemyField[coordI - 1][coordC] != '#' && enemyField[coordI - 2][coordC] != '#' && ClearShipFieldChecker(coordI - 1, coordC) && ClearShipFieldChecker(coordI - 2, coordC)) {
					enemyField[coordI - 2][coordC] = '*';
					enemyField[coordI - 1][coordC] = '*';
					enemyField[coordI][coordC] = '*';
					ship++;
				}
			}
			else if (direction == 1) { //вниз
				if (enemyField[coordI + 1][coordC] != '#' && enemyField[coordI + 2][coordC] != '#' && ClearShipFieldChecker(coordI + 1, coordC) && ClearShipFieldChecker(coordI + 2, coordC)) {
					enemyField[coordI + 2][coordC] = '*';
					enemyField[coordI + 1][coordC] = '*';
					enemyField[coordI][coordC] = '*';
					ship++;
				}
			}
			else if (direction == 2) { //влево
				if (enemyField[coordI][coordC - 1] != '#' && enemyField[coordI][coordC - 2] != '#' && ClearShipFieldChecker(coordI, coordC - 1) && ClearShipFieldChecker(coordI, coordC - 2)) {
					enemyField[coordI][coordC - 2] = '*';
					enemyField[coordI][coordC - 1] = '*';
					enemyField[coordI][coordC] = '*';
					ship++;
				}
			}
			else { //вправо
				if (enemyField[coordI][coordC + 1] != '#' && enemyField[coordI][coordC + 2] != '#' && ClearShipFieldChecker(coordI, coordC + 1) && ClearShipFieldChecker(coordI, coordC + 2)) {
					enemyField[coordI][coordC + 2] = '*';
					enemyField[coordI][coordC + 1] = '*';
					enemyField[coordI][coordC] = '*';
					ship++;
				}
			}
		}

	}

	//заполняем поле четёрёхпалубником
	ship = 0;

	while (ship < 1) {
		coordI = rand() % 10 + 1;
		coordC = rand() % 10 + 1;

		if (ClearShipFieldChecker(coordI, coordC)) {
			direction = rand() % 4;

			if (direction == 0) { //вверх
				if (enemyField[coordI - 1][coordC] != '#' && enemyField[coordI - 2][coordC] != '#' && enemyField[coordI - 3][coordC] != '#' 
					&& ClearShipFieldChecker(coordI - 1, coordC) && ClearShipFieldChecker(coordI - 2, coordC) && ClearShipFieldChecker(coordI - 3, coordC)) {
					enemyField[coordI - 3][coordC] = '*';
					enemyField[coordI - 2][coordC] = '*';
					enemyField[coordI - 1][coordC] = '*';
					enemyField[coordI][coordC] = '*';
					ship++;
				}
			}
			else if (direction == 1) { //вниз
				if (enemyField[coordI + 1][coordC] != '#' && enemyField[coordI + 2][coordC] != '#' && enemyField[coordI + 3][coordC] != '#'
					&& ClearShipFieldChecker(coordI + 1, coordC) && ClearShipFieldChecker(coordI + 2, coordC) && ClearShipFieldChecker(coordI + 3, coordC)) {
					enemyField[coordI + 3][coordC] = '*';
					enemyField[coordI + 2][coordC] = '*';
					enemyField[coordI + 1][coordC] = '*';
					enemyField[coordI][coordC] = '*';
					ship++;
				}
			}
			else if (direction == 2) { //влево
				if (enemyField[coordI][coordC - 1] != '#' && enemyField[coordI][coordC - 2] != '#' && enemyField[coordI][coordC - 3] != '#' 
					&& ClearShipFieldChecker(coordI, coordC - 1) && ClearShipFieldChecker(coordI, coordC - 2) && ClearShipFieldChecker(coordI, coordC - 3)) {
					enemyField[coordI][coordC - 3] = '*';
					enemyField[coordI][coordC - 2] = '*';
					enemyField[coordI][coordC - 1] = '*';
					enemyField[coordI][coordC] = '*';
					ship++;
				}
			}
			else { //вправо
				if (enemyField[coordI][coordC + 1] != '#' && enemyField[coordI][coordC + 2] != '#' && enemyField[coordI][coordC + 3] != '#' 
					&& ClearShipFieldChecker(coordI, coordC + 1) && ClearShipFieldChecker(coordI, coordC + 2) && ClearShipFieldChecker(coordI, coordC + 3)) {
					enemyField[coordI][coordC + 3] = '*';
					enemyField[coordI][coordC + 2] = '*';
					enemyField[coordI][coordC + 1] = '*';
					enemyField[coordI][coordC] = '*';
					ship++;
				}
			}
		}

	}
}

bool ClearShipFieldChecker(int i, int c) {
	for (int i1 = i - 1; i1 <= i + 1; i1++) {
		for (int c1 = c - 1; c1 <= c + 1; c1++) {
			if (enemyField[i1][c1] == '*') {
				return false;
			}
			else {
				true;
			}	
		}
	}
}

bool menu() {

	int n;
	std::cout << "1.Start new game." << std::endl;
	std::cout << "2.Exit." << std::endl;
	std::cin >> n;
    
	if (n == 1) {
		return true;
	}
	else {
		return false;
	}

}

void playerShipPlacer() {

	int ship = 1;
	int firstCoordI = 0;
	int firstCoordC = 0;

	while (ship < 5) {
		system("CLS");
		ShowField();
		std::cout << "Enter coordinate Y " << ship << " ship: ";
		std::cin >> firstCoordI;
		std::cout << "Enter coordinate X " << ship << " ship: ";
		std::cin >> firstCoordC;
		std::cout << std::endl;
		mineField[firstCoordI][firstCoordC] = '*';
		
		ship++;
	}

}