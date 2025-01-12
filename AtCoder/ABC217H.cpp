#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool memory1;
int n;
struct OPER {
    int t,d,x;
}op[N];
bool memory2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>op[i].t>>op[i].d>>op[i].x;
    sort(op+1,op+n+1,[](const OPER &q,const OPER &p) { return q.t<p.t; });
    priority_queue<int> l;
    priority_queue<int,vector<int>,greater<int>> r;
    ll ml=0,mr=0,ans=0;
    for(int i=1;i<=n;i++) l.push(0),r.push(0);
    for(int i=1,lst=0;i<=n;i++) {
        OPER o=op[i];
        ml-=o.t-lst,mr+=o.t-lst,lst=o.t;
        if(!o.d) {
            if(r.empty()||o.x<=r.top()+mr) l.push(o.x-ml);
            else {
                int v=r.top()+mr;
                l.push(v-ml),r.pop(),r.push(o.x-mr);
                ans+=o.x-v;
            }
        }
        else {
            if(l.empty()||o.x>=l.top()+ml) r.push(o.x-mr);
            else {
                int v=l.top()+ml;
                r.push(v-mr),l.pop(),l.push(o.x-ml);
                ans+=v-o.x;
            }
        }
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&memory1-&memory2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}