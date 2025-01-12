#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool memory1;

bool memory2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int n; cin>>n;
    priority_queue<int> q;
    ll ans=0;
    for(int i=1,x;i<=n;i++) {
        cin>>x; x-=i;
        if(q.empty()||x>q.top()) q.push(x);
        else {
            q.push(x),q.push(x);
            ans+=q.top()-x;
            q.pop();
        }
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&memory1-&memory2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}