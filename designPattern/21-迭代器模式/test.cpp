#include <iostream>
#include <vector>
#include <list>

// 通用节点指针
//这种初始化导致了判断下一个节点是否为空只需要判断next是否为空即可。
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T val) : data(val), next(nullptr) {}
};

// 通用迭代器
template <typename T>
class SharedIterator {
private:
    Node<T>* current;

public:
    explicit SharedIterator(Node<T>* start) : current(start) {}

    bool hasNext() const {
        return current != nullptr;
    }

    T next() {
        T value = current->data;
        current = current->next;
        return value;
    }
};

// 链表实现，头插法实现
template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    void add(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    Node<T>* getHead() const {
        return head;
    }
};

int main() {
    LinkedList<int> list1;
    list1.add(1);
    list1.add(2);
    list1.add(3);

    LinkedList<int> list2;
    list2.add(4);
    list2.add(5);
    list2.add(6);

    // 复用通用迭代器
    SharedIterator<int> it1(list1.getHead());
    SharedIterator<int> it2(list2.getHead());

    while (it1.hasNext()) {
        std::cout << it1.next() << " ";
    }
    std::cout << std::endl;

    while (it2.hasNext()) {
        std::cout << it2.next() << " ";
    }

    return 0;
}
