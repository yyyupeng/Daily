#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class AVLNode
{
public:
    T key;
    AVLNode<T> *left;
    AVLNode<T> *right;
    int height;

    AVLNode(T value, AVLNode<T> *l, AVLNode<T> *r) : key(value), left(l), right(r), height(0) {}
};

template <typename T>
class AVLTree
{
public:
    AVLNode<T> *root;
    AVLTree() : root(nullptr) {}
    ~AVLTree();
    //插入节点
    void Insert(AVLNode<T> *&root, T );
    //删除节点
    bool Delete(AVLNode<T> *&root, T );
    //中序遍历
    void InOrderTra(AVLNode<T> *root) const;

private:
    //求树的高度
    int GetHeight(AVLNode<T> *root);
    //左旋
    AVLNode<T> *LL(AVLNode<T> *root);
    //右旋
    AVLNode<T> *RR(AVLNode<T> *root);
    //先左旋再右旋
    AVLNode<T> *LR(AVLNode<T> *root);
    //先右旋再左旋
    AVLNode<T> *RL(AVLNode<T> *root);
    //销毁AVLTree
    void destory(AVLNode<T> *&root);
};

template <typename T>
int AVLTree<T>::GetHeight(AVLNode<T> *root)
{
    if(root != nullptr)
        return root->height;
    return 0;
}

template <typename T>
AVLTree<T>::~AVLTree()
{
    cout << "销毁AVL树..." << endl;
    destory(root);
}

template <typename T>
AVLNode<T> * AVLTree<T>::LL(AVLNode<T> *root)
{
    AVLNode<T> *q = root->right;
    root->right = q->left;
    q->left = root;
    root->height = max(GetHeight(root->left), GetHeight(root->right)) + 1;
    q->height = max(root->height, GetHeight(q->right)) + 1;
    return q;
}

template <typename T>
AVLNode<T>* AVLTree<T>::RR(AVLNode<T> *root)
{
    AVLNode<T> *q = root->left;
    root->left = q->right;
    q->right = root;
    root->height = max(GetHeight(root->left), GetHeight(root->right)) + 1;
    q->height = max(GetHeight(q->left), root->height) + 1;
    return q;
}

template <typename T>
AVLNode<T>* AVLTree<T>::LR(AVLNode<T> *root)
{
    root->left = LL(root->left);
    return RR(root);
}

template <typename T>
AVLNode<T>* AVLTree<T>::RL(AVLNode<T> *root)
{
    root->right = RR(root->right);
    return LL(root);
}

template <typename T>
void AVLTree<T>::Insert(AVLNode<T> *&root, T key)
{
    if(root == nullptr)
        root = new AVLNode<T>(key, nullptr, nullptr);
    else if(key < root->key)    //插入到左子树中
    {
        Insert(root->left, key);
        //判断平衡情况
        if(GetHeight(root->left) - GetHeight(root->right) >= 2)
        {
            //左子树的左子树
            if(key < root->left->key)
                root = RR(root);
            //左子树的右子树
            else
                root = LR(root);
        }
    }
    else if(key > root->key)    //插入到右子树中
    {
        Insert(root->right, key);
        //判断平衡情况
        if(GetHeight(root->right) - GetHeight(root->left) >= 2)
        {
            //右子树的右子树
            if(key > root->right->key)
                root = LL(root);
            //右子树的左子树
            else
                root = RL(root);
        }
    }
    else
        cout << "添加失败！" << endl;

    //更新高度
    /* cout << key << " " << root->height << endl; */
    root->height = max(GetHeight(root->left), GetHeight(root->right)) + 1;
    /* cout << key << " " << root->height << endl; */
}

template <typename T>
bool AVLTree<T>::Delete(AVLNode<T> *&root, T key)
{

}

template <typename T>
void AVLTree<T>::InOrderTra(AVLNode<T> *root) const
{
    if(root)
    {
        InOrderTra(root->left);
        cout << root->key << ' ';
        InOrderTra(root->right);
    }
}

template <typename T>
void AVLTree<T>::destory(AVLNode<T> *&root)
{
    if(root == nullptr)
        return;
    destory(root->left);
    destory(root->right);
    delete root;
}

#endif

