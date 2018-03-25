/*
  idea : consider this things 
         - maximum prefix frequency
         - maximum suffix frequency
         - maximum prefix number 
         - maximum suffix number 
         - maximum frequency
*/

#include<bits/stdc++.h>

using namespace std ;

#define	M 	100005
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
#define fast ios_base :: sync_with_stdio(false ) ; cin.tie(NULL ) ;
#define dbg(x )  cout << #x << " : " << x << endl ;

int _set(int n , int pos  ) { return n = n|(1<< pos) ; }
int reset(int n ,int pos ) { return n =  n & ~(1<<pos ); }
bool check(int n ,int pos ) { return (bool ) (n& (1<<pos))  ; }

typedef long long ll ;


struct _node {
	int ret , msf ,  mpf  , msn ,  mpn  ;
	_node() {} ;
	_node( int a  , int b , int c , int d , int e ) {
		ret =a ; msf  = b ; mpf = c ; msn = d ; mpn  = e ;
	}
	void show() {
        	cout << ret << " " << mpf <<" " << msf <<" "  <<  mpn << " " <<  msn<< endl ;
	}
};

_node tree[4*M  +2] ;
int arr[ M+2 ] ;


void sett(int node ) {
	int left = node<<1   , right = left +1  ;
	int temp  = max(tree[left].ret ,  tree[right ].ret  )  ;

	tree[node].mpf = ( tree[right].mpn == tree[left ].mpn ? tree[right].mpf + tree[left].mpf: tree[right].mpf  ) ;
	tree[node].mpn = ( tree[right].mpn == tree[left ].mpn ? tree[right].mpn: tree[right].mpn  ) ;

	tree[node].msf = ( tree[left].msn == tree[right].msn ? tree[right].msf + tree[left].msf: tree[left].msf  ) ;
	tree[node].msn = ( tree[left].msn == tree[right].msn ?  tree[left].msn : tree[left].msn  ) ;
	tree[node].ret = ( tree[left].mpn == tree[right].msn ? max( temp , tree[left].mpf + tree[right].msf )  : temp) ;

}

_node func(_node left , _node right  )  {
	if(left.ret == -inf )  return right  ;
	if(right.ret == -inf )  return left  ;
	int temp  = max( left.ret ,  right.ret  )  ;

	_node qret ;

	qret.mpf = (  right.mpn == left.mpn ? right.mpf + left.mpf: right.mpf   ) ;
	qret.mpn  =  (  right.mpn == left.mpn ? right.mpn: right.mpn   ) ;

	qret.msf = ( left.msn == right.msn ? right.msf + left.msf: left.msf  ) ;
	qret.msn  =  (  right.msn == left.msn ? left.msn : left.msn   ) ;

	qret.ret = ( left.mpn == right.msn ? max(temp , left.mpf + right.msf )  : temp ) ;
	return qret ;

}

void init(int node, int left , int right ) {
	if(left == right  ) {
		tree[ node ] = _node(1 ,1 , 1,arr[left] , arr[left] ) ;

		return ;
	}
    	int lf =  node<<1  ,rt =  lf +1  ,mid  = (left + right)>>1  ;

	init( lf , left  , mid ) ;
	init( rt ,  mid + 1,  right  ) ;

	sett( node ) ;

}

_node query( int node , int  left , int right  , int  i , int j ) {
	if(left  > j || right < i ) return  _node(-inf ,-inf ,-inf ,-inf ,-inf  ) ;
	if(left >=i && right <= j  )  return tree[node ]  ;

	int mid = (left + right )/2 , l =  node<<1 , r  =  l +1 ;

	_node q1  = query( l , left  , mid , i , j ) ;
	_node q2 =  query(r , mid+1 , right , i , j ) ;
	return func(q1 ,q2 ) ;



}

int main() {
    	fast

 	// freopen("in.txt", "r",stdin );
   
   	int k , cs = 0 , tc ;
   	int n , m ;

    	//cout << "oops \n"  ;
	while(1) {

		cin >> n ;
		if( n == 0 )  break;
    
    		cin >> m ;
		repi(i , n )  cin >> arr[i] ;

		init(1 , 1 ,  n) ;

		while(m-- ) {
			int i, j  ;
			cin >> i >> j ;
			_node q  = query(1 , 1, n , i , j ) ;
			cout << q.ret << endl   ;
		}
	}
	//cout << "hello world\n" ;

	return 0;
}



