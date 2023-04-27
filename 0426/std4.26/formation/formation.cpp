#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char getC() {
	static char *p1, *p2, buf[1<<20];
	return p1==p2?(p2=(p1=buf)+fread(buf, 1, 1<<20, stdin), p1==p2?'\n':*p1++):*p1++;
}
inline ll read() {
	ll f=1, r=0; char c=getC();
	while (!isdigit(c)) f^=c=='-', c=getC();
	while (isdigit(c)) r=r*10+c-48, c=getC();
	return f?r:-r;
}
#define mk make_pair
#define pii pair<int, int>
#define fi first
#define se second
template<class T> inline void ckmin(T &x, T y) {if (y<x) x=y;}
template<class T> inline void ckmax(T &x, T y) {if (x<y) x=y;}
const int N=5007, inf=0x3f3f3f3f, mod=1e9+7;
inline void inc(int &x, int y) {x+=y; if (x>=mod) x-=mod;}
inline void dec(int &x, int y) {x-=y; if (x<0) x+=mod;}
inline void mul(int &x, int y) {x=(ll)x*y%mod;}
inline int add(int x, int y) {return inc(x, y), x;}
inline int sub(int x, int y) {return dec(x, y), x;}
inline int qpow(int a, ll b) {
	int res=1;
	for (; b; b>>=1, mul(a, a)) if (b&1) mul(res, a);
	return res;
}
int s_p, pr[N], v[N], d[N], num[N];
inline void init_p(int n) {
	d[1]=1;
	for (int i=2; i<=n; i++) {
		if (!v[i]) v[i]=i, pr[++s_p]=i, d[i]=2, num[i]=1;
		for (int j=1; j<=s_p && i*pr[j]<=n; j++) {
			v[i*pr[j]]=pr[j];
			if (i%pr[j]==0) {
				num[i*pr[j]]=num[i]+1;
				d[i*pr[j]]=d[i]/(num[i]+1)*(num[i]+2);
				break;
			}
			num[i*pr[j]]=1, d[i*pr[j]]=d[i]*2;
		}
	}
}
int n, m, a[N], b[N][N], D[N], s[N], t[N], g[N][N], f[N][N];
int main() {
	freopen("formation.in", "r", stdin);
	freopen("formation.out", "w", stdout);
	n=read();
	for (int i=1; i<=n; i++) ckmax(m, a[i]=read());
	init_p(m);
	for (int i=0; i<=m; i++)
		for (int j=0; j<=i; j++)
			if (!j) g[i][j]=g[j][i]=i;
			else g[i][j]=g[j][i]=g[j][i%j];
	for (int i=1; i<=m; i++)
		for (int j=1; j<=m; j++) f[i][j]=i*j*d[g[i][j]];
	for (int i=1; i<n; i++) {
		for (int j=1; j<=n; j++) inc(D[i], f[a[i]][a[j]]);
		inc(t[a[i]], (ll)a[i]*a[i]*qpow(D[i], mod-2)%mod);
	}
	for (int i=1; i<=m; i++)
		for (int j=i; j<=m; j+=i) inc(s[i], t[j]);
	for (int i=1; i<=m; i++)
		for (int j=1; j<=m; j++) {
			b[i][j]=i==j; int k=i*j/g[i][j];
			if (k<=m) dec(b[i][j], s[k]);
		}
	int ans=1;
	for (int i=1; i<n; i++) mul(ans, D[i]);
	for (int i=m; i; i--) {
		int p=i; while (p && !b[p][i]) p--;
		if (!p) puts("0"), exit(0);
		if (i^p) swap(b[i], b[p]), ans=mod-ans;
		mul(ans, b[i][i]); int iv=qpow(b[i][i], mod-2);
		vector<int> vec;
		for (int j=i; j; j--) if (b[i][j]) vec.push_back(j);
		for (int j=i-1; j; j--) {
			if (!b[j][i]) continue;
			int x=(ll)(mod-b[j][i])*iv%mod;
			for (auto k:vec)
				inc(b[j][k], (ll)x*b[i][k]%mod);
		}
	}
	printf("%d\n", ans);
	return 0;
}
