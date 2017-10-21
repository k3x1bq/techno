#include <iostream>
using namespace std;

unsigned strlen (const char *str){
	int len = 0;
	for (; *str != '\0'; ++str)
		++len;
	return len;
}

void cpy (char* str1,const char* str2){
	for (; *str2 != '\0'; ++str2,++str1)
		*str1 = *str2;
	*str1 = '\0'; 
	return;
}

class product{
public:
	product(const char* s = "", const char* s2 = "", int pr = 0, int days = 0, int count = 0):
	 	name(new char[strlen(s)+1]),manufacturer(new char[strlen(s2)+1]), price(pr), days(days), amount(amount)
		{
			cpy(this->name,s);
			cpy(this->manufacturer, s2);
		}

	product(const product& other){
		this->name = new char [strlen(other.name)+1];
		cpy(this->name, other.name);
		this->manufacturer = new char [strlen(other.manufacturer)+1];
		cpy(this->manufacturer, other.manufacturer);
		this->price = other.price;
		this->days = other.days;
		this->amount = other.amount;
	}	

	void set_name (const char* s){	
		delete [] this->name;
		this->name = new char[strlen(s)+1];
		cpy(this->name, s);
		return;
	}
	void set_manufacturer (const char* s){	
		delete [] this->manufacturer;
		this->manufacturer = new char[strlen(s)+1];
		cpy(this->manufacturer, s);
		return;
	}
	void set_price (int pr){	
		this->price = pr;
		return;
	}
	void set_days (int d){	
		this->days = d;
		return;
	}
	void set_amount (int c){	
		this->amount =c;
		return;
	}

	char* get_name(){
		return this->name;
	}
	char* get_manufacturer(){
		return this->manufacturer;
	}
	int get_price(){
		return this->price;
	}
	int get_days(){
		return this->days;
	}
	int get_amount(){
		return this->amount;
	}

	void show_name(){
		cout << "Name: " << this->name << endl;
		return;
	}
	void show_manufacturer(){
		cout << "manufacturer: " << this->manufacturer << endl;
		return;
	}
	void show_price(){
		cout << "price: " << this->price << endl;
		return;
	}
	void show_days(){
		cout << "days: " << this->days << endl;
		return;
	}
	void show_amount(){
		cout << "amount: " << this->amount << endl;
		return;
	}

	void show_all(){
		cout << name <<" "<< manufacturer <<" "<< price <<" "<< days <<" "<< amount << endl;
	}	
private:
	char* name;
	char* manufacturer;
	int price;
	int days;
	int amount;
};	

int main (int argc, char *argv[]){
	product test("tovar","me",300);
	test.show_all();
	product test2(test);
	test2.show_all();
	product test3;
	test3.set_name("NewTovar");
	test3.show_all();
	product* test4 = new product;
	test4->set_name("ttt");
	test4->set_manufacturer("I");
	test4->set_price(10202);
	test4->set_days(123);
	test4->set_amount(23);
	test4->show_all();
	int a = test4->get_amount();
	cout << a << endl;
	test3.show_name();
	return 0;
}