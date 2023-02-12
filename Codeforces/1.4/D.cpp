#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e3+10;
int n,x[N],y[N];
void solve() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
    vector<int> ans;
    while(1) {
        int ok1=0, ok2=0; ans.clear();
        for(int i=1;i<=n;i++) {
            if((x[i]+y[i])%2) ok1=1, ans.emplace_back(i);
            else ok2=1;
        }
        if(ok1&&ok2) {
            cout<<ans.size()<<endl;
            for(auto now:ans) cout<<now<<" ";
            return;
        }
        if(ok1) {
            for(int i=1;i<=n;i++) x[i]-=1;
        }
        else {
            for(int i=1;i<=n;i++) {
                int a=x[i], b=y[i];
                x[i]=(a+b)/2, y[i]=(a-b)/2;
            }
        }

    }
}
int main() {
    int T=1;
    while(T--) solve();
    return 0;
}