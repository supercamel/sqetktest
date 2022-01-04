#include <iostream>
#include <squirrel.h>
#include <etk/pool.h>
#include <sqstdio.h>
#include <stdarg.h>
#include <sqstdaux.h>
#include <stdio.h>
#include <chrono>
using namespace std::chrono;
using namespace std;

typedef etk::experimental::BlockyPool<1024*100> PoolType;
//typedef etk::experimental::Heap PoolType;
PoolType pool;

void *sq_vm_malloc(SQUnsignedInteger size)
{ 
    return pool.alloc(size); 
}

void *sq_vm_realloc(
        void *p, 
        SQUnsignedInteger SQ_UNUSED_ARG(oldsize), 
        SQUnsignedInteger size)
{ 
    return pool.realloc(p, size, oldsize); 
}

void sq_vm_free(void *p, SQUnsignedInteger SQ_UNUSED_ARG(size))
{ 
    pool.free(p, size); 
}


void printfunc(HSQUIRRELVM v, const SQChar* s,...)
{
    va_list vl;
    va_start(vl, s);
    vfprintf(stdout, s, vl);   
    va_end(vl);
    sq_collectgarbage(v);
}

void errorfunc(HSQUIRRELVM v, const SQChar* s,...)
{
    va_list vl;
    va_start(vl, s);
    vfprintf(stdout, s, vl);   
    va_end(vl);
}

int main() {
    //PoolType pool);
    //pool->begin();

    HSQUIRRELVM vm = sq_open(1024);
    sqstd_seterrorhandlers(vm);
    sq_setprintfunc(vm, printfunc, errorfunc);

    //sqstd_register_iolib(vm);
    sq_pushroottable(vm);
	auto start = high_resolution_clock::now();
    sqstd_dofile(vm, "test.nut", true, true);
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);
	  
	// To get the value of duration use the count()
	// // member function on the duration object
	cout << duration.count()/1000000.0 << endl;
}

