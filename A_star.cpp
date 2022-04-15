#include<iostream>
#include<set>
#include<stack>
#include<vector>
#include<algorithm>
#include<math.h>
#define ROW 10
#define COL 11

/// Astar shortest path planning //
using namespace std;
struct cell{
    int parent_i,parent_j;
    double f,g,h;
};
bool is_valid(int i, int j)
{
    return (i>=0 && i < ROW && j>=0 && j < COL);
}
bool is_unblocked(int grid[][COL],int i,int j)
{
    return (is_valid(i,j) && grid[i][j] == 1 );
}
bool isDest(int i, int j, pair<int,int> dest)
{
    return (i == dest.first && j == dest.second);
}
double calculate_h(int i, int  j, pair<int,int> dest)
{
    return ((double)sqrt((i-dest.first)*(i - dest.first) + (j-dest.second)*(j-dest.second)) );
}
vector<pair<int,int>> get_neighbours( int r, int c, vector<int> dr, vector<int>  dc)
{
    vector<pair<int,int>> neighbors;
    for(int i = 0;i< dr.size();i++)
    {
        int x = r + dr[i];
        int y = c + dc[i];
        if(is_valid(x,y))
        neighbors.push_back({x,y});
    }
    return neighbors;
}


vector<pair<int,int>> trace_path(vector<vector<cell>> &cost_grid, pair<int,int> &dest)
{
    vector<pair<int,int>> path;
    int row = dest.first;
    int col = dest.second;
    stack<pair<int,int>> Path;
    while(!(cost_grid[row][col].parent_i == row && cost_grid[row][col].parent_j == col))
    {
        path.push_back(make_pair(row,col));
        int temp_row = cost_grid[row][col].parent_i;
        int temp_col = cost_grid[row][col].parent_j;
        row = temp_row;
        col = temp_col;
        // cout<<"("<<row<<","<<col<<")-> ";
    }
    cout<<endl;
     path.push_back(make_pair(row,col));
    reverse(path.begin(),path.end());
    return path;
}

vector<pair<int,int>> aStar(int grid[][COL], pair<int,int> &src, pair<int,int> &dest)
{
    vector<pair<int,int>> sol;
    if(is_valid(src.first, src.second) == false)
    {
        cout<<"Invalid Source";
        return sol;
    }
    if(is_valid(dest.first, dest.second) == false)
    {
        cout<<"Invalid Source";
        return sol;
    }
    bool closedList [ROW][COL];
    memset(closedList, false, sizeof(closedList));


    vector<vector<cell>> cost_grid;
    int i,j;
    for(int i = 0; i< ROW; i++)
    {
        vector<cell> cellRow;
        for(int j = 0; j< COL; j++)
        {
            cell temp;
            temp.f = FLT_MAX;
            temp.g = FLT_MAX;
            temp.h = FLT_MAX;
            temp.parent_i = -1;
            temp.parent_j = -1;
            cellRow.push_back(temp);
        }
        cost_grid.push_back(cellRow);
    }
    
    i = src.first; j = src.second;
    cost_grid[i][j].f = 0;
    cost_grid[i][j].g = 0;
    cost_grid[i][j].h = 0;
    cost_grid[i][j].parent_i = i;
    cost_grid[i][j].parent_j = j;

    set<pair<double,pair<int,int>>> openlist;

    openlist.insert(make_pair(0.0,make_pair(i,j)));
    //int pPair = pair<double,pair<int,int>>;
    vector<int> dr{-1,-1, 0,  1,  1,  1,  0,-1};
    vector<int> dc{ 0, 1, 1,  1,  0, -1, -1,-1};
    bool foundDest = false;
    while(!openlist.empty())
    {
       pair<double,pair<int,int>> p = *openlist.begin();
        openlist.erase(openlist.begin());

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        double gNew, hNew, fNew;
        vector<pair<int,int>> neighbors = get_neighbours(i,j,dr,dc);
        for(int k = 0;k<neighbors.size();k++)
        {
            pair<int,int> node = neighbors[k];
            int x = node.first, y = node.second; 
            if(isDest(x,y,dest)) 
            {
                cost_grid[x][y].parent_i = i;
                cost_grid[x][y].parent_j = j;
                foundDest = true; 
                break;
            }
            else if(closedList[x][y] == false && is_unblocked(grid,x,y) == true)
            {
                gNew = cost_grid[i][j].g + 1.0;
                hNew = calculate_h(x,y,dest);
                fNew = gNew + hNew;
                if(cost_grid[x][y].f == FLT_MAX || cost_grid[x][y].f>fNew)
                {
                    openlist.insert(make_pair(fNew,make_pair(x,y)));
                    cost_grid[x][y].f = fNew;
                    cost_grid[x][y].g = gNew;
                    cost_grid[x][y].h = hNew;
                    cost_grid[x][y].parent_i = i;
                    cost_grid[x][y].parent_j = j;

                }
            }
        }

    if(foundDest)
    {
        cout<<"found dest with cost "<<endl;
        sol = trace_path(cost_grid,dest); 

        break;
    }
    }
    return sol;
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

    pair<int,int> source = pair<int,int>(1,5);
    pair<int,int> dest = pair<int,int>(8,5);
    vector<pair<int,int>> path = aStar(grid,source,dest);
    print_path(path);
 return 0;
}
