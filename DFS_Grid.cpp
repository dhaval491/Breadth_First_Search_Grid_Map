// Author Dhaval Patel
// Liscence: MIT liscence 

#include<iostream>
#include<stack>
#include<vector>
#include<map>
#include<unordered_map>
#include<algorithm>
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
                          {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
                          {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
                          {1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1},
                          {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
                          {1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1}};

    pair<int,int> source = pair<int,int>(3,1);
    pair<int,int> dest = pair<int,int>(6,0);
    vector<pair<int,int>> path = bfs(source,dest,grid);
    print_path(path);

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

vector<pair<int,int>> get_neighbors(pair<int,int> node,vector<int> dc, vector<int> dr,int grid[ROW][COL])
{
 // Function to explore neighbours in 6 directions  
    vector<pair<int,int>> sol;
    for(int i =0;i<dc.size();i++)
    {
        int x = node.first+dr[i]; // find the coordinates of new node
        int y = node.second+dc[i];
        // check the validity of node if outside the grid or on the obstacle
        if( x < 0 || y < 0 || x >= ROW || y >= COL) continue;
        if(grid[x][y] == 0) continue;
        //if valid then add it the solution
        pair<int,int> next{x,y};
        sol.push_back(next);
    }
    return sol;
    
}

vector<pair<int,int>> bfs(pair<int,int> source,pair<int,int> dest, int grid[ROW][COL])
{
    
    vector<pair<int,int>> sol;
    bool visited[ROW][COL];
    // Make a visited grid of same size with the grid and set all elements to false
    for(int i = 0;i < ROW;i++)
    {
        for(int j = 0;j < COL; j++)
        {
            visited[i][j] = false;
        }
    }
    // map to store the node mapping to its parent
    unordered_map<pair<int,int>,pair<int,int>,hash_pair> mymap;
    // direction vectors
    vector<int> dr{-1,0,1,0}; //dr{-1,-1, 0,  1,  1,  1,  0};
    vector<int> dc{0,1,0,-1};//dc{ 0, 1, 1,  1,  0, -1, -1};
    stack<pair<int,int>> stk;
    stk.push(source);
    bool found  = false;
    while(!stk.empty() && !found)
    {
        pair<int,int> node = stk.top(); stk.pop();
        visited[node.first][node.second] = true;
        vector<pair<int,int>> neighbors;
        neighbors  = get_neighbors(node,dc,dr,grid);
        for(int i = 0;i< neighbors.size();i++)
        {
            if(visited[neighbors[i].first][neighbors[i].second] == false)
            {
                stk.push(neighbors[i]);
                mymap[neighbors[i]] = node;
                if(neighbors[i] == dest) 
                {
                    found = true;
                    break;
                }
            }
        }

    }
    
    
    sol = trace_path(mymap,dest,source); // trace back the path from source to destination
    return sol;

}
vector<pair<int,int>> trace_path(unordered_map<pair<int,int>,pair<int,int>, hash_pair>mymap,pair<int,int> point,pair<int,int> source)
{
    vector<pair<int,int>> sol_rev;
    sol_rev.push_back(point); // push the first point that is destination to the path 
    vector<pair<int,int>> sol;
    pair<int,int> temp = point;
    while(temp != source)
    {
        temp = mymap[temp]; // add the parent to the path
        //cout<<temp.first<<" "<<temp.second<<endl;
        sol_rev.push_back(temp);
    }
    reverse(sol_rev.begin(),sol_rev.end()); // reverse the path
    
    return sol_rev;
}