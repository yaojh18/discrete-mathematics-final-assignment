#include"init.h"
#include"loader.h"
#include"data.h"
#include <iostream>
using namespace std;

int main(){
    load_data();
    init_author();
    init_paper();
    system("pause");
    return 0;
}