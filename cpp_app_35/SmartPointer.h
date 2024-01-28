#ifndef SmartPointer_h
#define SmartPointer_h

#include <iostream>

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    explicit UniquePtr(T* p = nullptr) : ptr(p) {} 

    ~UniquePtr() {
        delete ptr;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

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

    T* get() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }
};

template <typename T>
class SharedPtr {
private:
    T* ptr;
    size_t* ref_count;

public:
    explicit SharedPtr(T* p = nullptr) : ptr(p), ref_count(new size_t(1)) {}

    ~SharedPtr() {
        if (--(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }

    SharedPtr(const SharedPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        (*ref_count)++;
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            if (--(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }

            ptr = other.ptr;
            ref_count = other.ref_count;
            (*ref_count)++;
        }
        return *this;
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), ref_count(other.ref_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            if (--(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }

            ptr = other.ptr;
            ref_count = other.ref_count;

            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    T* get() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    size_t use_count() const {
        return *ref_count;
    }
};

#endif 
