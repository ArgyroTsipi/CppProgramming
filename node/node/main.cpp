//
//  main.cpp
//  node
//
//  Created by Argyro on 23/6/21.
//
include<iostream>
using namespace std;

struct Node{
int number;
Node* left;
Node* right;
};

typedef struct Node* TNode;

int max(int a, int b){
if(a>b)
return a;
else return b;
}

int findHeightOfNode(TNode t){
if(t == nullptr)
return -1;
else return max(findHeightOfNode(t->left), findHeightOfNode(t->right))+1;
}

int findDepthOfNode(TNode t, int data, int level){
if(t==nullptr)
return 0;
if(t->number == data)
return level;
int l = findDepthOfNode(t->left, data, level+1);
if(l!=0)
return l;
l = findDepthOfNode(t->right, data, level+1);
return l;
}

int countEH(struct Node* root){
//an einai fullo tote einai isobares
if(root == nullptr || (root->left == nullptr && root->right == nullptr))
return 1;
//prepei to height tou root->right na einai iso me to height tou root->left gia na einai isobarhs o komvos
else if(root->left == nullptr && root->right != nullptr)
return countEH(root->right);
else if(root->right == nullptr && root->left != nullptr)
return countEH(root->left);
else return 1 + countEH(root->left) + countEH(root->right);
}

if(findHeightOfNode(root->right))
