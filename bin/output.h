#include <fstream>
#include "data.h"
using namespace std;
void output_as_csv(vector<Paper>& paper, vector<Author>& author,vector<vector<Connection>>& paper_connection,vector<vector<Connection>>& author_connection){
    ofstream fout("paper.csv");
    fout<<"ID,closeness_centrality,betweenness_centrality,group,label"<<endl;
    for (int i=0;i<paper.size();i++)
        fout<<paper[i].DOI<<','<<paper[i].closeness_centrality<<','<<paper[i].betweenness_centrality<<','<<paper[i].group<<','<<paper[i].label<<endl;
    fout.close();
    fout.open("paper_connection.csv");
    fout<<"source,target,distance,label"<<endl;
    for (int i=0;i<paper.size();i++)
        for (int j=0;j<paper[i].neighbors.size();j++)
            fout<<i<<','<<paper[i].neighbors[j]<<','<<paper[i].distance[j]<<','<<(paper[i].label==paper[paper[i].neighbors[j]].label)<<endl;
    fout.close();
    fout.open("author.csv");
    fout<<"ID,closeness_centrality,betweenness_centrality,group,label"<<endl;
    for (int i=0;i<author.size();i++)
        fout<<'\"'<<author[i].name<<"\","<<author[i].closeness_centrality<<','<<author[i].betweenness_centrality<<','<<author[i].group<<','<<author[i].label<<endl;
    fout.close();
    fout.open("author_connection.csv");
    fout<<"source,target,distance,label"<<endl;
    for (int i=0;i<author.size();i++)
        for (int j=0;j<author[i].neighbors.size();j++)
            fout<<i<<','<<author[i].neighbors[j]<<','<<author[i].distance[j]<<','<<(author[i].label==author[author[i].neighbors[j]].label)<<endl;
    fout.close();
    fout.open("paper_distance.csv");
    fout<<0;
    for (int i=1;i<paper_connection.size();i++)
        fout<<','<<i;
    fout<<endl;
    for (int i=0;i<paper_connection.size();i++){
        fout<<paper_connection[i][0].distance;
        for(int j=1;j<paper_connection.size();j++)
            fout<<','<<paper_connection[i][j].distance;
        fout<<endl;
    }   
    fout.close();
    fout.open("author_distance.csv");
    fout<<0;
    for (int i=1;i<author_connection.size();i++)
        fout<<','<<i;
    fout<<endl;
    for (int i=0;i<author_connection.size();i++){
        fout<<author_connection[i][0].distance;
        for(int j=1;j<author_connection.size();j++)
            fout<<','<<author_connection[i][j].distance;
        fout<<endl;
    }   
    fout.close();
    fout.open("references.csv");
    fout<<"source,target"<<endl;
    for (int i=0;i<paper.size();i++)
        for (int j=0;j<paper[i].references.size();j++)
            fout<<i<<','<<paper[i].references[j]<<endl;
    fout.close();
}