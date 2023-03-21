#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=52;
const int M=21;
int n,num[1<<M],m;
ll g[1<<M];
double f[1<<M];
string s[N];
int main() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>s[i];
    m=s[1].size();
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++) {
            int res=0;
            for(int k=0;k<m;k++) if(s[i][k]==s[j][k]) res|=(1<<k);
            g[res]|=(1ll<<i)|(1ll<<j);
        }
    for(int i=0;i<m;i++)
        for(int j=(1<<m)-1;j>=0;j--) if(!((1<<i)&j)) g[j]|=g[j|(1<<i)];
    for(int i=0;i<(1<<m);i++) for(int j=1;j<=n;j++) if((1ll<<j)&g[i]) num[i]++;
    for(int s=(1<<m)-1;s>=0;s--) {
        if(!g[s]) continue;
        int tot=0;
        for(int i=0;i<m;i++) if(!((1<<i)&s)) tot++;
        for(int i=0;i<m;i++) if(!((1<<i)&s)) f[s]=f[s]+f[s|(1<<i)]*num[s|(1<<i)]/num[s];
        f[s]=f[s]/tot+1;
    }
    printf("%.10lf\n",f[0]);
    return 0;
}