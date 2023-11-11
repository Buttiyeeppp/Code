#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
int n;
struct node {
    int a,b;
}nd[N];
bool mem2;
int main() {
    freopen("ball.in","r",stdin);
    freopen("ball.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>nd[i].a;
    for(int i=1;i<=n;i++) cin>>nd[i].b;
    sort(nd+1,nd+n+1,[](const node &x,const node &y) { return x.a+x.b<y.a+y.b; });
    priority_queue<PII> q;
    ll s=0;
    for(int i=1;i<=n;i++) {
        if(s<=nd[i].b) {
            s+=nd[i].a; q.emplace(nd[i].a,i);
        }
        else if(q.size()) {
            PII now=q.top();
            if(now.first>nd[i].a) 
                s+=nd[i].a-now.first, q.pop(), q.emplace(nd[i].a,i);
        }
    }
    cout<<q.size()<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
/*
5
5 7 4 6 3
10 6 5 7 15

10
10 4 18 16 5 4 14 11 12 4
16 17 15 15 11 14 2 20 8 6
*/