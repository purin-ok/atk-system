#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 1024

/* リストの要素 (ノード) を表す構造体 */
typedef struct tagListNode {
  struct tagListNode *prev;     /* 前の要素へのポインタ */
  struct tagListNode *next;     /* 次の要素へのポインタ */

  int data;                     /* この要素が持つデータ */
} ListNode;

ListNode *firstnode, *lastnode, *newnode, *thisnode, *removenode;

void SetValue(int, ListNode *);

void CreateNewNode(int buf){/* 新しいノードを作成 */
	newnode = (ListNode *)malloc(sizeof(ListNode));
  SetValue(buf, newnode);
	newnode->next=NULL;

if (lastnode != NULL) {
    lastnode->next = newnode;
    newnode->prev = lastnode;
    lastnode = newnode;
  } else {
    /*先頭のノード*/
    firstnode = lastnode = newnode;
    newnode->prev = NULL;
     }
}

int GetValue(ListNode *thisnode){ /*ノードの値を取得*/
	return thisnode->data;
}

void SetValue(int num,ListNode *setnode){/*ノードの値を設定*/
  setnode->data=num;
}

ListNode *NextNode(ListNode *thisnode){/*ノードの次のポインタを取得*/
  thisnode=thisnode->next;
  return thisnode;
}

void RemoveList(ListNode *firstnode){ /* リストの全ノードを削除 */
	thisnode=firstnode;
 	 while (thisnode!=NULL) {
    		removenode = thisnode;
    		thisnode = thisnode->next;
    		free(removenode);	
	}
}

void AppendNode(int buf,ListNode *setnode){       /*すでにあるリストの末尾に新しいノードを繋げる */
      ListNode *tempnode;
      tempnode=setnode->next;
      newnode=(ListNode *)malloc(sizeof(ListNode));
      SetValue(buf, newnode);
      newnode->next = tempnode;
      setnode->next = newnode;
      newnode->prev = setnode;
      tempnode->prev = newnode;   
}	
void InsertNode(ListNode *setnode1,ListNode *setnode2){   /*引数1:挿入される直後のノード,引数2:挿入したいノード*/
    ListNode *tempnode,*tempnode2,*tempnode3; //tempnode2:開始時点でsetnode2の次のノード,tempnode3:開始時点でsetnode2の前のノード
      if(setnode2->next!=NULL){
      //setnode2を分離
      tempnode2=setnode2->next; 
      tempnode3=setnode2->prev; 
      tempnode2->prev=tempnode3; 
      tempnode3->next=tempnode2; 
      }

      if(setnode1->prev!=NULL){
      tempnode=setnode1->prev;
      /*setnode2の直前のノードにつなげる*/
      setnode2->prev=tempnode;
      tempnode->next=setnode2;
      }
      /*setnode2の直後のノードにつなげる*/
      setnode1->prev=setnode2;
      setnode2->next=setnode1;
}

void InsertSort(ListNode **fnode ,ListNode **lnode){
    ListNode *sorted,*insert,*sorted2;

    /*最初から最後まですべてソート済みになるまで繰り返す*/
    for(sorted=*fnode;sorted!=*lnode;sorted=sorted->next){
      /*ソート済み領域の次の値を取り出す。*/
      insert=sorted->next;
      /*挿入する場所を見つけて挿入*/
      if(GetValue(sorted)>GetValue(insert)){
        for(sorted2=*fnode;GetValue(sorted2)<GetValue(insert);sorted2=sorted2->next){
        }
        InsertNode(sorted2,insert);
      }
    }
}

int main(void)
{
  int      buf, sum;
  char     buffer[MAXLENGTH];
  
  firstnode = lastnode = NULL;  /* 最初は要素は何もない */

  do {
    printf("整数を入力してください (0を入力すると終了): ");
    fgets(buffer, MAXLENGTH, stdin);
    sscanf(buffer, "%d", &buf);

    if (buf) { /* 新たな入力があったら */
      CreateNewNode(buf);
    }
  } while (buf!=0);

  /* 合計値を算出 */
  printf("--入力されたのは以下の数です--\n");
  sum=0;
   for (thisnode=firstnode; thisnode!=NULL;thisnode=NextNode(thisnode)) {
     printf("%d\t",GetValue(thisnode));
     
     	sum += GetValue(thisnode);
   }

  InsertSort(&firstnode, &lastnode);


  printf("\n----\n以上の数の合計値は%dです．\n", sum);
  printf("--ソート後--\n");
  for (thisnode=firstnode; thisnode!=NULL;thisnode=NextNode(thisnode)) {
    
     printf("%d\t",GetValue(thisnode));
     
  }

	RemoveList(firstnode);  

  return EXIT_SUCCESS;
}
