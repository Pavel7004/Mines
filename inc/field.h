#ifndef __FIELD__
#define __FIELD__

#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

// класс представляющий поле для игры в сапёр
class Field {
  // граница поля в высоту
  short max_x;
  // граница поля в ширину
  short max_y;

  // количество мин на поле
  short number_of_mines;

  // количество мин, отмеченных флагом, на поле
  short flaged_mines;

  // количество флагов, поставленных игроком
  short flag_count;

  // двумерный массив представляющий элементы поля
  short **field;

  // функция ставящая числа на клетках рядом с минами
  void place_numbers();

public:
  // конструктор класса инициализирующий массив field, принимает требуемые
  // границы поля
  Field(const short &maxX, const short &maxY);

  // функция возвращает количество мин на поле
  short get_Number_of_mines();

  // функция возвращает количество флагов поставленных игроком
  short get_flag_count();

  // функция возращает состояние клетки
  short get_tile_status(const short &x, const short &y);

  // функция ставящая мины на поле, принимает требуемое количество мин на поле
  void place_mines(const short &numberOfMines);

  // функция очищающая память после игры
  void clear_Field();

  // функция выводит на экран поле для игры,
  // переменная win определяет показать все мины при выйгрыше или показывать
  // флаги на клетках
  void printField(const bool &win);

  // функция открытия клетки на поле, принимает кординаты клетки
  bool open_tile(const short &x, const short &y);

  // функция ставит флаг на клетке, принимает кординаты клетки
  bool put_flag(const short &x, const short &y);

  // функция убирает флаг с клетки, принимает кординаты клетки
  void remove_flag(const short &x, const short &y);
};

#endif
