
#ifndef CLION_HW6_SHAPE_H
#define CLION_HW6_SHAPE_H

#include <cmath> //константа M_PI
#include <iostream>
#include <fstream>
#include <string> 

class shape { //базовый класс из чистых виртуальных методов
public:
    virtual double area() = 0; //чисто виртуальный метод для подсчета площади
    virtual double volume() = 0; //чисто виртуальный метод для подсчета объема
    virtual void show() = 0; //чисто виртуальный метод для вывода информации об объекте
};

class cylinder : public shape{ //наследник-цилиндр. Публичное наследование сохраняет все теже права доступа как у родителя
public:                        //по умолчанию стоит private наследование. Private наследование закрывает все поля базового класса.(всё что было паблик стало приват)
    cylinder(double R, double H); //конструктор

    double area() override ; //переопределенный(override) метод из базового класса 
    double volume() override ;
    void show() override ;

private:
    double R;
    double H;
};

class parallelepiped : public shape {
public:
    parallelepiped(double a, double b, double c);
    double area() override ;
    double volume() override ;
    void show() override ;
private:
    double a;
    double b;
    double c;
};
/*ОБРАТИ ВНИМАНИЕ на тип второго аргумента: ссылка на <указатель на указатель>. Дело в том что в ходе работы мы 
удаляем память по указателю mas и заново выделяем её. Мы изменяем значение mas(т.е меняется адресс начала массива.
Поэтому мы впередаем аргумент как ссылку на <указатель на указатель>*/
int create_mas_from_file(std::ifstream& input,shape** &mas); //создать массив указателей из файла. 
void free_mas(shape** mas, int size); //отчистить массив
#endif //CLION_HW6_SHAPE_H
