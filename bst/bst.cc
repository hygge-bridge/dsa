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

    // 利用非递归层序遍历的思想析构每一个节点
    ~Bst() {
        if (!root_) {
            return;
        }
        Node<T>* curr = root_;
        queue<Node<T>*> que;
        que.push(curr);
        while (!que.empty()) {
            Node<T>* node = que.front();
            que.pop();
            if (node->left) {
                que.push(node->left);
            }
            if (node->right) {
                que.push(node->right);
            }
            delete node;
        }
    }

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

    // 区间搜索问题，搜索值在[left,right]之间的节点
    void RangeQuery(vector<T>& res, int left, int right) const {
        RangeQuery(root_, res, left, right);
    }

    // 判断二叉树是否为bst问题
    bool IsBst() const {
        Node<T>* prev = nullptr;
        return IsBst(prev, root_);
    }

    // 二叉树子树问题
    bool IsChildTree(Node<T>* root) const {
        if (!root) {
            return true;
        }
        if (!root_) {
            return false;
        }
        Node<T>* curr = root_;
        Node<T>* father_node = nullptr;
        while (curr) {
            if (curr->data == root->data) {
                father_node = curr;
                break;
            }
            else if (comp_(curr->data, root->data)) {
                curr = curr->right;
            }
            else {
                curr = curr->left;
            }
        }
        return father_node != nullptr && IsChildTree(father_node, root);
    }

    // 获取bst中两个节点的lca问题
    Node<T>* GetLca(const T& val1, const T& val2) const {
        if (!root_) {
            return nullptr;
        }
        Node<T>* curr = root_;
        while (curr) {
            if (comp_(curr->data, val1) && comp_(curr->data, val2)) {
                curr = curr->right;
            }
            else if (comp_(val1, curr->data) && comp_(val2, curr->data)) {
                curr = curr->left;
            }
            else {
                return curr;
            }
        }
        return nullptr;
    }

    // 二叉树的镜像翻转问题
    void Mirroring() const {
        if (!root_) {
            return;
        }
        // 非递归前序遍历的同时将左右孩子节点交换
        // 这里使用非递归只是为了复习，讲道理递归更简单
        Node<T>* root = root_;
        stack<Node<T>*> stk;
        stk.push(root);
        while (!stk.empty()) {
            Node<T>* node = stk.top();
            stk.pop();
            swap(node->left, node->right);
            if (node->right) {
                stk.push(node->right);
            }
            if (node->left) {
                stk.push(node->left);
            }
        }
    }

    // 二叉树镜像对称问题
    bool IsMirrorSymmetry() const {
        if (!root_) {
            return true;
        }
        return IsMirrorSymmetry(root_->left, root_->right);
    }

    // 根据前序遍历和中序遍历重建二叉树
    Node<T>* RebuildBinaryTree(const vector<T>& pre, const vector<T>& in) const {
        return RebuildBinaryTree(pre, 0, pre.size() - 1, in, 0, in.size() - 1);
    }

    // 判断二叉树是否是avl
    bool IsAvl() const {
        bool is_avl = true;
        int level = 0;
        IsAvl(root_, level, is_avl);
        return is_avl;
    }

    // 求中序遍历倒数第k个节点
    int GetKthNodeFromBottomIn(int k) {
        Node<T>* node = GetKthNodeFromBottomIn(root_, k);
        if (!node) {
            throw "invalid input k value";
        } 
        return node->data;
    }

    // 获取当前的根节点
    Node<T>* GetRoot() const { return root_; }
    // 修改当前根节点
    void SetRoot(Node<T>* root) { root_ = root; }

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

    // 递归求二叉树的深度的具体实现
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

    void RangeQuery(Node<T>* node, vector<T>& res, int left, int right) const {
        if (!node) {
            return;
        }
        if (node->data > left) {
            RangeQuery(node->left, res, left, right);
        }
        if (node->data >= left && node->data <= right) {
            res.push_back(node->data);
        }
        if (node->data < right) {
            RangeQuery(node->right, res, left, right);
        }
    }

    bool IsBst(Node<T>*& prev, Node<T>* curr) const {
        if (!curr) {
            return true;
        }
        if (!IsBst(prev, curr->left)) {
            return false;
        }
        if (prev && comp_(curr->data, prev->data)) {
            return false;
        }
        prev = curr;
        return IsBst(prev, curr->right);
    }

    bool IsChildTree(Node<T>* father_node, Node<T>* child_node) const {
        if (!child_node) {
            return true;
        }
        if (!father_node) {
            return false;
        }
        if (child_node->data != father_node->data) {
            return false;
        }
        return IsChildTree(father_node->left, child_node->left)
                && IsChildTree(father_node->right, child_node->right);
    }

    bool IsMirrorSymmetry(Node<T>* left, Node<T>* right) const {
        if (!left && !right) {
            return true;
        }
        if (!left || !right) {
            return false;
        }
        if (left->data != right->data) {
            return false;
        }
        return IsMirrorSymmetry(left->left, right->right) 
                && IsMirrorSymmetry(left->right, right->left);
    }

    // 范围为[begin, end]
    Node<T>* RebuildBinaryTree(const vector<T>& pre, int pre_begin, int pre_end, 
                            const vector<T>& in, int in_begin, int in_end) {
        if (pre_begin > pre_end || in_begin > in_end) {
            return nullptr;
        }
        const T root_val = pre[pre_begin];
        Node<T>* root = new Node<T>(root_val);
        int root_idx_in = -1;  // -1表示还没有找到根节点在中序遍历结果中的位置
        for (int i = in_begin; i <= in_end; ++i) {
            if (in[i] == root_val) {
                root_idx_in = i;
            }
        }
        root->left = RebuildBinaryTree(pre, pre_begin + 1, pre_begin + root_idx_in - in_begin,
                                        in, in_begin, root_idx_in);
        root->right = RebuildBinaryTree(pre, pre_begin + root_idx_in - in_begin + 1, pre_end,
                                        in, root_idx_in + 1, in_end);
        return root;
    }

    int IsAvl(Node<T>* node, int level, bool& is_avl) const {
        if (!node) {
            return level;
        }
        int left_level = IsAvl(node->left, level + 1, is_avl);
        if (!is_avl) {
            return left_level;
        }
        int right_level = IsAvl(node->right, level + 1, is_avl);
        if (!is_avl) {
            return right_level;
        }
        if (abs(left_level - right_level) > 1) {
            is_avl = false;
        }
        return max(left_level, right_level);
    }

    // 函数返回值建议设置为指针，并利用nullptr来判断用户输入的k值无效的情况
    int i = 1;
    Node<T>* GetKthNodeFromBottomIn(Node<T>* node, int k) {
        if (!node) {
            return nullptr;
        }
        Node<T>* right = GetKthNodeFromBottomIn(node->right, k);
        if (right) {
            return right;
        }
        // 倒序从1开始计数，正序从0开始计数，所以倒数第k个就是正数第k-1个
        if (k == i++) {
            return node;
        }
        return GetKthNodeFromBottomIn(node->left, k);
    }

private:
    Node<T>* root_;
    Comp comp_;
};

int main() {
    // 为了代码的整洁度，我把所有的测试代码全删了
    return 0;
}