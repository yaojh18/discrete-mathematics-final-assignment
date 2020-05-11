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
        for(int j=0;j<pdata.referencesDOI.size();j++)
            p.references.push_back(paper_DOI_to_id.find(pdata.referencesDOI[j])->second);
        for(int j=0;j<pdata.authorname.size();j++){
            p.author.push_back(author[author_name_to_id.find(pdata.authorname[j])->second]);
        }
    }

}
void init_author(){
    //TODO
    for (int i=0;i<author_id_to_name.size();i++){
        Author a;
        AuthorData adata=authordata.find(author_id_to_name[i])->second;
        a.affiliation=adata.affiliation;
        a.name=adata.name;
        for (int j=0;j<adata.paperDOI.size();j++)
            a.paperid.push_back(paper_DOI_to_id.find(adata.paperDOI[j])->second);
        author.push_back(a);
    }
}
void init_paper_connection(){
    //TODO

}
void init_author_connection(){
    //TODO

}
