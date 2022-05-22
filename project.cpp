#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define f first
#define s second

using namespace std;
const int canvas_size=20; //size of the map

struct edge{
    pair<int,int> p;
    int cost;
    int time;
    edge(pair<int,int> p){
        this->p=p;
        cost=rand()%500; //Cost between two adjacent pair of points
        time=rand()%60;  //Time is generated in minutes
    }
};

//Destination Details
struct des{
    string name;
    pair<int, int> coordinates;
    int visit_no;
    des(string name, pair<int, int> co, int v_no){
        this->name=name;
        this->coordinates=co;
        this->visit_no=v_no;
    }

};

struct Astar{
	// Row and Column index of its parent
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	int parent_i, parent_j;
	// f = g + h
	double f, g, h;
};

class Map{
public:
    string grid[canvas_size][canvas_size];
    map<pair<int, int>, vector<edge>> edges;
    map<string, string> cities_map;
private:
    int no_of_obstructions=50;
    int no_of_cities=20;
    void defineCities(){
        string cities[no_of_cities]={
            "Model Town", "Kashmere Gate", "Rajiv Chowk", "Preet Vihar", "Anand Vihar",
            "Laxmi Nagar", "Indraprastha", "New Delhi", "Patel Chowk", "Udyog Bhawan",
            "Rajouri Garden", "Janak Puri", "Subhash Nagar", "Dwarka", "Chandni Chowk",
            "Shahadra", "Dilshad Garden", "Akshardham", "Lajpat Nagar", "Rohini"
        };
        string abre_cities[no_of_cities]={
            "MT", "KG", "RC", "PV", "AV",
            "LN", "IP", "ND", "PC", "UB",
            "RG", "JP", "SN", "DW", "CC",
            "SD", "DG", "AK", "LP", "RN",
        };
        for(int i=0; i<no_of_cities; i++){
            int x=rand()%20;
            int y=rand()%20;
            cities_map[abre_cities[i]]=cities[i];
            if(grid[x][y]=="P"){
                grid[x][y]=abre_cities[i];;
            }
            else{
                i--;
            }
        }
    }
    void defineObstructions(){
        for(int i=0; i<no_of_obstructions; i++){
            int x=rand()%20;
            int y=rand()%20;
            if(grid[x][y]=="P"){
                grid[x][y]="O";
            }
            else{
                i--;
            }
        }
    }
    void generateEdges(){
        int dx[]={1, 0, -1, 0};
        int dy[]={0, 1, 0, -1};
        for(int i=0; i<canvas_size; i++){
            for(int j=0; j<canvas_size; j++){
                for(int k=0; k<4; k++){
                    int newX=i+dx[k];
                    int newY=j+dy[k];
                    if(newX>=0 && newY>=0 && newX<canvas_size && newY<canvas_size && grid[i][j]!="O"){
                        edge e({newX, newY});
                        pair<int,int> p1=make_pair(i, j);
                        edges[p1].push_back(e);
                    }
                }
            }
        }
    }
public:
    void create_map(){
        for(int i=0; i<canvas_size; i++){
            for(int j=0; j<canvas_size; j++){
                grid[i][j]="P";
            }
        }
        defineCities();
        defineObstructions();
        generateEdges();
    }
    void print_edges(){
        int j=1;
        for(auto itr=edges.begin(); itr!=edges.end(); itr++){
            cout<<"edge "<<j++<<endl;
            cout<<itr->first.first<<" "<<itr->first.second<<endl;
            for(int i=0; i<(itr->second).size(); i++){
                cout<<((itr->second)[i]).p.first<<" "<<((itr->second)[i]).p.second<<endl;
                cout<<(itr->second)[i].cost<<endl;
                cout<<(itr->second)[i].time<<endl;
                cout<<"--------------------------------"<<endl;
            }
            cout<<endl<<endl;
        }
    }
    void print_map(){
        cout<<"\n\n\t\t\t\tCity Map"<<endl<<endl;
        cout<<"\t-----------------------------------------------------------"<<endl;
        for(int i=0; i<canvas_size; i++){
            cout<<"\t";
            for(int j=0; j<canvas_size; j++){
                cout<<grid[i][j]<<"  ";
            }
            cout<<endl<<endl;
        }
        cout<<"\t-----------------------------------------------------------"<<endl;
    }
    void print_unordered_map(){
        for(auto itr=cities_map.begin(); itr!=cities_map.end(); itr++){
            cout<<itr->first<<" "<<itr->second<<endl;
        }
    }
    bool search_city(string city){
        if(cities_map.find(city)!=cities_map.end()){
            return true;
        }
        return false;
    }
};

