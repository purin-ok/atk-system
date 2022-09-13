#include <stdio.h>
#include <stdlib.h>
#define MAXLENGTH 1024

typedef struct _tag_tree_node {
  int value;                   /* このノードがもつ値 */
  struct _tag_tree_node *left; /* 自分より小さい値のノード（左側のノード）*/
  struct _tag_tree_node *right; /* 自分より大きい値のノード（右側のノード）*/
} tree_node;

tree_node *tree_root = NULL; /* 木の根っこ */

/* 新しいノードを作る関数 */
tree_node *create_new_node(int num) {
  tree_node *tree_new;

  /* 新しいノードを作成して、初期化する */
  tree_new = (tree_node *)malloc(sizeof(tree_node));
  if (tree_new == NULL) exit(EXIT_FAILURE);
  tree_new->left = NULL;
  tree_new->right = NULL;
  tree_new->value = num; /* ノードの値に num をセット */

  return tree_new;
}

/* ノードを挿入する関数 */
void insert_tree(int num, tree_node *node) {
  /* 一つも挿入されていない場合 */
  if (node == NULL) {
    tree_root = create_new_node(num);
    return;
  }

  if (node->value > num) { /* num が現在のノードの値よりも小さい場合 */
    if (node->left != NULL) {
      /* 左側に子があれば、そちらに挿入 */
      insert_tree(num, node->left);
    } else {
      /* 左側に子がなければ、子を作って追加する */
      node->left = create_new_node(num);
    }
  } else { /* num が現在のノードの値以上の場合 */
    if (node->right != NULL) {
      /* 右側の子があれば、そちらに挿入 */
      insert_tree(num, node->right);
    } else {
      /* 右側に子がなければ、子を作って追加する */
      node->right = create_new_node(num);
    }
  }
  return;
}

/* 検索関数 */
/* 発見したツリーノードのポインタを返す。ない場合はNULL */
tree_node *find_value(tree_node *node, int val) {
  /* 自分よりも小さい値ならば、左側 */
  if (node->value > val) {
    if (node->left == NULL) return NULL; /* もし左側がなければ、valはない */
    return find_value(node->left, val);
  }
  /* 自分よりも大きい値ならば、右側 */
  if (node->value < val) {
    if (node->right == NULL) return NULL; /* 右側がなければ、valはない */
    return find_value(node->right, val);
  }
  return node; /* 見つかったノードのアドレスを返す */
}

/* 値を削除する関数 */
/* val を削除する。成功すれば 1, 失敗すれば 0 を返す */
int delete_tree(int val) {
  tree_node *node, *parent_node;
  tree_node *left_biggest;
  int direction;

  node = tree_root; /* 根ノードから探し始める */
  parent_node = NULL;
  direction = 0;

  /* 削除すべき対象を見つける(find_valueと同じことを再帰なしでやっている) */
  while (node != NULL && node->value != val) {
    parent_node = node;
    if (node->value > val) {
      node = node->left;
      direction = -1; /* 親の左側 */
    } else {
      node = node->right;
      direction = 1; /* 親の右側 */
    }
  }
  if (node == NULL) return 0; /* 見つからなかった */

  if (node->left == NULL || node->right == NULL) {
    /* 左か右、どちらかがNULLの場合（両方NULLも含む）*/
    if (node->left == NULL) {
      /* 親のポインタを変更する */
      if (direction == -1) parent_node->left = node->right;
      if (direction == 1) parent_node->right = node->right;
      if (direction == 0) tree_root = node->right;
    } else { /* 右がNULL */
      /* 親のポインタを変更する */
      if (direction == -1) parent_node->left = node->left;
      if (direction == 1) parent_node->right = node->left;
      if (direction == 0) tree_root = node->left;
    }
    free(node);
  } else {
    /* 両者ともNULLでなかった場合 */
    /* ノードの左側の最も大きな値（最も右側の値）を取得する */
    left_biggest = node->left;
    parent_node = node;
    direction = -1;
    while (left_biggest->right != NULL) {
      parent_node = left_biggest;
      left_biggest = left_biggest->right;
      direction = 1;
    }

    /* left_biggestの値をnodeに代入し、left_biggestは左側の枝を入れる */
    node->value = left_biggest->value;
    if (direction == -1)
      parent_node->left = left_biggest->left;
    else
      parent_node->right = left_biggest->left;
    free(left_biggest);
  }
  return 1;
}

/* ツリーの表示（簡易版）*/
void print_tree(int depth, tree_node *node) {
  int i;
  if (node == NULL) return;
  print_tree(depth + 1, node->left);
  for (i = 0; i < depth; i++) printf("  ");
  printf("%d\n", node->value);
  print_tree(depth + 1, node->right);
}

/* ツリーのメモリ解放 */
void free_tree(tree_node *node) {
  if (node == NULL) return;
  /* まず子ノードのメモリを解放する */
  free_tree(node->left);
  free_tree(node->right);
  /* 自分自身を解放 */
  free(node);
}

/* メインプログラム */
int main(void) {
  int i, action;
  char buf[MAXLENGTH];

  /* ランダムな値をツリーに挿入していく */
  for (i = 0; i < 10; i++) insert_tree(rand() % 99 + 1, tree_root);

  while (1) {
    print_tree(0, tree_root);
    printf("実行する操作のタイプを入力してください\n");
    printf("1:追加 2:検索 3:削除 それ以外:終了>");
    fgets(buf, MAXLENGTH, stdin);
    action = atoi(buf);
    switch (action) {
      case 1:
        printf("1～100の範囲で追加する数値を入力してください:");
        fgets(buf, MAXLENGTH, stdin);
        i = atoi(buf);
        if (i < 1 || i > 100) continue;
        insert_tree(i, tree_root);
        break;
      case 2:
        printf("検索する数値を入力してください:");
        fgets(buf, MAXLENGTH, stdin);
        i = atoi(buf);
        if (find_value(tree_root, i) != NULL)
          printf("%dを発見しました\n", i);
        else
          printf("%dは見つかりませんでした\n", i);
        break;
      case 3:
        printf("削除する数値を入力してください:");
        fgets(buf, MAXLENGTH, stdin);
        i = atoi(buf);
        if (delete_tree(i) == 1)
          printf("%dを削除しました\n", i);
        else
          printf("%dは見つかりませんでした\n", i);
        break;
      default:
        free_tree(tree_root);
        return EXIT_SUCCESS;
    }
  }
}
