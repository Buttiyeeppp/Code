#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
int n, m, t[maxn], sum = 0,k;
int main(){
    cin>>n>>m;
    for (int i = 1; i <= m;i++)
        for (int j = 1; j <= n;j++){
            cin >> k;
            t[j] += k;
        }
    for (int i = 1;i<=n;i++){
        cin >> k;
        if (t[i] > (m - t[i]) && k == 1) sum++;
        if (t[i] <= (m - t[i]) && k == 0) sum++;
    }
    cout << sum;
    return 0;
}