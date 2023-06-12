#include "MagicalContainer.hpp"
#include <algorithm>
#include <vector>
#include <stdexcept>

namespace ariel
{
    //magic container class that can store integers representing mystical elements
    //constructor
    MagicalContainer::MagicalContainer()
    {
        // Constructor is simplified: we just initialize 'elements' to an empty vector of integers
        elements = std::vector<int>();
    }
    //destructor
    MagicalContainer::~MagicalContainer()
    {
    }
    //add element to the container
    bool MagicalContainer::addElement(int newElement)
    {
        // Insert the new element in the correct place
        elements.insert(std::upper_bound(elements.begin(), elements.end(), newElement), newElement);
        return true;
    }
    //remove element from the container
    bool MagicalContainer::removeElement(int element)
    {
        // Find the element in the container
        auto it = std::find(elements.begin(), elements.end(), element);
        // If the element was found, remove it
        if (it != elements.end())
        {
            // Remove the element from the container
            elements.erase(it);
            return true;
        }
        else
        {
            throw std::runtime_error("Element not found in container");
        }
    }
    //get the number of elements in the container
    std::vector<int> MagicalContainer::getElements() const
    {
        return this->elements;
    }
    //get the number of elements in the container
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
    // AscendingIterator constructor
    MagicalContainer::AscendingIterator::AscendingIterator() : container(nullptr), currElement(nullptr)
    {
    }

    // AscendingIterator constructor with container parameter
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
    // AscendingIterator copy constructor

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
            : container(other.container), currElement(other.currElement)
    {
    }
    // AscendingIterator destructor
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
        // If the iterator is not at the end of the container, move to the next element
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

    //return the begining of the container
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::begin() {
        currElement = container->elements.begin(); // or wherever the beginning is for this iterator
        return *this;
    }
    //return the end of the container
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::end() {
        currElement = container->elements.end(); // or wherever the end is for this iterator
        return *this;
    }
    //operator= for AscendingIterator
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        // Check for self-assignment
        if (this != &other)
        {
            // Check that the iterators are from the same container
            if (container != other.container) {
                throw std::runtime_error("Assigning iterators from different containers is not allowed!");
            }
            container = other.container;
            currElement = other.currElement;
        }
        return *this;
    }
    //noexcept operator= for AscendingIterator
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

    //bool operators for AscendingIterator

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
        // If the container is not empty, initialize the iterator to point to the first and last elements
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
        // Destructor
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other)
    {
        if (this != &other)
        {
            // Check if the iterators belong to different containers
            if (container != other.container) {
                throw std::runtime_error("Assigning iterators from different containers is not allowed!");
            }

            // Copy the values from the other iterator
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
        // Check if the container and progress of the iterators are equal
        return container == other.container && progress == other.progress;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const
    {
        // Inverse of the equality operator
        return !(*this == other);
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const
    {
        // Check if the iterators belong to different containers
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
        // Check if the iterators belong to different containers
        if (container != other.container)
        {
            throw std::runtime_error("Comparing iterators from different containers is not allowed!");
        }

        return other < *this; // Inverse of the < operator
    }

    int& MagicalContainer::SideCrossIterator::operator*() {
        // Dereference operator
        if (fromStart) {
            if (currStartElement <= currEndElement) {
                return *currStartElement;
            }
        } else {
            if (currEndElement >= currStartElement) {
                return *currEndElement;
            }
        }
        throw std::runtime_error("Iterator out of bounds");
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        // Pre-increment operator
        if (fromStart) {
            if (currStartElement <= currEndElement) {
                ++currStartElement;
                ++progress;
                fromStart = false;
            } else {
                throw std::runtime_error("Iterator out of bounds");
            }
        } else {
            if (currEndElement >= currStartElement) {
                --currEndElement;
                ++progress;
                fromStart = true;
            } else {
                throw std::runtime_error("Iterator out of bounds");
            }
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::begin() {
        // Set the iterator to the beginning state
        currStartElement = container->elements.begin();
        currEndElement = container->elements.end() - 1;
        fromStart = true;
        progress = 0;
        return *this;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::end() {
        // Set the iterator to the end state
        currStartElement = container->elements.end();
        currEndElement = container->elements.begin() - 1;
        fromStart = false;
        progress = container->elements.size();
        return *this;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator&& other) noexcept
            : Iterator(), container(other.container), currStartElement(other.currStartElement),
              currEndElement(other.currEndElement), fromStart(other.fromStart),
              progress(other.progress)
    {
        // Move constructor
        other.currStartElement = container->elements.end();
        other.currEndElement = container->elements.end();
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(SideCrossIterator&& other) noexcept
    {
        if (this != &other)
        {
            // Move the values from the other iterator
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
        // Default constructor
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container)
            : Iterator(), container(&container), currElement(container.elements.end())
    {
        // Constructor that takes a container
        if (container.elements.empty())
        {
            return;
        }

        // Initialize the iterator to the first prime element in the container
        currElement = container.elements.begin();
        while (currElement != container.elements.end() && !isPrime(*currElement))
        {
            ++currElement;
        }
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
            : Iterator(), container(other.container), currElement(other.currElement)
    {
        // Copy constructor
    }

    MagicalContainer::PrimeIterator::~PrimeIterator()
    {
        // Destructor
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other)
    {
        if (this != &other)
        {
            // Check if the iterators belong to different containers
            if (container != other.container) {
                throw std::runtime_error("Assigning iterators from different containers is not allowed!");
            }
            // Copy the values from the other iterator
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
        // Check if the current elements of the iterators are equal
        return currElement == other.currElement;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const
    {
        // Inverse of the equality operator
        return !(*this == other);
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const
    {
        // Compare the current elements of the iterators
        return currElement < other.currElement;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const
    {
        // Compare the current elements of the iterators
        return currElement > other.currElement;
    }

    int& MagicalContainer::PrimeIterator::operator*()
    {
        // Dereference operator
        if (currElement != container->elements.end())
        {
            return *currElement;
        }
        throw std::out_of_range("Attempting to dereference end iterator");
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++()
    {
        // Pre-increment operator
        if (currElement != container->elements.end())
        {
            ++currElement;
            // Find the next prime element in the container
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
        // Set the iterator to the beginning state
        currElement = container->elements.begin();
        if (currElement != container->elements.end() && !isPrime(*currElement)) {
            // Find the first prime element in the container
            ++(*this);
        }
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::end() {
        // Set the iterator to the end state
        currElement = container->elements.end();
        return *this;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator&& other) noexcept
            : Iterator(), container(other.container), currElement(other.currElement)
    {
        // Move constructor
        other.currElement = other.container->elements.end();
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(PrimeIterator&& other) noexcept
    {
        if (this != &other)
        {
            // Move the values from the other iterator
            container = other.container;
            currElement = other.currElement;
            other.currElement = other.container->elements.end();
        }

        return *this;
    }

    bool MagicalContainer::PrimeIterator::isPrime(int num){
        // Function to check if a number is prime
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
