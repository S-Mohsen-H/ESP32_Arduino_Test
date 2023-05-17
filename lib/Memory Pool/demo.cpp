#include <mempool_heap.hpp>
#include <memory_pool.hpp>

class A
{
    private:
        typedef memory_pool<A, mempool_heap<A, 16> > MemoryPool;
        static MemoryPool mem;
    private:
        int data; // some data
    public:
        // initiailzation of the object.
        A(int data) : data(data) {}

        // cleanup
        virtual ~A() {}

        // operator 'new' and 'delete' overloaded to redirect any memory management,
        // in this case delegated to the memory pool
        void * operator new(unsigned int n)
        {
            return mem.alloc(n);
        }

        void operator delete(void * p)
        {
            mem.free(p);
        }
};

A::MemoryPool A::mem; // instance of the static memory pool

int main(int, char **)
{
    // array to hold objects
    A * a[64];

    // create objects, allocate memory
    for (int i = 0; i < 8; ++i)
        a[i] = new A(i);

	// delete objects, free memory
    for (int i = 0; i < 8; ++i) {
        delete a[i];
        a[i] = NULL;
    }

    return 0;
}

