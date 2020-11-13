#include<bits/stdc++.h>
#define lson (o<<1)
#define rson (o<<1|1)
#define fi first
#define sc second
#define dbg(x) 
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
using namespace std;
const double pi=acos(-1);
const double eps=1e-6;
inline int lowbit(int x){return x&(-x);}
inline int read(){
	int f=1,x=0;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return f*x;
}
template<typename T> inline T max(T x,T y,T z){return max(max(x,y),z);}
template<typename T> inline T min(T x,T y,T z){return min(min(x,y),z);}
template<typename T> inline T sqr(T x){return x*x;}
template<typename T> inline void checkmax(T &x,T y){x=max(x,y);}
template<typename T> inline void checkmin(T &x,T y){x=min(x,y);}
template<typename T> inline void read(T &x){
x=0;T f=1;char ch;do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
do x=x*10+ch-'0',ch=getchar();while(ch<='9'&&ch>='0');x*=f;
}
template<typename A,typename B> inline A fpow(A x,B p,A yql){
	A ans=1;
	for(;p;p>>=1,x=1LL*x*x%yql)if(p&1)ans=1LL*x*ans%yql;
	return ans;
}
struct FastIO{
	static const int S=1310720;
	int wpos;char wbuf[S];
	FastIO():wpos(0) {}
	inline int xchar(){
		static char buf[S];
		static int len=0,pos=0;
		if(pos==len)pos=0,len=fread(buf,1,S,stdin);
		if(pos==len)return -1;
		return buf[pos++];
	}
	inline int read(){
		int c=xchar(),x=0;
		while(c<=32&&~c)c=xchar();
		if(c==-1)return -1;
		for(;'0'<=c&&c<='9';c=xchar())x=x*10+c-'0';
		return x;
	}
}io;
//#define read io.read

struct Node{
	int len,p;
	char val;
	double k;
	struct Node *pre,*next,*head,*tail;
}a[10010];
int cnt=0,last=0,x=0;
inline void InitList(Node &o){
	o.len=0;
	o.head=(Node *)malloc(sizeof(Node));
	o.head->next=NULL;
}
inline void DestroyList(Node &o){
    Node *tmp;
    while(o.head!=NULL){
        tmp=o.head->next;
        free(o.head);
        o.head=tmp;
        o.len--;
    }
    //assert(o.len==1);
    o.len=0;
}
inline void ClearList(Node &o){
    DestroyList(o);
    InitList(o);
}
inline int ListEmpty(Node &o){
    return o.len==0;
}
inline int ListLength(Node &o){
    return o.len;
}
inline int GetElem(Node &o,int x){
    if(ListEmpty(o)||x>ListLength(o)||x<=0) return -1;
    Node *t1=o.head;
    last=x;
    while(x--){
        t1=t1->next;
    }
    return t1->val;
}
inline int LocateElem(Node &o,char v){
    Node *t1=o.head;int flag=0;last=0;
    while(t1->next!=NULL){
        t1=t1->next;
        ++last;
        if(t1->val==v)return last;
    }
    return -1;
}
inline int PriorElem(Node &o,int x){
    return GetElem(o,x);
}
inline int NextElem(Node &o,int x){
    return GetElem(o,x);
}
inline void ListInsert(Node &o,int pos,int val){
    Node *t1=o.head;
    for(;pos!=1;pos--)t1=t1->next;
    Node *tmp=(Node*)malloc(sizeof(Node));
    tmp->val=val;
    tmp->pre=t1;
    tmp->next=t1->next;
    if(t1->next!=NULL)t1->next->pre=tmp;
    t1->next=tmp;
    o.len++;
}
inline char ListDelete(Node &o,int pos){
    Node *t1=o.head;
    char ret=0;
    while(pos--)t1=t1->next;
    ret=t1->val;
    if(t1->next!=NULL)t1->next->pre=t1->pre;
    t1->pre->next=t1->next;
    free(t1);
    o.len--;
    return ret;
}
inline void ListTraverse(Node &o){
    Node *t1=o.head->next;
    while(t1!=NULL){
        printf("%c",t1->val);
        t1=t1->next;
    }
    puts("");
}

vector<pair<int,double> >b;

