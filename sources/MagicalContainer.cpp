#include "MagicalContainer.hpp"
#include <algorithm>
#include <vector>
#include <stdexcept>

namespace ariel
{
    MagicalContainer::MagicalContainer()
    {
        // Constructor is simplified: we just initialize 'elements'
        elements = std::vector<int>();
    }

    MagicalContainer::~MagicalContainer()
    {
    }

    bool MagicalContainer::addElement(int newElement)
    {
        // Insert the new element in the correct place to maintain ascending order
        elements.insert(std::upper_bound(elements.begin(), elements.end(), newElement), newElement);

        // The iterators are no longer valid, so we reset them
        ascendingIterator.setCurrentElement(nullptr);
        sideCrossIterator.setCurrentElement(nullptr);
        primeIterator.setCurrentElement(nullptr);

        return true;
    }
    bool MagicalContainer::removeElement(int element)
    {
        auto it = std::find(elements.begin(), elements.end(), element);
        if (it != elements.end())
        {
            elements.erase(it);

            // Update the iterators after modifying the container
            ascendingIterator.setCurrentElement(nullptr);
            sideCrossIterator.setCurrentElement(nullptr);
            primeIterator.setCurrentElement(nullptr);

            return true;
        }
        else
        {
            throw std::runtime_error("Element not found in container");
        }
    }

    std::vector<int> MagicalContainer::getElements() const
    {
        return this->elements;
    }

    int MagicalContainer::size() const
    {
        return this->elements.size();
    }

    MagicalContainer::AscendingIterator& MagicalContainer::getAscendingIterator()
    {
        return this->ascendingIterator;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::getSideCrossIterator()
    {
        return this->sideCrossIterator;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::getPrimeIterator()
    {
        return this->primeIterator;
    }

    // AscendingIterator
    MagicalContainer::AscendingIterator::AscendingIterator() : container(nullptr), currElement(nullptr)
    {
    }

    // AscendingIterator
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container)
            : container(&container)
    {
        if (!container.elements.empty())
        {
            currElement = container.elements.begin(); // It should start from the smallest element
        }
        else
        {
            currElement = container.elements.end(); // If container is empty, currElement is end
        }
    }
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other) : currElement(other.currElement)
    {
    }

    MagicalContainer::AscendingIterator::~AscendingIterator()
    {
    }

