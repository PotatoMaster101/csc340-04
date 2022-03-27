//  LinkedBag.cpp
//  Created by Frank M. Carrano and Timothy M. Henry.
//  Updated by Duc Ta
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include <cstddef>
#include <iostream>
#include "Node.h"
#include "LinkedBag.h"

template<typename ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0) {}

template<typename ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag) {
    itemCount = aBag.itemCount;
    auto origChainPtr = aBag.headPtr;

    if (origChainPtr == nullptr) {
        headPtr = nullptr;
    }
    else {
        headPtr = std::make_shared<Node<ItemType>>();
        headPtr->setItem(origChainPtr->getItem());

        auto newChainPtr = headPtr;
        origChainPtr = origChainPtr->getNext();

        while (origChainPtr != nullptr)
        {
            ItemType nextItem = origChainPtr->getItem();
            auto newNodePtr = std::make_shared<Node<ItemType>>(nextItem);
            newChainPtr->setNext(newNodePtr);
            newChainPtr = newChainPtr->getNext();
            origChainPtr = origChainPtr->getNext();
        }

        newChainPtr->setNext(nullptr);
    }
}

template<typename ItemType>
LinkedBag<ItemType>::~LinkedBag() {
    std::cout << "LinkedBag<ItemType>::~LinkedBag() called (count = " << itemCount << ")\n";
    clear();
}

template<typename ItemType>
bool LinkedBag<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize() const {
    return itemCount;
}

template<typename ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry) {
    auto nextNodePtr = std::make_shared<Node<ItemType>>(newEntry);
    nextNodePtr->setNext(headPtr);
    headPtr = nextNodePtr;
    itemCount++;
    return true;
}

template<typename ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const {
    std::vector<ItemType> bagContents;
    auto curPtr = headPtr;
    int counter = 0;

    while ((curPtr != nullptr) && (counter < itemCount)) {
        bagContents.push_back(curPtr->getItem());
        curPtr = curPtr->getNext();
        counter++;
    }

    return bagContents;
}

template<typename ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry) {
    auto entryNodePtr = getPointerTo(anEntry);
    bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);

    if (canRemoveItem) {
        entryNodePtr->setItem(headPtr->getItem());
        auto nodeToDeletePtr = headPtr;
        headPtr = headPtr->getNext();

        nodeToDeletePtr->setNext(nullptr);
        itemCount--;
    }

    return canRemoveItem;
}

template<typename ItemType>
void LinkedBag<ItemType>::clear() {
    while (headPtr != nullptr) {
        auto toDelete = headPtr;
        headPtr = headPtr->getNext();
        toDelete->setNext(nullptr);
    }

    itemCount = 0;
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const {
    int frequency = 0;
    int counter = 0;
    auto curPtr = headPtr;

    while ((curPtr != nullptr) && (counter < itemCount)) {
        if (anEntry == curPtr->getItem()) {
            frequency++;
        }
        counter++;
        curPtr = curPtr->getNext();
    }

    return frequency;
}

template<typename ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const {
    return (getPointerTo(anEntry) != nullptr);
}

template<typename ItemType>
std::shared_ptr<Node<ItemType>> LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const {
    bool found = false;
    auto curPtr = headPtr;

    while (!found && (curPtr != nullptr)) {
        if (anEntry == curPtr->getItem()) {
            found = true;
        }
        else {
            curPtr = curPtr->getNext();
        }
    }

    return curPtr;
}
