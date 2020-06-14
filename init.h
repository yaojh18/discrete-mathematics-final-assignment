#pragma once
#include"data.h"
#include"m_algorithm.h"
using namespace std;

void init_paper(){
    for (int i=0;i<paper_id_to_DOI.size();i++){
        PaperData pdata=paperdata.find(paper_id_to_DOI[i])->second;
        Paper p(pdata.title,pdata.abstract,pdata.keywords);
        p.conference=pdata.conference;
        p.year=pdata.year;
        p.DOI=paper_id_to_DOI[i];
        for(int j=0;j<pdata.referencesDOI.size();j++){
            auto t = paper_DOI_to_id.find(pdata.referencesDOI[j]);
            if (t!=paper_DOI_to_id.end())
                p.references.push_back(t->second);
        }  
        for(int j=0;j<pdata.authorname.size();j++){
            auto t = author_name_to_id.find(pdata.authorname[j]);
            if (t!=author_name_to_id.end())
                p.author.push_back(t->second);
        }
        paper.push_back(p);
    }
}
void init_author(){
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
    int size = paper.size();
    paper_connection.resize(size);
    for (int i=0;i<size;i++)
        paper_connection[i].resize(size);
}
void init_author_connection(){
    int size = author.size();
    author_connection.resize(size);
    for (int i=0;i<size;i++)
        author_connection[i].resize(size);
}
void init(){
    init_author();
    init_paper();
    init_author_connection();
    init_paper_connection();
}

void init_distance(){
    const int abstract_match = 10;
    const int kewords_match = 10;
    const int title_match = 10;
    const int author_match = 5;
    const int affiliation_match = 2; 
    const int paper_match = 10;
    vector<vector<int>> paper_tmp(paper.size());
    for (int i=0;i<paper.size();i++){
        for (int j=i+1;j<paper.size();j++){
            int match = 0;
            int tmp_match = 0;
            for (int k=0;k<paper[i].keywords.size();k++){
                if (BM_Search()(paper[j].abstract.c_str(),paper[i].keywords[k].c_str())!=-1)
                    match+=abstract_match;
                if (BM_Search()(paper[j].title.c_str(),paper[i].keywords[k].c_str())!=-1)
                    match+=title_match;
            }
            for (int k=0;k<paper[j].keywords.size();k++){
                if (BM_Search()(paper[i].abstract.c_str(),paper[j].keywords[k].c_str())!=-1)
                    match+=abstract_match;
                if (BM_Search()(paper[i].title.c_str(),paper[j].keywords[k].c_str())!=-1)
                    match+=title_match;
            }
            for (int k=0;k<paper[i].keywords.size();k++)
                for (int l=0;l<paper[j].keywords.size();l++)
                    if (paper[i].keywords[k]==paper[j].keywords[l])
                        match+=kewords_match;
            for (int k=0;k<paper[i].author.size();k++)
                for (int l=0;l<paper[j].author.size();l++){
                    if (author[paper[i].author[k]].name == author[paper[j].author[l]].name)
                        tmp_match+=author_match;
                    if (author[paper[i].author[k]].affiliation == author[paper[j].author[l]].affiliation)
                        tmp_match+=affiliation_match;
                }
            if (match!=0||tmp_match!=0){
                paper[i].neighbors.push_back(j);
                paper[i].distance.push_back(match);
                paper_tmp[i].push_back(tmp_match);
                paper[j].neighbors.push_back(i);
                paper[j].distance.push_back(match);
                paper_tmp[j].push_back(tmp_match);
            }
        }
    }
    for (int i=0;i<author.size();i++)
        for (int j=i+1;j<author.size();j++){
            int match = 0;
            if (author[i].affiliation == author[j].affiliation)
                match+=affiliation_match;
            for (int k=0;k<author[i].paperid.size();k++)
                for (int l=0;l<author[j].paperid.size();l++){
                    if (author[i].paperid[k] == author[j].paperid[l])
                        match+=paper_match;
                    for (int m=0;m<paper[author[i].paperid[k]].neighbors.size();m++)
                        if (paper[author[i].paperid[k]].neighbors[m] == author[j].paperid[l]){
                            match+=paper[author[i].paperid[k]].distance[m]/10;
                            break;
                        }
                }
            if (match!=0){
                author[i].neighbors.push_back(j);
                author[i].distance.push_back((int)(100.0/(double)match));
                author[j].neighbors.push_back(i);
                author[j].distance.push_back((int)(100.0/(double)match));
            }
        }
    for (int i=0;i<paper.size();i++){
        for (int j=0;j<paper[i].neighbors.size();j++)
            paper[i].distance[j] = (int)(100.0/(double)(paper[i].distance[j] + paper_tmp[i][j]));
    }
    Warshall<vector<Paper>>()(paper_connection,paper);
    Warshall<vector<Author>>()(author_connection,author);
}

void init_group(){
    DFS<vector<Author>>()(author);
    DFS<vector<Paper>>()(paper);
}

void init_label(){
    LabelSpreading<vector<Author>>()(author);
    LabelSpreading<vector<Paper>>()(paper);
}