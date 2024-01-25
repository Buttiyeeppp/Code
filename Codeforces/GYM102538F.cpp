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

    ll n,a,b;
    cin>>n>>a>>b;
    priority_queue<ll> q;
    ll res=0, ans=0;
    for(int i=1,h;i<=n;i++) {
        cin>>h;
        ll f=((h-1)%b+1+(a-1))/a, g=(h-1)/b;
        while(res+g+1<-1) res+=q.top(), q.pop(), ans--;
        // cout<<f<<" "<<g<<" "<<(res+g-f>=-1)<<endl;
        if(res+g-f<-1&&q.size()&&res+q.top()+g-f>res) res+=q.top(), q.pop(), ans--;
        if(res+g-f>=-1) res+=g-f, ans++, q.push(f+1);
        else res+=g+1;
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
/*
10 1 2
2 2 2 1 1 2 1 1 1 2

5
*/