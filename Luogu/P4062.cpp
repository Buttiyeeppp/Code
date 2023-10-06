#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
const int M=1e6+10;
bool mem1;
int n,type,a[N],cnt[N*10],vis[N];
ll ans;
void sol(int l,int r) {
    if(l==r) return ans++, void();
    int mid=(l+r)>>1;
    sol(l,mid), sol(mid+1,r);
    vector<int> v;
    for(int i=mid;i>=l;i--) {
        cnt[a[i]]++;
        if(cnt[a[i]]*2>mid-i+1&&!vis[a[i]])
            vis[a[i]]=1, v.push_back(a[i]);
    }
    for(int i=mid;i>=l;i--) cnt[a[i]]=0;
    for(int i=mid+1;i<=r;i++) {
        cnt[a[i]]++;
        if(cnt[a[i]]*2>i-mid&&!vis[a[i]])
            vis[a[i]]=1, v.push_back(a[i]);
    }
    for(int i=mid+1;i<=r;i++) cnt[a[i]]=0;
    for(auto now:v) vis[now]=0;
    for(auto now:v) {
        int L=INT_MAX, R=INT_MIN;
        for(int i=mid+1,tot=0;i<=r;i++) {
            tot+=(a[i]==now);
            cnt[i-2*tot+1+M]++;
            L=min(L,i-2*tot+1), R=max(R,i-2*tot+1);
        }
        for(int i=mid,tot=0;i>=l;i--) {
            tot+=(a[i]==now);
            L=min(L,2*tot+i-1), R=max(R,2*tot+i-1);
        }
        for(int i=L;i<=R;i++) cnt[i+M]+=cnt[i+M-1];
        for(int i=mid,tot=0;i>=l;i--) {
            tot+=(a[i]==now);
            ans+=cnt[2*tot+i-1+M];
        }
        for(int i=L;i<=R;i++) cnt[i+M]=0;
    }
    
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>type;
    for(int i=1;i<=n;i++) cin>>a[i];
    sol(1,n);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}