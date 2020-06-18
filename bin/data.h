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
        int label = -1;
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
        int label = -1;
        vector<int> neighbors;
        vector<int> distance;

        string title;
        string abstract;
        vector<string> keywords;
        Paper(){}
};
class Connection{
    public:
        int distance = 200000;
        int intermediary = -1;
        Connection(){}
};

