#include "field.h"

/*  фаил с реализацией функций для класса Field в файле field.h  */

// реализация конструктора
Field::Field(const short &maxX, const short &maxY) : max_x(maxX), max_y(maxY){

	// создание двумерного массива
	field = new short*[max_x];
	for (short i = 0; i < max_x; i++)
		field[i] = new short[max_y];
	
	// заполнение массва нулями
	for (short i = 0; i < max_x; i++)
		for (short j = 0; j < max_y; j++)
			field[i][j] = 0;
	
	// начальная инициализация переменных класса
	number_of_mines = 0;
	flaged_mines = 0;
	flag_count = 0;
}

// функция расставляет цифры вокруг мин на поле
void Field::place_numbers(){
	// если количество мин 0 функция не выполняется
	if (number_of_mines == 0) {
		// вывод сообщения игроку
		cout << "На поле нет мин" << endl;
		return;
	}
	
	// цикл перебора всех клеток в массиве field
	for (short i = 0; i < max_x; i++)
		for (short j = 0; j < max_y; j++){
			// для клеток с минами ничего не выполняется 
			if (field[i][j] == 9) continue;
			
			// счетчик количества мин вокруг клетки
			short mineCount = 0;
			
			// перебор всех клеток вокруг данной клетки
			//-----------------------------//
			// клетка сверху
			if (i != 0) 
				if (field[i - 1][j] == 9) mineCount++;
			// клетка слева
			if (j != 0)
				if (field[i][j - 1] == 9) mineCount++;
			// клетка снизу
			if (i != max_x - 1)
				if (field[i + 1][j] == 9) mineCount++;
			// клетка справа
			if (j != max_y - 1)
				if (field[i][j + 1] == 9) mineCount++;
			// левая верхняя клетка
			if (i != 0 && j != 0)
				if (field[i - 1][j - 1] == 9) mineCount++;
			// правая верхняя клетка
			if (i != 0 && j != max_y - 1)
				if (field[i - 1][j + 1] == 9) mineCount++;
			// правая нижняя клетка
			if (i != max_x - 1 && j != max_y - 1)
				if (field[i + 1][j + 1] == 9) mineCount++;
			// левая нижняя клетка
			if (i != max_x - 1 && j != 0)
				if (field[i + 1][j - 1] == 9) mineCount++;
			//-----------------------------//
			
			// обновление элемента массива 
			field[i][j] = mineCount;
		}
}

// функция ставит мины на на поле
void Field::place_mines(const short &numberOfMines){
	// калибровка подбора псевдо-случайных чисел
	srand(static_cast<unsigned int>(time(NULL)));
	
	// если количество мин больше количества клеток на поле функция не выполняется
	if (numberOfMines >= max_x * max_y) {
		// вывод сообщения игроку
		cout << "Количество мин больше количества клеток на поле" << endl;
		return;
	}
	
	// количество мин нужно запомнить
	number_of_mines = numberOfMines;
	
	// количество сгенерированных мин
	short tmpCount = 0;
	
	// цикл генерации мин на поле, 
	// цикл остановиться когда количество генерированных мин будет равно требуемому количеству мин
	while (tmpCount != number_of_mines){
		// подбор случайных кординат для мины
		short x = rand() % max_x;
		short y = rand() % max_y;
		// цикл запускается заного если на подобранных кординатах есть мина
		if (field[x][y] == 9) continue;
		// установка мины на клетке
		field[x][y] = 9;
		// увеличение счетчика сгенерированных мин
		tmpCount++;
	}
	
	// расстановка чисел на всём поле
	place_numbers();
}

// функция очищает память после игры
void Field::clear_Field(){
	// очистка памяти для двумерного массива
	for (short i = 0; i < max_x; i++)
		delete[] field[i];
	
	delete[] field;
}

// функция выводит поле на экран
void Field::printField(const bool &win){
	// если игра закончена победой мины показываются '*'
	// если нет то 'F'
	char flag;
	if (win)
		flag = '*';
	else
		flag = 'F';	
	
	// вывод чисел для нумерации столбцов
	cout << ' ' << ' ' << ' ';
	for (short i = 0; i < max_x; i++)
		cout << i + 1 << ' ';
	cout << endl;
	
	// цикл перебора всех элементов массива
	for (short i = 0; i < max_x; i++) {
		// нумерация строк
		if (i + 1 != 10) cout << ' ' << i + 1 << ' ';
		else cout << i + 1 << ' ';
		
		// цикл обработки одной строки поля
		for (short j = 0; j < max_y; j++){
			// варианты при которых клетки выводятся не как '#'
			//----------------------------------------------//
			// открытая клетка с нулём
			if (field[i][j] == 100)
				cout << ' ' << ' ';
			// открытая клетка с числом от 1 до 8
			else if (field[i][j] >= 101 && field[i][j] <= 108)
				cout << field[i][j] % 10 << ' ';
			// клетка с флагом
			else if (field[i][j] / 100 == 2 && field[i][j] != 209)
				cout << 'F' << ' ';
			// клетка с миной, помеченная флагом
			else if (field[i][j] == 209)
				cout << flag << ' ';
			// открытая клетка с миной
			else if (field[i][j] == 109)
				cout << '*' << ' ';
			//----------------------------------------------//
			// нетронутые клетки отображаются как '#'
			else
				cout << '#' << ' ';
		}
		
		// переход на новую строку для вывода следуйщей строки поля
		cout << endl;
	}	
}

