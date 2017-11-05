#include <iostream>
#include "multimap.hpp"
#include <string>

using namespace std;

int main() {
    Multimap<string,int> test("HEh", 5);
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
   // cout << l1.find("heh") << endl;
    return 0;
}