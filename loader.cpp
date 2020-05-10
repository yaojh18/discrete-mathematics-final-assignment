#include"loader.h"
#include"init.h"
static int paper_cnt=0;
static int author_cnt=0;
void load_data(){
    ifstream fin("papers.csv");
    string line;
    getline(fin,line);
    while (getline(fin, line))                          
    {
        istringstream sin(line);                        
        PaperData p;
        vector<string> tp={};
        string s;
        while (1){
            if (sin.peek()=='"')
                if (!getline(sin,s,'"'))break;
                else{
                    tp.push_back(s);
                    sin.get();
                } 
            else
                if (!getline(sin,s,',')) break; 
                else tp.push_back(s);
        }
        paper_id_to_DOI.push_back(tp[3]);
        paper_DOI_to_id.insert(make_pair(tp[3],paper_cnt++));
        p.conference=tp[0];
        p.year=stoi(tp[1]);
        p.title=tp[2];
        p.abstract=tp[9];
        sin.str(tp[12]);
        while (getline(sin,s,';'))
            p.referencesDOI.push_back(s);
        sin.str(tp[13]);
        while (getline(sin,s,','))
            p.keywords.push_back(s);
        vector<string> aname;
        sin.str(tp[10]);
        while (getline(sin,s,';'))
            aname.push_back(s);
        vector<string> aaffiliation;
        sin.str(tp[11]);
        while (getline(sin,s,';'))
            aaffiliation.push_back(s);
        for (int i=0;i<aname.size();i++){
            p.authorname.push_back(aname[i]);
            map<string, AuthorData>::iterator iter=authordata.find(aname[i]);
            if (iter==authordata.end()){
                AuthorData a;
                author_id_to_name.push_back(a.name);
                author_name_to_id.insert(make_pair(a.name,author_cnt++));
                a.name=aname[i];
                a.affiliation=aaffiliation[i];
                a.paperDOI.push_back(tp[3]);
                authordata.insert(make_pair(a.name,a));
            }
            else
                iter->second.paperDOI.push_back(tp[3]);
        }
        paperdata.insert(make_pair(tp[3],p));
    }
    fin.close();

}