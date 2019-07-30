//
// Created by alex on 30.07.2019.
//

#ifndef ALX_MAYBEERROR_H
#define ALX_MAYBEERROR_H

#include <optional>
#include <utility>
#include <cassert>

namespace alx
{

template<typename ErrorType>
class [[nodiscard]] MaybeError
{
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

    void discard() { }

private:
    std::optional<ErrorType> m_error;
};
}

#endif //ALX_MAYBEERROR_H
