#include"init.h"
#include"loader.h"
#include"data.h"
using namespace std;

int main(){
    load_author_data();
    load_paper_data();
    init_author();
    init_paper();
    return 0;
}