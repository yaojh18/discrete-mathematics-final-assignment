#include"init.h"
#include"loader.h"
#include"data.h"
#include"m_algorithm.h"
#include <iostream>
using namespace std;

map<string,AuthorData> authordata;
map<string,PaperData> paperdata;

vector<Paper> paper;
vector<Author> author;

vector<vector<Connection>> paper_connection;
vector<vector<Connection>> author_connection;

vector<string> author_id_to_name;
vector<string> paper_id_to_DOI;
map<string,int> author_name_to_id;
map<string,int> paper_DOI_to_id;

int main(){
    load_data();
    init();
    init_distance();
    init_group();
    init_label();
    system("pause");
    return 0;
}