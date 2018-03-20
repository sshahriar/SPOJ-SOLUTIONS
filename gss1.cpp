/*
  data structure used : segment tree 
  Idea : we can either get our solution from x  = max( left valid max sequence or right valid max sequence )
         or by merging y =  max valid prefix sum + right valid suffix sum 
         answer will be ans  = max(x ,y ) 
         
*/



#include <bits/stdc++.h>

using namespace std ;

#define M   50005
#define inf  1LL << 62
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

int _set(int n, int pos  ){ return n = n|(1<< pos) ; }
int reset(int n,int pos ){ return n =  n & ~(1<<pos );}
bool check(int n,int pos ){ return (bool ) (n& (1<<pos))  ; }
/*


#define cst clock_t s =  clock() ;
#define cnd cout << (double) (clock() - s )/CLOCKS_PER_SEC  << endl ;

//int dx[] = { -1 ,+1, 0 , 0 , -1 , -1  , 1 , 1 };
//int dy[] = { 0 , 0, +1, -1  , +1 , -1 , 1 , -1 };

//int dx[] = { 1 , 1, 2 , 2  , -1 , -1 , -2 , -2 };
//int dy[] = { 2 , -2, +1, -1 ,2 , -2 , 1 , -1 };

*/

typedef long long ll ;
////////////code from here //////////////////

struct _node
{
    ll _max, sum, suffix, prefix  ;
    _node() {} ;
    _node(ll a, ll b, ll c, ll d )
    {
        _max = a;
        sum = b ;
        suffix =  c;
        prefix = d;

    } ;
};

_node tree[4*M]  ;
ll arr[M+2] ;

void func ( int node  )                         // used in init function 
{
    int left = node<< 1, right =  left +1 ;

    tree[node].sum = tree[left].sum + tree[right].sum ;
    tree[node].suffix = max( tree[left ].suffix , tree[left].sum  + tree[right ].suffix  );
    tree[node].prefix =  max( tree[right ].prefix , tree[right].sum + tree[left].prefix ) ;
    tree[node]._max =  max( max( tree[right]._max, tree[left]._max ), tree[left].prefix  + tree[right].suffix ) ;
}

_node func2(_node left, _node right )     // used in query function 
{
    _node tnew  ;
    if(left.sum  ==  -inf ) return right ;
    if(right.sum  ==  -inf  ) return left   ;

    tnew.sum   = left.sum + right.sum  ;
    tnew.suffix =  max(left.suffix, left.sum + right.suffix  ) ;
    tnew.prefix  =  max(right.prefix, right.sum + left.prefix  ) ;
    tnew._max = max(max( right._max , left._max ),  left.prefix + right.suffix )  ;
    return tnew ;
}

void init(int node, int l, int r )
{
    if(l > r ) return ;
    if(l == r )
    {
        tree[node] =  _node(arr[r],arr[r],arr[r],arr[r] )  ;
        return ;
    }
    else
    {
        int mid =  (l+r )>>1 ;
        int left = node<< 1, right  = left + 1 ;
        init( left, l, mid) ;
        init( right, mid+1,r ) ;
        func(node ) ;
    }
}


_node  query(int node, int l, int r, int i, int j )
{
    if( i > r || l > j ) return _node( -inf , -inf , -inf , -inf ) ;
    if( l >= i && r <= j ) { return tree[node];  }

    int mid =  (l +r)>> 1, left = node<<1, right =  left +1   ;

    _node q1 = query(left, l, mid, i, j  ) ;
    _node q2 =  query(right, mid+1,r, i, j ) ;

    return func2(q1, q2) ;
}

int main()
{
    fast

   // freopen("in.txt", "r",stdin );
   //  freopen("out.txt", "w",stdout );

    int k, cs = 0, tc ;
    cin  >> k  ;
    repi(i, k) cin >> arr[i] ;
    init(1, 1,  k ) ;
  
    cin >> tc ;
    while(tc--)
    {
        int i, j ;
        cin >> i  >> j  ;
       
        _node ans  =  query(1, 1, k, i,  j )  ;
        cout <<  ans._max  << endl ;
    }
    return 0;
}





