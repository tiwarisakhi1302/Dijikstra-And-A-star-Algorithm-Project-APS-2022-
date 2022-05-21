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
        cout<<obj.grid[source.f][source.s]<<" "<<obj.grid[destin.f][destin.s]<<"  "<<costTo[destin.f][destin.s]<<" "<<timeTo[destin.f][destin.s]<<endl;
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
        cout<<obj.grid[source.f][source.s]<<" "<<obj.grid[destin.f][destin.s]<<"  "<<costTo[destin.f][destin.s]<<" "<<timeTo[destin.f][destin.s]<<endl;
    }
    //A* Star Algorithm

public:
    GraphAlgorithms(string src, string *des, int des_size, Map ob){
        d_size=des_size;
        destination=new string[d_size];
        destination=des;
        source=src;
        obj=ob;
    }
    void find_in_map(){
        vector<vector<bool>> vis(canvas_size, vector<bool> (canvas_size, false));
        find_city(0, 0, vis);
        cout<<"Source Coordinates : "<<source_coordinates.first<<" "<<source_coordinates.second<<" "<<endl;
        for(int i=0; i<des_coordinates.size(); i++){
            cout<<des_coordinates[i].name<<"  "<<des_coordinates[i].visit_no<<"    "<<des_coordinates[i].coordinates.f<<" "<<des_coordinates[i].coordinates.s<<endl;
        }
    }
    static bool custom_sort(des d1, des d2){
        return d1.visit_no<d2.visit_no;
    }
    void callDijkstra(){
        pair<int, int> s=source_coordinates;
        string dijks[canvas_size][canvas_size];
        for(int i=0; i<canvas_size; i++){
            for(int j=0; j<canvas_size; j++){
                dijks[i][j]=obj.grid[i][j];
            }
        }
        cout<<"-----------------------------------------------------------"<<endl;
        cout<<"Dijkstra Algorithm Efficient Cost : "<<endl;
        sort(des_coordinates.begin(), des_coordinates.end(), custom_sort);
        for(int i=0; i<des_coordinates.size(); i++){
            DijkstraAlgorithmEfficientCost(s, des_coordinates[i].coordinates);
            vector<pair<int, int>> path;
            pair<int, int> p=des_coordinates[i].coordinates;
            while(p.f!=-1 && p.s!=-1){
                path.push_back({p.f, p.s});
                p=parent_cost[{p.f, p.s}];
            }
            reverse(path.begin(), path.end());
            cout<<"Path : "<<endl;
            for(int i=0; i<path.size(); i++){
                if(i!=0 && i!=path.size()-1)
                dijks[path[i].f][path[i].s]="@";
                cout<<"{"<<path[i].f<<","<<path[i].s<<"}"<<" --> ";
            }
            cout<<endl<<endl;
             cout<<"\n\n\t\t\t\tCity Map"<<endl<<endl;
            cout<<"\t-----------------------------------------------------------"<<endl;
            for(int i=0; i<canvas_size; i++){
                cout<<"\t";
                for(int j=0; j<canvas_size; j++){
                    cout<<dijks[i][j]<<"  ";
                }
                cout<<endl<<endl;
            }
            cout<<"\t-----------------------------------------------------------"<<endl;
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
        for(int i=0; i<des_coordinates.size(); i++){
            DijkstraAlgorithmEfficientTime(s, des_coordinates[i].coordinates);
            vector<pair<int, int>> path;
            pair<int, int> p=des_coordinates[i].coordinates;
            while(p.f!=-1 && p.s!=-1){
                path.push_back({p.f, p.s});
                p=parent_time[{p.f, p.s}];
            }
            reverse(path.begin(), path.end());
            cout<<"Path : "<<endl;
            for(int i=0; i<path.size(); i++){
                if(i!=0 && i!=path.size()-1)
                dijks[path[i].f][path[i].s]="@";
                cout<<"{"<<path[i].f<<","<<path[i].s<<"}"<<" --> ";
            }
            cout<<endl<<endl;
             cout<<"\n\n\t\t\t\tCity Map"<<endl<<endl;
            cout<<"\t-----------------------------------------------------------"<<endl;
            for(int i=0; i<canvas_size; i++){
                cout<<"\t";
                for(int j=0; j<canvas_size; j++){
                    cout<<dijks[i][j]<<"  ";
                }
                cout<<endl<<endl;
            }
            cout<<"\t-----------------------------------------------------------"<<endl;
            s=des_coordinates[i].coordinates;
        }
        cout<<endl<<endl<<"-----------------------------------------------------------"<<endl;
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