inline void CreateList(Node &o){
	dbg(x);
    Node *t1=o.head,*tmp;
    int p=0,n=read();double k;
    b.resize(0);
    for(int i=1;i<=n;i++){
        scanf("%lf%d",&k,&p);
        b.push_back(make_pair(p,k));
    }
    sort(b.begin(),b.end());
    for(int i=0;i<b.size();i++){
        int existed=0;
        t1=o.head;
        while(t1->next!=NULL){
            t1=t1->next;
            if(b[i].fi==t1->p){
                existed=1;
                t1->k+=b[i].sc;
                break;
            }
        }
        if(!existed){
            tmp=(Node*)malloc(sizeof(Node));
            tmp->k=b[i].sc;
            tmp->p=b[i].fi;
            tmp->pre=t1;
            tmp->next=NULL;
            t1->next=tmp;
            
        }
    }
	o.tail=tmp;
    o.tail->next=NULL;
}

inline void ShowList(Node &o){
    Node *t1=o.tail;int ended=1;
    while(t1!=o.head){
        if(t1->k!=0){
            if(!ended&&t1->k>0)putchar('+');
            if(t1->k!=1&&t1->k!=-1)cout<<t1->k;
            else if(t1->k==-1)putchar('-');
            if(t1->p==1)putchar('x');
            else printf("x^%d",t1->p);
            ended=0;
        }
        t1=t1->pre;
    }
    if(ended)putchar('0');
    puts("");
}

inline void CalcList(Node o1,Node o2,Node &o3,int k){//k:-1 or +1
    Node *to1=o1.head->next,*to2=o2.head->next,*t3=o3.head;
    Node* tmp;
    while(to1!= NULL||to2!= NULL){
		//dbg("!!!");
        tmp=(Node*)malloc(sizeof(Node));
        t3->next=tmp;tmp->pre=t3;t3=tmp;
        //dbg(to1);dbg(to2);
        if(to1!= NULL&&to2!= NULL&&to1->p==to2->p){
            t3->p=to1->p;
            if(k==1)t3->k=to1->k+to2->k;else t3->k=to1->k-to2->k;
            //dbg(to2->p);
            //dbg(t3->k);
            to1=to1->next;
            to2=to2->next;
        }
        else if(to1!=NULL&&(to2==NULL||to1->p < to2->p)){
            t3->p=to1->p;
            t3->k=to1->k;
            to1=to1->next;
        }
        else if(to2!=NULL&&(to1==NULL||to2->p < to1->p)){
            t3->p=to2->p;
            t3->k=(double)k*to2->k;
            to2=to2->next;
        }
    }
    t3->next=NULL;
    o3.tail=t3;
}


int main(){
    for(;;){
        int opt=read();
        int y,ans,t1,t3,t2;
        char e;
        switch(opt){
            case 19:
                x=read();
                break;
            case 1:
                InitList(a[x]);
                break;
            case 2:
                DestroyList(a[x]);
                break;
            case 3:
                ClearList(a[x]);
                break;
            case 4:
                if(ListEmpty(a[x]))puts("1");else puts("0");
                break;
            case 5:
                printf("%d\n",ListLength(a[x]));
                break;
            case 6:
                y=read();ans=GetElem(a[x],y);
                if(ans==-1)puts("NoElem");else printf("%c\n",ans);
                break;
            case 7:
                char st[20];
                scanf("%s",st);
                ans=LocateElem(a[x],st[0]);
                if(ans==-1)puts("NoElem");else printf("%d\n",ans);
                break;
            case 8:
                ans=PriorElem(a[x],last-1);
                if(ans==-1)puts("NoElem");else printf("%c\n",ans);
                break;
            case 9:
                ans=NextElem(a[x],last+1);
                if(ans==-1)puts("NoElem");else printf("%c\n",ans);
                break;
            case 10:
                scanf("%d %c",&y,&e);
                ListInsert(a[x],y,e);
                break;
            case 11:
                y=read();
                printf("%c\n",ListDelete(a[x],y));
                break;
            case 12:
                ListTraverse(a[x]);
                break;
            case 21:
                CreateList(a[x]);
                break;
            case 22:
                y=read();
                ShowList(a[y]);
                break;
            case 23:
                t1=read(),t2=read(),t3=read();
                CalcList(a[t1],a[t2],a[t3],1);
                break;
            case 24:
                t1=read(),t2=read(),t3=read();
                CalcList(a[t1],a[t2],a[t3],-1);
                break;
            case 0:
                return 0;
        }
    }
}
