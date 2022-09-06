#pragma once

#include <cstddef>
#include <cstdint>

namespace bc
{
    template <typename T>
    struct Value
    {
        using Type = T;
        Type value;
        size_t offset;
        Value() = delete;
        Value(Type x, size_t deltaAt)
            : value(x),
              offset(deltaAt)
        {
        }
    };

    class BinaryCoder
    {
        uint8_t *m_Data;
        size_t m_At;

    public:
        BinaryCoder(uint8_t *);

        uint8_t *Data();
        uint8_t const *Data() const;
        size_t At() const;
        void At(size_t);

        template <typename T>
        typename T::Type Read()
        {
            Value<typename T::Type> result = T::Read(*this);
            m_At += result.offset;
            return result.value;
        }
        template <typename T>
        size_t Write(typename T::Type const &x)
        {
            size_t deltaAt = T::Write(*this, x);
            m_At += deltaAt;
            return deltaAt;
        }
    };
}
