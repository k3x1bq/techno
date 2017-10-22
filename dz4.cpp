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
			cout << tmp->data << " ";
			tmp = tmp->next;
		}
	}
private:
	element* head;
};

int main (int argc, char *argv[]){
	
	return 0;
}