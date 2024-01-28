#ifndef SmartPointer_h
#define SmartPointer_h

#include <iostream>

template <typename T>
class UniquePtr {
private:
    T* ptr;
public:
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}   //ptr(p) - is a member initialization list
    ~UniquePtr() {
        delete ptr;
    }
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& other) noexcept {   
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    T* operator->() const {
        return ptr;
    }
    T& operator*() const {
        return *ptr;
    }
    T* get() const {
        return ptr;
    }
};

template <typename T>
class SharedPtr {
private:
    T* ptr;
    size_t* refCount;    // refCount is a pointer to size_t

    void release() {
        if (refCount != nullptr && --(*refCount) == 0) {  // if refCount is not nullptr and refCount is 0 after decrement 
            delete ptr;
            delete refCount;
        }
    }

public:
    explicit SharedPtr(T* p = nullptr) : ptr(p), refCount(new size_t(1)) {}
    SharedPtr(const SharedPtr& other) : ptr(other.ptr), refCount(other.refCount) {
        (*refCount)++;
    }
    ~SharedPtr() {
        release();
    }
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            (*refCount)++;   // (*refCount)++ - incrementing the value pointed to by the pointer 
        }
        return *this;
    }
    SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr;
        other.refCount = nullptr;
    }
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            other.ptr = nullptr;
            other.refCount = nullptr;
        }
        return *this;
    }
    T* operator->() const {
        return ptr;
    }
    T& operator*() const {
        return *ptr;
    }
    T* get() const {
        return ptr;
    }
};

#endif 
