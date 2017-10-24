#include <iostream>
#include <cstring> // strlen, strcpy
#include <algorithm> //swap
#include <cctype>
#include <string>

#define STEP 100
using namespace std;

class String { //с большой буквы! чтобы не было проблем с встроенным класом string
public:
	String(const char *str = "") {      //конструктор с параметром по умолчанию "" (вызывается при String s;)
		this->size = strlen(str);
		this->str = new char[size+1];
		strcpy(this->str,str);
	}
	String(const String &other){   //констркутор копирования
		this->size = other.size;
		this->str = new char[size+1];
		strcpy(this->str,other.str);
	}
	int len(){
		return this->size;
	}
	int len() const {    //константный метод нужен для работы с константыми объектами(дальше мы очень часто передаем константные объекты)
		return this->size; //компилятор может(и будет) ругаться если для константого объекта будет использован неконстантный метод
	}
	/*при перегрузке внутри класса первый аргумент - указатель на текущий объект(this).(передается по умолчанию)*/
	/*у бинарный операторв(-*+=/) два аргумента, "левый" и правый". Первый аргумент в перегрузке - левый(стоит слева от оператора.Правый - справа*/
	String& operator = (const String &other) {  //перегрузка оператора присваивания. Возвращает ссылку!(существует реальный объект,на который возвращается ссылка) 
		if (this != &other)				
			String(other).swap_s(*this); // эквивалентно {String tmp(a); t(a).swap(*this);} создается временная копия объекта(которая полностью копирует 
		return *this;                    // элемент которому нужно прировняться). Затем меняется местами
	}									
	String& operator += (const char c){ //перегрузка оператора += для добавления одного символа чар. Перегрузка оператора + за классом! 
		this->append(c);				//перегрузка выполняется внутри класса. Т.к будет нужно изменить внутрние поля(которые Private)
		return *this;					//но т.к это внутри класса то мы имеем доступ. => удобнее перегрузить внутри.
	}
	String& operator += (const String &other){ //перегрузка оператора += для добавления другой строки(конкатенации)
		this->append(other);				   //оператор + перегружен за классом. Для того чтобы можно было работать с выражениями вида
		return *this;						  //s = "blablabla" + s2; Если перегрузить внутри, то для первого элемента не будет объекта(т.к тип const char* а не String)
	}										  //из-за отсутсвия объекта - нету This=> ошибка. Если же перегрузить за классом, то для строки "blablabla" будет вызван конструктор и создасться временный объект
	char& operator [] (int i){	//не константный метод, возвращает ссылку на символ внури массива,что позволяет менять поля т.е можно делать stroka[i] = 'b';
		if (i <= this->size)
			return str[i];
		else
			return str[this->size];
	}
	char operator [] (int i) const { //константный метод. Вовзращает копию значения.Используется при вызове у константых объектов. Таким образом, если stroka const
		if (i <= this->size)		//stroka[i] = 'a'; -ошибка из-за попытки изменить констатный объект
			return str[i];			//но можно char c = stroka[i];
		else
			return '\0';
	}
	friend std::ostream& operator << (std::ostream& os, String const& obj){ //перегрузка вывода на экран
		return os << obj.str;
	}
	friend std::istream& operator >> (std::istream& is, String& obj){ //перегрузка считывание с экрана
		is.sync(); //что-то там про отчистку буфера, возможно работает и без этого
		while(isspace(is.peek())) //пропускаем пробелы оставшиеся(возможно)
			is.get();			//от предидущего ввода с помощью cin >> ;
		int cap = STEP; // размер буфера
		char* tmp = new char[cap+1];
		int i = 0;
		while ( !isspace(is.peek()) ){ //is.peek() "смотрит" на следующий за текущим символом(не переводит его вперед)
			if (i < cap)
				is >> tmp[i++];//tmp[i++] = is.get(); //читаем 1 символ из потока ввода и кладем его в массив чаров
			else { //если место кончилось
				cap = cap + STEP; // увиличиваем его
				char *temp = new char[cap+1];
				for (int j = 0; j < i; ++j)  //копируем в новый увеличенный массив данные
					temp[j] = tmp[j]; 
				delete [] tmp; //удаляем что было раньше
				tmp = temp; // присваиваем новый массив(указатель на него)
				is >> tmp[i++];//tmp[i++] = is.get();
			}
			tmp[i] = '\0'; 
		}
		delete [] obj.str; //удаляем то что хранилось раньше в строке 
		obj.size = strlen(tmp); //strlen Берет размер строки ДО \0 таким образом отметается лишние части выделенные большими кусками
		obj.str = new char[obj.size+1]; 
		strcpy(obj.str,tmp);
		delete [] tmp;
		return is;
	}
	friend bool operator == (const String s1, const String s2){ //Дружественная функция(это не метод хоть он и внутри класса)
		if (strcmp(s1.str,s2.str)==0)							//Словом friend мы говорим что функция дружественная и может использовать закрытые поля
			return true;										//можно определить сразу внутри класса, или за ним. Это в данном случае не важно из-за слова freind
		else 													//оператор != определен после класса(он использует оператор ==)
			return false;
	}
	friend bool operator < (const String s1, const String s2){ //отсальные операторы сравнения определенны после класса(они используют оператор <)
		if (strcmp(s1.str,s2.str) < 0)
			return true;
		else 
			return false;
	}
	~String(){  //деструктор
		delete [] str;
	}
	void append(const String &other){  //метод добавляет в конец одной строки - другую строку
		char *p = new char[size + other.size + 1];
		strcpy(p,this->str);
		int i = this->size;
		for (int k = 0; i < (this->size + other.size) && k < other.size; ++i,++k) 
			p[i] = other.str[k];
		p[i] = '\0';
		delete [] (this->str);
		//this->str = new char [size+other.size+1];
		this->str = p;
		//cout << &str << endl;
		//cout << &p <<endl;
		//strcpy(str,p);
		//delete [] p;
		this->size = strlen(str);
	}
	void append(const char c){  //добавляет в конец строки символ 
		char *tmp = new char[size+2];
		strcpy(tmp, str);
		tmp[this->size] = c;
		tmp[this->size + 1] = '\0';
		delete [] str;
		this->str = tmp;
		this->size = strlen(str);
	}

