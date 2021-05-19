
#ifndef FT_STACK
#define FT_STACK
# include "list.hpp"
# include <stack>

namespace ft
{
	template<typename T, typename Container = ft::list<T> >
	class stack
	{
		public:
			typedef size_t size_type;
			typedef T value_type;
			typedef Container container_type;
			typedef T* pointer;
			typedef T const * const_pointer;
			typedef T& reference;
			typedef T const & const_reference;
			container_type c;

		public:
			stack(container_type const &container = container_type()): c(container) {}
			stack(stack const &other): c(other.c) {}
			virtual ~stack() {}

			stack &operator=(stack const &other)
			{
				c = other.c;
				return (*this);
			}

			bool empty(void) const
			{
				return (c.empty());
			}

			size_t size(void) const
			{
				return (c.size());
			}

			reference top(void)
			{
				return (c.back());
			}

			void push(const_reference val)
			{
				c.push_back(val);
			}

			void pop(void)
			{
				c.pop_back();
			}
	};

	template<typename T, typename C>
	bool operator==(stack<T, C> const &lhs, stack<T, C> const &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template<typename T, typename C>
	bool operator!=(stack<T, C> const &lhs, stack<T, C> const &rhs)
	{
		return (lhs.c != rhs.c);
	}

	template<typename T, typename C>
	bool operator<(stack<T, C> const &lhs, stack<T, C> const &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template<typename T, typename C>
	bool operator<=(stack<T, C> const &lhs, stack<T, C> const &rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template<typename T, typename C>
	bool operator>(stack<T, C> const &lhs, stack<T, C> const &rhs)
	{
		return (lhs.c > rhs.c);
	}

	template<typename T, typename C>
	bool operator>=(stack<T, C> const &lhs, stack<T, C> const &rhs) {
		return (lhs.c >= rhs.c);
	}
}

#endif