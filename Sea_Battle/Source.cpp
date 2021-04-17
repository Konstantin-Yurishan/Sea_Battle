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

struct playerField {

	int ship1 = 0;
	int ship2 = 0;
	int ship3 = 0;
	int ship4 = 0;

	char** field;

};


playerField createPlayerField();
void showField(playerField, playerField);	//	показ игровых полей
void fillFieldManual(playerField*);	//	заполнение поля в ручном режиме
void fillFieldAutomatic(playerField*);	//	заполнение поля в автоматическом режиме

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
	srand(time(NULL));

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
			SetConsoleTextAttribute(hConsole, 3);
			std::cout << field1.field[i][c] << "  ";
		}

		SetConsoleTextAttribute(hConsole, 7);
		std::cout << "\t";
		std::cout << i + 1;
		if (i != 9) std::cout << " ";

		for (int c = 0; c < 10; c++) {
			SetConsoleTextAttribute(hConsole, 3);
			std::cout << field2.field[i][c] << "  ";
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
	

	int ship = 4;
	int coordX = 1, coordY = 4;


	while (ship != 0) {

		coordX = rand() % 9 + 1;
		coordY = rand() % 9 + 1;
		// TODO проверка окресности точки
		if (field1->field[coordX][coordY] == '~') {
			field1->field[coordX][coordY] = '#';
			ship--;
		}

	}
	
	


}


