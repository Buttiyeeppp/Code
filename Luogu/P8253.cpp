#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, m, a[7][maxn],sum=0;
int main(){
    cin >> m >> n;
    for (int i = 1; i <= m;i++)
        for (int j = 1; j <= n;j++){
            cin >> a[i][j];
            if (m == 2) sum += a[i][j];
        }
    if(m==2){
        cout << sum * 2;
        return 0;
    }
    for (int i = 1; i <= n;i++)
        for (int j = i; j <= n;j++){
            if(i==j) 
        }
            return 0;
}