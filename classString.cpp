#include <iostream>
#include <cstring> // strlen, strcpy
#include <algorithm> //swap
#include <cctype>

using namespace std;

class String {
public:
	String(const char *str = "") { 
		size = strlen(str);
		this->str = new char[size+1];
		strcpy(this->str,str);
	}
	String(const String &other){
		size = other.size;
		this->str = new char[size+1];
		for (int i = 0; i < size+1; ++i) 
			str[i] = other.str[i];
	}
	int len(){
		return this->size;
	}
	int len() const {
		return this->size;
	}
	String& operator = (const String &other) {
		if (this != &other)
			String(other).swap_s(*this); // создается временная копия объекта(которая полностью копирует 
		return *this;                    // элемент которому нужно прировняться. Затем меняется местами
	}
	String& operator += (const char c){
		this->append(c);
		return *this;
	}
	String& operator += (const String &other){
		this->append(other);
		return *this;
	}
	char operator [] (int i){
		if (i <= this->size)
			return str[i];
		else
			return ' ';
	}
	char operator [] (int i) const {
		if (i <= this->size)
			return str[i];
		else
			return ' ';
	}
	friend std::ostream& operator << (std::ostream& os, String const& obj){
		return os << obj.str;
	}
	friend std::istream& operator >> (std::istream& is, String& obj){
		//int tmp_size = 0;
		is.sync();
		String tmp;
		while ( !isspace(is.peek()) ){
			tmp += (char)cin.get();
			//++tmp_size;
		}
		delete [] obj.str;
		obj.size = tmp.size;
		obj.str = new char[tmp.size];
		obj = tmp;
		return is;
	}
	friend bool operator == (const String s1, const String s2){
		if (strcmp(s1.str,s2.str)==0)
			return true;
		else 
			return false;
	}
	friend bool operator < (const String s1, const String s2){
		if (strcmp(s1.str,s2.str) < 0)
			return true;
		else 
			return false;
	}
	~String(){
		delete [] str;
	}
	void append(const String &other){
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
	void append(const char c){
		char *tmp = new char[size+2];
		strcpy(tmp, str);
		tmp[this->size] = c;
		tmp[this->size + 1] = '\0';
		delete [] str;
		this->str = tmp;
		this->size = strlen(str);
	}

	void swap_s(String &other){
		swap(size,other.size);
		swap(str, other.str);
	}
//private:	
	int size;
	char *str;
};

String operator + (String s1, String const& s2){ //за классом чтобы можно было писать
	return s1 += s2;							//s1 = "hello" + s2;(вызывается конструктор и создает временный объект)
}
String operator + (String s, const char c){
	return s += c;
}
/*bool operator == (const String s1, const String s2){
	if (strcmp(s1.str,s2.str)==0)
		return true;
	else 
		return false;
}*/
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

int main (int argc, char *argv[]){
	String* mas = new String[5];
	String s1;
	int d = 0;
	cin >> s1 >> d;
	cout << s1 <<" " << d;
	delete [] mas;
	return 0;
}