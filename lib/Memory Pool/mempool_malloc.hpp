#ifndef __MEMPOOL_MALLOC__HPP__
#define __MEMPOOL_MALLOC__HPP__

#include <memory>

template <typename T> class mempool_malloc
{
	public:
		void init() {}

		void * allocate()
		{
			return ::malloc(sizeof(T));
		}

		void deallocate(void * p)
		{
			::free(p);
		}
};

#endif
