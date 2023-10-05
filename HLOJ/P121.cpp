#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,k,mem[N],mn;
struct node {
    int c,p;
}a[N],b[N];
vector<int> nd[N];
/*
template<typename T> void chk_out(string op,T a[],int l1=-1,int r1=-1) {
    cerr<<"Out of "<<op<<' ';
    if(~l1) for(int i=l1;i<=r1;i++) cerr<<a[i]<<' ';
    cerr<<endl;
}
*/
void merge(int v) {
    int cnt=0,m=0;
    for(int i=1;i<=n;i++) {
        if(a[i].c==v) {
            if(cnt) b[++m]={v+1,a[i].p}, cnt=0;
            else cnt++;
        }
        else {
            if(cnt) nd[a[i-1].p].push_back(v), b[++m]={v+1,a[i-1].p}, cnt=0;
            b[++m]=a[i];
        }
    }
    if(cnt) nd[a[n].p].push_back(v), b[++m]={v+1,a[n].p};
    n=m;
    for(int i=1;i<=n;i++) a[i]=b[i];
}
vector<int> ans;
void split(int v,int k) {
    //v-1,v-1
    if(k==1) return ans.push_back(v), void();
    int val=min(k-1,1<<(v-1));
    split(v-1,val), split(v-1,k-val);
}
/*
int need,c[N],len,d[N];
bool check() {
    if((int)ans.size()!=need) return false;
    len=need;
    for(int i=0;i<need;i++) c[i+1]=ans[i];
    // chk_out("C",c,1,len);
    for(int v=0;v<=29;v++) {
        int cnt=0,len2=0;
        for(int i=1;i<=len;i++) {
            if(c[i]==v) {
                if(cnt) d[++len2]=v+1, cnt=0;
                else cnt++;
            }
            else {
                if(cnt) d[++len2]=v, cnt=0;
                d[++len2]=c[i];
            }
        }
        len=len2;
        for(int i=1;i<=len;i++) c[i]=d[i];
    }
    return (len==1&&c[1]==30);
}
*/
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k;
    // need=n+k;
    mn=n;
    for(int i=1;i<=n;i++) cin>>a[i].c, a[i].p=i, mem[i]=a[i].c;
    for(int i=0;i<=29;i++) merge(i);
    for(int i=1;i<=mn;i++) if(nd[i].size()) k-=nd[i].size();
    for(int i=1;i<=mn;i++) {
        ans.push_back(mem[i]);
        for(auto now:nd[i]) {
            if(k) split(now,min(k+1,1<<now)), k-=min(k+1,1<<now)-1;
            else ans.push_back(now);
        }
    }
   for(auto now:ans) cout<<now<<" ";
   cout<<endl;
    // if(!check()) cout<<"Wrong!"<<endl;

    #ifdef xxzx
   cerr<<"Time: "<<clo<<"MS"<<endl;
   cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
