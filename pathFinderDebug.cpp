#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <sstream>
#include <string>
using namespace std;

//this function was adapted from https://www.geeksforgeeks.org/shortest-path-in-a-binary-maze/
bool inBounds(int r, int c, std::size_t maxR, std::size_t maxC){
    if(r<maxR && r>=0 && c<maxC && c>=0)
        return true;
    return false;
}

//the dist struct and vector PQ were adapted from https://stackoverflow.com/questions/48840649/constructing-a-priority-queue-of-vectors
//these vectors represent the steps needed to get from the start index
//to the index associated with the vector
//all vectors have at least 3 elements: the value of the index, and the row
//and column of the index(these must be converted to ints.) So, the start index vector at 0, 0 is {'s', '0', '0'}, and an empty index vector to the right would be {'e', '0', '1', 'R'}
//these structures put the vector of smallest size at the front of the priority queue
//

struct dist
{
    // queue elements are vectors so we need to compare those
    bool operator()(vector<string> const& a, std::vector<string> const& b) const
    {
        // reverse sort puts the smallest vector at the top    
        return a.at(3).length() > b.at(3).length();
    }
};

using vectorPQ = priority_queue<vector<string>, vector<vector<string>>, dist>;


template<std::size_t rows, std::size_t cols> 
vector<char> pathfinder(char (&maze)[rows][cols]){
    
    //declare necessary structures
    bool visited[rows][cols];
    vector<char> ans;
    vectorPQ distances;
    
    
    //find start index and set everything to unvisited
    int startR, startC;
    for(int r=0; r<rows; r++){
        for(int c=0; c<rows; c++){
            visited[r][c] = false;
            if(maze[r][c]=='s'){
                startR = r;
                startC = c;
            }
        }
    }
    string sR = to_string(startR), sC=to_string(startC);
    
    //set starting values
    distances.push({"s", sR, sC, ""});
    cout<<"T: "<<distances.top().at(1)<<", "<<distances.top().at(2)<<endl;
    cout<<endl;
    visited[startR][startC] = true;
    vector<string> current = distances.top();
    int r = startR;
    int c = startC;
    string currDist = current.at(3);//empty string
    
    int count=0;
    //read in all the non-w, unvisited neighbors of current
    while(current.at(0)!="f"){
        
        cout<<"F: "<<current.at(0)<<endl;
        istringstream issR(current.at(1));
        issR >> r;
        istringstream issC(current.at(2));
        issC >> c;
        currDist = current.at(3);
        cout<<"C: "<<r<<", "<<c<<endl;
        cout<<"CurrDIst: "<<currDist<<endl;
        
        //check if left's valid
        if(inBounds(r, c-1, rows, cols) && visited[r][c-1]==false && maze[r][c-1]!='w'){
            cout<<"L: "<<maze[r][c-1]<<endl;
            visited[r][c-1] = true;
            string i;
            i.push_back(maze[r][c-1]);
            distances.push({i, to_string(r), to_string(c-1), (currDist+"L")});
        }
        //check if right's valid
        if(inBounds(r, c+1, rows, cols) && visited[r][c+1]==false && maze[r][c+1]!='w'){
            cout<<"Right: "<<maze[r][c+1]<<endl;
            visited[r][c+1] = true;
            string i;
            i.push_back(maze[r][c+1]);
            distances.push({i, to_string(r), to_string(c+1), (currDist+"R")});
        }
        //check if up's valid
        if(inBounds(r+1, c, rows, cols) && visited[r+1][c]==false && maze[r+1][c]!='w'){
            visited[r+1][c] = true;
            cout<<"D: "<<maze[r+1][c]<<endl;
            string i;
            i.push_back(maze[r+1][c]);
            distances.push({i, to_string(r+1), to_string(c), (currDist+"D")});
        }
        //check if down's valid
        if(inBounds(r-1, c, rows, cols) && visited[r-1][c]==false && maze[r-1][c]!='w'){
            cout<<"U: "<<maze[r-1][c]<<endl;
            visited[r-1][c]=true;
            string i;
            i.push_back(maze[r-1][c]);
            distances.push({i, to_string(r-1), to_string(c), (currDist+"U")});
        }
        
        //remove the last index you looked at
        //next element to check is the value in distances
        //with the lowest vector size
        distances.pop();
        current = distances.top();
        for(int i=0; i<current.size(); i++){
            cout<<current.at(i)<<" ";
        }
        cout<<endl;
        cout<<"Size: "<<distances.size()<<endl;
        cout<<endl;
        count++;
    }
    for(int i=0; i<current.at(3).length(); i++){
        ans.push_back(current.at(3)[i]);
    }
    return ans;
}

int main(){

    char myMaze[5][5];
    myMaze[0][0] = 'w';
    myMaze[0][1] = 'e';
    myMaze[0][2] = 'e';
    myMaze[0][3] = 'e';
    myMaze[0][4] = 'e';
    
    myMaze[1][0] = 'w';
    myMaze[1][1] = 'e';
    myMaze[1][2] = 'w';
    myMaze[1][3] = 'w';
    myMaze[1][4] = 'e';
    
    myMaze[2][0] = 'w';
    myMaze[2][1] = 'e';
    myMaze[2][2] = 's';
    myMaze[2][3] = 'e';
    myMaze[2][4] = 'e';
    
    myMaze[3][0] = 'w';
    myMaze[3][1] = 'e';
    myMaze[3][2] = 'w';
    myMaze[3][3] = 'w';
    myMaze[3][4] = 'w';
    
    myMaze[4][0] = 'w';
    myMaze[4][1] = 'e';
    myMaze[4][2] = 'e';
    myMaze[4][3] = 'e';
    myMaze[4][4] = 'f';
    vector<char> answer = pathfinder(myMaze);
    cout<<endl;
    for(int i=0; i<answer.size(); i++){
        cout<<answer.at(i)<<endl;
    }
    return 0;
}

