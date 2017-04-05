#pragma once

#include "gtest/gtest.h"

#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>


#include "comparators.hpp"
#include "expectation.hpp"
#include "stringify.hpp"

#define _ANONYMOUS_BEGIN \
    namespace mocks      \
    {
#define _ANONYMOUS_END }
#define NO_RETURN_TYPE int

#define _GEN_ARGS0() ()
#define _GEN_ARGS1(a1) (a1 a)
#define _GEN_ARGS2(a1, a2) (a1 a, a2 b)
#define _GEN_ARGS3(a1, a2, a3) (a1 a, a2 b, a3 c)
#define _GEN_ARGS4(a1, a2, a3, a4) (a1 a, a2 b, a3 c, a4 d)
#define _GEN_ARGS5(a1, a2, a3, a4, a5) (a1 a, a2 b, a3 c, a4 d, a5 e)
#define _GEN_ARGS6(a1, a2, a3, a4, a5, a6) (a1 a, a2 b, a3 c, a4 d, a5 e, a6 f)
#define _GEN_ARGS7(a1, a2, a3, a4, a5, a6, a7) \
    (a1 a, a2 b, a3 c, a4 d, a5 e, a6 f, a7 g)
#define _GEN_ARGS8(a1, a2, a3, a4, a5, a6, a7, a8) \
    (a1 a, a2 b, a3 c, a4 d, a5 e, a6 f, a7 g, a8 h)
#define _GEN_ARGS9(a1, a2, a3, a4, a5, a6, a7, a8, a9) \
    (a1 a, a2 b, a3 c, a4 d, a5 e, a6 f, a7 g, a8 h, a9 i)
#define _GEN_ARGS10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
    (a1 a, a2 b, a3 c, a4 d, a5 e, a6 f, a7 g, a8 h, a10 j)

#define _GET_VAL0() ()
#define _GET_VAL1(a1) (a)
#define _GET_VAL2(a1, a2) (a, b)
#define _GET_VAL3(a1, a2, a3) (a, b, c)
#define _GET_VAL4(a1, a2, a3, a4) (a, b, c, d)
#define _GET_VAL5(a1, a2, a3, a4, a5) (a, b, c, d, e)
#define _GET_VAL6(a1, a2, a3, a4, a5, a6) (a, b, c, d, e, f)
#define _GET_VAL7(a1, a2, a3, a4, a5, a6, a7) (a, b, c, d, e, f, g)
#define _GET_VAL8(a1, a2, a3, a4, a5, a6, a7, a8) (a, b, c, d, e, f, g, h)
#define _GET_VAL9(a1, a2, a3, a4, a5, a6, a7, a8, a9) \
    (a, b, c, d, e, f, g, h, i)
#define _GET_VAL10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
    (a, b, c, d, e, f, g, h, i, j)

#define _GET_MACRO(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME
#define GET_VALUES(...)                                                        \
    _GET_MACRO(_0, ##__VA_ARGS__, _GET_VAL10, _GET_VAL9, _GET_VAL8, _GET_VAL7, \
        _GET_VAL6, _GET_VAL5, _GET_VAL4, _GET_VAL3, _GET_VAL2, _GET_VAL1,      \
        _GET_VAL0)                                                             \
    (__VA_ARGS__)

#define GEN_ARGS(...)                                                  \
    _GET_MACRO(_0, ##__VA_ARGS__, _GEN_ARGS10, _GEN_ARGS9, _GEN_ARGS8, \
        _GEN_ARGS7, _GEN_ARGS6, _GEN_ARGS5, _GEN_ARGS4, _GEN_ARGS3,    \
        _GEN_ARGS2, _GEN_ARGS1, _GEN_ARGS0)                            \
    (__VA_ARGS__)

#define DECLARE_MOCK_VOID_FUNCTION_NO_PARAMS(function) \
    _ANONYMOUS_BEGIN                                   \
    extern Mock<int> mock_##function;                  \
    _ANONYMOUS_END

#define DECLARE_MOCK_VOID_FUNCTION(function, ...)  \
    _ANONYMOUS_BEGIN                               \
    extern Mock<int, __VA_ARGS__> mock_##function; \
    _ANONYMOUS_END

#define DECLARE_MOCK_FUNCTION_NO_PARAMS(returnType, function) \
    _ANONYMOUS_BEGIN                                          \
    extern Mock<returnType> mock_##function;                  \
    _ANONYMOUS_END

#define DECLARE_MOCK_FUNCTION(returnType, function, ...)  \
    _ANONYMOUS_BEGIN                                      \
    extern Mock<returnType, __VA_ARGS__> mock_##function; \
    _ANONYMOUS_END

#define MOCK_VOID_FUNCTION(function, ...)                                 \
    _ANONYMOUS_BEGIN                                                      \
    Mock<int, __VA_ARGS__> mock_##function((size_t*)&function);           \
    _ANONYMOUS_END                                                        \
    void function GEN_ARGS(__VA_ARGS__)                                   \
    {                                                                     \
        auto& mock = GET_MOCK(function);                                  \
        mock.call(std::make_tuple GET_VALUES(__VA_ARGS__), __FUNCTION__); \
    }

#define MOCK_VOID_FUNCTION_NO_PARAMS(function)     \
    _ANONYMOUS_BEGIN                               \
    Mock<int> mock_##function((size_t*)&function); \
    _ANONYMOUS_END                                 \
    void function()                                \
    {                                              \
        auto& mock = GET_MOCK(function);           \
        mock.call(__FUNCTION__);                   \
    }

#define MOCK_FUNCTION(returnType, function, ...)                                 \
    _ANONYMOUS_BEGIN                                                             \
    Mock<returnType, __VA_ARGS__> mock_##function((size_t*)&function);           \
    _ANONYMOUS_END                                                               \
    returnType function GEN_ARGS(__VA_ARGS__)                                    \
    {                                                                            \
        auto& mock = GET_MOCK(function);                                         \
        return mock.call(std::make_tuple GET_VALUES(__VA_ARGS__), __FUNCTION__); \
    }

#define MOCK_FUNCTION_NO_PARAMS(returnType, function)     \
    _ANONYMOUS_BEGIN                                      \
    Mock<returnType> mock_##function((size_t*)&function); \
    _ANONYMOUS_END                                        \
    returnType function()                                 \
    {                                                     \
        auto& mock = GET_MOCK(function);                  \
        return mock.call(__FUNCTION__);                   \
    }

#define DECLARE_NICEMOCK_VOID_FUNCTION(function, ...)  \
    _ANONYMOUS_BEGIN                                   \
    extern NiceMock<int, __VA_ARGS__> mock_##function; \
    _ANONYMOUS_END

#define DECLARE_NICEMOCK_FUNCTION(returnType, function, ...)  \
    _ANONYMOUS_BEGIN                                          \
    extern NiceMock<returnType, __VA_ARGS__> mock_##function; \
    _ANONYMOUS_END

#define NICEMOCK_VOID_FUNCTION(function, ...)                             \
    _ANONYMOUS_BEGIN                                                      \
    NiceMock<int, __VA_ARGS__> mock_##function((size_t*)&function);       \
    _ANONYMOUS_END                                                        \
    void function GEN_ARGS(__VA_ARGS__)                                   \
    {                                                                     \
        auto& mock = GET_MOCK(function);                                  \
        mock.call(std::make_tuple GET_VALUES(__VA_ARGS__), __FUNCTION__); \
    }

#define NICEMOCK_FUNCTION(returnType, function, ...)                             \
    _ANONYMOUS_BEGIN                                                             \
    NiceMock<returnType, __VA_ARGS__> mock_##function((size_t*)&function);       \
    _ANONYMOUS_END                                                               \
    returnType function GEN_ARGS(__VA_ARGS__)                                    \
    {                                                                            \
        auto& mock = GET_MOCK(function);                                         \
        return mock.call(std::make_tuple GET_VALUES(__VA_ARGS__), __FUNCTION__); \
    }

#define GET_MOCK(function) mocks::mock_##function

// #define SAFE_MOCK(function, name) std::unique_ptr<WrappedMock<decltype(mocks::mock_##function)>> name
// #define NEW_SAFE_MOCK(function) new WrappedMock<decltype(mocks::mock_##function)>(GET_MOCK(function))
#define SAFE_MOCK(function, name) WrappedMock<decltype(mocks::mock_##function)> name
#define EXPECT_CALL(function, ...) \
    GET_MOCK(function).expectCall(std::make_tuple(__VA_ARGS__), __FILE__, __LINE__)

#define VERIFY_MOCK(function) \
    GET_MOCK(function).verify()

#define GET_TYPE_MOCK(function) decltype(mocks::mock_##function)

namespace mocks
{
}

template <typename T>
class WrappedMock
{
    T& mock_;

  public:
    WrappedMock(T& mock)
        : mock_(mock)
    {
        mock_.clean();
    }

    ~WrappedMock()
    {
        mock_.verify();
    }

    T& get()
    {
        return mock_;
    }
};

template <typename Tuple, std::size_t N>
struct TupleToString
{
    static void toString(const Tuple& t, std::string& str)
    {
        TupleToString<Tuple, N - 1>::toString(t, str);
        str += ", ";
        str += std::to_string(std::get<N - 1>(t));
    }
};

template <typename Tuple>
struct TupleToString<Tuple, 1>
{
    static void toString(const Tuple& t, std::string& str)
    {
        str += std::to_string(std::get<0>(t));
    }
};

template <typename... Args>
std::string
    tupleToString(const std::tuple<Args...>& t)
{
    std::string str = "(";
    TupleToString<decltype(t), sizeof...(Args)>::toString(t, str);
    str += ")";
    return str;
}

template <typename... Args>
class Mock;

template <typename ReturnType>
class Mock<ReturnType>
{
  public:
    Mock() = delete;
    Mock(size_t* address)
        : functionAddress_(address)
    {
    }

    Mock(Mock&) = delete;
    Mock(Mock&&) = delete;
    Mock(const Mock&) = delete;
    Mock(const Mock&&) = delete;
    virtual ~Mock()
    {
        verifyInDestructor();
    }

    virtual void handleUnexpected(const char* name)
    {
        std::string error = "Unexpected call";
        error += ": ";
        error += name;

        std::cerr << "Unresolved calls:" << std::endl;
        for (const auto& call : expectations_)
        {
            std::cerr << call.getFile() << ":" << call.getLine() << std::endl;
        }

        throw std::range_error(error);
    }

    ReturnType call(const char* name)
    {
        if (0 == expectations_.size())
        {
            handleUnexpected(name);
        }

        ReturnType returns_;

        if (0 == expectations_.size())
        {
            returns_ = expectations_[0].returnValue();
            expectations_.erase(expectations_.begin());
        }
        else
        {
            handleUnexpected(name);
        }
        return returns_;
    }

    Expectation<ReturnType>& expectCall(const char* file,
        int line)
    {
        Expectation<ReturnType> expectation();
        expectation.setFile(file);
        expectation.setLine(line);
        expectations_.push_back(expectation);
        return expectations_[expectations_.size() - 1];
    }

    void clean()
    {
        expectations_.clear();
    }

    void verify()
    {
        std::cerr << "VERIFY" << std::endl;
        EXPECT_EQ(0, expectations_.size());

        if (!expectations_.size())
        {
            return;
        }

        std::cerr << "Unresolved calls:" << std::endl;
        for (const auto& call : expectations_)
        {
            std::cerr << call.getFile() << ":" << call.getLine() << std::endl;
        }

        expectations_.clear();
    }

    void verifyInDestructor()
    {
        if (!expectations_.size())
        {
            return;
        }

        std::cerr << "Unresolved calls:" << std::endl;
        for (const auto& call : expectations_)
        {
            std::cerr << call.getFile() << ":" << call.getLine() << std::endl;
        }

        expectations_.clear();
        exit(-1);
    }

  protected:
    size_t* functionAddress_;
    int expected = 0;
    ReturnType returnValue_;
    std::vector<Expectation<ReturnType>> expectations_;
};

template <typename ReturnType, typename... Args>
class Mock<ReturnType, Args...> : public Mock<ReturnType>
{
  protected:
    std::vector<Expectation<ReturnType, Args...>> expectations_;

  public:
    using Mock<ReturnType>::Mock;

    virtual void handleUnexpected(const std::tuple<Args...>& args,
        const char* name)
    {
        std::string error = "Unexpected call";
        error += ": ";
        error += name;
        error += tupleToString(args);

        std::cerr << "Unresolved calls:" << std::endl;
        for (const auto& call : expectations_)
        {
            std::cerr << call.getFile() << ":" << call.getLine() << std::endl;
        }

        throw std::range_error(error);
    }


    ReturnType call(const std::tuple<Args...>& args, const char* name)
    {
        if (0 == expectations_.size())
        {
            handleUnexpected(args, name);
        }

        int position = -1;

        for (int i = 0; i < expectations_.size(); ++i)
        {
            auto& expectation = expectations_[i];
            if (comparators::compareTuple(expectation.getExpectedArgs(), args) &&
                expectation.inSequence() && 0 == i)
            {
                position = 0;

                break;
            }
            else if (comparators::compareTuple(expectation.getExpectedArgs(), args) &&
                !expectation.inSequence())
            {
                position = i;

                break;
            }
        }
        ReturnType returns_;
        if (position >= 0)
        {
            returns_ = expectations_[position].returnValue();
            expectations_.erase(expectations_.begin() + position);
        }
        else
        {
            handleUnexpected(args, name);
        }
        return returns_;
    }


    Expectation<ReturnType, Args...>& expectCall(std::tuple<Args...> args, const char* file,
        int line)
    {
        Expectation<ReturnType, Args...> expectation(args);
        expectation.setFile(file);
        expectation.setLine(line);
        expectations_.push_back(expectation);
        return expectations_[expectations_.size() - 1];
    }

    void clean()
    {
        expectations_.clear();
    }


    void verify()
    {
        if (!expectations_.size())
        {
            return;
        }

        std::cerr << "Unresolved calls:" << std::endl;
        for (const auto& call : expectations_)
        {
            std::cerr << call.getFile() << ":" << call.getLine() << std::endl;
        }
        EXPECT_EQ(0, expectations_.size());
        expectations_.clear();
    }

    void verifyInDestructor()
    {
        if (!expectations_.size())
        {
            return;
        }

        std::cerr << "Unresolved calls:" << std::endl;
        for (const auto& call : expectations_)
        {
            std::cerr << call.getFile() << ":" << call.getLine() << std::endl;
        }

        expectations_.clear();
        exit(-1);
    }
};

template <typename ReturnType, typename... Args>
class NiceMock : public Mock<ReturnType, Args...>
{
  public:
    using Mock<ReturnType, Args...>::Mock;


    virtual void handleUnexpected(const std::tuple<Args...>& args,
        const char* name) override
    {
    }

    virtual void handleUnexpected(const char* name) override
    {
    }
};