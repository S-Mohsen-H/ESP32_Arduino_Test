#ifndef __MEMPOOL_LINEAR__HPP__
#define __MEMPOOL_LINEAR__HPP__

#include <memory>

template <typename T, unsigned int N> class mempool_linear
{
	private:
		typedef unsigned int size_type; // convinience
	private:
		uint8_t buf[sizeof(T)*N]; // the memory, the objects are stored here
		bool state[N]; // true if the memory chunk is occupied, false if it is free
	public:
		void init()
		{
			// initially all memory chunks are free
			for (size_type i = 0; i < N; ++i) state[i] = false;
		}

		void * allocate()
		{
			// search linearily through the array to find an unused
			// memory chunk, take it and mark it occupied
			for (size_type i = 0; i < N; ++i)
				if (!state[i]) {
					state[i] = true;
					return &buf[sizeof(T)*i];
				}

			// no free memory chunks could be found
			throw std::bad_alloc();
		}

		void deallocate(void * p)
		{
			// search all memory chunks to find the one to be freed,
			// then mark it as not occupied.
			// please note: this could have been done with pointer arithmetic,
			// to gain more efficiency, but is not done here intentionally.
			for (size_type i = 0; i < N; ++i)
				if (&buf[sizeof(T)*i] == p) {
					state[i] = false;
					return;
				}
		}
};

#endif