// функция открывает клетку на поле
bool Field::open_tile(const short &x, const short &y){	

	// если игрок открывает клетку с миной, игра заканчивается проигрышом
	if (field[x][y] == 9){
		// открытие клетки
		field[x][y] += 100;
		// отчистка экрана для вывода финального варианта поля
		system("clear");
		// вывод поля после проигрыша
		cout << endl;
		printField(0);
		cout << endl << endl;
		cout << "Вы проиграли!" << endl;
		// задержка курсора перед очисткой
		system("read tmp");
		// очистка экрана
		system("clear");
		// возвращает сигнал к завершению игры
		return 1;
	}	
	
	// если рядом с клеткой мина(мины)
	if (field[x][y] >= 1 && field[x][y] <= 8){
        // открытие клетки
        field[x][y] += 100;
        return 0;
	}
	
	// если рядом с клеткой мин нет
	if (field[x][y] == 0){
		// открытие клетки
		field[x][y] += 100;
		
		// открытие клеток рядом
		//----------------------------------------//
		// клетка сверху
		if (x != 0) open_tile(x - 1, y);
		// клетка слева
		if (y != 0) open_tile(x, y - 1);
		// клетка снизу
		if (x != max_x - 1) open_tile(x + 1, y);
		// клетка справа
		if (y != max_y - 1) open_tile(x, y + 1); 
		//----------------------------------------//

		return 0;
	}

	// клетку с флагом или уже открытую клетку нельзя ещё раз открыть
    if (field[x][y] / 100 != 0){
        return 0;
    }
	
	// возвращает сигнал к продолжению игры
	return 0;
}

// функция ставит флаг на клетку
bool Field::put_flag(const short &x, const short &y){
	// если на клетке уже стоит флаг или клетка уже открыта
	if (field[x][y] / 100 != 0){
		cout << "На этой клетке нельзя поставить флаг" << endl;
		// сигнал к продолжению игры
		return 0;
	}
	// флагов не может быть больше количества мин
	if (flag_count == number_of_mines){
		cout << "Вы поставили максимальное количество флагов" << endl;
		// сигнал к продолжению игры
		return 0;
	}
	// увеличение количества флагов на поле
	flag_count++;	
	// если на клетке мина
	if (field[x][y] == 9){
		// количество мин с флагом увеличевается
		flaged_mines++;
		// на клетку ставится флаг
		field[x][y] += 200;
		// если на всех минах стоит флаг то игрок выйгрывает
		if (flaged_mines == number_of_mines){
			// вывод поля с открытыми минами
			//----------------------------//
			system("clear");
			cout << endl;
			printField(1);
			cout << endl << endl;
			cout << "Вы выйграли!" << endl;
			//----------------------------//
			// задержкка программы перед очисткой
			system("read tmp");
			// очистка экрана
			system("clear");
			// сигнал к завершению игры
			return 1;
		}
	}
	
	// если на клетке мины нет то на клетку ставится флаг
	field[x][y] += 200;
	// сигнал к продолжению игры
	return 0;
}

// функция убирает флаг с клетки
void Field::remove_flag(const short &x, const short &y){
	// проверка есть ли на этой кординате флаг
	if (field[x][y] / 100 == 2){
		// если флаг есть то он убирается
		field[x][y] -= 200;
		// уменьшение количества флагов на поле
		flag_count--;
		// если на месте этого флага мина 
		if (field[x][y] == 9)
			// то количество мин с флагом уменьшается
			flaged_mines--;
		
		// функция завершает работу
		return;
	}
	// если на клетке флага нет то выводится сообщение игроку
	cout << "В этих кординатах нет флага!" << endl;
}

// функция возвращает количество мин на поле
short Field::get_Number_of_mines(){
	return number_of_mines;
}

// функция возвращает количество флагов, поставленных игроком
short Field::get_flag_count(){
	return flag_count;
}

// функция возвращает статус клетки поля
short Field::get_tile_status(const short & x, const short & y) {
    return field[x][y];
}
