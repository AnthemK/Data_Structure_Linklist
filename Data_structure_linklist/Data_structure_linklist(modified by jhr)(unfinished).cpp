// Data_structure_linklist.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstring>
#define debug
#define outt(x)  cout<<#x<<" = "<<x<<"    "
#define hh cout<<endl
//#define elemval1 char        //   第一种存储的权值数据类型
//#define elemval2 double       //   第二种存储的权值数据类型
//using elemkey = double;        //  存储的键值的数据类型
using namespace std;
typedef long long ll;
const int maxn = 1e6;

void noelem(void) { cout << "NoElem" << endl; return; }          //若查找指定位置没有元素，或者要查找的元素不在表里，又或者前驱后继没有值，均输出NoElem;

template <class elemval1,class elemval2,class elemkey>
class  Node {                   //点类，存储两种权值一种键值，和指向前驱后继的指针
	public:
		elemval1 val1;
        elemval2 val2;
		elemkey key;
		Node* next_node;
		Node* pre_node;
		Node(void) {val1 = val2 = key = 0; next_node = pre_node = NULL;}    //起始为空
		Node(elemval1 a1, elemval2 a2, elemkey b, Node* c, Node* d) : val1(a1), val2(a2), key(b), next_node(c), pre_node(d) {};   //传入起始值
        void printt(void) { outt(val1); outt(val2); outt(key); outt(next_node); outt(pre_node); hh; }
		void print_val1(void) { cout << val1; return; }                    //简易输出
        void print_val2(void) { cout << val2; return; }
        bool print_poly(void) {
            if (val2 == 0) return 0; 
            if (abs(val2) != 1 || key == 0) cout << val2;
            if(val2 == -1) cout<<"-"; 
            if (key != 0)cout << "x";
            if (key != 1) cout << "^" << key;
            return 1;
        }
        void print_all(void) { outt(val1); outt(val2); outt(key);hh; }
}input_polynomial[maxn];

bool Node_Sort_by_key(Node<char, double, double> a, Node<char, double, double> b) { return a.key > b.key; }

