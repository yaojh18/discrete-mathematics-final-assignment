#pragma once
#include <algorithm>
#include <cmath>
#include <cstring>
#include "data.h"
#include <stack>
#include <queue> 

using namespace std;

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
        Warshall(vector<vector<Connection>>& _map, T& _arr):map(_map),arr(_arr){}
        void operator () (){
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
        void DFS_search(T& arr, int root){
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
                    DFS_search(arr, i);
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
        void operator () (T& arr, const double a){
            int size = arr.size();
            const int max_iteration = 10000;
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


