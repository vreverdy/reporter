// ================================ REPORTER ================================ //
// Project:         Reporter
// Name:            reporter.hpp
// Description:     A reporter class to facilitate debugging
// Creator:         Vincent Reverdy
// Contributor(s):  Vincent Reverdy [2018-2019]
// License:         BSD 3-Clause License
// ========================================================================== //
#ifndef _REPORTER_HPP_INCLUDED
#define _REPORTER_HPP_INCLUDED
// ========================================================================== //



// ================================ PREAMBLE ================================ //
// C++ standard library
#include <mutex>
#include <cstdio>
#include <limits>
#include <string>
#include <thread>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <functional>
#include <type_traits>
// Project sources
// Third-party libraries
// Miscellaneous
// ========================================================================== //



/* ******************************** REPORTER ******************************** */
// Reporter class definition
template <class T = std::size_t>
class reporter
{
    // Assertions
    static_assert(std::is_constructible<T, std::size_t>::value, "");
    
    // Types
    public:
    using value_type = T;
    using size_type = std::size_t;
    using pointer = value_type*;
    
    // Lifecycle
    public:
    reporter();
    explicit reporter(std::ostream& stream);
    reporter(const reporter& other);
    reporter(reporter&& other);
    ~reporter();

    // Assignment
    public:
    reporter& operator=(const reporter& other);
    reporter& operator=(reporter&& other);
    
    // Function call operators
    public:
    template <class... Args>
    void operator()(Args&&...);
    template <class... Args>
    void operator()(Args&&...) const;
    template <class... Args>
    void operator()(Args&&...) volatile;
    template <class... Args>
    void operator()(Args&&...) const volatile;
    void operator()() &;
    void operator()() const&;
    void operator()() volatile&;
    void operator()() const volatile&;
    void operator()() &&;
    void operator()() const&&;
    void operator()() volatile&&;
    void operator()() const volatile&&;

    // Implementation details: logging
    private:
    template <class Self, class Text>
    static std::ostream& _log(Self&& self, Text&& text);

    // Implementation details: data members
    private:
    std::ostream& _stream;
    size_type _id;
    pointer _ptr;
    static size_type _counter;
    static std::mutex _mutex;
};

// Static variables initialization
template <class T> typename reporter<T>::size_type reporter<T>::_counter = 0;
template <class T> std::mutex reporter<T>::_mutex;
/* ************************************************************************** */



// --------------------------- REPORTER: LIFECYCLE -------------------------- //
// Default construct a reporter associated with the default log stream
template <class T>
reporter<T>::reporter()
: _stream(std::clog)
, _id(0)
, _ptr(nullptr)
{
    _mutex.lock();
    _id = ++_counter;
    _ptr = new value_type(_id);
    _log(*this, "reporter::reporter()");
    _mutex.unlock();
}

// Explicitly constructs a new reporter associated with a stream
template <class T>
reporter<T>::reporter(std::ostream& stream)
: _stream(stream)
, _id(0)
, _ptr(nullptr)
{
    _mutex.lock();
    _id = ++_counter;
    _ptr = new value_type(_id);
    _log(*this, "reporter::reporter(std::ostream&)");
    _mutex.unlock();
}

// Copy constructs from another reporter, creating a new id but copying data
template <class T>
reporter<T>::reporter(const reporter& other)
: _stream(other._stream)
, _id(0)
, _ptr(nullptr)
{
    _mutex.lock();
    _id = ++_counter;
    _ptr = new value_type(*other._ptr);
    _log(*this, "reporter::reporter(const reporter&)");
    _mutex.unlock();
}

// Move constructs from another reporter, creating a new id but moving data
template <class T>
reporter<T>::reporter(reporter&& other)
: _stream(other._stream)
, _id(0)
, _ptr(nullptr)
{
    _mutex.lock();
    _id = ++_counter;
    _ptr = other._ptr;
    other._ptr = nullptr;
    _log(*this, "reporter::reporter(reporter&&)");
    _mutex.unlock();
}

// Deletes the reporter and the associated data
template <class T>
reporter<T>::~reporter()
{
    _mutex.lock();
    _log(*this, "reporter::~reporter()");
    if (_ptr) {
        *_ptr = 0;
        delete _ptr;
        _ptr = nullptr;
    }
    _mutex.unlock();
}
// -------------------------------------------------------------------------- //



// -------------------------- REPORTER: ASSIGNMENT -------------------------- //
// Copy assigns from another reporter, copying data
template <class T>
reporter<T>& reporter<T>::operator=(const reporter& other)
{
    _mutex.lock();
    *_ptr = *other._ptr;
    _log(*this, "reporter& reporter::operator=(const reporter&)");
    _mutex.unlock();
    return *this;
}

