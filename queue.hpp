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

	protected:
		container_type container;
	public:
		queue(container_type const &container=container_type()): container(container) {}
		queue(queue<value_type, container_type> const &other): container(other.container) {}
		virtual ~queue() {}

		queue &operator=(queue const &other)
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

		reference front(void)
		{
			return (this->container.front());
		}

		const_reference front(void) const
		{
			return (this->container.front());
		}

		reference back(void)
		{
			return (this->container.back());
		}

		const_reference back(void) const
		{
			return (this->container.back());
		}

		void push(const_reference val)
		{
			this->container.push_back(val);
		}
		void pop(void)
		{
			this->container.pop_front();
		}
	};

	template<typename T, typename C>
	bool operator==(queue<T, C> const &lhs, queue<T, C> const &rhs)
	{
		return (lhs.container == rhs.container);
	}

	template<typename T, typename C>
	bool operator!=(queue<T, C> const &lhs, queue<T, C> const &rhs)
	{
		return (lhs.container != rhs.container);
	}

	template<typename T, typename C>
	bool operator<(queue<T, C> const &lhs, queue<T, C> const &rhs)
	{
		return (lhs.container < rhs.container);
	}

	template<typename T, typename C>
	bool operator<=(queue<T, C> const &lhs, queue<T, C> const &rhs)
	{
		return (lhs.container <= rhs.container);
	}

	template<typename T, typename C>
	bool operator>(queue<T, C> const &lhs, queue<T, C> const &rhs)
	{
		return (lhs.container > rhs.container);
	}

	template<typename T, typename C>
	bool operator>=(queue<T, C> const &lhs, queue<T, C> const &rhs)
	{
		return (lhs.container >= rhs.container);
	}
}

#endif