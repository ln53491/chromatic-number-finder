#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

// Neka je 𝑛 prirodan broj te 𝑆 ⊆ {1,2, … , 𝑛 − 1}.
// Graf 𝐺 s 𝑛 vrhova indeksiranih brojevima 1, 2, … , 𝑛
// zadan je na sljedeći način:
// Vrhovi 𝑘 i 𝑙 su susjedni ako i samo ako je |𝑘 − 𝑙| ∈ 𝑆. 

// datoteka:
// 1. redak - broj vrhova grafa
// 2. redak - broj elemenata skupa S
// 3. redak - elementi skupa S

// izlaz: kromatski broj grafa

bool testVertex(int n, int **matr_inc, int colors[], int v, int c){
	for(int i=0; i<n; i++){
		if (c == colors[i] && matr_inc[v][i] == 1) return false;
    }
	return true;
}

bool chromIndex(int n, int **matr_inc, int m, int colors[], int v){
	if(v == n) return true;
	for(int i=1; i<=m; i++){
		if (testVertex(n, matr_inc, colors, v, i)){
			colors[v] = i;
			if (chromIndex(n, matr_inc, m, colors, v+1) == true) return true;
			colors[v] = 0;
		}
	}
	return false;
}

int maxDeg(int **matr_inc, int n){
	int max_deg = 1;
    for(int i=0; i<n; i++){
        int sum = 1;
        for(int j=0; j<n; j++) sum += matr_inc[i][j];
        if(sum > max_deg) max_deg = sum;
    }
	return max_deg;
}

bool contains(int i, int j, int elem[], int s){
    bool result = false;
    int num = i-j;
    if(num < 0) num *= -1;
    for(int z=0; z<s; z++){
        if(num == elem[z]) result = true;       
    }
    return result;
}

void readFile(string file, int &n, int &s, string &e){
    string value;
    ifstream File(file);
    getline (File, value); n = stoi(value);
    getline (File, value); s = stoi(value);
    getline (File, value); e = value;
    File.close();
}

int main(void){
    int n, s;
    string e, file = "";
    cout << endl << "Unesite ime datoteke: ";
    cin >> file;
    readFile(file, n, s, e);
    int elem[s];
    istringstream is(e);
    for(int i=0; i<s; i++) is >> elem[i];

    //inicijalizacija matrice susjedstva
    int matr_inc_temp[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            matr_inc_temp[i][j] = 0;
            if(contains(i, j, elem, s)) matr_inc_temp[i][j] = 1;
        }
    }
    int *matr_inc[n];
	for (int i=0; i<n; i++){
        matr_inc[i] = matr_inc_temp[i];
    }

    //računanje najvećeg stupnja grafa + 1
    int max_deg = maxDeg(matr_inc, n);
    
    //rekurzivno pronalaženje kromatskog broja za do max_deg boje
    int color_num = 1, colors[n], result;
    do{ 
		for(int i=0; i<n; i++) colors[i] = 0;
		result = (!chromIndex(n, matr_inc, color_num++, colors, 0)) ? 0 : *max_element(colors, colors+n);
    } while(result == 0);

    cout << endl << "Kromatski broj zadanog grafa je " << result << endl << " ";
    return 0;
}