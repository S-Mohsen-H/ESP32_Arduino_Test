#ifndef __MEMORY_POOL__HPP__
#define __MEMORY_POOL__HPP__

#include <memory>

template <typename T, class Strategy> class memory_pool
{
	private:
		Strategy s;
	public:
		memory_pool()
		{
			s.init();
		}

		void * alloc(unsigned int n)
		{
			if (sizeof(T) != n) throw std::bad_alloc();
			return s.allocate();
		}

		void free(void * p)
		{
			s.deallocate(p);
		}
};

#endif
