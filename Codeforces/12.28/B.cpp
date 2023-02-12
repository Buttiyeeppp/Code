#include<bits/stdc++.h>
using namespace std;
const int N=1e2+10;
#define ll long long
const ll Mod=1e9+7;
struct Matrix {
    ll a[5][5];
    Matrix() {memset(a,0,sizeof(a));}
    Matrix operator*(const Matrix &q)const {
        Matrix p;
        for(int i=1;i<=4;i++)
            for(int j=1;j<=4;j++)
                for(int k=1;k<=4;k++)
                    p.a[i][j]=(p.a[i][j]+a[i][k]*q.a[k][j]%Mod)%Mod;
        return p;
    }
};
Matrix Mul(Matrix M,ll b) {
    Matrix res;
    for(int i=1;i<=4;i++) res.a[i][i]=1;
    while(b) {
        if(b&1) res=res*M;
        M=M*M;
        b>>=1;
    }
    return res;
}
void solve() {
    Matrix f,A; ll n;
    f.a[1][2]=1, f.a[1][3]=1, f.a[1][4]=1;
    A.a[1][1]=1, A.a[2][1]=2, A.a[2][2]=1, A.a[3][3]=1;
    A.a[3][1]=1, A.a[3][2]=2, A.a[4][2]=1, A.a[4][3]=1, A.a[4][4]=1;
    cin>>n;
    A=Mul(A,n-1);
	f=f*A;
    cout<<2022*(f.a[1][1]+n*n%Mod)%Mod<<endl;
}
int main() {
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
