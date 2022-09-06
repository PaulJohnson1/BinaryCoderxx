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

        return {x, 0};
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
        return {int32_t(unsignedValue >> 1) ^ (0 - int32_t(unsignedValue & 1)), 0};
    }
    size_t VarInt::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<VarUint>((VarUint::Type(x) << 1) ^ (x >> 31));
        return 0;
    }
    Value<Uint8::Type> Uint8::Read(BinaryCoder &coder)
    {
        Type x = coder.Data()[coder.At()];
        return {x, 1};
    }
    size_t Uint8::Write(BinaryCoder &coder, Type x)
    {
        coder.Data()[coder.At()] = x;
        return 1;
    }
    Value<Uint16::Type> Uint16::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Uint8>() | ((Type)coder.Read<Uint8>() << 8);
        return {x, 0};
    }
    size_t Uint16::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Uint8>(x & 255);
        coder.Write<Uint8>(x >> 8);
        return 0;
    }
    Value<Uint32::Type> Uint32::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Uint16>() | ((Type)coder.Read<Uint16>() << 16);
        return {x, 0};
    }
    size_t Uint32::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Uint16>(x & 65535);
        coder.Write<Uint16>(x >> 16);
        return 0;
    }
    Value<Uint64::Type> Uint64::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Uint32>() | ((Type)coder.Read<Uint32>() << 32);
        return {x, 0};
    }
    size_t Uint64::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Uint32>(x & 4294967295);
        coder.Write<Uint32>(x >> 32);
        return 0;
    }
    Value<Int8::Type> Int8::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Data()[coder.At()];
        return {x, 1};
    }
    size_t Int8::Write(BinaryCoder &coder, Type x)
    {
        coder.Data()[coder.At()] = x;
        return 1;
    }
    Value<Int16::Type> Int16::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Int8>() | ((Type)coder.Read<Int8>() << 8);
        return {x, 0};
    }
    size_t Int16::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Int8>(x & 255);
        coder.Write<Int8>(x >> 8);
        return 0;
    }
    Value<Int32::Type> Int32::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Int16>() | ((Type)coder.Read<Int16>() << 16);
        return {x, 0};
    }
    size_t Int32::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Int16>(x & 65535);
        coder.Write<Int16>(x >> 16);
        return 0;
    }
    Value<Int64::Type> Int64::Read(BinaryCoder &coder)
    {
        Type x = (Type)coder.Read<Int32>() | ((Type)coder.Read<Int32>() << 32);
        return {x, 0};
    }
    size_t Int64::Write(BinaryCoder &coder, Type x)
    {
        coder.Write<Int32>(x & 4294967295);
        coder.Write<Int32>(x >> 32);
        return 0;
    }
    Value<Float32::Type> Float32::Read(BinaryCoder &coder)
    {
        union
        {
            float floatValue;
            uint32_t uint32Value;
        } conversion;

        conversion.uint32Value = coder.Read<Uint32>();
        return {conversion.floatValue, 0};
    }
    size_t Float32::Write(BinaryCoder &coder, Type x)
    {
        union
        {
            float floatValue;
            uint32_t uint32Value;
        } conversion;

        conversion.floatValue = x;
        coder.Write<Uint32>(conversion.uint32Value);
        return 0;
    }
    Value<Float64::Type> Float64::Read(BinaryCoder &coder)
    {
        union
        {
            double doubleValue;
            uint64_t uint64Value;
        } conversion;

        conversion.uint64Value = coder.Read<Uint64>();
        return {conversion.doubleValue, 0};
    }
    size_t Float64::Write(BinaryCoder &coder, Type x)
    {
        union
        {
            double doubleValue;
            uint64_t uint64Value;
        } conversion;

        conversion.doubleValue = x;
        coder.Write<Uint64>(conversion.uint64Value);
        return 0;
    }
    Value<String::Type> String::Read(BinaryCoder &coder)
    {
        std::string output;
        char byte;
        while (byte = coder.Read<Int8>())
            output.push_back(byte);
        return {output, 0};
    }
    size_t String::Write(BinaryCoder &coder, Type const &x)
    {
        for (size_t i = 0; i < x.size(); i++)
            coder.Write<Int8>(x[i]);
        coder.Write<Int8>(0);
        return 0;
    }
}
