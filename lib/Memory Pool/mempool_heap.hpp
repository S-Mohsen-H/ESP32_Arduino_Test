#ifndef __MEMPOOL_HEAP__HPP__
#define __MEMPOOL_HEAP__HPP__

#include <memory>

template <typename T, unsigned int N> class mempool_heap
{
	private:
		typedef unsigned int size_type; // convinience
	private:
		size_type available; // number of memory chunks available
		T * a[N+1]; // book keeping, first place not used
		uint8_t buf[sizeof(T)*N]; // the memory itself, here will the objects be stored
	private:
		inline void swap(size_type i, size_type j)
		{
			T * t = a[i];
			a[i] = a[j];
			a[j] = t;
		}

		void up()
		{
			for (size_type n = available; n > 1; ) {
				size_type i = n / 2;
				if (!(a[i] && a[n]))
					swap(i, n);
				n = i;
			}
		}

		void down()
		{
			size_type i = 1;
			size_type c = 2 * i;
			while (c <= available) {
				if (c+1 <= available)
					if (!(a[c] && a[c+1]))
						++c;
				if (!(a[i] && a[c]))
					swap(i, c);
				i = c;
				c = 2 * i;
			}
		}
	public:
		void init()
		{
			// number of available memory chunks is the size of the memory pool, naturally
			available = N;

			// first node is not used, convinience
			a[0] = NULL;

			// all other memory chunks are free, the pointers are initialized
			for (size_type i = 1; i <= N; ++i) {
				a[i] = reinterpret_cast<T *>(&buf[sizeof(T)*(i-1)]);
			}
		}

		void * allocate()
		{
			// allocation not possible if the memory pool has no more space
			if (available <= 0) throw std::bad_alloc();

			// the first memory chunk is always on index 1, this is guaranteed
			// by the heap
			T * t = a[1];

			// move the last free node to front
			a[1] = a[available];

			// mark the used chunk
			a[available] = NULL;

			// number of free chunks decreased
			--available;

			// book keeping for the heap
			down();

			// return a pointer to the allocated space
			return t;
		}

		void deallocate(void * p)
		{
			// invalid pointers are ignored
			if (!p || available >= N) return;

			// memory is freed, more space within the pool
			++available;

			// the freed node is, well, free. status and pointer are restored.
			a[available] = reinterpret_cast<T *>(p);

			// book keeping for the heap
			up();
		}
};

#endif