class  List {
	public:
		int lenth;
        using Node = Node<char, double, double>;
		Node* now_pls;
		Node* first_node;
		Node* last_node;
		List(void) { 
			lenth = 0; now_pls = NULL; first_node = new Node();  last_node = new Node();
			first_node->next_node = last_node; last_node->pre_node = first_node;        //建立首尾哨兵节点
		}
		~List(void) {                   //需要清空整个链表
			Node* nowwa = first_node;
			while (nowwa->next_node != NULL) {
				nowwa = nowwa->next_node;
				delete nowwa->pre_node;
			}
		}
        void print_all() {   //依次遍历当前表，并输出所有的节点的所有成员的值
            cout<<"-----------"; hh;
			outt(lenth); outt(now_pls); hh;
            Node* nowwa = first_node;
            while (nowwa->next_node != NULL) {
                nowwa->print_all();
                nowwa = nowwa->next_node;
            }
            nowwa->print_all();
            hh;cout<<"-----------"; hh;
        }
		bool ListEmpty(void) { return lenth ? 0 : 1; }     //返回是否为空
		int ListLength(void) { return this->lenth; }       //返回维护的长度
		Node* ListTraverse(int typ, elemval1 aim_val, int aim_id) {     //核心部分   根据typ来遍历链表  (传参 前值后位置)
			Node* nowwa = first_node;
			int id = 0;
			while (nowwa->next_node != NULL) {
				if (typ == 1 && aim_val == nowwa->val1) {     //typ == 1 表示根据值找位置，输出最小位置，并且更新now_pls
					cout << id << endl;
					this->now_pls = nowwa;
					return NULL;
				} else if (typ == 2 && aim_id == id) {      //typ == 2 表示根据位置找值，输出值
					nowwa->print_val1(); hh;
					return NULL;
				} else if (typ == 3 && id != 0) { nowwa->print_val1();}  //typ == 3 表示输出整张链表
				else if (typ == 4 && id == aim_id) { return nowwa;}    //typ == 4 根据位置找到地址就返回地址
				id++; nowwa = nowwa->next_node;
			}
            if (typ == 3) hh;
			return nowwa;              //此处返回的一定是末尾哨兵的地址
		}
		void GetElem(int aim_id) { 
			Node* nowwa = ListTraverse(2, 0, aim_id); 
			if (nowwa != NULL) noelem();    //没找到 ，如果能够找到一定已经输出了
			return;
		}
		void LocateElem(elemval1 aim_val) { 
			Node* nowwa = ListTraverse(1, aim_val, 0);
			if (nowwa != NULL) noelem();   //同 GetElem()
			return; 
		}
		Node* PriorElem(void) { return now_pls == NULL ? this->first_node : now_pls->pre_node ; }   //返回第一个元素或者当前now_pls的前一个元素
		Node* NextElem(void)  { return now_pls == NULL ? this->last_node : now_pls->next_node; }   //返回最后一个元素或者当前now_pls的后一个元素
		void ListInsert(int aim_id, elemval1 aim_val) {               //指定一个位置，插入一个权值
			Node* nowwa = ListTraverse(4, 0, aim_id);
            lenth++;                      //更新长度
			Node* new_node = new Node(aim_val , 0, 0, nowwa, nowwa->pre_node);   //寻找位置
			(nowwa->pre_node)->next_node = new_node;
			nowwa->pre_node = new_node;
		}
		void ListDelete(int aim_id) {                  //基本等同ListInsert
			Node* nowwa = ListTraverse(4, 0, aim_id);
			if (nowwa->next_node == NULL) { noelem(); return; }
            lenth--;
			Node* nextnode = nowwa->next_node;
			Node* prenode = nowwa->pre_node;
			prenode->next_node = nextnode; nextnode->pre_node = prenode;
            nowwa->print_val1(); hh;
		}
		void CreateList(void) {      //把已经排好序的一个多项式放到一个空链表里
           // print_all();
			Node* nowwa = first_node;
            int totlenth = lenth;
            for (int i = 1; i <= totlenth; ++i) {
                Node* new_node = new Node(0, input_polynomial[i].val2, input_polynomial[i].key, last_node, nowwa);
                if(new_node->val2) {nowwa->next_node = new_node; nowwa = new_node;}
                else { delete new_node; lenth--; }
            }
		}
		void ShowList(void) {   //依次遍历元素，然后输出
            Node* nowwa = first_node;
            int flagg = 0;
            while (nowwa->next_node != NULL) {
                if (flagg == 1 && nowwa->val2) {
                if(nowwa->val2>0)cout << "+";
				 nowwa->print_poly();
            }
                else if (flagg == 0) flagg = nowwa->print_poly();
                nowwa = nowwa->next_node;
            }
            if(!flagg) cout<<0;hh; 
		}
        List* AddList(List* othe) {   //传入另一个链表的地址，然后做多项式加法
            List* final_poly = new List();
        //    print_all(); othe->print_all();
            Node* nowwa1 = this->first_node, * nowwa2 = othe->first_node, * ans_nowwa = final_poly->first_node;
            while (nowwa1->next_node != NULL || nowwa2->next_node != NULL) {
                if (nowwa2->next_node == NULL) swap(nowwa1, nowwa2);
                if (nowwa1->next_node == NULL) {
                    Node* new_node = new Node(0, nowwa2->val2, nowwa2->key, final_poly->last_node, ans_nowwa);
                    if (new_node->val2) { ans_nowwa->next_node = new_node; ans_nowwa = new_node; }
                    else delete new_node;
                    nowwa2 = nowwa2->next_node;
                } else {
                    if (nowwa1->key > nowwa2->key)swap(nowwa1, nowwa2);
                    if (nowwa1->key == nowwa2->key) {
                        Node* new_node = new Node(0, nowwa2->val2 + nowwa1->val2, nowwa2->key, final_poly->last_node, ans_nowwa);
                        if (new_node->val2) { ans_nowwa->next_node = new_node; ans_nowwa = new_node; }
                        else delete new_node;
                        nowwa2 = nowwa2->next_node; nowwa1 = nowwa1->next_node;
                    } else {
                        Node* new_node = new Node(0, nowwa2->val2, nowwa2->key, final_poly->last_node, ans_nowwa);
                        if (new_node->val2) { ans_nowwa->next_node = new_node; ans_nowwa = new_node; }
                        else delete new_node;
                        nowwa2 = nowwa2->next_node;
                    }
                }
            }
            return final_poly;
        }
        List* MinusList(List* othe) {              //传入另一个链表的地址，然后做多项式减法
            List* final_poly = new List();
            bool if_change=0;
            Node* nowwa1 = this->first_node, * nowwa2 = othe->first_node, * ans_nowwa = final_poly->first_node;
            while (nowwa1->next_node != NULL || nowwa2->next_node != NULL) {
                if (nowwa2==NULL || nowwa2->next_node == NULL) swap(nowwa1, nowwa2), if_change ^= 1;
                if (nowwa1->next_node == NULL) {
                    Node* new_node = new Node(0, nowwa2->val2, nowwa2->key, final_poly->last_node, ans_nowwa);
                    if(!if_change) new_node->val2*=-1;
                    if (new_node->val2) { ans_nowwa->next_node = new_node; ans_nowwa = new_node; final_poly->lenth++; }
                    else delete new_node;

                    nowwa2 = nowwa2->next_node;
                }
                else {
                    if (nowwa1->key > nowwa2->key)swap(nowwa1, nowwa2), if_change ^= 1;
                    if (nowwa1->key == nowwa2->key) {
                        Node* new_node = new Node(0, nowwa1->val2 - nowwa2->val2, nowwa2->key, final_poly->last_node, ans_nowwa);
                        if (if_change) new_node->val2 *= -1;
                        if (new_node->val2) { ans_nowwa->next_node = new_node; ans_nowwa = new_node; final_poly->lenth++; }
                        else delete new_node;
                        nowwa2 = nowwa2->next_node; nowwa1 = nowwa1->next_node;
                    } else {
                        Node* new_node = new Node(0, nowwa2->val2, nowwa2->key, final_poly->last_node, ans_nowwa);
                        if(!if_change) new_node->val2*=-1;
                        if (new_node->val2) { ans_nowwa->next_node = new_node; ans_nowwa = new_node; final_poly->lenth++; }
                        else delete new_node;
                        nowwa2 = nowwa2->next_node;
                    }
                }
            }
            return final_poly;
        }
};
using Node = Node<char, double, double>;
List* lists[maxn];
List* nowlist;
int now_listid, lenthn;
int oper_type;
elemval1 e;
int main()
{
    //  ofstream fout("out.txt");
      //freopen("out.txt", "w", stdout);
    now_listid = 0; oper_type = 0;
    int i;
  //  cout << "Hello world" << endl;
    for (int i = 0; i <= 100; ++i) lists[i] = new List();
    while (1) {
        cin >> oper_type;
        switch (oper_type) {
        case 0:
            return 0;
        case 1: {
            lists[now_listid] = new List();
            break;
        }
        case 2: {
            if (lists[now_listid] != NULL) delete lists[now_listid];
            break;
        }
        case 3: {
            if (lists[now_listid] != NULL) delete lists[now_listid];
            lists[now_listid] = new List();
            break;
        }
        case 4: {
            cout << lists[now_listid]->ListEmpty() << '\n';
            break;
        }
        case 5: {
            cout << lists[now_listid]->ListLength() << '\n';
            break;
        }
        case 6: {
            cin >> i;
            lists[now_listid]->GetElem(i);
            break;
        }
        case 7: {
            cin >> e;
            lists[now_listid]->LocateElem(e);
            break;
        }
        case 8: {
            Node* nowwa = lists[now_listid]->PriorElem();
            if (nowwa->pre_node == NULL) noelem();
            else nowwa->print_val1(), hh, lists[now_listid]->now_pls = nowwa;
            break;
        }
        case 9: {
            Node* nowwa = lists[now_listid]->NextElem();
            if (nowwa->next_node == NULL) noelem();
            else nowwa->print_val1(), hh, lists[now_listid]->now_pls = nowwa;
            break;
        }
        case 10: {
            cin >> i >> e;
            lists[now_listid]->ListInsert(i, e);
            break;
        }
        case 11: {
            cin >> i;
            lists[now_listid]->ListDelete(i);
            break;
        }
        case 12: {
            //    cin >> i;
            lists[now_listid]->ListTraverse(3, 0, 0);
            break;
        }
        case 19: {
            cin >> now_listid;
            break;
        }
        case 21: {
            if (lists[now_listid] != NULL) delete lists[now_listid];
            lists[now_listid] = new List();
            cin >> lenthn; lists[now_listid]->lenth = lenthn;
            input_polynomial[0].key = -1000000;
            for (int i = 1; i <= lenthn; i++)
                 cin >> input_polynomial[i].val2 >> input_polynomial[i].key;
            sort(input_polynomial + 1, input_polynomial + 1 + lenthn, Node_Sort_by_key);
            for(int i=1;i<=lenthn;++i){
            	if(input_polynomial[i].key==input_polynomial[i-1].key){
            		input_polynomial[i].val2+=input_polynomial[i-1].val2;
            		input_polynomial[i-1].val2=0;
            	}
            }
            lists[now_listid]->CreateList();
            break;
        }
        case 22: {
            cin >> i;
            lists[i]->ShowList();
          //  lists[i]->print_all();
            break;
        }
        case 23: {
            int List1, List2, List3;
            cin >> List1 >> List2 >> List3;
        //    if (lists[List3] != NULL) delete lists[List3];
        //    lists[List1]->print_all(); lists[List2]->print_all();
            lists[List3] = lists[List1]->AddList(lists[List2]);
            break;
        }
        case 24: {
            int List1, List2, List3;
            cin >> List1 >> List2 >> List3;
         //   if (lists[List3] != NULL) delete lists[List3];
            lists[List3] = lists[List1]->MinusList(lists[List2]);
            break;
        }
        default:
            break;
        }
    }
    return 0;
}
/*
19
3
1
3
21
3 -1 -1 2 1 -3 3
19
2
1
21
1 1 1
22
2
19
1
1
21
3 1 -1 1 1 3 3
3
23
1 3 2
22
2
0


*/