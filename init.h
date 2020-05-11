#pragma once
#include"data.h"
using namespace std;
void init_paper();
void init_author();
void init_paper_connection();
void init_author_connection();

extern vector<string> author_id_to_name;
extern vector<string> paper_id_to_DOI;
extern map<string,int> author_name_to_id;
extern map<string,int> paper_DOI_to_id;