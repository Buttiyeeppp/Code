#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e4+10;
bool mem1;
int mu[N],pri[N],s[N];
vector<int> P;
void init() {
    mu[1]=1;
    for(int i=2;i<N;i++) {
        if(!pri[i]) mu[i]=-1, P.push_back(i);
        for(auto now:P) {
            if(1ll*now*i>=N) break;
            pri[i*now]=1;
            if(i%now==0) break;
            mu[i*now]=mu[i]*-1;
        }
    }
    for(int i=1;i<N;i++) s[i]=s[i-1]+mu[i];
}
int k;
int calc(int a,int b) {
    ll res=0, lim=min(a,b);
    for(int l=1,r;l<=lim;l=r+1) {
        int v1=a/l, v2=b/l;
        r=min(a/v1,b/v2);
        res+=1ll*(s[r]-s[l-1])*v1*v2;
    }
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    int T; cin>>T;
    while(T--) {
        int a,b,c,d;
        cin>>a>>b>>c>>d>>k;
        cout<<calc(b/k,d/k)-calc(b/k,(c-1)/k)-calc((a-1)/k,d/k)+calc((a-1)/k,(c-1)/k)<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}