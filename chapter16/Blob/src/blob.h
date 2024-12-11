
#ifndef _BLOB_H_
#define _BLOB_H_

#include <vector>
#include <string>

template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);

template<typename T>
class Blob{
    friend class BlobPtr<T>;
    friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
    public:
        typedef T value_type;
        typedef typename std::vector<T>::size_type size_type;
        Blob();
        Blob(std::initializer_list<T> il);
        size_type size() const {return data->size();}
        bool empty() const {return data->empty();}
        void push_back(const T tt){data->push_back(t);}
        void push_back(T &&t) {data->push_back(std::move(t));}
        void pop_back();
        T& back();
        T& operator[] (size_type i);
    private:
        std::shared_ptr<std::vector<T>> data;
        void check(size_type i, const std::string &msg) const;
        
};

template <typename T>
Blob<T>::Blob():data(std::make_shared<std::vector<T>>) {}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il):data(std::make_shared<std::vector<T>>(il)) {}

template<typename T> 
void Blob<T>::check(size_type i, const std::string &msg) const 
{
    if (i >= data->size())
    {
        throw std::out_of_range(msg);
    }
}

template<typename T>
class BlobPtr {
    public:
        BlobPtr():curr(0) {}
        BlobPtr(Blob<T> &a, size_t sz = 0):wptr(a.data), curr(sz) {}
        T& operator *() const 
        {
            auto p = check(curr, "deference past end");
            return (*p)[curr];
        }
        BlobPtr& operator++();
        BlobPtr& operator--();
    private:
        std::shared_ptr<std::vector<T>> check (std::size_t, const std::string &) const;
        std::weak_ptr<std::vector<T>> wptr;
        std::size_t curr;
};

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator++(int)
{
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator--(int)
{
    BlobPtr ret = *this;
    --*this;
    return ret;
}

#endif //blob.h
