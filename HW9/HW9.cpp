#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int E;
vector<vector<int> > graph;
vector<int> color;

ifstream input("input.txt");
ofstream output("output.txt");

bool isBipartite(){
    color[0] = 1;
    queue <int> q;           // for BFS traversal
    q.push(0);
    while(!q.empty()){
        int tmp = q.front();
        q.pop();
        for(int i = 0; i < graph[tmp].size(); i++){
            if(color[graph[tmp][i]] == -1){
                color[graph[tmp][i]] = 1 - color[tmp];  // assign alternate color
                q.push(graph[tmp][i]);
            }
            else if(color[graph[tmp][i]] == color[tmp]) return false;
        }
    }
    vector<int> set_0;
    for(int i = 0; i < 2 * E; i++){       // 2 sets
        if(color[0] == color[i]){
        set_0.push_back(i);
        }
    }
    output << set_0[0];
    for(int i = 1; i < set_0.size(); i++){
         output << "," << set_0[i];
    }
    output << endl;
    return true;
}

int main(){
    while(!input.eof()){
        input >> E;
        int v1, v2;
        graph.resize(E);
        color.resize(2 * E, -1);       // -1 for no color, 1 for first color, 0 for second color
        for(int i = 0; i < E; i++){
            input >> v1 >> v2;
            graph[v1].push_back(v2);
            graph[v2].push_back(v1);
        }
        if(!isBipartite()){
            output << "-1" << endl;
        }
    }
    input.close();
    output.close();
    return 0;
}