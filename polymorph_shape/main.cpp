#include <iostream>
#include <fstream>
#include "shape.h"

using namespace std;



int main(int argc,char **argv) {
    ifstream input(*++argv); //открываем файл для ввода из него
    shape **mas;  //создаем массив указателей на базовый класс shape
    int size;
    if (input.is_open()) { // проверям открылся ли файл
        size = create_mas_from_file(input, mas); //заполняем из этого файла массив
        for (int i = 0; i < size; ++i) { //Выводим всю информацию
            mas[i]->show();
            cout << "area = " << mas[i]->area() << endl;
            cout << "volume = " << mas[i]->volume() << endl << endl;
        }
    } else {
        cout << "Can't open file" << endl;
    }
    free_mas(mas, size); //отчищаем массив
    input.close();
    return 0;
}