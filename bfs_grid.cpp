// Author Dhaval Patel
// Liscence: MIT liscence 

#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<unordered_map>
#define ROW 10
#define COL 11
using namespace std;
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

vector<pair<int,int>> trace_path(unordered_map<pair<int,int>,pair<int,int>, hash_pair>mymap,pair<int,int> point,pair<int,int> source);
vector<pair<int,int>> bfs(pair<int,int> source,pair<int,int> dest, int grid[ROW][COL]);
void print_path(vector<pair<int,int>>);

int main()
{
    int grid[ROW][COL] = {{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
                          {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
                          {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
                          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                          {1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1},
                          {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
                          {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
                          {1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1},
                          {1, 1, 1, 0, 1, 1, 1, 0, 1, 32, 1},
                          {1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1}};

    pair<int,int> source = pair<int,int>(0,0);
    pair<int,int> dest = pair<int,int>(8,2);
    vector<pair<int,int>> path = bfs(source,dest,grid);
    print_path(path);

    //cout<<grid[dest.first][dest.second]<<endl;


    return 0;
}
void print_path(vector<pair<int,int>> path)
{
    cout<<"shortest path from source to destination is"<<endl;
    int i = 0;
    for(;i<path.size()-1;i++)
    {
        cout<<"("<<path[i].first<<", "<<path[i].second<<") -> ";
    }
    cout<<"("<<path[i].first<<", "<<path[i].second<<")";
    cout<<endl;
}
vector<pair<int,int>> get_neigbors(pair<int,int> node,vector<int> dc, vector<int> dr,int grid[ROW][COL])
{
    vector<pair<int,int>> sol;
    for(int i =0;i<dc.size();i++)
    {
        int x = node.first+dc[i];
        int y = node.second+dr[i];
        if( x<0 || y < 0 || x > ROW || x> COL) continue;
        if(grid[x][y] == 0) continue;
        pair<int,int> next{x,y};
        sol.push_back(next);
    }
    return sol;
    
}

vector<pair<int,int>> bfs(pair<int,int> source,pair<int,int> dest, int grid[ROW][COL])
{
    vector<pair<int,int>> sol;
    bool visited[ROW][COL];
    for(int i = 0;i< ROW;i++)
    {
        for(int j = 0;j < COL; j++)
        {
            visited[i][j] = false;
        }
    }

    unordered_map<pair<int,int>,pair<int,int>,hash_pair> mymap;
    vector<int> dr{-1,0,1,0};
    vector<int> dc{0,1,0,-1};
    queue<pair<int,int>> Que;
    Que.push(source);bool found = false;
    while(!Que.empty())
    {
        vector<pair<int,int>> neighors;
        pair<int,int> node = Que.front();
        Que.pop();
        neighors  = get_neigbors(node,dc,dr,grid);
        for(int i = 0;i<neighors.size();i++)
        {
            if(visited[neighors[i].first][neighors[i].second] == false)
            {
            visited[neighors[i].first][neighors[i].second] = true;
            Que.push(pair<int,int>(neighors[i]));
            mymap[neighors[i]] = node;
            if(neighors[i] == dest) 
            {
                found = true;
                break;
            }
            }
            
        }
        if(found) break;
    }
    sol = trace_path(mymap,dest,source);
    return sol;

}
vector<pair<int,int>> trace_path(unordered_map<pair<int,int>,pair<int,int>, hash_pair>mymap,pair<int,int> point,pair<int,int> source)
{
    vector<pair<int,int>> sol_rev;
    sol_rev.push_back(point);
    vector<pair<int,int>> sol;
    pair<int,int> temp = point;
    while(temp != source)
    {
        temp = mymap[temp];
        //cout<<temp.first<<" "<<temp.second<<endl;
        sol_rev.push_back(temp);
    }

    for(auto it = sol_rev.rbegin();it != sol_rev.rend();it++)
    {
        sol.push_back(*it);
    }
    return sol;
}