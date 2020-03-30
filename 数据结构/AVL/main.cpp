#include "AVLTree.h"

int main()
{
    AVLTree<int> tree;
    int value;
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

    return 0;
}

