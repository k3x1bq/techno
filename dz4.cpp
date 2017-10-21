#include <iostream>
#include <cstring>
using namespace std;

void cpy (char* str1,const char* str2){
	for (; *str2 != '\0'; ++str2,++str1)
		*str1 = *str2;
	*str1 = '\0'; 
	return;
}

class product{
public:
	product(const char* s = "", const char* s2 = "", int pr = 0, int days = 0, int count = 0):
	 	name(new char[strlen(s)+1]),producer(new char[strlen(s2)+1]), price(pr), days(days), count(count)
		{
			cpy(this->name,s);
			cpy(this->producer, s2);
		}

	product(const product& other){
		this->name = new char [strlen(other.name)+1];
		cpy(this->name, other.name);
		this->producer = new char [strlen(other.producer)+1];
		cpy(this->producer, other.producer);
		this->price = other.price;
		this->days = other.days;
		this->count = other.count;
	}	
	void show_all(){
		cout << name <<" "<< producer <<" "<< price <<" "<< days <<" "<< count << endl;
	}	
private:
	char* name;
	char* producer;
	int price;
	int days;
	int count;
};	

int main (int argc, char *argv[]){
	product test("hui","ya",300);
	test.show_all();
	product test2(test);
	test2.show_all();
	return 0;
}