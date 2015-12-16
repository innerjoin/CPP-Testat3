#ifndef TESTAT3_INDEXABLESET_H
#define TESTAT3_INDEXABLESET_H

#include <set>
#include <stdexcept>

template <typename T, typename COMPARE=std::less<T>>
class IndexableSet : public std::set<T, COMPARE> {
    using IdxSet = std::set<T, COMPARE>;

public:
    using IdxSet::set;

    T const & front() const {
        return at(0);
    }

    T const & back() const {
        return at(-1);
    }

    T const & at(int index) const {
        if(index < 0)
            index += this->size();
        if(static_cast<unsigned>(index) >= this->size())
            throw std::out_of_range{"index out of range!!"};
        return *std::next(this->begin(), index);
    }

    T const & operator[](int index) const {
        return at(index);
    }
};

#endif //TESTAT3_INDEXABLESET_H
