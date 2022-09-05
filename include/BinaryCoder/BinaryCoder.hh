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
        void Write(typename T::Type const &x)
        {
            size_t deltaAt = T::Write(*this, x);
            m_At += deltaAt;
        }
    };

    struct Uint8
    {
        using Type = uint8_t;
        static Value<Type> Read(BinaryCoder &);
        static size_t Write(BinaryCoder &, Type x);
    };
    struct Uint16
    {
        using Type = uint16_t;
        static Value<Type> Read(BinaryCoder &);
        static size_t Write(BinaryCoder &, Type x);
    };
    struct Uint32
    {
        using Type = uint32_t;
        static Value<Type> Read(BinaryCoder &);
        static size_t Write(BinaryCoder &, Type x);
    };
    struct Uint64
    {
        using Type = uint64_t;
        static Value<Type> Read(BinaryCoder &);
        static size_t Write(BinaryCoder &, Type x);
    };
    struct Int8
    {
        using Type = uint8_t;
        static Value<Type> Read(BinaryCoder &);
        static size_t Write(BinaryCoder &, Type x);
    };
    struct Int16
    {
        using Type = uint16_t;
        static Value<Type> Read(BinaryCoder &);
        static size_t Write(BinaryCoder &, Type x);
    };
    struct Int32
    {
        using Type = uint32_t;
        static Value<Type> Read(BinaryCoder &);
        static size_t Write(BinaryCoder &, Type x);
    };
    struct Int64
    {
        using Type = uint64_t;
        static Value<Type> Read(BinaryCoder &);
        static size_t Write(BinaryCoder &, Type x);
    };
}
