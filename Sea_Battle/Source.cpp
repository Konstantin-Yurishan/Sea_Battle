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
#pragma comment(lib, "winmm.lib")

struct playerField {

	int ship1 = 0;
	int ship2 = 0;
	int ship3 = 0;
	int ship4 = 0;

	char** field;

};


playerField createPlayerField();	//	создаёт и заполняет поля значениями по умолчанию
void showField(playerField, playerField);	//	показ игровых полей
void fillFieldManual(playerField*);	//	заполнение поля в ручном режиме
void fillFieldAutomatic(playerField*);	//	заполнение поля в автоматическом режиме
void intro();	//	интро в начале игры
void musicThread();	//	поток для проигрывания музыки в интро
void consoleSize();	//	изменение размера окна консоли
int mainMenu();	//	главное меню программы


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

	intro();

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

// TODO сделать прерывание при нажатии любой клавиши
void intro()
{
	std::thread thr(musicThread);
	thr.join();
	std::this_thread::yield();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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




	for (int i = 0; i < 20; i++) {

		for (auto str : logo) {

			SetConsoleTextAttribute(hConsole, rand() % 15 + 1);

			std::cout << str << std::endl;
		}

		SetConsoleTextAttribute(hConsole, 7);

		std::cout << "\n\n\t\t\t\t\tEnter key to start";  // всё ещё работаю над этим
		

		Sleep(1000);
		system("CLS");
	}



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

int mainMenu()
{

	int choice;
	bool exit = false;

	while (!exit) {
		std::cout << "1. Начать новую игру.";
		std::cout << "2. Выход из программы";
		std::cin >> choice;

		switch (choice) {
		case 1:
			std::cout << "1. Игрок против игрока.";
			std::cout << "2. Игрок против компьютера.";
			std::cout << "0. Выход.";
			std::cin >> choice;


			break;
		case 0:
			exit = true;
			break;
		default:
			std::cout << "Введите корректный номер пункта меню." << std::endl;
			break;
		}
	}

}


