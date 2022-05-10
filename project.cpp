#include <iostream>
#include<bits/stdc++.h>

using namespace std;

const int canvas_size=20; //size of the map

class Map{
    string grid[canvas_size][canvas_size];
    unordered_map<string, string> cities_map;
    int no_of_obstructions=50;
    int no_of_cities=20;
    void defineCities(){
        string cities[no_of_cities]={
            "Model Town", "Kashmere Gate", "Rajiv Chawk", "Preet Vihar", "Aanand Vihar", 
            "Laxmi Nagar", "Indraprasth", "New Delhi", "Patel Chowk", "Udyog Bhawan", 
            "Rahouri Garden", "Janak Puri", "Subhash Nagar", "Dwarka", "Chandni Chowk", 
            "Shahdra", "Dilshad Garden", "Akshardham", "Lajpat Nagar", "Rohini"
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
public :
    void create_map(){
        for(int i=0; i<canvas_size; i++){
            for(int j=0; j<canvas_size; j++){
                grid[i][j]="P";
            }
        }
        defineCities();
        defineObstructions();
    }
    void print_map(){
        for(int i=0; i<canvas_size; i++){
            for(int j=0; j<canvas_size; j++){
                cout<<grid[i][j]<<"  ";
            }
            cout<<endl<<endl;
        }
    }
};

int main()
{
    Map obj;
    obj.create_map();
    obj.print_map();
    return 0;
}