class GraphAlgorithms{
    string source;
    string *destination;
    int d_size;
    int dx[4]={-1, 0, 1, 0};
    int dy[4]={0, 1, 0, -1};
    Map obj;
    pair<int, int> source_coordinates;
    vector<des> des_coordinates;
    map<pair<int, int>, pair<int, int>> parent_cost;
    map<pair<int, int>, pair<int, int>> parent_time;
    void print_grid(){
        cout<<"\n\n\t\t\t\tCity Map"<<endl<<endl;
        cout<<"\t-----------------------------------------------------------"<<endl;
        for(int i=0; i<canvas_size; i++){
            cout<<"\t";
            for(int j=0; j<canvas_size; j++){
                cout<<obj.grid[i][j]<<"  ";
            }
            cout<<endl<<endl;
        }
        cout<<"\t-----------------------------------------------------------"<<endl;
    }
    void find_city(int i, int j, vector<vector<bool>> vis){
        //Here in this we have used BFS
        map<string, int> _map;
        for(int k=0; k<d_size; k++){
            _map.insert({destination[k], k+1});
        }
        queue<pair<int, int>> q;
        q.push({0, 0});
        while(!q.empty()){
            auto p=q.front();
            q.pop();
            if(obj.grid[p.f][p.s]==source){
                source_coordinates.f=p.f;
                source_coordinates.s=p.s;
            }
            if(_map.find(obj.grid[p.f][p.s])!=_map.end()){
                auto itr=_map.find(obj.grid[p.f][p.s]);
                des d(itr->f, {p.f, p.s}, itr->s);
                des_coordinates.push_back(d);
                _map.erase(obj.grid[p.f][p.s]);
            }
            for(int k=0; k<4; k++){
                int newX=p.f+dx[k];
                int newY=p.s+dy[k];
                if(newX>=0 && newY>=0 && newX<canvas_size && newY<canvas_size && !vis[newX][newY] && obj.grid[p.f][p.s]!="O"){
                    vis[newX][newY]=true;
                    q.push({newX, newY});
                }
            }
        }
    }
    //Dijkstra Algorithm
    void DijkstraAlgorithmEfficientCost(pair<int, int> source, pair<int, int> destin){
        int costTo[canvas_size][canvas_size]; //source -> different position -> cost
        int timeTo[canvas_size][canvas_size]; //source -> different position -> cost
        int vis[canvas_size][canvas_size];
        for(int i=0; i<canvas_size; i++){
            for(int j=0; j<canvas_size; j++){
                costTo[i][j]=INT_MAX;
                timeTo[i][j]=INT_MAX;
                vis[i][j]=false;
                parent_cost[{i, j}]={-1, -1};
            }
        }
        costTo[source.f][source.s]=0;
        timeTo[source.f][source.s]=0;
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> minh;
        minh.push({0, {source.f, source.s}});
        while(!minh.empty()){
            int prev_cost=minh.top().first;
            int prev_x=minh.top().second.first;
            int prev_y=minh.top().second.second;
            vis[prev_x][prev_y]=true;
            minh.pop();
            for(auto itr : obj.edges[{prev_x, prev_y}]){
                pair<int, int> next=itr.p;
                int nextCost=itr.cost;
                int nextTime=itr.time;
                if(costTo[itr.p.f][itr.p.s]>costTo[prev_x][prev_y]+nextCost && !vis[itr.p.f][itr.p.s]){
                    costTo[next.f][next.s]=costTo[prev_x][prev_y]+nextCost;
                    timeTo[next.f][next.s]=timeTo[prev_x][prev_y]+nextTime;
                    minh.push({costTo[next.f][next.s],next});
                    parent_cost[next]={prev_x, prev_y};
                }
            }
        }
        cout<<endl<<endl<<"From "<<obj.cities_map[obj.grid[source.f][source.s]]<<" To "<<obj.cities_map[obj.grid[destin.f][destin.s]]<<endl;
        cout<<endl<<"Total Cost : "<<costTo[destin.f][destin.s]<<endl;
        cout<<"Total Time : "<<timeTo[destin.f][destin.s]<<endl;
    }
    void DijkstraAlgorithmEfficientTime(pair<int, int> source, pair<int, int> destin){
        int costTo[canvas_size][canvas_size]; //source -> different position -> cost
        int timeTo[canvas_size][canvas_size]; //source -> different position -> cost
        int vis[canvas_size][canvas_size];
        for(int i=0; i<canvas_size; i++){
            for(int j=0; j<canvas_size; j++){
                costTo[i][j]=INT_MAX;
                timeTo[i][j]=INT_MAX;
                vis[i][j]=false;
                parent_time[{i, j}]={-1, -1};
            }
        }
        costTo[source.f][source.s]=0;
        timeTo[source.f][source.s]=0;
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> minh;
        minh.push({0, {source.f, source.s}});
        while(!minh.empty()){
            int prev_time=minh.top().first;
            int prev_x=minh.top().second.first;
            int prev_y=minh.top().second.second;
            minh.pop();
            for(auto itr : obj.edges[{prev_x, prev_y}]){
                pair<int, int> next=itr.p;
                int nextCost=itr.cost;
                int nextTime=itr.time;
                vis[prev_x][prev_y]=true;
                if(timeTo[itr.p.f][itr.p.s]>timeTo[prev_x][prev_y]+nextTime && !vis[next.f][next.s]){
                    costTo[next.f][next.s]=costTo[prev_x][prev_y]+nextCost;
                    timeTo[next.f][next.s]=timeTo[prev_x][prev_y]+nextTime;
                    minh.push({timeTo[next.f][next.s],next});
                    parent_time[next]={prev_x, prev_y};
                }
            }
        }
        cout<<endl<<endl<<"From "<<obj.cities_map[obj.grid[source.f][source.s]]<<" To "<<obj.cities_map[obj.grid[destin.f][destin.s]]<<endl;
        cout<<endl<<"Total Cost : "<<costTo[destin.f][destin.s]<<endl;
        cout<<"Total Time : "<<timeTo[destin.f][destin.s]<<endl;
    }
    //A* Star Algorithm

