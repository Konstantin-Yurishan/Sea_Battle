//заполнение вражеского поля кораблями
//меню для воода информации с подсказками
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


void TextRunner();
void CreateField();
void ShowField();

char mineField[12][13] = { 0, };
char enemyField[12][13] = { 0, };

int main() {

	//TextRunner();
	CreateField();
	ShowField();
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

