#include <BinaryCoder/NativeTypes.hh>

namespace bc
{
    Value<VarUint::Type> VarUint::Read(BinaryCoder &coder)
    {
        Type x = 0;
        Type shift = 0;
        while (coder.Data()[coder.At()] & 0x80)
        {
            uint64_t byte = coder.Read<Uint8>();
            x |= (byte & 127) << shift;
            shift += 7;
        }

        x |= (coder.Read<Uint8>() & 127) << shift;

        return Value<Type>{x, 0};
    }
    size_t VarUint::Write(BinaryCoder &coder, Type x)
    {
        do
        {
            uint8_t byte = x & 127;
            x >>= 7;
            if (x != 0)
                byte |= 128;
            coder.Write<Uint8>(byte);
        } while (x != 0);

        return 0;
    }
    Value<VarInt::Type> VarInt::Read(BinaryCoder &coder)
    {
        VarUint::Type unsignedValue = coder.Read<VarUint>();
        return Value<VarInt::Type>{int32_t(unsignedValue >> 1) ^ (0 - int32_t(unsignedValue & 1)), 0};
    }
    size_t VarInt::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<VarUint>((VarUint::Type(x) << 1) ^ (x >> 31));
        return 0;
    }
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
}