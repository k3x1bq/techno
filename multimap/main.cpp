#include <iostream>
#include "multimap.hpp"
#include <string>

using namespace std;

class testcls {
public:
    testcls(int a, double b, string h):a(a),b(b),h(h){}
    testcls(const testcls& a){
        this->a = a.a;
        this->b = a.b;
        this->h = a.h;
    }
    int a;
    double b;
    string h;
};

int main() {
    Multimap<string,int>::element_multimap a("blablabla", 123);
    Multimap<string,int> test("HEh", 5);
    Multimap<string,int> test2;
   // cout << "test2: " << test2 << endl<< endl;
    test2.add("asdasda", 6);
    test2.add("asdasd",4);
    test2.add("aaa",123);
    test2.add("aaa",152);
    test2.show();
    test2.remove("asdasd");
    cout << endl;
    test2.show();
    cout << endl;
    Multimap<string,int>::element_multimap* p = test2.find("aaa1");
    p->show();
    cout << *p << endl;
    cout << endl;


    Multimap<string,int> test3;
    test3 += test2;
    test3.show();
    cout << endl;
    //test.show();
    list<string> l1;
    l1.add("hah");
    l1.add("heh");
   // cout << l1.find("heh") << endl;
    l1.add("hehe");
    l1.add("heha");
    l1.show();
    l1.remove("heh");
    l1.show();
    list<string> l2(l1); //ошибка конструктора копирования
    //l2 = l1;
    l2.show();
//    list<string> l3= l1;
//    cout << "l3: " << endl;
//    l3.show();
    //list<string> l2 = l1;
    //l2.show();
   // cout << l1.find("heh") << endl;
    //testcls t1(5,3.14,"asda");
   // testcls t2(12,32.2,"gsdsdsd");
   // list<testcls> l2;
//
   // l2.add(t1);
   // l2.add(t2);
  //  l2.show();
    return 0;
}