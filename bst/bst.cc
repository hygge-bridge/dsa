#include <iostream>
#include <vector>
using namespace std;

// 二叉树的节点定义
template<typename T>
struct Node {
    Node(const T& val = T())
        : data(val)
        , left(nullptr)
        , right(nullptr) {}

    T data;
    Node* left;
    Node* right;
};

// 二叉搜索树
template<typename T, typename Comp = less<T>>
class Bst {
public:
    // 构造一个空bst，用户可以自行传入函数对象
    Bst(const Comp& comp = Comp())
        : root_(nullptr)
        , comp_(comp) {} 

    ~Bst() {}

    // 非递归插入
    void NonRecurInsert(const T& val) {
        Node<T>* new_node = new Node(val);  
        if (!root_) {
            root_ = new_node;
            return;
        }
        Node<T>* parent = nullptr;
        Node<T>* curr = root_;
        while (curr) {
            parent = curr;
            if (comp_(val, curr->data)) {
                curr = curr->left;
            }
            else if (comp_(curr->data, val)) {
                curr = curr->right;
            }
            else {
                return;  // 该bst不允许插入相同元素，这个看个人想要实现的版本
            }
        }
        if (comp_(val, parent->data)) {
            parent->left = new_node;
        }
        else {
            parent->right = new_node;
        }
    }
   
    // 非递归删除
    void NonRecurRemove(const T& val) {
        if (!root_) {
            return;
        }
        Node<T>* curr = root_;
        while (curr) {
            if (comp_(val, curr->data)) {
                curr = curr->left;
            }
            else if (comp_(curr->data, val)) {
                curr = curr->right;
            }
            else {
                break;
            }
        }
        // 没有对应的元素，无需删除
        if (!curr) {
            return;
        }
        // 节点有两个孩子，查找前驱节点
        Node<T>* parent = curr;
        if (curr->left && curr->right) {
            Node<T>* precursor = curr->left;
            while (precursor->right) {
                parent = precursor;
                precursor = precursor->right;
            }
            curr->data = precursor->data;
            curr = precursor;
        }
        Node<T>* child = curr->left ? curr->left : curr->right;
        if (comp_(curr->data, parent->data)) {
            parent->left = child;
        }
        else {
            parent->right = child;
        }
        delete curr;
    }
    
    // 非递归查询
    bool NonRecurQuery(const T& val) const {
        Node<T>* curr = root_;
        while (curr) {
            if (comp_(val, curr->data)) {
                curr = curr->left;
            }
            else if (comp_(curr->data, val)) {
                curr = curr->right;
            }
            else {
                return true;
            }
        }
        return false;
    }

    // 递归前序遍历
    void RecurPreTraverse() const {
        cout << "Preorder traversal: ";
        RecurPreTraverse(root_);
        cout << endl;
    }

    // 递归中序遍历
    void RecurInTraverse() const {
        cout << "Inorder traversal: ";
        RecurInTraverse(root_);
        cout << endl;
    }

    // 递归后序遍历
    void RecurPostTraverse() const {
        cout << "Postorder traversal: ";
        RecurPostTraverse(root_);
        cout << endl;
    }

    // 递归层序遍历
    void RecurLevelTraverse() const {
        cout << "Levelorder traversal: ";
        int depth = RecurGetDepth(root_);
        for (int i = 0; i < depth; ++i) {
            RecurLevelTraverse(root_, i);
        }
        cout << endl;
    }

// 相关递归操作的内部实现
private:
    // 递归前序遍历的具体实现
    void RecurPreTraverse(Node<T>* node) const {
        if (!node) {
            return;
        }
        cout << node->data << " ";
        RecurPreTraverse(node->left);
        RecurPreTraverse(node->right);
    }

    // 递归中序遍历的具体实现
    void RecurInTraverse(Node<T>* node) const {
        if (!node) {
            return;
        }
        RecurInTraverse(node->left);
        cout << node->data << " ";
        RecurInTraverse(node->right);
    }

    // 递归后序遍历的具体实现
    void RecurPostTraverse(Node<T>* node) const {
        if (!node) {
            return;
        }        
        RecurPostTraverse(node->left);
        RecurPostTraverse(node->right);
        cout << node->data << " ";
    }

    // 递归求二叉树的深度
    int RecurGetDepth(Node<T>* node) const {
        if (!node) {
            return 0;
        }
        int left_depth = RecurGetDepth(node->left);
        int right_depth = RecurGetDepth(node->right);
        return max(left_depth, right_depth) + 1;
    }

    // 递归层序遍历的具体实现
    void RecurLevelTraverse(Node<T>* node, int level) const {
        // 因为二叉树可能有些节点没有两个孩子，所以这里必须判断是否为空的情况
        if (!node) {
            return;
        }
        if (level == 0) {
            cout << node->data << " ";
            return;
        }
        RecurLevelTraverse(node->left, level - 1);
        RecurLevelTraverse(node->right, level - 1);
    }

private:
    Node<T>* root_;
    Comp comp_;
};

int main() {
    vector<int> arr{58,24,67,0,34,62,69,5,41,64,78};
    Bst<int> bst;
    for (int num : arr) {
        bst.NonRecurInsert(num);
    }
    // bst.NonRecurInsert(7);
    // bst.NonRecurRemove(24);
    // cout << bst.NonRecurQuery(24) << endl;
    // cout << bst.NonRecurQuery(7) << endl;
    bst.RecurPreTraverse();
    bst.RecurInTraverse();
    bst.RecurPostTraverse();
    bst.RecurLevelTraverse();
    getchar();
    return 0;
}