// Author Dhaval Patel
// Liscence: MIT liscence 

#include<iostream>
#include<queue>
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

    pair<int,int> source = pair<int,int>(1,1);
    pair<int,int> dest = pair<int,int>(7,8);
    vector<pair<int,int>> path = bfs(source,dest,grid);
    print_path(path);

    //cout<<grid[dest.first][dest.second]<<endl;
    //shortest path from source to destination is
    //(8, 2) -> (9, 3) -> (8, 4) -> (7, 5) -> (8, 6) -> (9, 7) -> (8, 8) -> (7, 8) -> (6, 8) -> (5, 8) -> (4, 8) -> (3, 8) -> (2, 8) -> (1, 9) -> (0, 10)
   // shortest path from source to destination is
     //(4, 1) -> (5, 2) -> (6, 3) -> (5, 4) -> (6, 5) -> (7, 6) -> (8, 7) -> (7, 8)
    // shortest path from source to destination is
    // (1, 1) -> (2, 1) -> (3, 2) -> (4, 2) -> (5, 2) -> (6, 3) -> (5, 4) -> (6, 5) -> (7, 6) -> (8, 7) -> (7, 8)

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
    vector<int> dr{-1,-1, 0,  1,  1,  1,  0};
    vector<int> dc{ 0, 1, 1,  1,  0, -1, -1};
    // Making a que to store next node to be visited
    queue<pair<int,int>> Que;
    Que.push(source);bool found = false; // make a variable to check if the destination is found
    while(!Que.empty())
    {
        vector<pair<int,int>> neighors;
        pair<int,int> node = Que.front();
        Que.pop();
        neighors  = get_neigbors(node,dc,dr,grid);
        for(int i = 0;i<neighors.size();i++)
        {
            // if not visited select this node
            if(visited[neighors[i].first][neighors[i].second] == false)
            {
                visited[neighors[i].first][neighors[i].second] = true; // mark it to be visited
                Que.push(pair<int,int>(neighors[i])); // add it to the queue
                mymap[neighors[i]] = node;
                if(neighors[i] == dest)  // if the destination is reached set the found flag and break
                {
                    found = true;
                    break;
                 }
            }
            
        }
        if(found) break; // if destiantion is found stop the search
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
    while(temp != source) // Start tracing while the parent obtained is source
    {
        temp = mymap[temp]; // add the parent to the path
        //cout<<temp.first<<" "<<temp.second<<endl;
        sol_rev.push_back(temp);
    }
    reverse(sol_rev.begin(),sol_rev.end()); // reverse the path
    
    return sol_rev;
}
