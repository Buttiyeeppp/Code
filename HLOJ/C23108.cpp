#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=(1ll<<32);
const ll P=10099;
const int N=1e7+10;
bool mem1;
int n,m;
ll x[3],v[N],a,b,c;
struct Que {
    priority_queue<int,vector<int>,greater<int>> q1,q2;
    int top() {
        while(q1.size()&&q2.size()&&q1.top()==q2.top()) q1.pop(), q2.pop();
        return q1.top();
    }
    void insert(int x) { q1.push(x); }
    void erase(int x) { q2.push(x); }
}que;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>x[0]>>x[1]>>a>>b>>c;
    for(int i=0;i<n;i++) v[i]=-1;
    x[2]=(a*x[0]%Mod+b*x[1]%Mod+c)%Mod;
    ll z=1,res=0;
    for(int i=1;i<=m;i++) {
        ll q=(x[1]/4)%n, p=x[2]/4;
        if(~v[q]) que.erase(v[q]);
        v[q]=p, que.insert(v[q]);
        z=z*P%Mod, res=(res+z*(que.top()))%Mod;
        x[1]=(a*x[1]%Mod+b*x[2]%Mod+c)%Mod, x[2]=(a*x[2]%Mod+b*x[1]%Mod+c)%Mod;
    }
    cout<<res<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
   return 0;
}