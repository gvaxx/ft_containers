#ifndef BIDERECTIONAL_H
#define BIDERECTIONAL_H

#include <iterator>
#include "list.hpp"

namespace ft{
    template<typename ValueType>
    class BidirectionalIterator: public std::iterator<
        std::bidirectional_iterator_tag,
        ValueType,
        std::ptrdiff_t,
        ValueType*,
        ValueType&
    >
    {
	    template<class> friend class list;

    protected:
        Node<ValueType>*		 p;

    public:
        BidirectionalIterator(): p(NULL) {}
        BidirectionalIterator(Node<ValueType>* p) : p(p) {};
        BidirectionalIterator(const BidirectionalIterator &it) :p(it.p) {};
        ~BidirectionalIterator(void) {}

		BidirectionalIterator					&operator=(const BidirectionalIterator &rhs)
		{
			this->p = rhs.p;
			return (*this);
		}

		BidirectionalIterator					&operator++(void)
		{
			this->p = p->next;
			return (*this);
		}

		BidirectionalIterator					operator++(int)
		{
			BidirectionalIterator tmp = *this;
			this->operator++();	
			return (tmp);
		}

		BidirectionalIterator					&operator--(void)
		{
			this->p = p->prev;
			return (*this);
		}

		BidirectionalIterator					operator--(int)
		{
			BidirectionalIterator tmp = *this;
			this->operator--();
			return (tmp);
		}

		bool						operator==(const BidirectionalIterator &rhs) const
		{
			return (p == rhs.p);
		}

		bool						operator!=(const BidirectionalIterator &rhs) const
		{
			return !(p == rhs.p);
		}

		ValueType					&operator*(void)
		{
			return (p->value);
		}

		ValueType					*operator->(void)
		{ 
			return (&(p->value));
		}
		private:
			Node<ValueType>* getNode()
			{
				return (p);
			}
	};

    template<typename ValueType>
    class BidirectionalReverseIterator : public BidirectionalIterator<ValueType>
    {
    public:
	    BidirectionalReverseIterator():BidirectionalIterator<ValueType>() {}
	    BidirectionalReverseIterator(ValueType* p): BidirectionalIterator<ValueType>(p) {}
        BidirectionalReverseIterator(const BidirectionalReverseIterator &it):BidirectionalIterator<ValueType>(it) {}
        ~BidirectionalReverseIterator(void) {}

		BidirectionalReverseIterator					&operator++(void)
		{
			this->p->prev;
			return (*this);
		}

		BidirectionalReverseIterator					operator++(int)
		{
			BidirectionalReverseIterator tmp = *this;
			this->operator++();
			return (tmp);
		}

		BidirectionalReverseIterator					&operator--(void)
		{
			this->p->next;
			return (*this);
		}

		BidirectionalReverseIterator					operator--(int)
		{
			BidirectionalReverseIterator tmp = *this;
			this->operator--();
			return (tmp);
		}
	};
}

#endif // BIDERECTIONAL_H