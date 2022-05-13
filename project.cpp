#include <iostream>
#include<bits/stdc++.h>
#define f first
#define s second

using namespace std;
const int canvas_size=20; //size of the map

struct edge{
    pair<int,int> p1;
    pair<int,int> p2;
    int cost;
    int time;
    edge(pair<int,int> p1, pair<int, int> p2){
        this->p1=p1;
        this->p2=p2;
        cost=rand()%500; //Cost between two adjacent pair of points
        time=rand()%60;  //Time is generated in minutes
    }
};

class Map{
protected:
    string grid[canvas_size][canvas_size];
private:
    unordered_map<string, string> cities_map;
    int no_of_obstructions=50;
    int no_of_cities=20;
    vector<edge> edges;
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
    void generateEdgeWeightsUsingBFS(){
        int dx[]={-1, 0, 0, 1};
        int dy[]={0, 1, -1, 0};

        int vis[no_of_cities][no_of_cities]={false};
        queue<pair<int, int>> q;
        q.push({0, 0});
        while(!q.empty()){
            auto p=q.front();
            q.pop();
            if(p.first>no_of_cities-1 && p.second>no_of_cities-1) continue;
            for(int i=0; i<4; i++){
                int newX=p.first+dx[i];
                int newY=p.second+dy[i];
                if(!vis[newX][newY] && grid[newX][newY]!="O"){
                    vis[newX][newY]=true;
                    edges.push_back(edge(p, make_pair(newX, newY)));
                    q.push({newX, newY});
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
        generateEdgeWeightsUsingBFS();
    }
    void print_edges(){
        for(int i=0; i<edges.size(); i++){
            cout<<"edge "<<i<<endl;
            cout<<edges[i].p1.first<<" "<<edges[i].p1.second<<endl;
            cout<<edges[i].p2.first<<" "<<edges[i].p2.second<<endl;
            cout<<edges[i].cost<<endl;
            cout<<edges[i].time<<endl;
            cout<<"--------------------------------"<<endl;
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

class GraphAlgorithms : protected Map{
    string source;
    string *destination;
    int d_size;
    int dx[4]={-1, 0, 1, 0};
    int dy[4]={0, 1, 0, -1};
    pair<int, int> source_coordinates;
    void print_grid(){
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
    void find_source(int i, int j, vector<vector<bool>> vis){
        if(grid[i][j]==source){
            source_coordinates.f=i;
            source_coordinates.s=j;
            return;
        }
        for(int k=0; k<4; k++){
            int newX=i+dx[k];
            int newY=j+dy[k];
            if(newX>=0 && newY>=0 && newX<canvas_size && newY<canvas_size && !vis[newX][newY] && grid[i][j]!="O"){
                vis[newX][newY]=true;
                find_source(newX, newY, vis);
                vis[newX][newY]=false;
            }
        }
    }
public:
    GraphAlgorithms(string src, string *des, int des_size){
        d_size=des_size;
        destination=new string[d_size];
        destination=des;
        source=src;
    }
    void find_in_map(){
        vector<vector<bool>> vis(canvas_size, vector<bool> (canvas_size, false));
        vis[0][0]=true;
        //find_source(0, 0, vis);
        //cout<<source_coordinates.f<<" "<<source_coordinates.s<<" "<<endl;
        print_grid();
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

//    Graph Algorithm Started
    GraphAlgorithms gph(curr_location, destinations, no_of_destinations);
    gph.find_in_map();
}
int main()
{
    Map obj;
    obj.create_map();
    obj.print_map();
    //obj.print_edges();
    user_interface(obj);
    return 0;
}
