
#include <algorithm>

#ifndef UNIQUE_PTR_HPP
template<class T>
class UniquePtr {
    private:
        T* _ptr;
        void cleanup(){
            delete _ptr;
        }
    public:
        UniquePtr() : _ptr(nullptr){}
        /** parm ctor */
        UniquePtr(T* ptr) : _ptr(ptr) {}

        /** copy ctor deleted */
        UniquePtr(const UniquePtr<T> &copy) = delete;

        /** move ctor */
        UniquePtr(UniquePtr<T>&& other){
            _ptr = other._ptr;
            other._ptr = nullptr;
        }

        ~UniquePtr(){
            cleanup();
        }

        /** Copy Assignment deleted */
        UniquePtr<T>& operator=(const UniquePtr<T> &copy) = delete;

        /** Move Assignment */
        UniquePtr<T>& operator=(UniquePtr<T> &&other){
            if (this == &other)
                return *this;
            cleanup();
            _ptr = other.release();
            return *this;
        }

        const T* operator->() const { return _ptr; }

        T& operator*(){ return *_ptr; }

        operator bool(){
            return _ptr != nullptr;
        }

        T* release(){
            auto oldptr = _ptr;
            _ptr = nullptr;
            return oldptr;
        }

        T* reset(T* newptr = nullptr){
            delete _ptr;
            _ptr = newptr;
            return _ptr;
        }

        void swap(UniquePtr &other){
            std::swap(_ptr, other._ptr);
        }
};
#endif