// Move assigns from another reporter, moving data
template <class T>
reporter<T>& reporter<T>::operator=(reporter&& other)
{
    _mutex.lock();
    *_ptr = *other._ptr;
    other._ptr = nullptr;
    _log(*this, "reporter& reporter::operator=(reporter&&)");
    _mutex.unlock();
    return *this;
}
// -------------------------------------------------------------------------- //



// -------------------- REPORTER: FUNCTION CALL OPERATORS ------------------- //
// Overloads the function call operator
template <class T>
template <class... Args>
void reporter<T>::operator()(Args&&...)
{
    _mutex.lock();
    _log(*this, "void reporter::operator()(Args&&...)");
    _mutex.unlock();
}

// Overloads the function call operator for const
template <class T>
template <class... Args>
void reporter<T>::operator()(Args&&...) const
{
    _mutex.lock();
    _log(*this, "void reporter::operator()(Args&&...) const");
    _mutex.unlock();
}

// Overloads the function call operator for volatile
template <class T>
template <class... Args>
void reporter<T>::operator()(Args&&...) volatile
{
    _mutex.lock();
    _log(*this, "void reporter::operator()(Args&&...) volatile");
    _mutex.unlock();
}

// Overloads the function call operator for const volatile
template <class T>
template <class... Args>
void reporter<T>::operator()(Args&&...) const volatile
{
    _mutex.lock();
    _log(*this, "void reporter::operator()(Args&&...) const volatile");
    _mutex.unlock();
}

// Overloads the function call operator for &
template <class T>
void reporter<T>::operator()() &
{
    _mutex.lock();
    _log(*this, "void reporter::operator()() &");
    _mutex.unlock();
}

// Overloads the function call operator for const&
template <class T>
void reporter<T>::operator()() const&
{
    _mutex.lock();
    _log(*this, "void reporter::operator()() const&");
    _mutex.unlock();
}

// Overloads the function call operator for volatile&
template <class T>
void reporter<T>::operator()() volatile&
{
    _mutex.lock();
    _log(*this, "void reporter::operator()() volatile&");
    _mutex.unlock();
}

// Overloads the function call operator for const volatile&
template <class T>
void reporter<T>::operator()() const volatile&
{
    _mutex.lock();
    _log(*this, "void reporter::operator()() const volatile&");
    _mutex.unlock();
}

// Overloads the function call operator for &&
template <class T>
void reporter<T>::operator()() &&
{
    _mutex.lock();
    _log(*this, "void reporter::operator()() &&");
    _mutex.unlock();
}

// Overloads the function call operator for const&&
template <class T>
void reporter<T>::operator()() const&&
{
    _mutex.lock();
    _log(*this, "void reporter::operator()() const&&");
    _mutex.unlock();
}

// Overloads the function call operator for volatile&&
template <class T>
void reporter<T>::operator()() volatile&&
{
    _mutex.lock();
    _log(*this, "void reporter::operator()() volatile&&");
    _mutex.unlock();
}

// Overloads the function call operator for const volatile&&
template <class T>
void reporter<T>::operator()() const volatile&&
{
    _mutex.lock();
    _log(*this, "void reporter::operator()() const volatile&&");
    _mutex.unlock();
}
// -------------------------------------------------------------------------- //



// ---------------------------- REPORTER: LOGGING --------------------------- //
// Prints the current reporter status
template <class T>
template <class Self, class Text>
std::ostream& reporter<T>::_log(Self&& self, Text&& text)
{
    static const unsigned short int hash = typeid(T).hash_code();
    static const std::string fmt0 = "[type = %05hu";
    static const std::string fmt1 = ", thread = %05hu";
    static const std::string fmt2 = ", id = %05hu";
    static const std::string fmt3 = ", address = 0x%08llX";
    static const std::string fmt4 = ", data = %05hu]:";
    static const std::string fmt = "[%05hu, %05hu, %05hu, 0x%08llX, %05hu]: ";
    static const std::string format = fmt;
    static const int size = std::numeric_limits<char>::max();
    const std::thread::id tid = std::this_thread::get_id();
    const unsigned short int thread = std::hash<std::thread::id>()(tid);
    char buffer[size];
    unsigned short int id = std::forward<Self>(self)._id;
    pointer link = std::forward<Self>(self)._ptr;
    unsigned long long int ptr = reinterpret_cast<std::uintptr_t>(link);
    unsigned short int value = link ? *link : 0;
    std::snprintf(buffer, size, format.c_str(), hash, thread, id, ptr, value);
    std::forward<Self>(self)._stream << buffer << std::forward<Text>(text);
    return std::forward<Self>(self)._stream << std::endl;
}
// -------------------------------------------------------------------------- //



// ========================================================================== //
#endif // _REPORTER_HPP_INCLUDED
// ========================================================================== //
