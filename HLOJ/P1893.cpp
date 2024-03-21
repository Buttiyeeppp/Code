#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
#define fi first
#define se second
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
ll n,k,m,a[N],b[N],c[N],s[N],f[N],g[N],sum[N];
// int pd[N];
vector<PII> seg;
bool mem2;
int main() {
    freopen("guard.in","r",stdin);
    freopen("guard.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k>>m;
    for(int i=1;i<=m;i++) cin>>a[i]>>b[i]>>c[i];
    for(int i=1;i<=m;i++) if(!c[i]) s[a[i]]++, s[b[i]+1]--;
    int cnt=0;
    for(int i=1;i<=n;i++) {
        s[i]+=s[i-1];
        if(s[i]) cnt++;
    }
    vector<int> ans;
    if(n-cnt==k) {
        for(int i=1;i<=n;i++) if(!s[i]) ans.push_back(i);
        if(!ans.size()) cout<<-1<<endl;
        else for(auto i:ans) cout<<i<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++) s[i]=s[i-1]+(s[i]==0);
    for(int i=1;i<=m;i++) if(c[i]) {
        // if(s[b[i]]-s[a[i]-1]==b[i]-a[i]) cout<<"A "<<i<<endl;
        if(s[b[i]]-s[a[i]-1]==1) f[a[i]]++, f[b[i]+1]--;
    }
    for(int i=1;i<=n;i++) {
        f[i]+=f[i-1];
        if(f[i]&&(s[i]-s[i-1])) ans.push_back(i), k--, sum[i]=1;
    }
    for(int i=1;i<=n;i++) sum[i]+=sum[i-1];
    for(int i=1;i<=m;i++) 
        if(c[i]&&!(sum[b[i]]-sum[a[i]-1])) seg.emplace_back(a[i],b[i]);
    sort(seg.begin(),seg.end());
    int l=0,r=n+1,tot=0;
    for(auto i:seg) {
        if(r>=i.fi&&s[min(i.se,r)]-s[max(i.fi,l)-1]) {
            r=min(i.se,r), l=max(i.fi,l);
        }
        else {
            if(l) {
                tot++;
                if(s[r]-s[l-1]==1) g[l]++, g[r+1]--;
            }
            l=i.fi, r=i.se;
        }
    }
    tot++;
    if(s[r]-s[l-1]==1) g[l]++, g[r+1]--;
    sort(seg.begin(),seg.end(),[](const PII &x,const PII &y) { return (x.fi==y.fi)? x.se>y.se:x.fi>y.fi; });
    l=0,r=n+1;
    for(auto i:seg) {
        if(l<=i.se&&s[min(i.se,r)]-s[max(i.fi,l)-1]) {
            r=min(i.se,r), l=max(i.fi,l);
        }
        else {
            if(l&&s[r]-s[l-1]==1) g[l]++, g[r+1]--;
            l=i.fi, r=i.se;
        }
    }
    if(s[r]-s[l-1]==1) g[l]++, g[r+1]--;
    // cerr<<"Totk "<<tot<<" "<<k<<endl;
    if(tot==k) {
        for(int i=1;i<=n;i++) {
            g[i]+=g[i-1];
            if(g[i]==2&&(s[i]-s[i-1])) ans.push_back(i);
        }
    }
    // for(int i=0;i<(int)seg.size();i++) if(seg[i].first<=438&&438<=seg[i].second) cerr<<seg[i].fi<<" "<<seg[i].se<<endl;
    sort(ans.begin(),ans.end());
    // for(auto i:ans) pd[i]=1;
    // for(int i=1;i<=m;i++) {
    //     int tot=0;
    //     for(int j=a[i];j<=b[i];j++) tot+=pd[j];
    //     if(c[i]!=(tot!=0)) cerr<<"Wrong "<<endl;
    // }
    
    if(!ans.size()) cout<<-1<<endl;
    else for(auto i:ans) cout<<i<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
