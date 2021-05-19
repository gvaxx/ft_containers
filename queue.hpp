#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "list.hpp"
# include <queue>

namespace ft
{
	template<typename T, typename Container = ft::list<T> >
	class queue
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
		queue(container_type const &container=container_type()): c(container) {}
		queue(queue<value_type, container_type> const &other): c(other.c) {}
		virtual ~queue() {}

		queue &operator=(queue const &other)
		{
			this->c = other.c;
			return (*this);
		}

		bool empty(void) const
		{
			return (this->c.empty());
		}

		size_t size(void) const
		{
			return (this->c.size());
		}

		reference front(void)
		{
			return (this->c.front());
		}

		const_reference front(void) const
		{
			return (this->c.front());
		}

		reference back(void)
		{
			return (this->c.back());
		}

		const_reference back(void) const
		{
			return (this->c.back());
		}

		void push(const_reference val)
		{
			this->c.push_back(val);
		}

		void pop(void)
		{
			this->c.pop_front();
		}
	};

	template<typename T, typename C>
	bool operator==(queue<T, C> const &lhs, queue<T, C> const &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template<typename T, typename C>
	bool operator!=(queue<T, C> const &lhs, queue<T, C> const &rhs)
	{
		return (lhs.c != rhs.c);
	}

	template<typename T, typename C>
	bool operator<(queue<T, C> const &lhs, queue<T, C> const &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template<typename T, typename C>
	bool operator<=(queue<T, C> const &lhs, queue<T, C> const &rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template<typename T, typename C>
	bool operator>(queue<T, C> const &lhs, queue<T, C> const &rhs)
	{
		return (lhs.c > rhs.c);
	}

	template<typename T, typename C>
	bool operator>=(queue<T, C> const &lhs, queue<T, C> const &rhs)
	{
		return (lhs.c >= rhs.c);
	}
}

#endif