#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int N=25;
struct node{
	int data;
	node *l,*r;
};
void insert(node * &BST,int x)
{
	if(BST==NULL){
		BST=new node;
		BST->data=x;
		BST->l=BST->r=NULL;
	}
	else{
		if(x<BST->data){
			insert(BST->l,x);
		}
		else {
			insert(BST->r,x);
		}
	}
}//建BST树
bool isEqual(node *t1,node *t2)
{
	if(t1==NULL&&t2==NULL)//两颗都为NULL
	return true;
	if(!t1||!t2)//其中一颗为NULL
	return false;
	if(t1->data==t2->data)//若根相同，递归判断左右子树是否相等
	return isEqual(t1->l,t2->l) && isEqual(t1->r,t2->r);
	else
	return false;
}//判断两颗树是否相同
void delete_BST(node *BST)
{
	if(BST==NULL) return;
	delete_BST(BST->l);
	delete_BST(BST->r);
	delete BST;
}//析构
int main()
{
	//freopen("data.txt","r",stdin);
	int n;
	char s1[N],s2[N];
	while(scanf("%d",&n)!=EOF&&n){
	scanf("%s",s1);
	node *t1=NULL,*t2=NULL;
	for(int i=0;i<strlen(s1);i++) insert(t1,s1[i]-'0');
	while(n--){
		scanf("%s",s2);
		//cout<<s1<<endl<<s2<<endl;
		t2=NULL;
		for(int i=0;i<strlen(s2);i++) insert(t2,s2[i]-'0');
		bool r=isEqual(t1,t2);
		if(r==true) printf("YES\n");
		else printf("NO\n");
		delete_BST(t2);
		}
		delete_BST(t1);
	  }
	return 0;
} 
