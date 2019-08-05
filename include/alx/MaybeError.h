//
// Created by alex on 30.07.2019.
//

#ifndef ALX_MAYBEERROR_H
#define ALX_MAYBEERROR_H

#include <optional>
#include <utility>
#include <cassert>
#include <iostream>

namespace alx
{

    namespace detail {
        template<typename, template<typename...> typename Pattern, typename... Args>
        struct IllFormed {
            constexpr static bool value = false;
        };

        template<typename... Ts>
        using void_t = void;

        template<template<typename...> typename Pattern, typename... Args>
        struct IllFormed<void_t<Pattern<Args...>>, Pattern, Args...> {
            constexpr static bool value = true;
        };

        template<template<typename...> typename Pattern, typename... Args>
        struct Detect : public detail::IllFormed<void, Pattern, Args...> {
        };

    }

template<typename ErrorType>
class [[nodiscard]] MaybeError
{
    template<typename T>
    using Printable_d = decltype(std::cerr << std::declval<T>());

public:
    MaybeError(): m_error{std::nullopt} {}
    MaybeError(ErrorType error): m_error{std::move(error)} {}

    operator bool() const { return m_error.has_value(); }
    bool errorSet() const { return m_error.has_value(); }

    [[nodiscard]] ErrorType& error()
    {
        assert(errorSet());
        return m_error.value();
    }


    [[nodiscard]] const ErrorType& error() const
    {
        assert(errorSet());
        return m_error.value();
    }

    template <typename Handler>
    void handle(Handler&& handler)
    {
        if(errorSet())
            handler(m_error);
    }

    void discard()
    {
        if (errorSet())
        {
            if constexpr(detail::Detect<Printable_d>::value)
                std::cerr << "Discarded MaybeError with error set: \n" << m_error.value() << std::endl;
            else std::cerr << "Discarded MaybeError with error set" << std::endl;
            std::terminate();
        }
    }

private:
    std::optional<ErrorType> m_error;
};
}

#endif //ALX_MAYBEERROR_H