    double calculateHValue(int row, int col, pair<int, int> dest)
    {
        // Return using the distance formula
        return ((double) ( abs(row-dest.first) + abs(col-dest.second) ) );
    // 	return ((double)sqrt ((row-dest.first)*(row-dest.first)
                    // 		+ (col-dest.second)*(col-dest.second)));
    }
    // A Utility Function to trace the path from the source
    // to destination
    void tracePath(Astar cellDetails[][canvas_size], pair<int, int> dest, pair<int, int> src)
    {
        cout<<endl<<"From "<<obj.cities_map[obj.grid[src.f][src.s]]<<" To "<<obj.cities_map[obj.grid[dest.f][dest.s]]<<endl;
        int total_cost=0;
        int total_time=0;
        cout<<"\nThe Path is "<<endl;
        int row = dest.f;
        int col = dest.s;

        int hops=0;
        stack<pair<int, pair<int, int>>> Path;

        while (!(cellDetails[row][col].parent_i == row
                && cellDetails[row][col].parent_j == col ))
        {
            Path.push (make_pair(cellDetails[row][col].g, make_pair (row, col) ));
            int temp_row = cellDetails[row][col].parent_i;
            int temp_col = cellDetails[row][col].parent_j;
            row = temp_row;
            col = temp_col;
        }

        Path.push(make_pair(cellDetails[row][col].g, make_pair (row, col) ));
        pair<int, int> s=src;
        while (!Path.empty())
        {
            hops++;
            pair<int, pair<int, int>> p = Path.top();
            for(auto itr : obj.edges[s]){
                if(itr.p==p.s){
                    total_cost+=itr.cost;
                    total_time+=itr.time;
                }
            }
            s=p.s;
            Path.pop();
            cout<<"->("<<p.s.f<<","<<p.s.s<<")";
        }
        cout<<endl<<"Total Cost : "<<total_cost<<endl;
        cout<<"Total Time : "<<total_time<<endl;
//        cout<<endl<<"No of visited Places : "<<hops-1<<endl;
        return;
    }
    // A Utility Function to check whether destination cell has
    // been reached or not
    bool isDestination(int row, int col, pair<int, int> dest)
    {
        if (row == dest.first && col == dest.second)
            return (true);
        else
            return (false);
    }
    // template <typename T>
    class comp_f{
        public:
        int operator() (const pair<int, pair<int, int>>& p1, const pair<int, pair<int, int>>& p2){
            return p1.first > p2.first;
        }
    };
    // A Utility Function to check whether given cell (row, col)
    // is a valid cell or not.
    bool isValid(int row, int col)
    {
        // Returns true if row number and column number
        // is in range
        return (row >= 0) && (row < canvas_size) &&
            (col >= 0) && (col < canvas_size) && obj.grid[row][col]!="O";
    }

