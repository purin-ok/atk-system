#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 1024

/* リストの要素 (ノード) を表す構造体 */
typedef struct tagListNode {
  struct tagListNode *prev; /* 前の要素へのポインタ */
  struct tagListNode *next; /* 次の要素へのポインタ */

  int data; /* この要素が持つデータ */
} ListNode;

ListNode *firstnode, *lastnode, *newnode, *thisnode, *removenode;
//これは操作に必要なノード作ってない。お互いのやり取りはポインタでする
//順番は崩したくないけどそれより前で使いたくなったのでしょうがないプロトタイプ宣言
void SetValue(int, ListNode *);
ListNode *NextNode(ListNode *);
//プロトタイプ宣言したくないならここ以前に本体持ってくる

void CreateNewNode(int buf) {
  /* 新たな入力があったら */
  /* 新しいノードを作成 */
  newnode = (ListNode *)malloc(sizeof(ListNode));
  SetValue(buf, newnode);
  newnode->next = NULL;

  if (lastnode != NULL) {
    /* すでにあるリストの末尾に新しいノードを繋げる */
    lastnode->next = newnode;
    newnode->prev = lastnode;
    lastnode = newnode;
  } else {
    /* これが最初の要素の場合 (最初ならば，lastnodeがNULLのまま) */
    firstnode = lastnode = newnode;
    newnode->prev = NULL;
  }
}

int GetValue(ListNode *getnode) {  //引数に渡したノードの値を戻り値として返す
  return getnode->data;
}

void SetValue(int num, ListNode *getnode) {  //指定したノードの値を設定する
  getnode->data = num;
}

ListNode *NextNode(ListNode *getnode) {
  //指定したノードの次のノードのポインタを得る
  return getnode->next;
}

void RemoveValue(ListNode *getnode) {  //指定したリストのメモリを開放する
  free(removenode);
}

void AppendNode(int buf, ListNode *getnode) {
  //指定したノードの次に指定したノードを付け足す
  ListNode *tempnode;
  tempnode = getnode->next;
  newnode = (ListNode *)malloc(sizeof(ListNode));
  SetValue(buf, newnode);
  newnode->next = tempnode;
  //新しいノードから指定したノードの次のノードへのパスをつなげる
  getnode->next = newnode;
  //指定したノードから新しいノードへのパスをつなげる
  newnode->prev = getnode;
  //新しいノードから指定したノードへのパスをつなげる
  tempnode->prev = newnode;
  //指定したノードの次のノードから新しいノードへのパスを繋げる
}

void InsertNode(int buf, ListNode *getnode) {
  //指定したノードの前に指定したノードを挿入する．
  ListNode *tempnode;
  tempnode = getnode->prev;
  newnode = (ListNode *)malloc(sizeof(ListNode));
  SetValue(buf, newnode);
  newnode->next = tempnode;
  //新しいノードから指定したノードの前のノードへのパスをつなげる
  getnode->prev = newnode;
  //指定したノードから新しいノードへのパスをつなげる
  newnode->next = getnode;
  //新しいノードから指定したノードへのパスをつなげる
  tempnode->next = newnode;
  //指定したノードの前のノードから新しいノードへのパスを繋げる
}
int main(void) {
  int buf, sum;
  char buffer[MAXLENGTH];

  firstnode = lastnode = NULL; /* 最初は要素は何もない */

  do {
    printf("整数を入力してください (0を入力すると終了): ");
    fgets(buffer, MAXLENGTH, stdin);
    sscanf(buffer, "%d", &buf);
    if (buf == -1) {
      printf("整数を入力してください (0を入力すると終了)1: ");
      fgets(buffer, MAXLENGTH, stdin);
      sscanf(buffer, "%d", &buf);
      AppendNode(buf, firstnode->next);
    } else if (buf == -2) {
      printf("整数を入力してください (0を入力すると終了)2: ");
      fgets(buffer, MAXLENGTH, stdin);
      sscanf(buffer, "%d", &buf);
      InsertNode(buf, firstnode->next);
    } else if (buf) { /* 新たな入力があったら */
      CreateNewNode(buf);
    }
  } while (buf != 0);

  /* 合計値を算出 */
  printf("--入力されたのは以下の数です--\n");
  sum = 0;
  for (thisnode = firstnode; thisnode != NULL; thisnode = thisnode->next) {
    printf("%d\t", GetValue(thisnode));
    sum += GetValue(thisnode);
  }
  printf("\n----\n以上の数の合計値は%dです．\n", sum);

  /* リストの全ノードを削除 */
  thisnode = firstnode;
  while (thisnode != NULL) {
    removenode = thisnode;
    thisnode = NextNode(thisnode);
    RemoveValue(removenode);
  }
  return EXIT_SUCCESS;
}
