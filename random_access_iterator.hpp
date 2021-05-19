#ifndef FTITERATOR_H
#define FTITERATOR_H

#include <iterator>

namespace ft{

    template<class ValueType>
    class RandomAccessIterator: public std::iterator<
        std::random_access_iterator_tag,
        ValueType,
        std::ptrdiff_t,
        ValueType*,
        ValueType&
    >
    {
    protected:
        ValueType*		 p;
    public:
        RandomAccessIterator(): p(NULL) {}
        RandomAccessIterator(ValueType* p) : p(p) {};
        RandomAccessIterator(const RandomAccessIterator &it) :p(it.p) {};
        ~RandomAccessIterator(void) {}

		RandomAccessIterator					&operator=(const RandomAccessIterator &rhs)
		{
			this->p = rhs.p;
			return (*this);
		}

		RandomAccessIterator					&operator++(void)
		{
			this->p++;
			return (*this);
		}

		RandomAccessIterator					operator++(int)
		{
			RandomAccessIterator tmp = *this;
			this->operator++();	
			return (tmp);
		}

		RandomAccessIterator					&operator--(void)
		{
			this->p--;
			return (*this);
		}

		RandomAccessIterator					operator--(int)
		{
			RandomAccessIterator tmp = *this;
			this->operator--();
			return (tmp);
		}

		bool						operator==(const RandomAccessIterator &rhs) const
		{
			return (p == rhs.p);
		}

		bool						operator!=(const RandomAccessIterator &rhs) const
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

		RandomAccessIterator					operator+(int n) const
		{
			RandomAccessIterator		iter(p + n);
			return (iter);
		}

		RandomAccessIterator					operator-(int n) const
		{
			RandomAccessIterator		iter(p - n);
			return (iter);
		}

		bool						operator<(const RandomAccessIterator &rhs) const
		{
			return (p < rhs.p);
		}

		bool						operator>(const RandomAccessIterator &rhs) const
		{
			return (p > rhs.p);
		}

		bool						operator<=(const RandomAccessIterator &rhs) const
		{
			return (p <= rhs.p);
		}

		bool						operator>=(const RandomAccessIterator &rhs) const
		{
			return (p >= rhs.p);
		}

		RandomAccessIterator					&operator+=(int n)
		{
			p = p + n;
			return (*this);
		}

		friend RandomAccessIterator		operator+(int n, const RandomAccessIterator &rhs)
		{
			return rhs.operator+(n);
		};

		RandomAccessIterator					&operator-=(int n)
		{
			p = p - n;
			return (*this);
		}

		ValueType					&operator[](int n) const
		{
			return (*(*this + n));
		}

		typename  RandomAccessIterator::pointer
									getPtr(void) const
		{
			return (p);
		}

		typename  RandomAccessIterator::difference_type operator-(const RandomAccessIterator rhs) const
		{
			return (p - rhs.p);
		}
	};

    template<typename ValueType>
    class RandomAccessReverseIterator : public RandomAccessIterator<ValueType>
    {
    private:
    public:
	    RandomAccessReverseIterator():RandomAccessIterator<ValueType>() {}
	    RandomAccessReverseIterator(ValueType* p):RandomAccessIterator<ValueType>(p) {}
        RandomAccessReverseIterator(const RandomAccessReverseIterator &it):RandomAccessIterator<ValueType>(it) {}
        ~RandomAccessReverseIterator(void) {}
		RandomAccessReverseIterator					&operator++(void)
		{
			this->p--;
			return (*this);
		}

		RandomAccessReverseIterator					operator++(int)
		{
			RandomAccessReverseIterator tmp = *this;
			this->operator++();
			return (tmp);
		}

		RandomAccessReverseIterator					&operator--(void)
		{
			this->p++;
			return (*this);
		}

		RandomAccessReverseIterator					operator--(int)
		{
			RandomAccessReverseIterator tmp = *this;
			this->operator--();
			return (tmp);
		}

		RandomAccessReverseIterator					operator+(int n) const
		{
			RandomAccessReverseIterator		iter(this->p - n);
			return (iter);
		}

		RandomAccessReverseIterator					operator-(int n) const
		{
			RandomAccessReverseIterator		iter(this->p + n);
			return (iter);
		}

		RandomAccessReverseIterator					&operator+=(int n)
		{
			this->p = this->p - n;
			return (*this);
		}

		RandomAccessReverseIterator					&operator-=(int n)
		{
			this->p = this->p + n;
			return (*this);
		}

		ValueType					&operator[](int n) const
		{
			return (*(*this - n));
		}

		typename RandomAccessIterator<ValueType>::difference_type operator-(const RandomAccessReverseIterator rhs) const
		{
			return (this->p - rhs.p);
		}
	};
}

#endif // FTITERATOR_H