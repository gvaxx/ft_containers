
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
		protected:
			container_type container;

		public:
			stack(container_type const &container=container_type()): container(container) {}
			stack(stack const &other): container(other.container) {}
			virtual ~stack() {}

			stack &operator=(stack const &other)
			{
				this->container = other.container;
				return (*this);
			}

			bool empty(void) const
			{
				return (this->container.empty());
			}

			size_t size(void) const
			{
				return (this->container.size());
			}

			reference top(void)
			{
				return (this->container.back());
			}

			void push(const_reference val)
			{
				this->container.push_back(val);
			}

			void pop(void)
			{
				this->container.pop_back();
			}
	};

	template<typename T, typename C>
	bool operator==(stack<T, C> const &lhs, stack<T, C> const &rhs)
	{
		return (lhs.container == rhs.container);
	}

	template<typename T, typename C>
	bool operator!=(stack<T, C> const &lhs, stack<T, C> const &rhs)
	{
		return (lhs.container != rhs.container);
	}

	template<typename T, typename C>
	bool operator<(stack<T, C> const &lhs, stack<T, C> const &rhs)
	{
		return (lhs.container < rhs.container);
	}

	template<typename T, typename C>
	bool operator<=(stack<T, C> const &lhs, stack<T, C> const &rhs)
	{
		return (lhs.container <= rhs.container);
	}

	template<typename T, typename C>
	bool operator>(stack<T, C> const &lhs, stack<T, C> const &rhs)
	{
		return (lhs.container > rhs.container);
	}

	template<typename T, typename C>
	bool operator>=(stack<T, C> const &lhs, stack<T, C> const &rhs) {
		return (lhs.container >= rhs.container);
	}
}

#endif