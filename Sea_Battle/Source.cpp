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


#include <iostream>
#include <string>

void showField(std::string**, std::string**);
void fillBackgroundField(std::string**);


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

	std::string** field1 = new std::string * [10];
	std::string** field2 = new std::string * [10];

	for (int i = 0; i < 10; i++)
	{
		field1[i] = new std::string[10];
		field2[i] = new std::string[10];
	}

	fillBackgroundField(field1);
	fillBackgroundField(field2);

	showField(field1, field2);

	return 0;
}


void fillBackgroundField(std::string** field)
{

	for (int i = 0; i < 10; i++)
	{
		for (int c = 0; c < 10; c++)
		{
			field[i][c] = "~";
		}
	}
}

//показ обоих полей
void showField(std::string** field1, std::string** field2)
{

	std::cout << "  ABCDEFGHIJ\t  ABCDEFGHIJ" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << i + 1;
		for (int c = 0; c < 10; c++)
		{
			std::cout << field1[i][c];
		}
		std::cout << "\t";
		std::cout << i + 1;
		for (int c = 0; c < 10; c++)
		{
			std::cout << field2[i][c];
		}
		std::cout << std::endl;
	}

	//показ статистики: количество кораблей наших и противника
	//номер хода
	//время игры
	//чей ход в данный момент
	//показать горячии клавиши для выхода из игры и выхода в главное меню

}



