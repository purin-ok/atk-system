/*
～追加したもの～
受け取ったノードをリストからはずす関数Detahode()
リストを昇順に並び替える関数AppendSort()

～AppendSort()の動作原理～
受け取った2つの値を比べ昇順に並べる
２つの値をそれぞれvariable,constとすると
variable < constとなるまでvariableをずらしていき，
正しく昇順の関係になったときにvariableの前にconstを挿入する．
*/
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
void DetachNode(ListNode *);
void InsertNode(ListNode *, ListNode *);
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

void AppendNode(ListNode *getnode1, ListNode *getnode2) {
  //指定したノードの次に指定したノードを付け足す
  DetachNode(getnode2);
  ListNode *tempnode;
  tempnode = getnode1->next;
  getnode2->next = tempnode;
  //ノード2から指定したノードの次のノードへのパスをつなげる
  getnode1->next = getnode2;
  //指定したノードから新しいノードへのパスをつなげる
  getnode2->prev = getnode1;
  //新しいノードから指定したノードへのパスをつなげる
  if (tempnode != NULL) {
    tempnode->prev = getnode2;
    //指定したノードの次のノードから新しいノードへのパスを繋げる
  } else {
    lastnode = getnode2;
  }
}

void InsertNode(ListNode *getnode1, ListNode *getnode2) {
  //指定したノードの前に指定したノードを挿入する．まじで挿入するだけ
  DetachNode(getnode2);
  ListNode *tempnode;
  tempnode = getnode1->prev;
  getnode2->prev = tempnode;
  //挿入したいノード(getnode2)から指定したノード(getnode1)の前のノードへのパスをつなげる
  getnode1->prev = getnode2;
  //指定したノード(getnode1)から挿入したいノード(getnode2)へのパスをつなげる
  getnode2->next = getnode1;
  //挿入したいノード(getnode2)から指定したノード(getnode1)へのパスをつなげる
  if (tempnode != NULL) {
    tempnode->next = getnode2;  //多分firstnode->prev=NULLなことが関わってる．
    //指定したノードの前のノードから指定したノードへのパスを繋げる
  } else {
    firstnode = getnode2;
  }
}

void DetachNode(ListNode *getnode) {
  //指定したノードを切り取るだじぇ
  ListNode *tempnode;
  if (getnode->prev == NULL) {  // firstnodeの場合
    firstnode = getnode->next;
    firstnode->prev = NULL;
  } else if (getnode->next == NULL) {  // lastnodeの場合
    lastnode = getnode->prev;
    lastnode->next = NULL;
  } else {  //前後に要素がある場合
    tempnode = getnode->prev;
    tempnode->next = getnode->next;
    //前の要素から次の要素へポインタをつなげる
    tempnode = getnode->next;
    tempnode->prev = getnode->prev;
    //次の要素から前の要素へのポインタをつなげる
  }
}

void AppendSort(ListNode *getnode1, ListNode *getnode2) {
  // getnode1:これの前にgetnode2を挿入，可変型
  // getnode2:これをgetnode1の前に挿入．不変
  if (GetValue(getnode1) > GetValue(getnode2)) {
    if (getnode1->prev == NULL) {
      // printf("1");
      InsertNode(getnode1, getnode2);
      return;
    }
    // printf("2");
    AppendSort(getnode1->prev, getnode2);
    return;
  } else {  //交換しないといけない
    // printf("3");
    AppendNode(getnode1, getnode2);
    return;
  }
}

int main(void) {
  int buf, sum;
  char buffer[MAXLENGTH];
  ListNode *countnode;

  firstnode = lastnode = NULL; /* 最初は要素は何もない */

  do {
    printf("整数を入力してください (0を入力すると終了): ");
    fgets(buffer, MAXLENGTH, stdin);
    sscanf(buffer, "%d", &buf);
    if (buf == -1) {
      AppendNode(firstnode, firstnode->next);
    } else if (buf == -2) {
      InsertNode(firstnode, firstnode->next);
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

  printf("\nこれよりデータを昇順に並べ替える\n");
  for (countnode = firstnode->next; countnode != NULL;
       countnode = countnode->next) {
    // firstnodeのポインタに帰ってきたら終了って感じにすればいいと思う
    //循環リスト，単方向リストだと多分できない
    AppendSort(countnode->prev, countnode);
    // if (countnode->next == NULL) printf("err");
    // if (countnode == lastnode) printf("err");
  }
  for (thisnode = firstnode; thisnode != NULL; thisnode = thisnode->next) {
    printf("%d\t", GetValue(thisnode));
  }
  printf("\n並び替え成功\n");

  printf("%d,%d", GetValue(firstnode), GetValue(lastnode));
  /* リストの全ノードを削除 */
  thisnode = firstnode;
  while (thisnode != NULL) {
    removenode = thisnode;
    thisnode = NextNode(thisnode);
    RemoveValue(removenode);
  }
  return EXIT_SUCCESS;
}
