#pragma once
#include"data.h"
#include"m_algorithm.h"
#include <iostream>
using namespace std;

void init_paper(map<string,PaperData>& paperdata, vector<Paper>& paper,
vector<string>& paper_id_to_DOI, map<string,int>& paper_DOI_to_id, map<string,int>& author_name_to_id){
    for (int i=0;i<paper_id_to_DOI.size();i++){
        PaperData pdata=paperdata.find(paper_id_to_DOI[i])->second;
        Paper p;
        p.title=pdata.title;
        p.abstract=pdata.abstract;
        p.keywords=pdata.keywords;
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
void init_author(map<string,AuthorData>& authordata, vector<Author>& author,
vector<string>& author_id_to_name,map<string,int>& paper_DOI_to_id){
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
void init_paper_connection(vector<Paper>& paper, vector<vector<Connection>>& paper_connection){
    int size = paper.size();
    paper_connection.resize(size);
    for (int i=0;i<size;i++)
        paper_connection[i].resize(size);
}
void init_author_connection(vector<Author>& author, vector<vector<Connection>>& author_connection){
    int size = author.size();
    author_connection.resize(size);
    for (int i=0;i<size;i++)
        author_connection[i].resize(size);
}
void init(map<string,PaperData>& paperdata, map<string,AuthorData>& authordata, 
vector<Paper>& paper, vector<Author>& author, 
vector<string>& paper_id_to_DOI, map<string,int>& paper_DOI_to_id, 
vector<string>& author_id_to_name, map<string,int>& author_name_to_id,
vector<vector<Connection>>& paper_connection, vector<vector<Connection>>& author_connection){
    init_author(authordata,author,author_id_to_name,paper_DOI_to_id);
    init_paper(paperdata,paper,paper_id_to_DOI,paper_DOI_to_id,author_name_to_id);
    init_author_connection(author,author_connection);
    init_paper_connection(paper,paper_connection);
}

void init_distance(vector<Paper>& paper, vector<Author>& author, 
vector<vector<Connection>>& paper_connection, vector<vector<Connection>> & author_connection){
    const int abstract_match = 5;
    const int kewords_match = 10;
    const int title_match = 8;
    const int author_match = 8;
    const int affiliation_match = 2; 
    const int paper_match = 10;
    const int reference_match = 10;
    for (int i=0;i<paper.size();i++){
        for (int j=i+1;j<paper.size();j++){
            int match = 0;
            for (int k=0;k<paper[i].keywords.size();k++){
                if (paper[j].abstract.find(paper[i].keywords[k])!=paper[j].abstract.npos)
                    match+=abstract_match;
                if (paper[j].title.find(paper[i].keywords[k])!=paper[j].title.npos)
                    match+=title_match;
            }
            for (int k=0;k<paper[j].keywords.size();k++){
                if (paper[i].abstract.find(paper[j].keywords[k])!=paper[i].abstract.npos)
                    match+=abstract_match;
                if (paper[i].title.find(paper[j].keywords[k])!=paper[i].title.npos)
                    match+=title_match;
            }
            for (int k=0;k<paper[i].keywords.size();k++)
                for (int l=0;l<paper[j].keywords.size();l++)
                    if (paper[i].keywords[k]==paper[j].keywords[l])
                        match+=kewords_match;
            if (match!=0){
                paper[i].neighbors.push_back(j);
                paper[i].distance.push_back(match);
                paper[j].neighbors.push_back(i);
                paper[j].distance.push_back(match);
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
                            match+=paper[author[i].paperid[k]].distance[m]/5;
                            break;
                        }
                }
            if (match>2){
                author[i].neighbors.push_back(j);
                author[i].distance.push_back((int)(100.0/(double)match));
                author[j].neighbors.push_back(i);
                author[j].distance.push_back((int)(100.0/(double)match));
            }
        }
    for (int i=0;i<author.size();i++){
        for (int j=0;j<author[i].paperid.size();j++)
            for (int k=j+1;k<author[i].paperid.size();k++){
                bool f=true;
                for (int l=0;l<paper[author[i].paperid[j]].neighbors.size();l++)
                    if (paper[author[i].paperid[j]].neighbors[l] == author[i].paperid[k]){
                        paper[author[i].paperid[j]].distance[l]+=author_match;
                        f=false;
                        break;
                    }
                if (f){
                    paper[author[i].paperid[j]].neighbors.push_back(author[i].paperid[k]);
                    paper[author[i].paperid[j]].distance.push_back(author_match);
                }
                f=true;
                for (int l=0;l<paper[author[i].paperid[k]].neighbors.size();l++)
                    if (paper[author[i].paperid[k]].neighbors[l] == author[i].paperid[j]){
                        paper[author[i].paperid[k]].distance[l]+=author_match;
                        f=false;
                        break;
                    }
                if (f){
                    paper[author[i].paperid[k]].neighbors.push_back(author[i].paperid[j]);
                    paper[author[i].paperid[k]].distance.push_back(author_match);
                }
            }
    }
    for (int i=0;i<paper.size();i++){
        for (int j=0;j<paper[i].references.size();j++){
            bool f=true;
            for (int k=0;k<paper[i].neighbors.size();k++)
                if (paper[i].neighbors[k] == paper[i].references[j]){
                    paper[i].distance[k]+=reference_match;
                    f=false;
                    break;
                }
            if (f){
                paper[i].neighbors.push_back(paper[i].references[j]);
                paper[i].distance.push_back(reference_match);
            }
            f=true;
            for (int k=0;k<paper[paper[i].references[j]].neighbors.size();k++){
                if (paper[paper[i].references[j]].neighbors[k] == i){
                    paper[paper[i].references[j]].distance[k]+=reference_match;
                    f=false;
                    break;
                }
            }
            if (f){
                paper[paper[i].references[j]].neighbors.push_back(i);
                paper[paper[i].references[j]].distance.push_back(reference_match);
            }
        }
    }
    for (int i=0;i<paper.size();i++){
        for (int j=0;j<paper[i].neighbors.size();j++)
            paper[i].distance[j] = (int)(100.0/(double)(paper[i].distance[j]));
    }
    Warshall<vector<Paper>>(paper_connection,paper)();
    Warshall<vector<Author>>(author_connection,author)();
}
void init_group(vector<Paper>& paper, vector<Author>& author){
    DFS<vector<Author>>()(author);
    DFS<vector<Paper>>()(paper);
}

void init_label(vector<Paper>& paper, vector<Author>& author){
    LabelSpreading<vector<Author>>()(author,13.0);
    LabelSpreading<vector<Paper>>()(paper,10.0);
}