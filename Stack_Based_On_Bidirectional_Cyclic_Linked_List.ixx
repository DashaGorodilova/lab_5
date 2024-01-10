module;

#include <iostream>
#include <new>

export module Dynamic_Structures: Stack_Based_On_Bidirectional_Cyclic_Linked_List;

import :Abstract_Class_Stack;
export namespace Dynamic_Structures
{
    template <typename T>
    class StackBasedOnBidirectionalCyclicLinkedList {
    private:
        template <typename T>
        class Node {
        public:
            T data;
            Node* next;
            Node* prev;

            Node(T data = T(), Node* prev = nullptr, Node* next = nullptr) {
                this->data = data;
                this->prev = prev;
                this->next = next;
            }
        };

        Node<T>* top;
        int size;

    public:

        int GetSize() const {
            return size;
        };
        void clear();
        bool Push(const T& element);
        bool Pop(T& element);
        bool Peek(T& element) const;
        StackBasedOnBidirectionalCyclicLinkedList();
        StackBasedOnBidirectionalCyclicLinkedList(const StackBasedOnBidirectionalCyclicLinkedList<T>& other);
        StackBasedOnBidirectionalCyclicLinkedList(StackBasedOnBidirectionalCyclicLinkedList<T>&& other);
        StackBasedOnBidirectionalCyclicLinkedList(std::initializer_list<T> ilist);
        ~StackBasedOnBidirectionalCyclicLinkedList();
        void InsertAt(int value, int index)
        {
            Node<T>* newNode = new(std::nothrow) Node<T>(value);
            Node<T>* tempNode = top;
            if (GetSize() < index)
            {
                std::cout << "Было вставлено в конце" << std::endl;
                if (top == nullptr) {
                    newNode->next = newNode;
                    newNode->prev = newNode;
                }
                else
                {
                    newNode->next = top->next;
                    newNode->prev = top;
                    top->next->prev = newNode;
                    top->next = newNode;
                }
            }
            else
            {
                int temp = 0;
                while (temp != index)
                {
                    tempNode = tempNode->next;
                    temp++;
                }
                newNode->next = tempNode;
                newNode->prev = tempNode->prev;
            }
        };
        int RemoveAt(int index)
        {
            if (top == nullptr) {
                return 0;
            }
            Node<T>* tempNode = top;
            int temp = 0;
            while (temp != index)
            {
                tempNode = tempNode->next;
                temp++;
            }
            tempNode->next->prev = tempNode->prev;
            tempNode->prev->next = tempNode->next;
            delete tempNode;
        };
        StackBasedOnBidirectionalCyclicLinkedList<T>& operator=(const StackBasedOnBidirectionalCyclicLinkedList<T>& other);
        StackBasedOnBidirectionalCyclicLinkedList<T>& operator=(StackBasedOnBidirectionalCyclicLinkedList<T>&& other);
        StackBasedOnBidirectionalCyclicLinkedList<T>& operator=(std::initializer_list<T> ilist);
    };

    template<typename T>
    StackBasedOnBidirectionalCyclicLinkedList<T>::StackBasedOnBidirectionalCyclicLinkedList()
    {
        size = 0;
        top = nullptr;
    }

    template<typename T>
    StackBasedOnBidirectionalCyclicLinkedList<T>::~StackBasedOnBidirectionalCyclicLinkedList() {
        clear();
    }


    template <typename T>
    StackBasedOnBidirectionalCyclicLinkedList<T>::StackBasedOnBidirectionalCyclicLinkedList(const StackBasedOnBidirectionalCyclicLinkedList<T>& other) : top(nullptr), size(0) {
        *this = other;
    }

    template <typename T>
    StackBasedOnBidirectionalCyclicLinkedList<T>::StackBasedOnBidirectionalCyclicLinkedList(StackBasedOnBidirectionalCyclicLinkedList<T>&& other) : top(nullptr), size(0) {
        *this = std::move(other);
    }

    template <typename T>
    StackBasedOnBidirectionalCyclicLinkedList<T>::StackBasedOnBidirectionalCyclicLinkedList(std::initializer_list<T> ilist) : top(nullptr), size(0) {
        *this = ilist;
    }


    template <typename T>
    StackBasedOnBidirectionalCyclicLinkedList<T>& StackBasedOnBidirectionalCyclicLinkedList<T>::operator=(const StackBasedOnBidirectionalCyclicLinkedList<T>& other) {
        if (this != &other) {
            clear();
            if (other.top != nullptr) {
                Node<T>* currentOther = other.top->next;
                do {
                    if (!Push(currentOther->data)) {
                        clear();
                        throw std::bad_alloc();
                    }
                    currentOther = currentOther->next;
                } while (currentOther != other.top->next);
            }
        }

        return *this;
    }

    template <typename T>
    StackBasedOnBidirectionalCyclicLinkedList<T>& StackBasedOnBidirectionalCyclicLinkedList<T>::operator=(StackBasedOnBidirectionalCyclicLinkedList<T>&& other) {
        if (this != &other) {
            clear();
            top = other.top;
            size = other.size;
            other.top = nullptr;
            other.size = 0;
        }

        return *this;
    }

    template <typename T>
    StackBasedOnBidirectionalCyclicLinkedList<T>& StackBasedOnBidirectionalCyclicLinkedList<T>::operator=(std::initializer_list<T> ilist) {
        clear();
        for (const T& item : ilist) {
            Push(item);
        }
        return *this;
    }

    template<typename T>
    void StackBasedOnBidirectionalCyclicLinkedList<T>::clear() {
        Node<T>* prevNode;
        while (size > 0) {
            prevNode = top->prev;
            delete top;
            top = prevNode;
            --size;
        }
        top = nullptr;
    }

    template<typename T>
    bool StackBasedOnBidirectionalCyclicLinkedList<T>::Push(const T& element) {
        Node<T>* newNode = new(std::nothrow) Node<T>(element);
        if (newNode == nullptr) {
            return false;
        }

        if (top == nullptr) {
            newNode->next = newNode;
            newNode->prev = newNode;
        }
        else {
            newNode->next = top->next;
            newNode->prev = top;
            top->next->prev = newNode;
            top->next = newNode;
        }

        top = newNode;
        size++;
        return true;
    }

    template<typename T>
    bool StackBasedOnBidirectionalCyclicLinkedList<T>::Pop(T& element) {
        if (top == nullptr) {
            return false;
        }

        element = top->data;

        Node<T>* toDelete = top;

        if (top == top->next) {
            top = nullptr;
        }
        else {
            top->prev->next = top->next;
            top->next->prev = top->prev;
            top = top->prev;
        }

        delete toDelete;
        --size;
        return true;
    }

    template<typename T>
    bool StackBasedOnBidirectionalCyclicLinkedList<T>::Peek(T& element) const {
        if (top == nullptr) {
            return false;
        }
        element = top->data;
        return true;
    }


}