#ifndef LOCK_FREE_LIST_H
#define LOCK_FREE_LIST_H
#include <atomic>
#include <pthread.h>
namespace sablin{
template <typename T>
struct ListNode{
    T data_;
    ListNode<T>* next_;
};

template <typename T>
class LockFreeList{
private: 
    std::atomic<ListNode<T>*> head_;
    pthread_mutex_t head_lock_;
public:
    explicit LockFreeList();
    LockFreeList(const LockFreeList&) = delete;
    LockFreeList& operator=(const LockFreeList<T>&) = delete;
    ~LockFreeList();

    void PushFront(const T&);
    T PopFront();
    bool IsEmpty() const;
};

template <typename T>
LockFreeList<T>::LockFreeList(): head_{nullptr}{
    pthread_mutex_init(&head_lock_, NULL);
}

template <typename T>
LockFreeList<T>::~LockFreeList(){
    pthread_mutex_lock(&head_lock_);
    while(head_.load() != nullptr){
        ListNode<T> *temp = head_.load();
        head_.store(head_.load()->next_);
        delete temp;
    }
    pthread_mutex_unlock(&head_lock_);
}

template <typename T>
void LockFreeList<T>::PushFront(const T &element){
    auto node = new ListNode<T>();
    node->data_ = element;
    node->next_ = head_;
    while(!head_.compare_exchange_weak(node->next_, node)){
        node->next_ = head_;
    }
}

template <typename T>
T LockFreeList<T>::PopFront(){
    pthread_mutex_lock(&head_lock_);
    ListNode<T> *node_p = head_.load();
    head_.store(node_p->next_);
    pthread_mutex_unlock(&head_lock_);
    T temp = std::move(node_p->data_);
    delete node_p;
    return temp;
}

template <typename T>
bool LockFreeList<T>::IsEmpty() const{
    return head_.load() == nullptr;
}

}
#endif
