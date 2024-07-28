#include <iostream>
#include <vector>
#include <stack>
#include <queue>
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
   
    // 递归插入
    void RecurInsert(const T& val) {
        root_ = RecurInsert(root_, val);
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
    
    // 递归删除
    void RecurRemove(const T& val) {
        root_ = RecurRemove(root_, val);
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
   
    // 递归查询
    bool RecurQuery(const T& val) const {
        return RecurQuery(root_, val);
    }

    // 非递归前序遍历
    void NonRecurPreTraverse() const {
        if (!root_) {
            return;
        }
        stack<Node<T>*> stk;
        stk.push(root_);
        while (!stk.empty()) {
            Node<T>* node = stk.top();
            stk.pop();
            cout << node->data << " ";
            if (node->right) {
                stk.push(node->right);
            }
            if (node->left) {
                stk.push(node->left);
            }
        }
        cout << endl;
    }

    // 递归前序遍历
    void RecurPreTraverse() const {
        cout << "Preorder traversal: ";
        RecurPreTraverse(root_);
        cout << endl;
    }

    // 非递归中序遍历
    void NonRecurInTraverse() const {
        if (!root_) {
            return;
        }
        // 虽然这里出现的两处相同的while是可以优化的，
        // 但是个人觉得这种写法的可读性很好，所以这里就不优化了
        Node<T>* curr = root_;
        stack<Node<T>*> stk;
        while (curr) {
            stk.push(curr);
            curr = curr->left;
        }
        while (!stk.empty()) {
            Node<T>* node = stk.top();
            stk.pop();
            cout << node->data << " ";
            curr = node->right;
            while (curr) {
                stk.push(curr);
                curr = curr->left;
            }
        }
        cout << endl;
    }

    // 递归中序遍历
    void RecurInTraverse() const {
        cout << "Inorder traversal: ";
        RecurInTraverse(root_);
        cout << endl;
    }

    // 非递归后序遍历
    void NonRecurPostTraverse() const {
        if (!root_) {
            return;
        }
        // 将后序遍历的倒序结果保存到res中，然后逆序打印
        vector<Node<T>*> res;
        stack<Node<T>*> stk;
        stk.push(root_);
        while (!stk.empty()) {
            Node<T>* node = stk.top();
            stk.pop();
            res.push_back(node);
            if (node->left) {
                stk.push(node->left);
            }
            if (node->right) {
                stk.push(node->right);
            }   
        }
        for (auto it = res.rbegin(); it != res.rend(); ++it) {
            cout << (*it)->data << " ";
        }
        cout << endl;
    }

    // 递归后序遍历
    void RecurPostTraverse() const {
        cout << "Postorder traversal: ";
        RecurPostTraverse(root_);
        cout << endl;
    }

    // 非递归层序遍历
    void NonRecurLevelTraverse() const {
        if (!root_) {
            return;
        }
        Node<T>* curr = root_;
        queue<Node<T>*> que;
        que.push(curr);
        while (!que.empty()) {
            Node<T>* node = que.front();
            que.pop();
            cout << node->data << " ";
            if (node->left) {
                que.push(node->left);
            }
            if (node->right) {
                que.push(node->right);
            }
        }
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
    // 递归插入的具体实现
    Node<T>* RecurInsert(Node<T>* node, const T& val) {
        if (!node) {
            return new Node<T>(val);
        }
        if (comp_(val, node->data)) {
            node->left = RecurInsert(node->left, val);
        }
        else if (comp_(node->data, val)) {
            node->right = RecurInsert(node->right, val);
        }
        return node;  // 值相等时需要直接返回节点，所以这里已经包含该情况
    }

    // 递归删除的具体实现
    Node<T>* RecurRemove(Node<T>* node, const T& val) {
        if (!node) {
            return nullptr;
        }
        if (node->data == val) {
            if (node->left && node->right) {
                Node<T>* precussor = node->left;
                while (precussor->right) {
                    precussor = precussor->right;
                }
                node->data = precussor->data;
                node->left = RecurRemove(node->left, precussor->data);
            }
            else {
                Node<T>* child = node->left ? node->left : node->right;
                delete node;
                return child;
            }
        }
        else if (comp_(val, node->data)) {
            node->left = RecurRemove(node->left, val);
        }
        else {
            node->right = RecurRemove(node->right, val);
        }
        return node;
    }

    // 递归查询的具体实现
    Node<T>* RecurQuery(Node<T>* node, const T& val) const {
        if (!node) {
            return nullptr;
        }
        if (comp_(val, node->data)) {
            return RecurQuery(node->left, val);
        }
        else if (comp_(node->data, val)) {
            return RecurQuery(node->right, val);
        }
        else {
            return node; 
        }
    }

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
        // bst.RecurInsert(num);
    }
    // bst.RecurInsert(7);
    // bst.RecurRemove(24);
    // cout << bst.RecurQuery(24) << endl;
    // cout << bst.RecurQuery(7) << endl;
    // bst.RecurPreTraverse();
    // bst.RecurInTraverse();
    // bst.RecurPostTraverse();
    // bst.RecurLevelTraverse();
    bst.NonRecurPreTraverse();
    bst.NonRecurInTraverse();
    bst.NonRecurPostTraverse();
    bst.NonRecurLevelTraverse();
    getchar();
    return 0;
}