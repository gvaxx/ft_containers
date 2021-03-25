namespace ft
{
	template <class T>
	void swap_value(T & x, T & y)
	{
		T tmp = x;
		x = y;
		y = tmp;
	}
} // namespace ft
