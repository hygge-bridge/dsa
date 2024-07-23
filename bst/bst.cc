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
    bst.NonRecurInsert(7);
    bst.NonRecurRemove(24);
    cout << bst.NonRecurQuery(24) << endl;
    cout << bst.NonRecurQuery(7) << endl;
    return 0;
}