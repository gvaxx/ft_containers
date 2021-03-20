#ifndef FTITERATOR_H
#define FTITERATOR_H

#include <iterator>

namespace ft{

    template<typename ValueType>
    class FtIterator: public std::iterator<
        std::random_access_iterator_tag,
        ValueType,
        std::ptrdiff_t,
        ValueType*,
        ValueType&
    >
    {
        FtIterator(void) {}
        ValueType*		 p;

    public:
        FtIterator(ValueType* p) : p(p) {};
        FtIterator(const FtIterator &it) :p(it.p) {};

        // bool operator!=(FtIterator const& other) const {return p != other.p;};
        // bool operator==(FtIterator const& other) const {return p == other.p;};
        // typename FtIterator::reference operator*() const {return *p;};
        // FtIterator& operator++() {p++; return *this;};
        // FtIterator& operator--() {p--; return *this;};
        // FtIterator& operator->() {return p;};
        // FtIterator& operator*() {return *p;};

        ~FtIterator(void) {}

		FtIterator					&operator=(const FtIterator &rhs)
		{
			this->p = rhs.p;
			return (*this);
		}

		FtIterator					&operator++(void)
		{
			this->p++;
			return (*this);
		}

		FtIterator					operator++(int)
		{
			FtIterator tmp = *this;
			this->operator++();	
			return (tmp);
		}

		FtIterator					&operator--(void)
		{
			this->p--;
			return (*this);
		}

		FtIterator					operator--(int)
		{
			FtIterator tmp = *this;
			this->operator--();
			return (tmp);
		}

		bool						operator==(const FtIterator &rhs) const
		{
			return (p == rhs.p);
		}

		bool						operator!=(const FtIterator &rhs) const
		{
			return !(p == rhs.p);
		}

		ValueType					&operator*(void)
		{
			return (*p);
		}

		ValueType					*operator->(void)
		{ 
			return (p);
		}

		FtIterator					operator+(int n) const
		{
			FtIterator		iter(p + n);
			return (iter);
		}

		FtIterator					operator-(int n) const
		{
			FtIterator		iter(p - n);
			return (iter);
		}

		bool						operator<(const FtIterator &rhs) const
		{
			return (p < rhs.p);
		}

		bool						operator>(const FtIterator &rhs) const
		{
			return (p > rhs.p);
		}

		bool						operator<=(const FtIterator &rhs) const
		{
			return (p <= rhs.p);
		}

		bool						operator>=(const FtIterator &rhs) const
		{
			return (p >= rhs.p);
		}

		FtIterator					&operator+=(int n)
		{
			p = p + n;
			return (*this);
		}

		FtIterator					&operator-=(int n)
		{
			p = p - n;
			return (*this);
		}

		ValueType					&operator[](int n) const
		{
			return (*(*this + n));
		}

		typename  FtIterator::pointer
									getPtr(void) const
		{
			return (p);
		}

		typename  FtIterator::difference_type operator-(const FtIterator rhs) const
		{
			return (p - rhs.p);
		}
	};















    template<class T>
    class FtReverseIterator: public FtIterator<T>
    {
    private:
        FtReverseIterator(T *p);
    public:
        FtReverseIterator(const FtReverseIterator &it);

        bool operator!=(FtReverseIterator const& other) const;
        bool operator==(FtReverseIterator const& other) const;
        typename FtReverseIterator::reference operator*() const;
        FtReverseIterator& operator++();
        FtReverseIterator& operator--();
    private:
        T* p;
    };

    // template<typename ValueType>
    // FtReverseIterator<ValueType>::FtReverseIterator(ValueType *p) :
    //     p(p)
    // {}

    // template<typename ValueType>
    // FtReverseIterator<ValueType>::FtReverseIterator(const FtReverseIterator& it) :
    //     p(it.p)
    // {}

    // template<typename ValueType>
    // bool FtReverseIterator<ValueType>::operator!=(FtReverseIterator const& other) const
    // {
    //     return p != other.p;
    // }

    // template<typename ValueType>
    // bool FtReverseIterator<ValueType>::operator==(FtReverseIterator const& other) const
    // {
    //     return p == other.p;
    // }

    // template<typename ValueType>
    // typename FtReverseIterator<ValueType>::reference FtReverseIterator<ValueType>::operator*() const
    // {
    //     return *p;
    // }

    // template<typename ValueType>
    // FtReverseIterator<ValueType> &FtReverseIterator<ValueType>::operator++()
    // {
    //     ++p;
    //     return *this;
    // }

    // template<typename ValueType>
    // FtReverseIterator<ValueType> &FtReverseIterator<ValueType>::operator--()
    // {
    //     --p;
    //     return *this;
    // }
}

#endif // FTITERATOR_H