#include <iostream>
#include <fstream>
#include "shape.h"

using namespace std;



int main(int argc,char **argv) {
    ifstream input(*++argv);
    shape** mas;
    int size = create_mas_from_file(input,mas);
    for (int i = 0; i < size; ++i) {
        mas[i]->show();
        cout << "area = "<<mas[i]->area() << endl;
        cout << "volume = " << mas[i]->volume() << endl<<endl;
    }
    free_mas(mas,size);
    return 0;
}