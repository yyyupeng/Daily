#include "AVLTree.h"

int main()
{
    AVLTree<int> tree;
    int value;
    int temp;
    cout << "请输入整数建立二叉树(-1结束)：" << endl;
    while (cin >> value)
    {
        if (value == -1)
            break;
        tree.Insert(tree.root, value);
    }

    cout << "中序遍历：";
    tree.InOrderTra(tree.root);
    cout << endl;

    cout << "删除那个节点? ";
    cin >> temp;
    AVLNode<int> *node = tree.Delete(tree.root, temp);

    cout << "删除后中序遍历：";
    tree.InOrderTra(tree.root);
    cout << endl;
    
    return 0;
}

