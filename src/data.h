#pragma once
#include<limits.h>
#include<string>
#include<vector>
#include<map>
using namespace std;
class AuthorData{
    public:
        string name;
        string affiliation = "";
        vector<string> paperDOI = {};
        AuthorData(){}
};
class PaperData{
    public:
        string conference;
        int year;
        string title;
        string abstract;
        vector<string> authorname = {};
        vector<string> referencesDOI = {};
        vector<string> keywords = {};
        PaperData(){}
};
class Author{
    public:
        string name;
        string affiliation = "";
        vector<int> paperid;
        int closeness_centrality = 0;
        int betweenness_centrality = 0;
        int group = -1;
        int label = 0;
        vector<int> neighbors;
        vector<int> distance;
        Author(){}
};
class Paper{
    public:
        string conference;
        int year;
        string DOI;
        vector<int> author;
        vector<int> references;
        int closeness_centrality = 0;
        int betweenness_centrality = 0;
        int group = -1;
        int label = 0;
        vector<int> neighbors;
        vector<int> distance;

        string& title;
        string& abstract;
        vector<string>& keywords;
        Paper(string t, string a, vector<string> k):title(t),abstract(a),keywords(k){}
};
class Connection{
    public:
        int distance = 200000;
        int intermediary = -1;
        Connection(){}
};

extern map<string,AuthorData> authordata;
extern map<string,PaperData> paperdata;

extern vector<Paper> paper;
extern vector<Author> author;

extern vector<vector<Connection>> paper_connection;
extern vector<vector<Connection>> author_connection;

extern vector<string> author_id_to_name;
extern vector<string> paper_id_to_DOI;
extern map<string,int> author_name_to_id;
extern map<string,int> paper_DOI_to_id;

