#pragma once
#include"data.h"
#include<fstream>
#include<sstream>
using namespace std;

static int paper_cnt=0;
static int author_cnt=0;

void load_data(map<string,PaperData>& paperdata, map<string,AuthorData>& authordata, 
vector<string>& paper_id_to_DOI, map<string,int>& paper_DOI_to_id, 
vector<string>& author_id_to_name, map<string,int>& author_name_to_id){
    ifstream fin("../bin/test.csv");
    string line;
    getline(fin,line);
    while (getline(fin, line))                          
    {
        istringstream sin(line);                        
        PaperData p;
        vector<string> tp={};
        string s;
        while (!sin.eof()){
            if (sin.peek()=='"'){
                string ss="";
                do{
                    sin.get();
                    getline(sin,s,'"');
                    ss+=s;
                }
                while (sin.peek()=='"');
                tp.push_back(ss);  
                sin.get();
            } 
            else{
                getline(sin,s,',');
                tp.push_back(s);
            }  
	    }
        paper_id_to_DOI.push_back(tp[3]);
        paper_DOI_to_id.insert(make_pair(tp[3],paper_cnt++));
        p.conference=tp[0];
        p.year=stoi(tp[1]);
        p.title=tp[2];
        p.abstract=tp[9];
        istringstream sinreferences(tp[12]);
        while (getline(sinreferences,s,';'))
            p.referencesDOI.push_back(s);
        istringstream sinkeywords(tp[13]);   
        while (getline(sinkeywords,s,','))
            p.keywords.push_back(s);
        vector<string> aname;
        istringstream sinaname(tp[10]);
        while (getline(sinaname,s,';'))
            aname.push_back(s);
        vector<string> aaffiliation;
        istringstream sinaaffiliation(tp[11]);
        while (getline(sinaaffiliation,s,';'))
            aaffiliation.push_back(s);
        if (aaffiliation.size()<aname.size())
            aaffiliation.push_back("");
        for (int i=0;i<aname.size();i++){
            p.authorname.push_back(aname[i]);
            map<string, AuthorData>::iterator iter=authordata.find(aname[i]);
            if (iter==authordata.end()){
                AuthorData a;
                author_id_to_name.push_back(aname[i]);
                author_name_to_id.insert(make_pair(aname[i],author_cnt++));
                a.name=aname[i];
                a.affiliation=aaffiliation[i];
                a.paperDOI.push_back(tp[3]);
                authordata.insert(make_pair(a.name,a));
            }
            else{
                iter->second.paperDOI.push_back(tp[3]);
                if (iter->second.affiliation==""&&aaffiliation[i]!="")
                    iter->second.affiliation=aaffiliation[i];
            }
        }
        paperdata.insert(make_pair(tp[3],p));
    }
    fin.close();
}