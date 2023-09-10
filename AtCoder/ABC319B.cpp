#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;

bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int n; cin>>n;
    for(int i=0;i<=n;i++) {
        int pd=0;
        for(int j=1;j<=9;j++) if(n%j==0&&i%(n/j)==0) {
            pd=1; cout<<j; break;
        }
        if(!pd) cout<<'-';
    }
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}