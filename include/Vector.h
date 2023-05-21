#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

template <class T, class Allocator = std::allocator<T>>
class Vector {
private:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    T* m_data;
    size_t m_size;
    size_t m_capacity;
    Allocator m_allocator;
public:
    Vector();
    Vector(size_t size);
    Vector(size_t size, const T& value);
    Vector(const Vector& other);
    Vector(Vector&& other);
    ~Vector();
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);
    void assign(size_t size, const T& value);
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last);
    Allocator get_allocator() const;

    T& at(size_t index);
    const T& at(size_t index) const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    T* data();
    const T* data() const;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    bool empty() const;
    size_t size() const;
    size_t maxSize() const;
    void reserve(size_t capacity);
    size_t capacity() const;
    void shrink_to_fit();

    void clear();
    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, T&& value);
    iterator insert(const_iterator pos, size_t count, const T& value);
    template <class InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last);
    iterator insert(const_iterator pos, std::initializer_list<T> ilist);
    template <class... Args>
    iterator emplace(const_iterator pos, Args&&... args);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    void push_back(const T& value);
    void push_back(T&& value);
    template <class... Args>
    void emplace_back(Args&&... args);
    void pop_back();
    void resize(size_t count);
    void resize(size_t count, const T& value);
    void swap(Vector& other);
};

template <class T, class Allocator>
Vector<T, Allocator>::Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(size_t size) : m_data(nullptr), m_size(size), m_capacity(size) {
    m_data = m_allocator.allocate(m_capacity);
    for (size_t i = 0; i < m_size; ++i) {
        m_allocator.construct(m_data + i);
    }
}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(size_t size, const T& value) : m_data(nullptr), m_size(size), m_capacity(size) {
    m_data = m_allocator.allocate(m_capacity);
    for (size_t i = 0; i < m_size; ++i) {
        m_allocator.construct(m_data + i, value);
    }
}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector& other) : m_data(nullptr), m_size(other.m_size), m_capacity(other.m_capacity) {
    m_data = m_allocator.allocate(m_capacity);
    for (size_t i = 0; i < m_size; ++i) {
        m_allocator.construct(m_data + i, other.m_data[i]);
    }
}

template <class T, class Allocator>
Vector<T, Allocator>::Vector(Vector&& other) : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) {
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

template <class T, class Allocator>
Vector<T, Allocator>::~Vector() {
    for (size_t i = 0; i < m_size; ++i) {
        m_allocator.destroy(m_data + i);
    }
    m_allocator.deallocate(m_data, m_capacity);
}

template <class T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& other) {
    if (this != &other) {
        for (size_t i = 0; i < m_size; ++i) {
            m_allocator.destroy(m_data + i);
        }
        m_allocator.deallocate(m_data, m_capacity);
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = m_allocator.allocate(m_capacity);
        for (size_t i = 0; i < m_size; ++i) {
            m_allocator.construct(m_data + i, other.m_data[i]);
        }
    }
    return *this;
}

template <class T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& other) {
    if (this != &other) {
        for (size_t i = 0; i < m_size; ++i) {
            m_allocator.destroy(m_data + i);
        }
        m_allocator.deallocate(m_data, m_capacity);
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    return *this;
}

template <class T, class Allocator>
void Vector<T, Allocator>::assign(size_t size, const T& value) {
    for (size_t i = 0; i < m_size; ++i) {
        m_allocator.destroy(m_data + i);
    }
    m_allocator.deallocate(m_data, m_capacity);
    m_size = size;
    m_capacity = size;
    m_data = m_allocator.allocate(m_capacity);
    for (size_t i = 0; i < m_size; ++i) {
        m_allocator.construct(m_data + i, value);
    }
}

template <class T, class Allocator>
template <class InputIterator>
void Vector<T, Allocator>::assign(InputIterator first, InputIterator last) {
    for (size_t i = 0; i < m_size; ++i) {
        m_allocator.destroy(m_data + i);
    }
    m_allocator.deallocate(m_data, m_capacity);
    m_size = last - first;
    m_capacity = last - first;
    m_data = m_allocator.allocate(m_capacity);
    for (size_t i = 0; i < m_size; ++i) {
        m_allocator.construct(m_data + i, *(first + i));
    }
}

template <class T, class Allocator>
Allocator Vector<T, Allocator>::get_allocator() const {
    return m_allocator;
}

template <class T, class Allocator>
T& Vector<T, Allocator>::at(size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("Index is out of range");
    }
    return m_data[index];
}

