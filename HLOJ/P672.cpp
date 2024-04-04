#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll P=1331;
const int N=2e6+10;
bool mem1;
string s;
ll hs[2][N],Pow[2][N];
ll Mod[2]={998244353,1000000007};
ll Hash(int op,int l,int r) {
    return (hs[op][r]-hs[op][l-1]*Pow[op][r-l+1]%Mod[op]+Mod[op])%Mod[op];
}
bool ans[N];
bool mem2;
int main() {
    freopen("twister.in","r",stdin);
    freopen("twister.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    for(int op:{0,1}) {
        Pow[op][0]=1;
        for(int i=1;i<N;i++) Pow[op][i]=Pow[op][i-1]*P%Mod[op];
    }
    int tot=0;
    while(cin>>s) {
        int n=s.size(), m=n<<1; s=" "+s+s;
        for(int op:{0,1})
            for(int i=1;i<=m;i++)
                hs[op][i]=(hs[op][i-1]*P+(s[i]-'a'+1))%Mod[op];
            
        memset(ans,0,sizeof(ans));
        int l=1,r;
        while(l<=m) {
            while(l!=1&&l<=m&&s[l]==s[l-1]) l++;
            if(l>m) break;
            r=l;
            while(r<m&&s[r]!=s[r+1]) r++;
            if(l!=1) l--;
            for(int i=1;i<=min(r-l+1,n);i++) {
                if(Hash(0,l,r-i+1)!=Hash(0,l+i-1,r)
                 ||Hash(1,l,r-i+1)!=Hash(1,l+i-1,r)) ans[n-i]=1;
            }
            l=r+1;
        }
        ans[n-1]=1;

        cout<<"Case "<<++tot<<": ";
        for(int i=0;i<n;i++) cout<<ans[i];
        cout<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}