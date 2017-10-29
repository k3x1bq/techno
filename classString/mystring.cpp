#include "mystring.hpp"
#define STEP 100



String::String(const char *str) { 
	this->size = strlen(str);
	this->str = new char[size+1];
	strcpy(this->str,str);
}
String::String(const String &other){
	this->size = other.size;
	this->str = new char[size+1];
	strcpy(this->str,str);
}
String::~String(){
	delete [] str;
}
String& String::operator = (const String &other) {
	if (this != &other)
		String(other).swap_s(*this); 
	return *this;                    
}



int String::len(){
	return this->size;
}
int String::len() const {
	return this->size;
}
void String::append(const String &other){
	char *p = new char[size + other.size + 1];
	strcpy(p,this->str);
	int i = this->size;
	for (int k = 0; i < (this->size + other.size) && k < other.size; ++i,++k) 
		p[i] = other.str[k];
	p[i] = '\0';
	delete [] (this->str);
	this->str = p;
	this->size = strlen(str);
}
void String::append(const char c){
	char *tmp = new char[size+2];
	strcpy(tmp, str);
	tmp[this->size] = c;
	tmp[this->size + 1] = '\0';
	delete [] str;
	this->str = tmp;
	this->size = strlen(str);
}

void String::swap_s(String &other){
// 	String tmp = other;
// 	other = *this;
// 	*this = tmp;
	std::swap(this->size,other.size);
	std::swap(this->str, other.str);
}

void swap (String& s1, String& s2){
	String tmp = s1;
 	s1 = s2;
 	s2 = tmp;
}


char& String::operator [] (int i){
	if (i <= this->size)
		return str[i];
	else
		return str[this->size];
}
char String::operator [] (int i) const {
	if (i <= this->size)
		return str[i];
	else
		return '\0';
}


std::ostream& operator << (std::ostream& os, String const& obj){
	return os << obj.str;
}
std::istream& operator >> (std::istream& is, String& obj){ //перегрузка считывание с экрана
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


String& String::operator += (const char c){
	this->append(c);
	return *this;
}
String& String::operator += (const String &other){
	this->append(other);
	return *this;
}
String operator + (String s1, String const& s2){
	return s1 += s2;
}
String operator + (String s, const char c){
	return s += c;
}



bool operator == (const String s1, const String s2){
	if (strcmp(s1.str,s2.str)==0)
		return true;
	else 
		return false;
}
bool operator < (const String s1, const String s2){
	//return (strcmp(s1.str,s2.str) < 0);
	if (strcmp(s1.str,s2.str) < 0)
		return true;
	else 
		return false;
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