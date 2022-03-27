#include <random>
#include "LinkedBag.h"

template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340() {
    if (itemCount < 2)
        return false;

    auto secondNode = headPtr->getNext();
    headPtr->setNext(secondNode->getNext());
    secondNode->setNext(nullptr);
    itemCount--;
    return true;
}

template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType& item) {
    if (isEmpty())
        return add(item);       // let `add` handle empty

    auto currentNode = headPtr;
    while (currentNode->getNext() != nullptr)
        currentNode = currentNode->getNext();

    currentNode->setNext(std::make_shared<Node<ItemType>>(item));
    itemCount++;
    return true;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const {
    auto size = 0;
    auto currentNode = headPtr;
    while (currentNode != nullptr) {
        currentNode = currentNode->getNext();
        size++;
    }
    return size;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const {
    return getCurrentSize340RecursiveHelper(headPtr);
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const {
    static auto currentNode = headPtr;
    if (currentNode == nullptr)
        return 0;

    auto backup = currentNode;
    currentNode = currentNode->getNext();
    auto size = 1 + getCurrentSize340RecursiveNoHelper();
    currentNode = backup;
    return size;
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType& item) const {
    return getFrequencyOf340RecursiveHelper(headPtr, item);
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType& item) const {
    static auto currentNode = headPtr;
    if (currentNode == nullptr)
        return 0;

    auto backup = currentNode;
    auto toAdd = currentNode->getItem() == item ? 1 : 0;
    currentNode = currentNode->getNext();
    auto frequency = toAdd + getFrequencyOf340RecursiveNoHelper(item);
    currentNode = backup;
    return frequency;
}

template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340() {
    if (isEmpty())
        return ItemType{};

    std::mt19937 randEng{std::random_device{}()};
    auto randIndex = std::uniform_int_distribution<int>{0, itemCount - 1}(randEng);
    auto currentPtr = headPtr;
    auto previousPtr= headPtr;
    for (auto i = 0; i < randIndex; i++) {
        previousPtr = currentPtr;
        currentPtr = currentPtr->getNext();
    }

    auto data = currentPtr->getItem();
    if (randIndex == 0) {
        headPtr = headPtr->getNext();
        currentPtr->setNext(nullptr);
    } else {
        previousPtr->setNext(currentPtr->getNext());
        currentPtr->setNext(nullptr);
    }

    --itemCount;
    return data;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(std::shared_ptr<Node<ItemType>> node) const {
    if (node == nullptr)
        return 0;

    auto nextNode = node->getNext();
    return nextNode == nullptr ? 1 : 1 + getCurrentSize340RecursiveHelper(nextNode);
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(std::shared_ptr<Node<ItemType>> node, const ItemType& item) const {
    if (node == nullptr)
        return 0;

    auto nextNode = node->getNext();
    auto toAdd = node->getItem() == item ? 1 : 0;
    return toAdd + getFrequencyOf340RecursiveHelper(nextNode, item);
}
