#include<bits/stdc++.h>

using namespace std ;

#define	M  100005
#define inf  1 << 30
#define mp make_pair
#define pb push_back
#define pii pair<int , int>
#define rep(i , n) for(int  i = 0 ; (i) < n ; i++ )
#define repi(i , n ) for(int   i = 1  ; i <= n ; i++ )
#define mem(x , y ) memset(x , y , sizeof x )
#define ff first
#define ss second
#define sq(x)  ((x)*(x))
#define sf1(x)  scanf("%d", &x ) ;
#define sf2(x, y  ) scanf("%d%d",  &x, &y) ;
#define all(a ) a.begin() , a.end()
#define _lb(x ,y ) lower_bound(all(x  ) , y ) - x.begin
#define fast ios_base :: sync_with_stdio(false ) ; cin.tie(NULL ) ;
#define dbg(x )  cout << #x << " : " << x << endl ;

int _set(int n , int pos  ) { return n = n|(1<< pos) ; }
int reset(int n ,int pos ) { return n =  n & ~(1<<pos ); }
bool check(int n ,int pos ) { return (bool ) (n& (1<<pos))  ; }
/*


#define cst	clock_t s =  clock() ;
#define cnd	cout << (double) (clock() - s )/CLOCKS_PER_SEC  << endl ;

//int dx[] = { -1 ,+1, 0 , 0 , -1 , -1  , 1 , 1 };
//int dy[] = { 0 , 0, +1, -1  , +1 , -1 , 1 , -1 };

//int dx[] = { 1 , 1, 2 , 2  , -1 , -1 , -2 , -2 };
//int dy[] = { 2 , -2, +1, -1 ,2 , -2 , 1 , -1 };

*/

typedef long long ll ;

ll tree1[3*M+2] , tree2[3*M +2] , arr[M+2] ;
ll type1[3*M+ 2] , type2[3*M +2] ;

void debug(ll krr[] , ll sz   ){
	rep(i , sz ) cout << krr[i] << " " ;
	cout << endl ;
}


void clr() {
	mem(type1 , 0);
	mem(type2 , 0) ;


}

void init( int node ,int r1 , int r2 ){

    if(r1 == r2)
    {
    	tree1[node] = arr[r1] ;
    	tree2[node ] = sq(arr[r1] )	;
    	return ;
    }

    int left , right  , mid;

    left =  node*2 ;
    right =  node*2+1 ;
    mid = (r1 + r2)/2 ;

    init(left , r1 , mid);
    init(right ,mid+1 , r2);

    tree1[node] = tree1[left] + tree1[right];
    tree2[node] = tree2[left] + tree2[right];
}

ll query(int node , int r1 , int r2 , int i , int j , ll prop  , ll setval   ) {

	if(r1 > j || i > r2) return 0    ;
	if(r1 >=  i && r2 <= j   ) {
		if(setval !=  0  )  return (r2 - r1 +1  )*setval ;
		return tree2[node ]	+ (r2-r1 +1 )*sq(prop ) + 2*prop * tree1[node]  ;


	}

	int left , right , mid ;
	left =  node*2 ;
	right =  node*2 + 1;
	mid =  (r1+ r2 )/ 2;

	if(setval ==  0 && type2[node] != 0 ) setval  = type2[node] ;
	else prop += type1[node] ;


	return query(left , r1 , mid,i ,j  , prop ,  setval  ) + query(right  , mid+1 , r2 , i , j , prop , setval  );

}

void update1(int node , int r1 , int r2 , int i , int j  ,  int value ) {
	if(r1 > j || i > r2) return   ;
	if(r1 >=  i && r2 <= j   ) {			/// in range// 1 sum /// 2 sq
		tree2[node ] = tree2[node ]	+ (r2-r1 +1 )*sq(value ) + 2*value* tree1[node] ;
		tree1[node ] =  tree1[node] + 	2*value ;

		type1[node] += value ;

		return  ;
	}
	int left , right , mid ;

	left =  node*2 ;
	right =  node*2 + 1;
	mid =  (r1+ r2 )/ 2;

	update1( left , r1 , mid ,i , j , value );
	update1( right  , mid+1 , r2 , i , j ,  value );

	tree1[node] = tree1[left ] + tree1[right];
	tree2[node] = tree2[left ] + tree2[right];

}

void update2(int node , int r1 , int r2 , int i , int j  ,  int value ) {
	if(r1 > j || i > r2) return   ;
	if(r1 >=  i && r2 <= j   ) {			/// in range// 1 sum /// 2 sq
		tree2[node ] = (r2-r1 +1 )*value ;
		tree1[node ] =  (r2 - r1 +1 )*value ;

		type2[node] = value ;

		return  ;
	}
	int left , right , mid ;

	left =  node*2 ;
	right =  node*2 + 1;
	mid =  (r1+ r2 )/ 2;

	update2( left , r1 , mid ,i , j , value );
	update2( right  , mid+1 , r2 , i , j ,  value );

	tree1[node] = tree1[left ] + tree1[right];
	tree2[node] = tree2[left ] + tree2[right];

}

int main() {

 //   freopen("in.txt", "r",stdin );
   // freopen("out.txt", "w",stdout );

	int k , cs = 0 , tc ;
	int n , m ;

	cin >> tc ;
	while(tc-- ) {
		clr() ;
		cout << "Case " << ++cs << ":\n" ;
		cin >> n >> m ;
		repi(i , n ) cin >> arr[i]  ;
		init( 1 , 1, n ) ;

		while(m--) {
			int tag ; cin >> tag ;
			if(tag == 2 ) {
				int i , j ;
				cin >> i >> j  ;
				k = query(1 , 1, n , i , j  , 0  ,0    ) ;
				cout <<  k << endl ;

			}
			else if(tag == 1 ){
				int i , j ;
				cin >> i >> j >> k  ;
				update1(1 ,1 , n ,  i , j ,  k )  ;


			}
			else {
				int i , j ;
				cin >> i >> j >> k  ;
				update2(1 ,1 , n ,  i , j ,  k )  ;
			}
		}
	}
	return 0;
}



