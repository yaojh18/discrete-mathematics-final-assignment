#pragma once
#include <algorithm>
#include <cmath>
#include <cstring>
#include "data.h"
#include <stack>
#include <queue>
#define SIZE 256   

using namespace std;

class BM_Search{
    private:
        void generateBadChar(const char *b, int m, int *badchar){
            int i, ascii;
            for(i = 0; i < SIZE; ++i){
                badchar[i] = -1;
            }
            for(i = 0; i < m; ++i){
                ascii = int(b[i]);
                badchar[ascii] = i;
            }
        }
        void generateGS(const char *b, int m, int *suffix, bool *prefix){
            int i, j, k;
            for(i = 0; i < m; ++i){
                suffix[i] = -1;
                prefix[i] = false;
            }
            for(i = 0; i < m-1; ++i){
                j = i;
                k = 0;
                while(j >= 0 && b[j] == b[m-1-k]){
                    --j;
                    ++k;
                    suffix[k] = j+1;
                }
                if(j == -1)
                    prefix[k] = true;
            }
        }
        int moveByGS(int j, int m, int *suffix, bool *prefix){
            int k = m - 1 - j;
            if(suffix[k] != -1)
                return j - suffix[k] + 1;
            for(int r = j + 2; r < m; ++r){
                if(prefix[m-r] == true)
                    return r;
            }
            return m;
        }
    public:
        BM_Search() {}
        int operator () (const char* a, const char *b){
            int n = strlen(a);
            int m = strlen(b);
            int *badchar = new int [SIZE];
            generateBadChar(b,m,badchar);    
            int *suffix = new int [m];
            bool *prefix = new bool [m];
            generateGS(b, m, suffix, prefix);   
            int i = 0, j, moveLen1, moveLen2;
            while(i < n-m+1){
                for(j = m -1; j >= 0; --j){
                    if(a[i+j] != b[j])
                        break; 
                }
                if(j < 0){
                    delete [] badchar;
                    delete [] suffix;
                    delete [] prefix;
                    return i;   
                }
                moveLen1 = j - badchar[int(a[i+j])];
                moveLen2 = 0;
                if(j < m-1){
                    moveLen2 = moveByGS(j,m,suffix,prefix);
                }
                i = i + max(moveLen1,moveLen2);
            }
            delete [] badchar;
            delete [] suffix;
            delete [] prefix;
            return -1;
        }
};

template <typename T>
class Warshall{
    private:
        vector<vector<Connection>>& map;
        T& arr;
        void search_intermediary(int x, int y){
            if (map[x][y].intermediary==-1)
                return; 
            else{
                arr[map[x][y].intermediary].betweenness_centrality++;
                search_intermediary(x,map[x][y].intermediary);
                search_intermediary(map[x][y].intermediary,y);
            }
        }
        void calculate_closeness(int v){
            for (int i=0;i<v;i++){
                int closeness = 0;
                for (int j=0;j<v;j++)
                    closeness += map[i][j].distance;
                // need changing
                arr[i].closeness_centrality = closeness;
            }
        }
    public:
        Warshall(){}
        void operator () (vector<vector<Connection>>& _map, T& _arr){
            map = _map;
            arr = _arr;
            int v = map.size();
            for (int i=0;i<arr.size();i++){
                for (int j=0;j<arr[i].neighbors.size();j++)
                    map[i][arr[i].neighbors[j]].distance = arr[i].distance[j];
            }
            for (int k=0;k<v;k++)
                for (int i=0;i<v;i++)
                    for (int j=0;j<v;j++)
                        if (map[i][k].distance + map[k][j].distance < map[i][j].distance){
                            map[i][j].distance = map[i][k].distance + map[k][j].distance;
                            map[i][j].intermediary = k;
                        }
            for (int i=0;i<v;i++)
                for (int j=0;j<v;j++)
                    search_intermediary(i,j);
            calculate_closeness(v);
        }
};
template <typename T>
class DFS{
    private:
        int group_cnt = -1;
        void DFS_search(vector<vector<Connection>>& map, T& arr,int root){
            stack<int> stack;
            stack.push(root);
            while (!stack.empty()){
                int pos = stack.top();
                stack.pop();
                for (int i = 0; i<arr[pos].neighbors.size(); i++){
                    if (arr[arr[pos].neighbors[i]].group == -1){
                        arr[arr[pos].neighbors[i]].group = group_cnt;
                        stack.push(arr[pos].neighbors[i]);
                    }
                }
            }
        }
    public:
        DFS(){}
        void operator () (T& arr){
            int v = arr.size();
            for (int i = 0; i<v; i++)
                if (arr[i].group == -1){
                    group_cnt++;
                    arr[i].group = group_cnt;
                    DFS_search(i, v);
                }
        }
};
class BFS{
    public:
        BFS(){}
        void operator() (vector<Author>& arr){
            
        }
};


template <typename T>
class LabelSpreading{
    public:
        LabelSpreading(){}
        void operator () (T& arr){
            int size = arr.size();
            const double a = 20.0;
            const int max_iteration = 100;

            vector<vector<double>> weight(size,vector<double>(size));
            for (int i=0;i<size;i++){
                double sum = 0.0;
                for (int j=0;j<arr[i].neighbors.size();j++){
                    weight[i][arr[i].neighbors[j]] = exp(-pow(arr[i].distance[j],2)/pow(a,2));
                    sum += weight[i][arr[i].neighbors[j]];
                }
                for (int j=0;j<arr[i].neighbors.size();j++){
                    weight[i][arr[i].neighbors[j]]/=sum;
                } 
            }
            for (int i=0;i<size;i++){
                arr[i].label = i;
            }

            bool flag = true;
            int interation = 0;
            while (flag&&interation<max_iteration){
                flag = true;
                interation++;
                for (int i = 0;i<size;i++){
                    double max_chance = 0.0;
                    int max_position;
                    map<int,double> label_chance;
                    for (int j = 0; j<arr[i].neighbors.size();j++){
                        auto k = label_chance.find(arr[arr[i].neighbors[j]].label);
                        if (k == label_chance.end()){
                            label_chance.insert(make_pair(arr[arr[i].neighbors[j]].label,weight[i][arr[i].neighbors[j]]));
                            if (weight[i][arr[i].neighbors[j]]>max_chance){
                                max_chance = weight[i][arr[i].neighbors[j]];
                                max_position = arr[arr[i].neighbors[j]].label;
                            }
                        }
                        else{
                            k->second+=weight[i][arr[i].neighbors[j]];
                            if (k->second>max_chance){
                                max_chance = k->second;
                                max_position = k->first;
                            }
                        }
                    }
                    if (arr[i].label != max_position){
                        arr[i].label = max_position;
                        flag = false;
                    }
                }
            }
        }
};


