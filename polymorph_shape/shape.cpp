

#include "shape.h"

#define STEP 10 //шаг расширения массива указателей



double cylinder::area() { //M_PI - число пи определенное в cmath
    return (2*M_PI*R*R + 2*M_PI*R*H); //считаем площадь поверхности
}

double cylinder::volume() {
    return (M_PI*R*R*H);
}

cylinder::cylinder(double R, double H) : R(R), H(H) {} //конструктор класса цилиндр(двоеточие и далее - это список инициализации)

void cylinder::show() { //метод выводящий информацию о цилиндре
    std::cout << "This is a cylinder" << std::endl;
    std::cout << "H = " << H << std::endl;
    std::cout << "R = " << R << std::endl;
}

parallelepiped::parallelepiped(double a, double b, double c) : a(a), b(b), c(c) {} //констркутор класса параллелепипед

double parallelepiped::area() {
    return (a*b*2+b*c*2+a*c*2);
}

double parallelepiped::volume() {
    return (a*b*c);
}

void parallelepiped::show() { // метод возвращающий информацию о параллелепипеде
    std::cout << "This is a parallelepiped" << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
}

/*прочитай про тип второго аргумента в заголовочном файле shape.h */
int create_mas_from_file(std::ifstream& input, shape **&mas) {//создать массив указателей из файла
    delete [] mas; //удаляем память по указателю(если вдруг там до этого что-то лежало)
    int size = STEP;
    mas = new shape*[size]; //выделяем память под массив размера size каждый элемент которого-указатель НА БАЗОВЫЙ КЛАСС
    int i = 0;
    while (!input.eof()){ //если поток не исчерпан(не достигнут конец файла)
        std::string name; //тип стринг из библиотеке <string>
        input >> name; 
        if (name == "cylinder"){
            double r;
            double h;
            input >> r >> h;
            mas[i] = new cylinder(r,h);//в i'ый элемент массива кладем указатель на объект выделенный динамически и проинициализированный значениями r,h
        } else if (name == "parallelepiped"){
            double a,b,c;
            input >> a >> b >> c;
            mas[i] = new parallelepiped(a,b,c);//new возвращает указатель на объект выделенный динамически. Для создания объекта вызывается его конструктор
        }                //здесь происходит приведение (от указателя на наследника к указателю на базовый класс).
        else {           // new возвращет указатель на объект parallelepiped и этот указатель приводится к типу указатель на shape(базовый класс)
            std::cout << "wrong input" << std::endl;
            return -1;
        }
        ++i;
        if (i >= size){ //если закончилось место 
            size += STEP; // мы расширяем размер
            shape** tmp = new shape*[size];//выделяем новую память 
            for (int j = 0; j < size - STEP; ++j) //копируем туда все старые значения
                tmp[j] = mas[j]; //копируются указатели(выделенные динамически) так что мы не теряем память
            delete [] mas; // удаляем старый указатль на массив указателей
            mas = tmp; //кладем в него новый(расширенные) указатель
        }
    }
    size = i; //теперь,когда всё прочитали мы знаем реальный размер массива(скажем последний элемент в который мы положили был 12)
    shape** tmp2 = new shape*[size];  //значит реальный размер массива 13(т.к отсчет i шел от нуля) в конце while мы лишний раз увеличим i и как раз выйдет 13-размер массива
    for (int k = 0; k < size; ++k) //ещё раз копируем все значения
        tmp2[k] = mas[k]; 
    delete [] mas; //удаляем старый(слишком большой массив с лишними, не использованными элементами)
    mas = tmp2; //кладем в указатель уже конечный массив.
    return size; //возвращаем его размер
}

void free_mas(shape **mas,int size) { //освобождение памяти
    for (int i = 0; i < size; ++i) { //сначала отчищаем все указатели(т.к объекты выделялись динамически)
        delete mas[i];
    }
    delete [] mas; //затем удаляем сам массив указателей
}
