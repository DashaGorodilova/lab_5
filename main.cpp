import Dynamic_Structures;
#include <iostream>
using namespace Dynamic_Structures;

template <typename T>
void demonstrate(AbstractClassStack<T>& structure, const std::initializer_list<T>& elements) {
    std::cout << "Добавление элементов в стр-ру: ";
    for (const auto& element : elements) {
        structure.Push(element);
        std::cout << element << "  ";
    }
    std::cout << "\n";

    std::cout << "Размер стр-ры: " << structure.GetSize() << "\n";

    T topElement;
    if (structure.Peek(topElement)) {
        std::cout << "Элемент (верхний): " << topElement << "\n";
    }

    std::cout << "Извлечение эл-в из стр-ры: ";
    while (structure.GetSize() > 0) {
        structure.Peek(topElement);
        std::cout << topElement << "  ";
        structure.Pop(topElement);
    }
    std::cout << "\n";
};


int main() {

    std::cout << "\n" << "Стек на основе однонаправленного списка" << "\n";
    Dynamic_Structures::StackBasedOnUnidirectionalLinkedList<int> intStack;
    demonstrate(intStack, { 1, 2, 3, 4, 5});

    std::cout << "\n" <<"Стек на основе двунаправленного циклического списка" << "\n";
    Dynamic_Structures::StackBasedOnUnidirectionalLinkedList<double> doubleStack;
    demonstrate(doubleStack, { 1.1, 2.2, 3.3, 4.4, 5.5 });

	return 0;
}