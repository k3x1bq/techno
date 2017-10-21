#include <iostream>
#include <cstring>
using namespace std;

void cpy (char* str1, char* str2){
	for (; *str2 != '\0'; ++str2,++str1)
		*str1 = *str2;
	*str = '\0'; 
	return;
}

class product{
public:
	product(const char* s = "", const char* s2 = "", int pr = 0, int days = 0, int count = 0):
	 	name(new char[strlen(s)+1]),producer(new char[strlen(s2)+1]), price(pr), days(days), count(count)
		{
			for (int i = 0; i < strlen(s); ++i)
				name[i] = s[i];
			for (int i = 0; i < strlen(s2); ++i) 
				producer[i]=s2[i];
			name[strlen(s)] = '\0';
			producer[strlen(s2)] = '\0';
		}

	product(const product& other){
		this->name = new char [strlen(other.name)+1];

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
	return 0;
}