	void swap_s(String &other){ //меняет местами поля двух объектов  
		swap(size,other.size);
		swap(str, other.str);
	}
private:	
	int size;
	char *str;
};



String operator + (String s1, String const& s2){ //Возвращаем не ссылку! за классом чтобы можно было писать
	return s1 += s2;							//s1 = "hello" + s2;(вызывается конструктор и создает временный объект)
}
String operator + (String s, const char c){ //возвращаем уже не ссылку! т.к на самом деле реального объета не существует есть лишь временное значение 
	return s += c;							//как например с int a = b + c; результат вычесления b+c временно хранится где-то на стеке
}
bool operator != (const String s1, const String s2){
	return !(s1 == s2);
}

bool operator > (const String s1, const String s2){
	return s2 < s1;
}
bool operator <= (const String s1, const String s2){
	return !(s2 < s1);
}
bool operator >= (const String s1, const String s2){
	return !(s1 < s2);
}



void bubblesort(String* m, int size){  //сортировка пузырьком 
	for (int i = 0; i < size; ++i) 
		for (int j = i; j < size; ++j) 
			if (m[j] < m[i])
				m[j].swap_s(m[i]);
}

void printMas(String* m, int size){ //печать массива
	for (int i = 0; i < size; ++i) {
		cout << m[i] << " ";
	}
	cout << endl;
}

int main (int argc, char *argv[]){
	cout << "Enter mas size:";
	int size = 0;
	cin >> size; 
	cout << "Enter " << size << " words" << endl;
	String* mas = new String[size];
	for (int i = 0; i < size; ++i) {
		cin >> mas[i];
	}
	cout << "Your input:" <<endl;
	printMas(mas,size);
	bubblesort(mas,size);
	cout << "After sort:" <<endl;
	printMas(mas,size);
	delete	[] mas;
	return 0;
}