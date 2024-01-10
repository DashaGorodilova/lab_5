
module;
#include <iostream>
#include <new>
export module Dynamic_Structures: Stack_Based_On_Unidirectional_Linked_List;

import :Abstract_Class_Stack;
export namespace Dynamic_Structures
{
    template <typename T>
    class StackBasedOnUnidirectionalLinkedList : public AbstractClassStack<T> {

        template <typename T>
        class Node {
        public:
            T data;
            Node* next;

            Node(T data = T(), Node* next = nullptr)
                : data(data), next(next) {}
        };

        Node<T>* head; 
        Node<T>* top;
        int size; 

    public:

        int GetSize() const override {
            return size;
        };

        void clear();
        bool Push(const T& element) override;
        bool Pop(T& element) override;
        bool Peek(T& element) const override;

        StackBasedOnUnidirectionalLinkedList();
        StackBasedOnUnidirectionalLinkedList(const StackBasedOnUnidirectionalLinkedList<T>& other);
        StackBasedOnUnidirectionalLinkedList(StackBasedOnUnidirectionalLinkedList<T>&& other);
        StackBasedOnUnidirectionalLinkedList(std::initializer_list<T> ilist);
        ~StackBasedOnUnidirectionalLinkedList() override;

        StackBasedOnUnidirectionalLinkedList<T>& operator=(const StackBasedOnUnidirectionalLinkedList<T>& other);
        StackBasedOnUnidirectionalLinkedList<T>& operator=(StackBasedOnUnidirectionalLinkedList<T>&& other);
        StackBasedOnUnidirectionalLinkedList<T>& operator=(std::initializer_list<T> ilist);

        friend std::ostream& operator<<(std::ostream& os, const StackBasedOnUnidirectionalLinkedList<T>& stack);
    };

    template<typename T>
    StackBasedOnUnidirectionalLinkedList<T>::StackBasedOnUnidirectionalLinkedList() : head(nullptr), top(nullptr), size(0) {}

    template <typename T>
    StackBasedOnUnidirectionalLinkedList<T>::StackBasedOnUnidirectionalLinkedList(const StackBasedOnUnidirectionalLinkedList<T>& other) : head(nullptr), top(nullptr), size(0) {
        *this = other;  
    }

    template <typename T>
    StackBasedOnUnidirectionalLinkedList<T>::StackBasedOnUnidirectionalLinkedList(StackBasedOnUnidirectionalLinkedList<T>&& other) : head(nullptr), top(nullptr), size(0) {
        *this = std::move(other);  
    }

    template <typename T>
    StackBasedOnUnidirectionalLinkedList<T>::StackBasedOnUnidirectionalLinkedList(std::initializer_list<T> ilist) : head(nullptr), top(nullptr), size(0) {
        *this = ilist;  
    }

    template<typename T>
    StackBasedOnUnidirectionalLinkedList<T>::~StackBasedOnUnidirectionalLinkedList() {
        clear();  
    }

    template<typename T>
    StackBasedOnUnidirectionalLinkedList<T>& StackBasedOnUnidirectionalLinkedList<T>::operator=(const StackBasedOnUnidirectionalLinkedList<T>& other) {
        if (this != &other) {
            clear();

            if (other.head != nullptr) {
                Node<T>* newNode = new Node<T>(other.head->data);
                head = newNode;  
                top = newNode;  
                size = 1;     

                Node<T>* currentOther = other.head->next;
                while (currentOther != nullptr) {
                    newNode->next = new Node<T>(currentOther->data);
                    newNode = newNode->next;
                    currentOther = currentOther->next;
                    ++size;
                }
            }
        }

        return *this;
    }

    template<typename T>
    StackBasedOnUnidirectionalLinkedList<T>& StackBasedOnUnidirectionalLinkedList<T>::operator=(StackBasedOnUnidirectionalLinkedList<T>&& other) {
        if (this != &other) {  
            clear();  

            head = other.head;
            top = other.top;
            size = other.size;
            other.head = nullptr;
            other.top = nullptr;
            other.size = 0;
        }

        return *this;
    }

    template<typename T>
    StackBasedOnUnidirectionalLinkedList<T>& StackBasedOnUnidirectionalLinkedList<T>::operator=(std::initializer_list<T> ilist) {
        clear();  

        for (const T& item : ilist) {
            Push(item);
        }

        return *this;  
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const StackBasedOnUnidirectionalLinkedList<T>& stack) {
        typename StackBasedOnUnidirectionalLinkedList<T>::Node* current = stack.head;

        os << "[";
        while (current != nullptr) {
            os << current->data;
            current = current->next;
            if (current != nullptr) {
                os << ", ";
            }
        }
        os << "]";

        return os;
    }

    template<typename T>
    void StackBasedOnUnidirectionalLinkedList<T>::clear() {
        Node<T>* currentNode = head;
        while (currentNode != nullptr) {
            Node<T>* nextNode = currentNode->next; 
            delete currentNode; 
            currentNode = nextNode; 
        }

        top = nullptr; 
        size = 0;
    }

    template<typename T>
    bool StackBasedOnUnidirectionalLinkedList<T>::Push(const T& element) {
        Node<T>* newNode = new(std::nothrow) Node<T>(element);

        if (newNode == nullptr) {
            return false;
        }

        if (head == nullptr) {
            head = newNode;    
        }
        else {
            top->next = newNode;
        }

        top = newNode;
        ++size;
        return true;
    }

    template<typename T>
    bool StackBasedOnUnidirectionalLinkedList<T>::Pop(T& element) {
        if (head == nullptr) {
            return false;
        }

        element = top->data;

        Node<T>* toDelete = top;

        if (head == top) {
            head = nullptr;
            top = nullptr;
        }
        else {
            Node<T>* currentNode = head;
            while (currentNode->next != top) {
                currentNode = currentNode->next;
            }
            currentNode->next = nullptr;
            top = currentNode;  
        }

        delete toDelete;  
        --size;           
        return true;
    }

    template<typename T>
    bool StackBasedOnUnidirectionalLinkedList<T>::Peek(T& element) const {
        if (head == nullptr) {
            return false;
        }
        element = top->data;

        return true;
    }
}