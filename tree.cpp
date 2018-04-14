#include <iostream>
using namespace std;

class BinTree {
private:
    class BinNode {
    public:
        int idata;
        BinNode *left,*right;
        BinNode(int a = 0) {idata = a; left = right = 0;}
        void printNode() {cout << idata << " ";}
    };
    BinNode *root;
    void traverse(BinNode *rp); //rpの木を表示
    BinNode* addNode(BinNode *rp, BinNode *node); //rpの木にnodeを連結
    BinNode* delNode(BinNode *rp, int x);
public:
    BinTree() {root = 0;}
    void printTree() {traverse(root);}
    void insert(int x) {
        BinNode *np = new BinNode(x);
        root = addNode(root, np);
    }
    void remove(int x) {root = delNode(root, x);}
};
void BinTree::traverse(BinNode *rp) {
    rp->printNode();
    if (rp->left) {
        traverse(rp->left);
    } 
    if (rp->right) {
        traverse(rp->right);
    } else {
        return;
    }
}
BinTree::BinNode* BinTree::addNode(BinNode *rp, BinNode *node) {
    if (!rp) {
        return node;
    }
    if (!node) {
        return rp;
    }
    if (rp->idata > node->idata) {
        rp->left = addNode(rp->left, node);
    } else {
        rp->right = addNode(rp->right, node);
    }
    return rp;
}
 BinTree::BinNode* BinTree::delNode(BinNode *rp, int x) {
    if (rp->idata > x) {
        if (!rp->left) {
            return rp;
        }
        rp->left = delNode(rp->left, x);
        return rp;
    }
    if (rp->idata < x) {
        if (!rp->right) {
            return rp;
        }
        rp->right = delNode(rp->right, x);
        return rp;
    }
    if (rp->idata == x) {
        BinNode *temp = rp;
        if (rp->left && rp->right) {
            rp = rp->right;
            addNode(root, rp->left);
        } else if (rp->left) {
            rp = rp->left;
        } else if (rp->right) {
            rp = rp->right;
        } else {
            rp = NULL;
        }
        delete temp;
        return rp;
    }
}

int main() {
    BinTree bt;
    int x;

    cout << "正整数をいくつか入力せよ――＞";
    while (cin >> x && x > 0) {
        bt.insert(x);
    }

    bt.printTree();
    cout << endl;

    while (cout << "削除したい正整数――＞" && cin >> x && x > 0) {
        bt.remove(x);
        bt.printTree();
        cout << endl;
    }
    return 0;
}
