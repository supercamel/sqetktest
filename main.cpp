#include <iostream>
#include <squirrel.h>
#include <etk/pool.h>
#include <sqstdio.h>
#include <stdarg.h>
#include <sqstdaux.h>
#include <stdio.h>

using namespace std;

typedef etk::experimental::MemPool<1024*100> PoolType;
PoolType* pool;

void *sq_vm_malloc(SQUnsignedInteger size)
{ 
    return pool->alloc(size); 
}

void *sq_vm_realloc(
        void *p, 
        SQUnsignedInteger SQ_UNUSED_ARG(oldsize), 
        SQUnsignedInteger size)
{ 
    return pool->realloc(p, size); 
}

void sq_vm_free(void *p, SQUnsignedInteger SQ_UNUSED_ARG(size))
{ 
    pool->free(p); 
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
    pool = new PoolType();
    pool->begin();

    HSQUIRRELVM vm = sq_open(1024);
    sqstd_seterrorhandlers(vm);
    sq_setprintfunc(vm, printfunc, errorfunc);

    //sqstd_register_iolib(vm);

    sq_pushroottable(vm);
    sqstd_dofile(vm, "test.nut", true, true);

}

