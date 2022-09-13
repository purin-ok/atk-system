/* 文字列をキーにした二分木：strcmp()関数を使って文字列の大小関係を判別できる */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENGTH 1024

typedef struct _tag_tree_node {
  char *key;                    /* このノードがもつキー */
  char *val;                    /* キーに対応する値 */
  struct _tag_tree_node *left;  /* 自分より小さい値のノード */
  struct _tag_tree_node *right; /* 自分より大きい値のノード */
} tree_node;

tree_node *tree_root = NULL;

/* 新しいノードを作成する関数 */
tree_node *create_new_node(char *key, char *val) {
  tree_node *tree_new;

  /* 新しいノードを作成して、初期化する */
  tree_new = (tree_node *)malloc(sizeof(tree_node));
  if (tree_new == NULL) exit(EXIT_FAILURE);
  tree_new->left = NULL;
  tree_new->right = NULL;
  /* key と val の文字列を新しいノードにコピー */
  tree_new->key = (char *)malloc(sizeof(char) * strlen(key) + 1);
  tree_new->val = (char *)malloc(sizeof(char) * strlen(val) + 1);
  if (tree_new->key == NULL || tree_new->val == NULL) exit(EXIT_FAILURE);
  strcpy(tree_new->key, key);
  strcpy(tree_new->val, val);

  return tree_new;
}

/* ノードを挿入する関数 */
void insert_tree(char *key, char *val, tree_node *node) {
  /* 一つも挿入されていない場合 */
  if (node == NULL) {
    tree_root = create_new_node(key, val);
    return;
  }

  if (strcmp(node->key, key) > 0) { /* keyが現在のノードの値よりも小さい場合 */
    if (node->left != NULL) { /* 左側に挿入する */
      insert_tree(key, val, node->left);
    } else { /* 左側に追加する */
      node->left = create_new_node(key, val);
    }
  } else { /* keyが現在のノードの値以上の場合 */
    if (node->right != NULL) { /* 右側に挿入する */
      insert_tree(key, val, node->right);
    } else { /* 右側に追加する */
      node->right = create_new_node(key, val);
    }
  }
  return;
}

/* キーを検索する関数：発見したノードのポインタを返す。ない場合はNULL */
tree_node *find_key(tree_node *node, char *val) {
  int cmp = strcmp(node->key, val);
  /* 自分よりも小さいならば左側 */
  if (cmp > 0) {
    if (node->left == NULL) return NULL; /* 左側がなければ valはない */
    return find_key(node->left, val);
  }
  /* 自分よりも大きいならば右側 */
  if (cmp < 0) {
    if (node->right == NULL) return NULL; /* 右側がなければ valはない */
    return find_key(node->right, val);
  }

  return node; /* 見つかれば(cmp == 0: 等しい文字列)、見つかった値を返す */
}

/* val を削除する関数　成功すれば1、失敗すれば0を返す */
int delete_tree(char *val) {
  tree_node *node = tree_root, *parent_node = NULL;
  tree_node *left_biggest;
  int direction = 0, cmp;

  /* 削除すべき対象をみつける */
  while (node != NULL && (cmp = strcmp(node->key, val)) != 0) {
    parent_node = node;
    if (cmp > 0) {
      node = node->left;
      direction = -1; /* 親の左側 */
    } else {
      node = node->right;
      direction = 1; /* 親の右側 */
    }
  }
  if (node == NULL) return 0; /* 見つからなかった */

  if (node->left == NULL || node->right == NULL) {
    /* 左か右、どちらかがNULLであった場合（両方NULL含む）*/
    if (node->left == NULL) {
      /* 親のポインタを変更する */
      if (direction == -1) parent_node->left = node->right;
      if (direction == 1) parent_node->right = node->right;
      if (direction == 0) tree_root = node->right;
    } else {
      /* 親のポインタを変更する */
      if (direction == -1) parent_node->left = node->left;
      if (direction == 1) parent_node->right = node->left;
      if (direction == 0) tree_root = node->left;
    }
    free(node->key);
    free(node->val);
    free(node);
  } else { /* 両者ともNULLでなかった場合 */
    /* ノードの左側の最も大きな値（右端）を取得する */
    left_biggest = node->left;
    parent_node = node;
    direction = -1;
    while (left_biggest->right != NULL) {
      parent_node = left_biggest;
      left_biggest = left_biggest->right;
      direction = 1;
    }

    /* left_biggestの値をノードに代入し、
       left_biggestの左側の枝を親ノードの枝に入れる */
    free(node->key);
    free(node->val);
    node->key = left_biggest->key;
    node->val = left_biggest->val;
    if (direction == -1)
      parent_node->left = left_biggest->left;
    else
      parent_node->right = left_biggest->left;
    free(left_biggest);
  }
  return 1;
}

/* ツリーの表示 */
void print_tree(int depth, tree_node *node) {
  int i;
  if (node == NULL) return;
  print_tree(depth + 1, node->left);
  for (i = 0; i < depth; i++) printf(" ");
  printf("%s : %s \n", node->key, node->val);
  print_tree(depth + 1, node->right);
}

/* ツリーのメモリ解放 */
void free_tree(tree_node *node) {
  if (node == NULL) return;
  /* まず子ノードのメモリを解放する */
  free_tree(node->left);
  free_tree(node->right);
  /* 自分自身を解放 */
  free(node->key);
  free(node->val);
  free(node);
}

/* メインプログラム */
int main(void) {
  int i;
  char tmp[MAXLENGTH], tmpval[MAXLENGTH], buf[MAXLENGTH];
  tree_node *node_found;

  while (1) {
    print_tree(0, tree_root);
    printf("0:終了 1:挿入 2:探索 3:削除> ");
    fgets(buf, MAXLENGTH, stdin);
    i = atoi(buf);
    if (i == 0) break;
    switch (i) {
      case 1:
        printf("挿入する文字列（キー）: ");
        fgets(buf, MAXLENGTH, stdin);
        sscanf(buf, "%s", tmp);
        printf("キーに対応させる値: ");
        fgets(buf, MAXLENGTH, stdin);
        sscanf(buf, "%s", tmpval);
        insert_tree(tmp, tmpval, tree_root);
        break;
      case 2:
        printf("探索する文字列: ");
        fgets(buf, MAXLENGTH, stdin);
        sscanf(buf, "%s", tmp);
        node_found = find_key(tree_root, tmp);
        if (node_found != NULL)
          printf("対応する値は %s です\n", node_found->val);
        else
          printf("見つかりませんでした\n");
        break;
      case 3:
        printf("削除する文字列: ");
        fgets(buf, MAXLENGTH, stdin);
        sscanf(buf, "%s", tmp);
        if (delete_tree(tmp) == 1)
          printf("削除しました\n");
        else
          printf("見つかりませんでした\n");
        break;
    }
  }
  free_tree(tree_root);
  return EXIT_SUCCESS;
}