    int& MagicalContainer::AscendingIterator::operator*()
    {
        if (currElement != container->elements.end())
        {
            return *currElement;
        }
        else
        {
            throw std::runtime_error("Iterator out of bounds");
        }
    }


    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++()
    {
        if (currElement != container->elements.end())
        {
            ++currElement;
        }
        else
        {
            throw std::runtime_error("Iterator out of bounds");
        }
        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::begin() {
        currElement = container->elements.begin(); // or wherever the beginning is for this iterator
        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::end() {
        currElement = container->elements.end(); // or wherever the end is for this iterator
        return *this;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if (this != &other)
        {
            if (container != other.container) {
                throw std::runtime_error("Assigning iterators from different containers is not allowed!");
            }
            container = other.container;
            currElement = other.currElement;
        }
        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(AscendingIterator&& other) noexcept
    {
        if (this != &other)
        {
            other.container = nullptr;
            other.currElement = container->elements.end();
        }
        return *this;
    }

    MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator&& other) noexcept
            : container(other.container), currElement(other.currElement)
    {
        other.container = nullptr;
        other.currElement = container->elements.end();
    }



    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const
    {
        return currElement == other.currElement;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const
    {
        return currElement < other.currElement;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const
    {
        // Return true if the current iterator has moved further than the other iterator.
        return currElement > other.currElement;
    }


    // SideCrossIterator
    MagicalContainer::SideCrossIterator::SideCrossIterator()
            : Iterator(), container(nullptr), currStartElement(nullptr),
              currEndElement(nullptr), fromStart(true), progress(0)
    {
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container)
            : Iterator(), container(&container), currStartElement(nullptr),
              currEndElement(nullptr), fromStart(true), progress(0)
    {
        if (!container.elements.empty())
        {
            currStartElement = container.elements.begin();
            currEndElement = container.elements.end() - 1;
        }
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
            : Iterator(), container(other.container), currStartElement(other.currStartElement),
              currEndElement(other.currEndElement), fromStart(other.fromStart),
              progress(other.progress)
    {
    }

    MagicalContainer::SideCrossIterator::~SideCrossIterator()
    {
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other)
    {
        if (this != &other)
        {
            if (container != other.container) {
                throw std::runtime_error("Assigning iterators from different containers is not allowed!");
            }
            container = other.container;
            currStartElement = other.currStartElement;
            currEndElement = other.currEndElement;
            fromStart = other.fromStart;
            progress = other.progress;
        }
        else
        {
            throw std::runtime_error("Assigning iterator to itself is not allowed!");
        }
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const
    {
        return container == other.container && currStartElement == other.currStartElement &&
               currEndElement == other.currEndElement && fromStart == other.fromStart &&
               progress == other.progress;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const
    {
        if (container != other.container)
        {
            throw std::runtime_error("Comparing iterators from different containers is not allowed!");
        }

        if (fromStart && !other.fromStart)
        {
            return true; // This iterator is at the start, while the other is at the end
        }
        else if (!fromStart && other.fromStart)
        {
            return false; // This iterator is at the end, while the other is at the start
        }
        else
        {
            return progress < other.progress; // Compare the progress of the iterators
        }
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const
    {
        if (container != other.container)
        {
            throw std::runtime_error("Comparing iterators from different containers is not allowed!");
        }

        return other < *this; // Inverse of the < operator
    }

    int& MagicalContainer::SideCrossIterator::operator*()
    {
        if (fromStart)
        {
            if (*currStartElement)
            {
                return *currStartElement;
            }
        }
        else
        {
            if (*currEndElement)
            {
                return *currEndElement;
            }
        }
        throw std::runtime_error("Iterator out of bounds");
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        if (fromStart) {
            if (currStartElement != container->elements.end()) {
                ++currStartElement;
                fromStart = false;
                ++progress;
                return *this;
            }
        } else {
            if (currEndElement != container->elements.begin() - 1) {
                --currEndElement;
                fromStart = true;
                ++progress;
                return *this;
            }
        }
        throw std::runtime_error("Iterator out of bounds");
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::begin() {
        currStartElement = container->elements.begin(); // Adjust to your implementation details
        currEndElement = container->elements.end(); // Adjust to your implementation details
        fromStart = true; // Reset to the starting state
        progress = 0; // Reset to the starting state
        return *this;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::end() {
        currStartElement = container->elements.end(); // Or wherever the "end" is for this iterator
        currEndElement = container->elements.end(); // Or wherever the "end" is for this iterator
        return *this;
    }




    MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator&& other) noexcept
            : Iterator(), container(other.container), currStartElement(other.currStartElement),
              currEndElement(other.currEndElement), fromStart(other.fromStart),
              progress(other.progress)
    {
        other.currStartElement = container->elements.end();
        other.currEndElement = container->elements.end();
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(SideCrossIterator&& other) noexcept
    {
        if (this != &other)
        {
            container = other.container;
            fromStart = other.fromStart;
            progress = other.progress;
            other.currStartElement = container->elements.end();
            other.currEndElement = container->elements.end();
        }
        return *this;
    }

    // PrimeIterator
    MagicalContainer::PrimeIterator::PrimeIterator()
            : Iterator(), container(nullptr), currElement()
    {
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container)
            : Iterator(), container(&container), currElement(container.elements.end())
    {
        if (container.elements.empty())
        {
            return;
        }

        currElement = container.elements.begin();
        while (currElement != container.elements.end() && !isPrime(*currElement))
        {
            ++currElement;
        }
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
            : Iterator(), container(other.container), currElement(other.currElement)
    {
    }

    MagicalContainer::PrimeIterator::~PrimeIterator()
    {
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other)
    {
        if (this != &other)
        {
            if (container != other.container) {
                throw std::runtime_error("Assigning iterators from different containers is not allowed!");
            }
            container = other.container;
            currElement = other.currElement;
        }
        else{
            throw std::runtime_error("Cannot assign to itself");
        }
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const
    {
        return currElement == other.currElement;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const
    {
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const
    {
        return currElement < other.currElement;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const
    {
        return currElement > other.currElement;
    }

    int& MagicalContainer::PrimeIterator::operator*()
    {
        if (currElement != container->elements.end())
        {
            return *currElement;
        }
        throw std::out_of_range("Attempting to dereference end iterator");
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++()
    {
        if (currElement != container->elements.end())
        {
            ++currElement;
            while (currElement != container->elements.end() && !isPrime(*currElement))
            {
                ++currElement;
            }
        }
        else
        {
            throw std::runtime_error("Iterator out of bounds");
        }
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::begin() {
        currElement = container->elements.begin(); // Adjust to your implementation details
        currElement = container->elements.end(); // Adjust to your implementation details
        fromStart = true; // Reset to the starting state
        progress = 0; // Reset to the starting state
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::end() {
        currElement = container->elements.end(); // Or wherever the "end" is for this iterator
        currElement = container->elements.end(); // Or wherever the "end" is for this iterator
        return *this;
    }


    MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator&& other) noexcept
            : Iterator(), container(other.container), currElement(other.currElement)
    {
        other.currElement = other.container->elements.end();
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(PrimeIterator&& other) noexcept
    {
        if (this != &other)
        {
            container = other.container;
            currElement = other.currElement;
            other.currElement = other.container->elements.end();
        }

        return *this;
    }
    bool MagicalContainer::PrimeIterator::isPrime(int num){
        if(num <= 1){
            return false;
        }
        for(int i = 2; i < num; i++){
            if(num % i == 0){
                return false;
            }
        }
        return true;
    }

}