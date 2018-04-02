#include <bits/stdc++.h>

using namespace std ;

#define	M 	100555
#define inf  1 << 30
#define mp make_pair
#define pb push_back
#define pii pair<int , int>
#define rep(i , n) for(int  i = 0 ; (i) < n ; i++ )
#define repi(i , n ) for(int   i = 1  ; i <= n ; i++ )
#define mem(x , y ) memset(x , y , sizeof x )
#define ff first
#define ss second
#define sf1(x)  scanf("%d", &x ) ;
#define sf2(x, y  ) scanf("%d%d",  &x, &y) ;
#define all(a ) a.begin() , a.end()
#define _lb(x ,y ) lower_bound(all(x  ) , y ) - x.begin
#define fast ios_base :: sync_with_stdio(false ) ;
#define dbg(x )  cout << #x << " : " << x << endl ;
#define dbg2(x, y ) cout << #x << " : " << x << " " << #y << " : " << y  << endl ;
#define dbg3(x, y ,z ) cout << #x << " : " << x << " " << #y << " : " << y  << " " << #z << " : " << z << endl ;


int _set(int n , int pos  ) { return n = n|(1<< pos) ; }
int reset(int n ,int pos ) { return n =  n & ~(1<<pos ); }
bool check(int n ,int pos ) { return (bool ) (n& (1<<pos))  ; }


//int dx[] = { -1 ,+1, 0 , 0 , -1 , -1  , 1 , 1 };
//int dy[] = { 0 , 0, +1, -1  , +1 , -1 , 1 , -1 };

//int dx[] = { 1 , 1, 2 , 2  , -1 , -1 , -2 , -2 };
//int dy[] = { 2 , -2, +1, -1 ,2 , -2 , 1 , -1 };


typedef long long ll ;

ll tree[M+2] , arr[M+2] , par[M+2] , maxn   ;

void update(int i , ll val  ) {
	for( ; i <= maxn  ; i += i&(-i) ){
		tree[i] += val ;

	}

}

ll _query(int i ) {
	ll sum = 0 ;
	for(; i >= 1 ; i -= i&(-i )  ){
		sum += tree[i] ;

	}
	return sum ;
}

int find(int i ) {
	if(par[i] == i ) return i ;
	else return par[i] =  find(par[i] ) ;

}

void func( int x , int y ) {
	int i = find( x) ;
	for( ; i <= y  ; ) {
        	if(arr[i] != 1 ) {
            		update(i , -arr[i] ) ;
           		arr[i ]  = sqrt(arr[i] ) ;
            		update(i , arr[i] ) ;
        	}
		if(arr[i] <= 1)  par[i]  = i+1  ;
		i =  find(i+1) ;
	}
}

int main() {
	 //fast

    	//freopen("in.txt", "r",stdin );
   	// freopen("out.txt", "w",stdout );

	int k , cs = 0 , tc  ,  n ;

	while(scanf("%d", &n ) ==1) {
		mem(tree,  0 )  ;
		printf("Case #%d:\n" , ++cs );

		maxn =  n ;
		repi(i  , n ) { scanf("%lld" ,&arr[i] );   update(i , arr[i]  ) ;   }
		repi( i, n +5) par[i] = i ;

		int qr  ;
		sf1(qr) ;

		while(qr--) {
			int type , x , y ;
			scanf("%d %d %d" ,&type , &x , &y ) ;  if(x > y ) swap(x , y ) ;

			if(type ){
				printf("%lld\n" ,  _query(y) - _query(x-1)  ) ;
			}
			else func(x ,y  ) ;
		}
		printf("\n") ;
	
	}
	return 0;
}