template <class T, class Allocator>
const T& Vector<T, Allocator>::at(size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("Index is out of range");
    }
    return m_data[index];
}

template <class T, class Allocator>
T& Vector<T, Allocator>::operator[](size_t index) {
    return m_data[index];
}

template <class T, class Allocator>
const T& Vector<T, Allocator>::operator[](size_t index) const {
    return m_data[index];
}

template <class T, class Allocator>
T& Vector<T, Allocator>::front() {
    return m_data[0];
}

template <class T, class Allocator>
const T& Vector<T, Allocator>::front() const {
    return m_data[0];
}

template <class T, class Allocator>
T& Vector<T, Allocator>::back() {
    return m_data[m_size - 1];
}

template <class T, class Allocator>
const T& Vector<T, Allocator>::back() const {
    return m_data[m_size - 1];
}

template <class T, class Allocator>
T* Vector<T, Allocator>::data() {
    return m_data;
}

template <class T, class Allocator>
const T* Vector<T, Allocator>::data() const {
    return m_data;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::begin() {
    return m_data;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::end() {
    return m_data + m_size;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::begin() const {
    return m_data;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::end() const {
    return m_data + m_size;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rbegin() {
    return reverse_iterator(m_data + m_size);
}

template <class T, class Allocator>
typename Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rend() {
    return reverse_iterator(m_data);
}

template <class T, class Allocator>
typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::rbegin() const {
    return const_reverse_iterator(m_data + m_size);
}

template <class T, class Allocator>
typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::rend() const {
    return const_reverse_iterator(m_data);
}

template <class T, class Allocator>
bool Vector<T, Allocator>::empty() const {
    return m_size == 0;
}

template <class T, class Allocator>
size_t Vector<T, Allocator>::size() const {
    return m_size;
}

template <class T, class Allocator>
size_t Vector<T, Allocator>::maxSize() const {
    return m_allocator.max_size();
}

template <class T, class Allocator>
void Vector<T, Allocator>::reserve(size_t capacity) {
    if (capacity > m_capacity) {
        T* new_data = m_allocator.allocate(capacity);
        for (size_t i = 0; i < m_size; ++i) {
            m_allocator.construct(new_data + i, m_data[i]);
        }
        for (size_t i = 0; i < m_size; ++i) {
            m_allocator.destroy(m_data + i);
        }
        m_allocator.deallocate(m_data, m_capacity);
        m_data = new_data;
        m_capacity = capacity;
    }
}

template <class T, class Allocator>
size_t Vector<T, Allocator>::capacity() const {
    return m_capacity;
}

template <class T, class Allocator>
void Vector<T, Allocator>::shrink_to_fit() {
    if (m_size < m_capacity) {
        T* new_data = m_allocator.allocate(m_size);
        for (size_t i = 0; i < m_size; ++i) {
            m_allocator.construct(new_data + i, m_data[i]);
        }
        for (size_t i = 0; i < m_size; ++i) {
            m_allocator.destroy(m_data + i);
        }
        m_allocator.deallocate(m_data, m_capacity);
        m_data = new_data;
        m_capacity = m_size;
    }
}

template <class T, class Allocator>
void Vector<T, Allocator>::clear() {
    for (size_t i = 0; i < m_size; ++i) {
        m_allocator.destroy(m_data + i);
    }
    m_size = 0;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, const T& value) {
    size_t index = pos - m_data;
    if (m_size == m_capacity) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    for (size_t i = m_size; i > index; --i) {
        m_allocator.construct(m_data + i, m_data[i - 1]);
        m_allocator.destroy(m_data + i - 1);
    }
    m_allocator.construct(m_data + index, value);
    ++m_size;
    return m_data + index;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, T&& value) {
    size_t index = pos - m_data;
    if (m_size == m_capacity) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    for (size_t i = m_size; i > index; --i) {
        m_allocator.construct(m_data + i, m_data[i - 1]);
        m_allocator.destroy(m_data + i - 1);
    }
    m_allocator.construct(m_data + index, std::move(value));
    ++m_size;
    return m_data + index;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, size_t count, const T& value) {
    size_t index = pos - m_data;
    if (m_size + count > m_capacity) {
        reserve(m_capacity == 0 ? count : m_capacity * 2);
    }
    for (size_t i = m_size + count - 1; i >= index + count; --i) {
        m_allocator.construct(m_data + i, m_data[i - count]);
        m_allocator.destroy(m_data + i - count);
    }
    for (size_t i = index; i < index + count; ++i) {
        m_allocator.construct(m_data + i, value);
    }
    m_size += count;
    return m_data + index;
}

template <class T, class Allocator>
template <class InputIterator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, InputIterator first, InputIterator last) {
    size_t index = pos - m_data;
    size_t count = last - first;
    if (m_size + count > m_capacity) {
        reserve(m_capacity == 0 ? count : m_capacity * 2);
    }
    for (size_t i = m_size + count - 1; i >= index + count; --i) {
        m_allocator.construct(m_data + i, m_data[i - count]);
        m_allocator.destroy(m_data + i - count);
    }
    for (size_t i = index; i < index + count; ++i) {
        m_allocator.construct(m_data + i, *(first + i - index));
    }
    m_size += count;
    return m_data + index;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> ilist) {
    size_t index = pos - m_data;
    size_t count = ilist.size();
    if (m_size + count > m_capacity) {
        reserve(m_capacity == 0 ? count : m_capacity * 2);
    }
    for (size_t i = m_size + count - 1; i >= index + count; --i) {
        m_allocator.construct(m_data + i, m_data[i - count]);
        m_allocator.destroy(m_data + i - count);
    }
    for (size_t i = index; i < index + count; ++i) {
        m_allocator.construct(m_data + i, *(ilist.begin() + i - index));
    }
    m_size += count;
    return m_data + index;
}

template <class T, class Allocator>
template <class... Args>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::emplace(const_iterator pos, Args&&... args) {
    size_t index = pos - m_data;
    if (m_size == m_capacity) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    for (size_t i = m_size; i > index; --i) {
        m_allocator.construct(m_data + i, m_data[i - 1]);
        m_allocator.destroy(m_data + i - 1);
    }
    m_allocator.construct(m_data + index, std::forward<Args>(args)...);
    ++m_size;
    return m_data + index;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::erase(const_iterator pos) {
    size_t index = pos - m_data;
    m_allocator.destroy(m_data + index);
    for (size_t i = index; i < m_size - 1; ++i) {
        m_allocator.construct(m_data + i, m_data[i + 1]);
        m_allocator.destroy(m_data + i + 1);
    }
    --m_size;
    return m_data + index;
}

template <class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::erase(const_iterator first, const_iterator last) {
    size_t index = first - m_data;
    size_t count = last - first;
    for (size_t i = index; i < index + count; ++i) {
        m_allocator.destroy(m_data + i);
    }
    for (size_t i = index; i < m_size - count; ++i) {
        m_allocator.construct(m_data + i, m_data[i + count]);
        m_allocator.destroy(m_data + i + count);
    }
    m_size -= count;
    return m_data + index;
}

template <class T, class Allocator>
void Vector<T, Allocator>::push_back(const T& value) {
    if (m_size == m_capacity) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    m_allocator.construct(m_data + m_size, value);
    ++m_size;
}

template <class T, class Allocator>
void Vector<T, Allocator>::push_back(T&& value) {
    if (m_size == m_capacity) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    m_allocator.construct(m_data + m_size, std::move(value));
    ++m_size;
}

template <class T, class Allocator>
template <class... Args>
void Vector<T, Allocator>::emplace_back(Args&&... args) {
    if (m_size == m_capacity) {
        reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    m_allocator.construct(m_data + m_size, std::forward<Args>(args)...);
    ++m_size;
}

template <class T, class Allocator>
void Vector<T, Allocator>::pop_back() {
    m_allocator.destroy(m_data + m_size - 1);
    --m_size;
}

template <class T, class Allocator>
void Vector<T, Allocator>::resize(size_t count) {
    if (count < m_size) {
        for (size_t i = count; i < m_size; ++i) {
            m_allocator.destroy(m_data + i);
        }
    } else if (count > m_size) {
        if (count > m_capacity) {
            reserve(m_capacity == 0 ? count : m_capacity * 2);
        }
        for (size_t i = m_size; i < count; ++i) {
            m_allocator.construct(m_data + i);
        }
    }
    m_size = count;
}

template <class T, class Allocator>
void Vector<T, Allocator>::resize(size_t count, const T& value) {
    if (count < m_size) {
        for (size_t i = count; i < m_size; ++i) {
            m_allocator.destroy(m_data + i);
        }
    } else if (count > m_size) {
        if (count > m_capacity) {
            reserve(m_capacity == 0 ? count : m_capacity * 2);
        }
        for (size_t i = m_size; i < count; ++i) {
            m_allocator.construct(m_data + i, value);
        }
    }
    m_size = count;
}

template <class T, class Allocator>
void Vector<T, Allocator>::swap(Vector& other) {
    std::swap(m_data, other.m_data);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
}

#endif