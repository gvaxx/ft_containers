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
    protected:
        ValueType*		 p;
        FtIterator(void) {}

    public:
        FtIterator(ValueType* p) : p(p) {};
        FtIterator(const FtIterator &it) :p(it.p) {};
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

    template<typename ValueType>
    class FtReverseIterator : public FtIterator<ValueType>
    {
    private:
	    FtReverseIterator() {}
    public:
	    FtReverseIterator(ValueType* p) {this->p = p;}
        FtReverseIterator(const FtReverseIterator &it) {this->p = it.p;}
        ~FtReverseIterator(void) {}
		FtReverseIterator					&operator++(void)
		{
			this->p--;
			return (*this);
		}

		FtReverseIterator					operator++(int)
		{
			FtReverseIterator tmp = *this;
			this->operator++();
			return (tmp);
		}

		FtReverseIterator					&operator--(void)
		{
			this->p++;
			return (*this);
		}

		FtReverseIterator					operator--(int)
		{
			FtReverseIterator tmp = *this;
			this->operator--();
			return (tmp);
		}

		FtReverseIterator					operator+(int n) const
		{
			FtReverseIterator		iter(this->p - n);
			return (iter);
		}

		FtReverseIterator					operator-(int n) const
		{
			FtReverseIterator		iter(this->p + n);
			return (iter);
		}

		FtReverseIterator					&operator+=(int n)
		{
			this->p = this->p - n;
			return (*this);
		}

		FtReverseIterator					&operator-=(int n)
		{
			this->p = this->p + n;
			return (*this);
		}

		ValueType					&operator[](int n) const
		{
			return (*(*this - n));
		}

		typename FtIterator<ValueType>::difference_type operator-(const FtReverseIterator rhs) const
		{
			return (this->p - rhs.p);
		}
	};
}

#endif // FTITERATOR_H