#include"../bin/init.h"
#include"../bin/loader.h"
#include"../bin/data.h"
#include"../bin/m_algorithm.h"
#include"../bin/output.h"
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
    load_data(paperdata,authordata,paper_id_to_DOI,paper_DOI_to_id,author_id_to_name,author_name_to_id);
    init(paperdata,authordata,paper,author,paper_id_to_DOI,paper_DOI_to_id,author_id_to_name,author_name_to_id,paper_connection,author_connection);
    output_as_csv(paper,author,paper_connection,author_connection);
    init_distance(paper,author,paper_connection,author_connection);
    init_group(paper,author);
    init_label(paper,author);
    output_as_csv(paper,author,paper_connection,author_connection);
    system("pause");
    return 0;
}