#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
int n,m,a[N],pre[N],lst[N],s[N],tot;
int v[N];
int lowbit(int x) { return x&-x; }
void Add(int x) {
    for(int i=x;i<=m;i+=lowbit(i)) v[i]++;
}
int Qry(int x) {
    int res=0;
    for(int i=x;i;i-=lowbit(i)) res+=v[i];
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=m;i++) 
        cin>>a[i], pre[i]=lst[a[i]], lst[a[i]]=i;
    for(int i=1;i<=m;i++) {
        if(!pre[i]) s[n]++;
        else {
            s[Qry(pre[i])-pre[i]]++;
        }
        Add(max(pre[i],1));
        // [pre[i]+1,i-1] different numbers
    }
    for(int i=n-1;i>=1;i--) s[i]+=s[i+1];
    for(int i=1;i<=n;i++) cout<<s[i]<<" ";
    cout<<endl;
    
    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}