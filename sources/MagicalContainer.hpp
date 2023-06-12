#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP

#include <iostream>
#include <vector>
#include <cmath>

namespace ariel
{
    using namespace std;

    // User-defined container class that can store integers representing mystical elements
    class MagicalContainer
    {
    private:

        class Iterator {
        private:
            int *currElement;

        public:
            Iterator() : currElement(nullptr) {};
            Iterator(const Iterator &other) = delete;
            virtual ~Iterator() = default;
            virtual int &operator*() = 0;
            virtual Iterator &operator++() = 0;
            Iterator &operator=(const Iterator &other) = delete;
            Iterator &operator=(Iterator &&other) = delete;
            Iterator(Iterator &&other) noexcept = delete;
            virtual Iterator &begin() = 0;
            virtual Iterator &end() = 0;

            void setCurrentElement(int *element) {
                currElement = element;
            }
        };


    public:
        // Iterator class for ascending order
        class AscendingIterator : public Iterator
        {
        private:
            MagicalContainer *container;
            vector<int>::iterator currElement;

        public:
            AscendingIterator();
            AscendingIterator(MagicalContainer &container);
            AscendingIterator(const AscendingIterator &other);
            ~AscendingIterator() override;
            AscendingIterator &operator=(const AscendingIterator &other);
            AscendingIterator &operator=(AscendingIterator &&other) noexcept; // Move assignment operator
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            bool operator>(const AscendingIterator &other) const;
            int &operator*() override;
            AscendingIterator &operator++() override;
            AscendingIterator& begin() override;
            AscendingIterator& end() override;
            AscendingIterator(AscendingIterator &&other) noexcept; // Move constructor
        };

        class SideCrossIterator : public Iterator
        {
        private:
            MagicalContainer *container;
            vector<int>::iterator currStartElement;
            vector<int>::iterator currEndElement;
            bool fromStart; // Flag to track whether to take an element from the start or end
            size_t progress;

        public:
            // Constructor
            SideCrossIterator();
            SideCrossIterator(MagicalContainer &container);
            SideCrossIterator(const SideCrossIterator &other);
            ~SideCrossIterator() override;
            SideCrossIterator &operator=(const SideCrossIterator &other);
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            int &operator*() override;
            SideCrossIterator &operator++() override;
            SideCrossIterator &begin() override;
            SideCrossIterator &end() override;
            SideCrossIterator(SideCrossIterator &&other) noexcept;
            SideCrossIterator &operator=(SideCrossIterator &&other) noexcept;
        };


        class PrimeIterator : public Iterator
        {
        private:
            MagicalContainer *container;
            vector<int>::iterator currElement;
            bool fromStart; // Flag to track whether to take an element from the start or end
            size_t progress;
            static bool isPrime(int num);

        public:
            // Constructor
            PrimeIterator();
            PrimeIterator(MagicalContainer &container);
            PrimeIterator(const PrimeIterator &other);
            ~PrimeIterator() override;
            PrimeIterator &operator=(const PrimeIterator &other);
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            bool operator>(const PrimeIterator &other) const;
            int &operator*() override;
            PrimeIterator &operator++() override;
            PrimeIterator &begin() override; // Changed return type to PrimeIterator
            PrimeIterator &end() override; // Changed return type to PrimeIterator
            PrimeIterator(PrimeIterator &&other) noexcept;
            PrimeIterator &operator=(PrimeIterator &&other) noexcept;
            void setToEnd();
        };

        vector<int> elements;
        AscendingIterator ascendingIterator;
        SideCrossIterator sideCrossIterator;
        PrimeIterator primeIterator;

        MagicalContainer();  // Magic container constructor
        ~MagicalContainer(); // Magic container destructor
        bool addElement(int element);
        bool removeElement(int element);
        vector<int> getElements() const;
        int size() const;
        AscendingIterator &getAscendingIterator();
        SideCrossIterator &getSideCrossIterator();
        PrimeIterator &getPrimeIterator();

        MagicalContainer(const MagicalContainer &other) = delete;
        MagicalContainer &operator=(const MagicalContainer& other)= delete;
        MagicalContainer(MagicalContainer &&other) noexcept = delete;
        MagicalContainer &operator=(MagicalContainer &&other) noexcept = delete;

    };
} // namespace ariel

#endif
