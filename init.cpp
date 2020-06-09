#include"init.h"
vector<string> author_id_to_name;
vector<string> paper_id_to_DOI;
map<string,int> author_name_to_id;
map<string,int> paper_DOI_to_id;
void init_paper(){
    //TODO
    for (int i=0;i<paper_id_to_DOI.size();i++){
        Paper p;
        PaperData pdata=paperdata.find(paper_id_to_DOI[i])->second;
        p.abstract=pdata.abstract;
        p.conference=pdata.conference;
        p.keywords=pdata.keywords;
        p.title=pdata.title;
        p.year=pdata.year;
        for(int j=0;j<pdata.referencesDOI.size();j++){
            auto t = paper_DOI_to_id.find(pdata.referencesDOI[j]);
            if (t!=paper_DOI_to_id.end())
                p.references.push_back(t->second);
        }  
        for(int j=0;j<pdata.authorname.size();j++){
            auto t = author_name_to_id.find(pdata.authorname[j]);
            if (t!=author_name_to_id.end())
                p.author.push_back(author[t->second]);
        }
        paper.push_back(p);
    }

}
void init_author(){
    //TODO
    for (int i=0;i<author_id_to_name.size();i++){
        Author a;
        AuthorData adata=authordata.find(author_id_to_name[i])->second;
        a.affiliation=adata.affiliation;
        a.name=adata.name;
        for (int j=0;j<adata.paperDOI.size();j++){
            auto t = paper_DOI_to_id.find(adata.paperDOI[j]);
            if (t!=paper_DOI_to_id.end())
                a.paperid.push_back(t->second);
        }
        author.push_back(a);
    }
}
void init_paper_connection(){
    //TODO

}
void init_author_connection(){
    //TODO

}