    // A Function to find the shortest path between
    // a given source cell to a destination cell according
    // to A* Search Algorithm
    void aStarSearch(pair<int, int> src, pair<int, int> dest, bool CostEfficient)
    {
        // If the source is out of range
        if (isValid (src.first, src.second) == false || isValid (dest.first, dest.second) == false)
        {
            cout<<"source or dest is invalid"<<endl;
            return;
        }

        if (isDestination(src.first, src.second, dest) == true)
        {
            cout<<"We are already at the destination\n";
            return;
        }

        // Create a viisted array and initialise it to false which means
        // that no cell has been included yet
        // This visited array is implemented as a boolean 2D array
        bool visited[canvas_size][canvas_size];
        for(int i=0; i<canvas_size; i++){
            for(int j=0; j<canvas_size; j++){
                visited[i][j]=0;
            }
        }

        // Declare a 2D array of structure to hold the details of that cell
        Astar cellDetails[canvas_size][canvas_size];

        int i, j;

        for (i=0; i<canvas_size; i++)
        {
            for (j=0; j<canvas_size; j++)
            {
                cellDetails[i][j].f = FLT_MAX;
                cellDetails[i][j].g = FLT_MAX;
                cellDetails[i][j].h = FLT_MAX;
                cellDetails[i][j].parent_i = -1;
                cellDetails[i][j].parent_j = -1;
            }
        }

        // Initialising the parameters of the starting node
        i = src.first, j = src.second;
        cellDetails[i][j].f = 0.0;
        cellDetails[i][j].g = 0.0;
        cellDetails[i][j].h = 0.0;
        cellDetails[i][j].parent_i = i;
        cellDetails[i][j].parent_j = j;
        /*
        Create a minHeap having information as <f, <i, j>>
        where f = g + h,
        and i, j are the row and column index of that cell
        This open list is implenented as a set of pair of pair.*/
    // 	set<pair<int, pair<int, int>>> openList;
        priority_queue <pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, comp_f> minHeap;

        // Push the starting cell to the minHeap and set its
        // 'f' as 0
        minHeap.push(make_pair (0.0, make_pair (i, j)));

        // We set this boolean value as false as initially
        // the destination is not reached.
        bool foundDest = false;


        while (!minHeap.empty())
        {
            pair<int, pair<int, int>> p = minHeap.top();
            minHeap.pop();

            // Add this vertex to the closed list
            i = p.second.first;
            j = p.second.second;
            visited[i][j] = true;

            // To store the 'g', 'h' and 'f' of the 4 successors
            double gNew, hNew, fNew;
            int vi, vj;

            for(auto itr : obj.edges[{i, j}]){

                pair<int, int> pr=itr.p;

                if (isValid(itr.p.f, itr.p.s) == true)
                {
                    // If the destination cell is the same as the current successor
                    if (isDestination(itr.p.f, itr.p.s, dest) == true)
                    {
                        // Set the Parent of the destination cell
                        cellDetails[itr.p.f][itr.p.s].parent_i = i;
                        cellDetails[itr.p.f][itr.p.s].parent_j = j;
                        //cout<<"The destination cell is found\n";
                        tracePath (cellDetails, dest, src);
                        foundDest = true;
                        return;
                    }
                    // If the successor is nit visited
                    else if (!visited[itr.p.f][itr.p.s])
                    {
                        visited[itr.p.f][itr.p.s]=true;
                        if(CostEfficient)
                        gNew = cellDetails[i][j].g + itr.cost;
                        else{
                        gNew = cellDetails[i][j].g + itr.cost;
                        }
                        hNew = calculateHValue (itr.p.f, itr.p.s, dest);
                        fNew = gNew + hNew;
                        int vi=itr.p.f;
                        int vj=itr.p.s;

                        // if the adjacent node is not in the minHeap insert it
                        //if it is present in the minHeap and the newer f is smaller than already entered f than update
                        if(cellDetails[vi][vj].f > fNew){
                            minHeap.push( make_pair(fNew, make_pair(vi, vj)));
                            // Update the details of this cell
                            cellDetails[vi][vj].f = fNew;
                            cellDetails[vi][vj].g = gNew;
                            cellDetails[vi][vj].h = hNew;
                            cellDetails[vi][vj].parent_i = i;
                            cellDetails[vi][vj].parent_j = j;
                        }
                    }
                }
            }
        }

        // When the destination cell is not found and the open
        // list is empty, then we conclude that we failed to
        // reach the destiantion cell. This may happen when the
        // there is no way to destination cell (due to blockages)
        if (foundDest == false)
            printf("Failed to find the Destination Cell\n");

        return;
    }

public:
    GraphAlgorithms(string src, string *des, int des_size, Map ob){
        d_size=des_size;
        destination=new string[d_size];
        destination=des;
        source=src;
        obj=ob;
    }
    void find_in_map(){
        cout<<"\t\t\t\t   Source And Destination Coordiantes in Map"<<endl;
        cout<<"\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n"<<endl;
        vector<vector<bool>> vis(canvas_size, vector<bool> (canvas_size, false));
        find_city(0, 0, vis);
        cout<<"-----------------------------------------------------------"<<endl;
        cout<<"Source :"<<endl;
        cout<<"-----------------------------------------------------------"<<endl;
        cout<<obj.cities_map[source]<<" Coordinates : ("<<source_coordinates.first<<","<<source_coordinates.second<<")"<<endl;
        sort(des_coordinates.begin(), des_coordinates.end(), custom_sort);
        cout<<"\n-----------------------------------------------------------"<<endl;
        cout<<"Destinations : "<<endl;
        cout<<"-----------------------------------------------------------"<<endl;
        for(int i=0; i<des_coordinates.size(); i++){
            cout<<i+1<<". "<<obj.cities_map[des_coordinates[i].name]<<" Coordinates : ("<<des_coordinates[i].coordinates.f<<","<<des_coordinates[i].coordinates.s<<")"<<endl;
        }
        cout<<endl<<endl;
    }
    static bool custom_sort(des d1, des d2){
        return d1.visit_no<d2.visit_no;
    }
    void callDijkstra(){
        cout<<"\t\t\t\t\t\tDijkstra Algorithm"<<endl;
        cout<<"\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n"<<endl;
        pair<int, int> s=source_coordinates;
        string dijks[canvas_size][canvas_size];
        for(int i=0; i<canvas_size; i++){
            for(int j=0; j<canvas_size; j++){
                dijks[i][j]=obj.grid[i][j];
            }
        }
        cout<<"-----------------------------------------------------------"<<endl;
        cout<<"Dijkstra Algorithm Efficient Cost : "<<endl;
        cout<<"-----------------------------------------------------------";
        for(int i=0; i<des_coordinates.size(); i++){
            DijkstraAlgorithmEfficientCost(s, des_coordinates[i].coordinates);
            vector<pair<int, int>> path;
            pair<int, int> p=des_coordinates[i].coordinates;
            while(p.f!=-1 && p.s!=-1){
                path.push_back({p.f, p.s});
                p=parent_cost[{p.f, p.s}];
            }
            reverse(path.begin(), path.end());
            cout<<"The Path is : "<<endl;
            for(int i=0; i<path.size(); i++){
                if(i!=0 && i!=path.size()-1)
                dijks[path[i].f][path[i].s]="@";
                cout<<"->("<<path[i].f<<","<<path[i].s<<")";
            }
//            cout<<endl<<endl;
//             cout<<"\n\n\t\t\t\tCity Map"<<endl<<endl;
//            cout<<"\t-----------------------------------------------------------"<<endl;
//            for(int i=0; i<canvas_size; i++){
//                cout<<"\t";
//                for(int j=0; j<canvas_size; j++){
//                    cout<<dijks[i][j]<<"  ";
//                }
//                cout<<endl<<endl;
//            }
//            cout<<"\t-----------------------------------------------------------"<<endl;
            s=des_coordinates[i].coordinates;
        }



        for(int i=0; i<canvas_size; i++){
            for(int j=0; j<canvas_size; j++){
                dijks[i][j]=obj.grid[i][j];
            }
        }
        s=source_coordinates;
        cout<<endl<<endl<<"-----------------------------------------------------------"<<endl;
        cout<<"Dijkstra Algorithm Efficient Time : "<<endl;
        cout<<"-----------------------------------------------------------";
        for(int i=0; i<des_coordinates.size(); i++){
            DijkstraAlgorithmEfficientTime(s, des_coordinates[i].coordinates);
            vector<pair<int, int>> path;
            pair<int, int> p=des_coordinates[i].coordinates;
            while(p.f!=-1 && p.s!=-1){
                path.push_back({p.f, p.s});
                p=parent_time[{p.f, p.s}];
            }
            reverse(path.begin(), path.end());
            cout<<"The Path is : "<<endl;
            for(int i=0; i<path.size(); i++){
                if(i!=0 && i!=path.size()-1)
                dijks[path[i].f][path[i].s]="@";
                cout<<"->("<<path[i].f<<","<<path[i].s<<")";
            }
//            cout<<endl<<endl;
//             cout<<"\n\n\t\t\t\tCity Map"<<endl<<endl;
//            cout<<"\t-----------------------------------------------------------"<<endl;
//            for(int i=0; i<canvas_size; i++){
//                cout<<"\t";
//                for(int j=0; j<canvas_size; j++){
//                    cout<<dijks[i][j]<<"  ";
//                }
//                cout<<endl<<endl;
//            }
//            cout<<"\t-----------------------------------------------------------"<<endl;
              s=des_coordinates[i].coordinates;
          }
//        cout<<endl<<endl<<"-----------------------------------------------------------"<<endl;
    }
    void callAStar(){
        cout<<endl<<endl<<"\n\t\t\t\t\t\tA Star Algorithm"<<endl;
        cout<<"\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<endl<<endl<<"-----------------------------------------------------------"<<endl;
        cout<<"A star Algorithm Cost Efficient"<<endl;
        cout<<"-----------------------------------------------------------"<<endl;
        pair<int, int> src=source_coordinates;
        for(int i=0; i<des_coordinates.size(); i++){
            pair<int, int> dest = des_coordinates[i].coordinates;
            aStarSearch(src, dest, true);
        }
        cout<<endl<<"-----------------------------------------------------------"<<endl;
        cout<<"A star Algorithm Time Efficient"<<endl;
        cout<<"-----------------------------------------------------------"<<endl;
        src=source_coordinates;
        for(int i=0; i<des_coordinates.size(); i++){
            pair<int, int> dest = des_coordinates[i].coordinates;
            aStarSearch(src, dest, false);
        }
    }
};


