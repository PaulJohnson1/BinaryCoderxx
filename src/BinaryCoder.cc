#include <BinaryCoder/BinaryCoder.hh>

namespace bc
{
    Value<Uint8::Type> Uint8::Read(BinaryCoder &coder)
    {
        Type x = coder.Data()[coder.At()];
        return Value<Type>{x, 1};
    }
    size_t Uint8::Write(BinaryCoder &coder, Type x)
    {
        coder.Data()[coder.At()] = x;
        return 1;
    }
    Value<Uint16::Type> Uint16::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Uint8>() | ((Type)coder.Read<Uint8>() << 8);
        return Value<Type>{x, 0};
    }
    size_t Uint16::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Uint8>(x & 255);
        coder.Write<Uint8>(x >> 8);
        return 2;
    }
    Value<Uint32::Type> Uint32::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Uint16>() | ((Type)coder.Read<Uint16>() << 16);
        return Value<Type>{x, 0};
    }
    size_t Uint32::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Uint16>(x & 65535);
        coder.Write<Uint16>(x >> 16);
        return 4;
    }
    Value<Uint64::Type> Uint64::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Uint32>() | ((Type)coder.Read<Uint32>() << 32);
        return Value<Type>{x, 0};
    }
    size_t Uint64::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Uint16>(x & 4294967295);
        coder.Write<Uint16>(x >> 32);
        return 8;
    }
    Value<Int8::Type> Int8::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Data()[coder.At()];
        return Value<Type>{x, 1};
    }
    size_t Int8::Write(BinaryCoder &coder, Type x)
    {
        coder.Data()[coder.At()] = x;
        return 1;
    }
    Value<Int16::Type> Int16::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Int8>() | ((Type)coder.Read<Int8>() << 8);
        return Value<Type>{x, 0};
    }
    size_t Int16::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Int8>(x & 255);
        coder.Write<Int8>(x >> 8);
        return 2;
    }
    Value<Int32::Type> Int32::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Int16>() | ((Type)coder.Read<Int16>() << 16);
        return Value<Type>{x, 0};
    }
    size_t Int32::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Int16>(x & 65535);
        coder.Write<Int16>(x >> 16);
        return 4;
    }
    Value<Int64::Type> Int64::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Int32>() | ((Type)coder.Read<Int32>() << 32);
        return Value<Type>{x, 0};
    }
    size_t Int64::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Int32>(x & 4294967295);
        coder.Write<Int32>(x >> 32);
        return 8;
    }

    BinaryCoder::BinaryCoder(uint8_t *buffer)
        : m_Data(buffer)
    {
    }

    size_t BinaryCoder::At() const
    {
        return m_At;
    }
    void BinaryCoder::At(size_t x)
    {
        m_At = x;
    }

    uint8_t *BinaryCoder::Data()
    {
        return m_Data;
    }

    uint8_t const *BinaryCoder::Data() const
    {
        return m_Data;
    }
}
