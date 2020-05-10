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
        string DOI;
        string title;
        string abstract;
        vector<AuthorData> author = {};
        vector<string> referencesDOI = {};
        vector<string> keywords = {};
        PaperData(){}
};
class Author{
    public:
        string name;
        string affiliation = "";
        vector<int> paperid = {};
        int closeness_centrality = 0;
        int betweenness_centrality = 0;
        //ADD

        Author(){}
};
class Paper{
    public:
        string conference;
        int year;
        string title;
        string abstract;
        vector<Author> author = {};
        vector<int> references = {};
        vector<string> keywords = {};
        int closeness_centrality = 0;
        int betweenness_centrality = 0;
        //ADD

        Paper(){}
};
class Connection{
    public:
        int distance = INT_MAX;
        int weight = INT_MAX;
        //ADD

        Connection(){}
};

vector<AuthorData> authordata;
vector<PaperData> paperdata;

vector<Paper> paper;
vector<Author> author;

vector<vector<Connection>> paper_connection;
vector<vector<Connection>> author_connection;

