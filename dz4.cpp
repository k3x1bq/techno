#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

/*unsigned strlen (const char *str){
	int len = 0;
	for (; *str != '\0'; ++str)
		++len;
	return len;
}*/

void cpy (char* str1,const char* str2){
	for (; *str2 != '\0'; ++str2,++str1)
		*str1 = *str2;
	*str1 = '\0'; 
	return;
}

class product{
public:
	product(const char* s = "", const char* s2 = "", int pr = 0, int days = 0, int count = 0):
	 	name(new char[strlen(s)+1]),manufacturer(new char[strlen(s2)+1]), price(pr), days(days), amount(count)
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

	product& operator= (const product& other){
		delete [] this->name;
		this->name = new char [strlen(other.name)+1];
		cpy(this->name,other.name);
		delete [] this->manufacturer;
		this->manufacturer = new char [strlen(other.manufacturer)+1];
		cpy(this->manufacturer,other.manufacturer);
		this->price = other.price;
		this->days = other.days;
		this->amount = other.amount;
		return *this;
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

	~product(){
		delete [] this->name;
		delete [] this->manufacturer;
	}
private:
	char* name;
	char* manufacturer;
	int price;
	int days;
	int amount;
};	

class list;

class element{
friend list;
private:
	product* data;
	element* next;
};

class list{
public:
	friend element;
	list(): head(NULL){}
	~list(){
		while (head != NULL){
			element* tmp = head->next;
			delete head;
			head = tmp;
		}
	}
	void add(product& elem){
		element* tmp = new element;
		tmp->data = new product(elem);
		tmp->next = head;
		head = tmp;
	}
	void show(){
		element* tmp = head;
		while (tmp != 0){
			tmp->data->show_all();
			tmp = tmp->next;
		}
	}
private:
	element* head;
};

void create_el(product& p,const char* s,const char* s2,int pr,int d,int am){
	p.set_name(s);
	p.set_manufacturer(s2);
	p.set_price(pr);
	p.set_days(d);
	p.set_amount(am);
}

int main (int argc, char *argv[]){
	product mas[5];	
	create_el(mas[0],"1p","aaa",10,10,5);
	create_el(mas[1],"2p","bbb",1,1,3);
	create_el(mas[2],"3p","ccc",20,15,1);
	create_el(mas[3],"2p","ddd",15,5,5);
	create_el(mas[4],"2p","3sd",123,456,2);
	list l1;
	list l2;
	list l3;
	const char* dano_name = "2p";
	int pr = 20;
	for (int i = 0; i < 5; ++i) {
		if (strcmp(mas[i].get_name(),dano_name) == 0)
			if(mas[i].get_price() <= pr){
				l1.add(mas[i]);
				l2.add(mas[i]);
			}
			else {
				l1.add(mas[i]);
			}
	}
	l1.show();
	l2.show();
	return 0;
}