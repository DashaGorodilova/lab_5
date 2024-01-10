module;
#include <iostream>
export module Dynamic_Structures: Abstract_Class_Stack;

export namespace Dynamic_Structures 
{

    template <typename T>
    class AbstractClassStack {
    public:

        virtual int GetSize() const = 0;
        virtual bool Push(const T& element) = 0;
        virtual bool Pop(T& element) = 0;
        virtual bool Peek(T& element) const = 0;
        virtual ~AbstractClassStack() {};
    };
}