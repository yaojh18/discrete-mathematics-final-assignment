#include"data.h"
using namespace std;
void init_paper();
void init_author();
void init_paper_connection();
void init_author_connection();

vector<string> author_id_to_name;
vector<string> paper_id_to_DOI;
map<string,int> author_name_to_id;
map<string,int> paper_DOI_to_id;