void user_interface(Map obj){
    cout<<"Available Locations on Map : "<<endl;
    obj.print_unordered_map();
    string curr_location;
    int no_of_destinations;
    string *destinations;
    do{
        cout<<endl<<"Choose Your Location : "<<endl;
        cin>>curr_location;
        if(!obj.search_city(curr_location)){
            cout<<"Invalid Location!"<<endl;
            continue;
        }else{
            cout<<"Enter the number of destinations : "<<endl;
            cin>>no_of_destinations;
            set<string> s;
            destinations=new string[no_of_destinations];
            obj.print_unordered_map();
            for(int i=0; i<no_of_destinations; i++){
                do{
                    cout<<"Enter destination "<<i+1<<" : ";
                    cin>>destinations[i];
                    if(!obj.search_city(destinations[i])){
                        cout<<"Invalid Destination!"<<endl;
                        continue;
                    }
                    else if(s.size()!=0){
                        while(s.find(destinations[i])!=s.end()){
                            cout<<"Already in the queue. \nEnter Another Location : ";
                            string diff;
                            cin>>diff;
                            destinations[i]=diff;
                        }
                    }
                    break;

                }while(true);
                s.insert(destinations[i]);
            }
            break;
        }
    }while(true);
//  Graph Algorithm Started
    GraphAlgorithms gph(curr_location, destinations, no_of_destinations, obj);
    gph.find_in_map();
    gph.callDijkstra();
    gph.callAStar();
    cout<<"\n\n\t\t\t\t\t     Successfully Completed"<<endl;
    cout<<"\t\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
}
int main()
{
    system("color 90");
    Map obj;
    obj.create_map();
    obj.print_map();
    //obj.print_edges();
    user_interface(obj);
    return 0;
}

