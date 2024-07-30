#include <iostream>
#include <queue>
using namespace std;

// 节点定义
template<typename T>
struct Node {
    Node(const T& val)
        : data(val)
        , left(nullptr)
        , right(nullptr)
        , height(1) {}

    T data;
    Node* left;
    Node* right;
    int height;
};

template<typename T, typename Comp = less<T>>
class Avl {
public:
    Avl(const Comp& comp = Comp())
        : root_(nullptr)
        , comp_(comp) {}

    ~Avl() {
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

    // 插入元素
    void Insert(const T& val) {
        root_ = Insert(root_, val);
    }

private:
    // 递归插入元素
    Node<T>* Insert(Node<T>* node, const T& val) {
        if (!node) {
            return new Node(val);
        }
        if (comp_(val, node->data)) {
            node->left = Insert(node->left, val);
            if (GetHeight(node->left) - GetHeight(node->right) > 1) {
                Node<T>* child = node->left;
                // 左孩子的左子树过高
                if (comp_(GetHeight(child->left), GetHeight(child->right))) {
                    node = RightRotate(node);
                }
                // 左孩子的右子树过高
                else {
                    node = LeftRightRotate(node);
                }
            }
        }
        else if (comp_(node->data, val)) {
            node->right = Insert(node->right, val);
            if (GetHeight(node->right) - GetHeight(node->left) > 1) {
                Node<T>* child = node->right;
                // 右孩子的右子树过高
                if (comp_(GetHeight(child->right), GetHeight(child->left))) {
                    node = LeftRotate(node);
                }
                // 右孩子的左子树过高
                else {
                    node = RightLeftRotate(node);
                }
            }
        }
        else {
            ;  // 该avl不允许值相同的情况
        }
        // 由于插入了一个节点，所以需要更新节点的高度
        SetHeight(node);
        return node;
    }

private:
    // 返回节点高度，空节点高度为0
    int GetHeight(const Node<T>* node) const { return node ? node->height : 0; }

    // 设置节点高度
    void SetHeight(Node<T>* node) { node->height = max(GetHeight(node->left), GetHeight(node->right)) + 1; }

    // 左旋操作，只有在二叉树失衡时才会调用，所以node一定存在
    Node<T>* LeftRotate(Node<T>* node) {
        // 左旋节点
        Node<T>* child = node->right;
        node->right = child->left;
        child->left = node;
        // 更新节点高度
        SetHeight(node);
        SetHeight(child);
        // 返回新的局部根节点
        return child;
    }

    // 右旋操作，与左旋同理
    Node<T>* RightRotate(Node<T>* node) {
        // 左旋节点
        Node<T>* child = node->left;
        node->left = child->right;
        child->right = node;
        // 更新节点高度
        SetHeight(node);
        SetHeight(child);
        // 返回新的局部根节点
        return child;
    }

    // 左右双旋操作
    Node<T>* LeftRightRotate(Node<T>* node) {
        Node<T>* child = LeftRotate(node->left);
        node->left = child;
        return RightRotate(node);
    }

    // 右左双旋操作
    Node<T>* RightLeftRotate(Node<T>* node) {
        Node<T>* child = RightRotate(node->right);
        node->right = child;
        return LeftRotate(node);
    }

private:
    Node<T>* root_;
    Comp comp_;
};

int main() {
    Avl<int> avl;
    for (int i = 0; i < 5; ++i) {
        avl.Insert(i);
    }
    getchar();
    return 0;
}