// Tikriname, ar simbolinė konstanta MYVECTOR_H dar nėra apibrėžta
#ifndef MYVECTOR_H
#define MYVECTOR_H

// Įterpiame reikalingas bibliotekas
#include <iostream>
#include <memory>
#include <algorithm>

// Apibrėžiame šabloninę klasę Vector su kintamuoju tipu T
template <class T> class Vector
{
    public:
        // Apibrėžiame sinonomus (alias) naudojantis "using" raktiniu žodžiu
        using iterator = T*;
        using const_iterator = const T*;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using size_type = size_t;
        using value_type = T;

        // Konstruktoriai
        Vector() { create(); };
        explicit Vector(size_t n, const T& val = T{}) { create(n, val); }
        Vector(const std::initializer_list<T> initList) { create(initList.begin(), initList.end()); } // su initializer list
        Vector(iterator first, iterator last) { create(first, last); }
        Vector(const Vector& v) { create(v.begin(), v.end()); } // Kopijavimo konstruktorius
        Vector(Vector&& v) : data(std::move(v.data)), avail(std::move(v.avail)), limit(std::move(v.limit)) // Perkėlimo konstruktorius
        {
            v.data = v.avail = v.limit = nullptr;
        }

        // Perkėlimo priskyrimo operatorius
        Vector& operator=(Vector&& rhs)
        {
            if (&rhs != this) {
                uncreate();
                data = std::move(rhs.data);
                avail = std::move(rhs.avail);
                limit = std::move(rhs.limit);
                rhs.data = rhs.avail = rhs.limit = nullptr;
            }
            return *this;
        }

        // Kopijavimo priskyrimo operatorius
        Vector& operator=(const Vector& rhs)
        {
            if (&rhs != this) {
                uncreate();
                create(rhs.begin(), rhs.end());
            }
            return *this;
        }

        ~Vector() { uncreate(); } // Destruktorius

        // Funkcijos "assign"
        void assign(size_type n, const T& value)
        {
            clear();
            if (n > capacity())
                grow(n);
            while (size() < n)
                unchecked_append(value);
        }

        void assign(iterator first, iterator last)
        {
            size_type n = std::distance(first, last);
            clear();
            if (n > capacity())
                grow(n);
            while (first != last) {
                unchecked_append(*first);
                ++first;
            }
        }

        void assign(std::initializer_list<T> initList)
        {
            assign(initList.begin(), initList.end());
        }

        // Elementų pasiekimo funkcijos
        T& at(size_type n)
        {
            if(n < size())
                return data[n];
            else
                throw std::out_of_range("Vector::at()");
        }

        T& operator[](size_type i){ return data[i]; } // indeksavimas
        const T& operator[](size_type i) const { return data[i]; }

        T& front() { return data[0]; }
        const T &front() const { return data[0]; }

        T& back() { return data[size()-1]; }
        const T &back() const { return data[size()-1]; }

        // Iteratorių funkcijos
        iterator begin() { return data; }
        const_iterator begin() const { return data; }

        iterator end() { return avail; }
        const_iterator end() const { return avail; }

        reverse_iterator rbegin() { return reverse_iterator(avail); }
        const_reverse_iterator rbegin() const { return reverse_iterator(avail); }

        reverse_iterator rend() { return reverse_iterator(data); }
        const_reverse_iterator rend() const { return reverse_iterator(data); }

        // Funkcijos, skirtos informacijai gauti apie vektorių
        bool empty() const { return (begin() == end()); }
        size_type size() const { return avail - data; }
        typename Vector<T>::size_type max_size() const noexcept
        {
            return std::numeric_limits<size_type>::max() / sizeof(T);
        }
        void reserve(size_type n) { if (n > capacity()) grow(n); }
        size_type capacity() const { return limit - data; }
        void shrink_to_fit() { limit = avail; }

        // Modifikavimo funkcijos
        void clear()
        {
            iterator it = avail;
            while (it != data) {
                alloc.destroy(--it);
            }
            avail = data;
        }

        iterator insert(iterator position, const T& value)
        {
            if (avail == limit)
                grow();
            std::move_backward(position, avail, avail + 1);
            *(position) = value;
            ++avail;
            return position;
        }

        iterator emplace(iterator position, T&& value)
        {
            if (avail == limit)
                grow();
            for (iterator it = avail; it != position; --it)
                *(it) = *(it - 1);
            alloc.construct(position, std::forward<T>(value));
            ++avail;
            return position;
        }

        iterator erase(iterator pos)
        {
            if (pos < avail) {
                iterator it = pos;
                while (it != avail - 1) {
                    *(it) = *(it + 1);
                    ++it;
                }
                --avail;
                alloc.destroy(avail);
            }
            return pos;
        }

        iterator erase(iterator first, iterator last)
        {
            if (first < avail && last <= avail) {
                iterator it = first;
                while (last != avail) {
                    *(it++) = *(last++);
                }
                iterator newAvail = avail - std::distance(first, last);
                while (avail != newAvail) {
                    alloc.destroy(--avail);
                }
            }
            return first;
        }

        void resize(size_type n)
        {
            if (n < size()) {
                iterator it = data + n;
                while (it != avail) {
                    alloc.destroy(it);
                    ++it;
                }
                avail = data + n;
            } else if (n > size()) {
                reserve(n);
                while (size() < n) {
                    unchecked_append(T());
                }
            }
        }

        void resize(size_type n, const value_type& val)
        {
            if (n < size()) {
                iterator it = data + n;
                while (it != avail) {
                    alloc.destroy(it);
                    ++it;
                }
                avail = data + n;
            } else if (n > size()) {
                reserve(n);
                while (size() < n) {
                    unchecked_append(val);
                }
            }
        }

        void swap(Vector<T>& other)
        {
            std::swap(data, other.data);
            std::swap(avail, other.avail);
            std::swap(limit, other.limit);
        }

        void push_back(const T& value)
        {
            if (avail == limit)
                grow();
            unchecked_append(value);
        }

        void push_back(T&& value)
        {
            if (avail == limit)
                grow();
            alloc.construct(avail++, std::move(value));
        }

        template <typename... Args>
        void emplace_back(Args&&... args)
        {
            if (avail == limit)
                grow();
            alloc.construct(avail++, std::forward<Args>(args)...);
        }

        void pop_back()
        {
            alloc.destroy(--avail);
        }

        // Capacity
        size_type size() const
        {
            return avail - data;
        }

        size_type capacity() const
        {
            return limit - data;
        }

        bool empty() const
        {
            return data == avail;
        }

        void reserve(size_type newcap)
        {
            if (newcap > capacity()) {
                iterator newdata = alloc.allocate(newcap);
                iterator newavail = std::uninitialized_copy(data, avail, newdata);
                uncreate();
                data = newdata;
                avail = newavail;
                limit = data + newcap;
            }
        }

    private:
        iterator data;
        iterator avail;
        iterator limit;
        std::allocator<T> alloc;

        void create()
        {
            data = avail = limit = nullptr;
        }

        void create(size_type n, const T& val)
        {
            data = alloc.allocate(n);
            limit = avail = data + n;
            std::uninitialized_fill(data, limit, val);
        }

        void create(iterator i, iterator j)
        {
            data = alloc.allocate(j - i);
            limit = avail = std::uninitialized_copy(i, j, data);
        }

        void uncreate()
        {
            if (data) {
                iterator it = avail;
                while (it != data)
                    alloc.destroy(--it);
                alloc.deallocate(data, limit - data);
            }
            data = limit = avail = nullptr;
        }

        void grow()
        {
            size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));
            iterator new_data = alloc.allocate(new_size);
            iterator new_avail = std::uninitialized_copy(data, avail, new_data);
            uncreate();
            data = new_data;
            avail = new_avail;
            limit = data + new_size;
        }

        void unchecked_append(const T& val)
        {
            alloc.construct(avail++, val);
        }
};

#endif // MYVECTOR_H
