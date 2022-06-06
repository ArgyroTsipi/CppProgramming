//
//  main.cpp
//  euler
//
//  Created by Argyro on 5/5/21.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
   
    int N,M;
    // N,M korufes, akmes
    cin >> N;
    cin >> M;
    
    int u, v;
    // u,v komvoi
    int array[N];
    // pinakas
    for(int i=0; i<M; i++){
        cin >> u;
        cin >> v;
        array[u]++;
        array[v]++;
    }
    int arr[N];
    int temp = 0;
    
    for(int i=0; i<N; i++){
        if(array[i]%2 != 0){
            arr[temp] = i;
            temp++;
            if(temp>2){
                cout << "IMPOSSIBLE" << endl;
                exit(0);
            }
        }
    }
    
    if(temp == 0){
        cout << "CYCLE" << endl;
    }
    else if(temp == 2){
        cout << "PATH" << endl;
    
        if(arr[0] < arr[1]){
            cout << arr[0] << " " << arr[1] << endl;
        }
        else {
            cout << arr[1] << " " << arr[0] << endl;
        }
        
    }
    else {
        cout << "IMPOSSIBLE" << endl;
        
    }
    return 0;
}
