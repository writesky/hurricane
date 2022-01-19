
#ifndef HURRICANE_DATAPACKAGE_H
#define HURRICANE_DATAPACKAGE_H

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>
#include <map>
#include <memory>
#include <vector>
#include "Variant.h"
#include "ByteArray.h"

namespace hurricane{
    namespace base{
        class Writable{ //序列化接口设计
        public:
            virtual int32_t Read(ByteArrayReader& reader, Variant& variant) = 0; //读取数据并放入对象内部
            virtual int32_t Write(ByteArrayWriter& writer, const Variant& variant) = 0; //将对象内部数据输出到二进制流中
        };

        class IntWritable:public Writable{
        public:
            int32_t Read(ByteArrayReader& reader,Variant& variant) override{
                int32_t intValue=reader.Read<int32_t >();
                variant.SetIntValue(intValue);

                return sizeof (int32_t);
            }

            int32_t Write(ByteArrayWriter& writer,const Variant& variant) override{
                int value=variant.GetIntValue();
                writer.Write(value);

                return sizeof (int32_t);
            }
        };

        class StringWritable:public Writable{
            int32_t Read(ByteArrayReader& reader, Variant& variant) override {
                int32_t size = reader.Read<int32_t>();

                ByteArray bytes = reader.ReadData(size);

                variant.SetStringValue(bytes.ToStdString());

                return sizeof(int32_t) + bytes.size();
            }

            int32_t Write(ByteArrayWriter& writer, const Variant& variant) override {
                std::string value = variant.GetStringValue();

                writer.Write(int32_t(value.size()));
                writer.Write(value.c_str(), value.size());
                return sizeof(int32_t) + value.size();
            }
        };

        extern std::map<int8_t,std::shared_ptr<Writable>> Writables;

        class DataPackage {
        public:
            DataPackage() : _version(0) {}

            void AddVariant(const Variant& variant) {
                _variants.push_back(variant);
            }

            const Variants& GetVariants() const {
                return _variants;
            }

            ByteArray Serialize() {
                ByteArray body = SerializeBody();
                ByteArray head = SerializeHead(body.size());

                return head + body;
            }

            void Deserialize(const ByteArray& data) {
                ByteArrayReader reader(data);

                DeserializeHead(reader);
                DeserializeBody(reader);
            }

        private:
            ByteArray SerializeBody() {
                ByteArrayWriter bodyWriter;
                for ( const Variant& variant : _variants ) {
                    SerializeVariant(bodyWriter, variant);
                }
                return bodyWriter.ToByteArray();
            }

            ByteArray SerializeHead(int32_t bodySize) {
                ByteArrayWriter headWriter;
                _length = sizeof(int32_t) + sizeof(_version) + bodySize;
                headWriter.Write(_length);
                headWriter.Write(_version);
                ByteArray head = headWriter.ToByteArray();

                return head;
            }

            void DeserializeHead(ByteArrayReader& reader) {
                _length = reader.Read<int32_t>();
                _version = reader.Read<int8_t>();
            }

            void DeserializeBody(ByteArrayReader& reader) {
                while ( reader.Tell() < _length ) {
                    Variant variant = DeserializeVariant(reader);
                    _variants.push_back(variant);
                }
            }

            Variant DeserializeVariant(ByteArrayReader& reader) {
                Variant variant;

                if ( reader.Tell() >= _length ) {
                    return variant;
                }

                int8_t typeCode = reader.Read<int8_t>();
                std::shared_ptr<Writable> writable = Writables[typeCode];
                writable->Read(reader, variant);

                return variant;
            }

            void SerializeVariant(ByteArrayWriter& writer, const Variant& variant) {
                Variant::Type type = variant.GetType();
                int8_t typeCode = Variant::TypeCodes[type];
                std::shared_ptr<Writable> writable = Writables[typeCode];

                writer.Write<int8_t>(typeCode);
                writable->Write(writer, variant);
            }

            int8_t _version;
            int32_t _length;
            std::vector<Variant> _variants;
        };
    }
}
#endif //HURRICANE_DATAPACKAGE_H
