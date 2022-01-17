//
// Created by yankaixin on 2021/12/19.
//

#ifndef HURRICANE_VALUES_H
#define HURRICANE_VALUES_H
#include <string>
#include<exception>
#include<cstdint>
#include<vector>
#include <initializer_list>
#include<iostream>
#define NOEXCEPT noexcept
#endif //HURRICANE_VALUES_H

//元组接口
namespace hurricane{
    namespace base{
        class Variant;

        class TypeMismatchException : std::exception {
        public:
            TypeMismatchException(const std::string& message) :
                    _message(message) {}


            const char* what() const NOEXCEPT override{
                return _message.c_str();
            }

        private:
            std::string _message;
        };

        class Value{
        public:
            enum class Type{
                Invalid,
                Boolean,
                Character,
                Int8,
                Int16,
                Int32,
                Int64,
                Float,
                Double,
                String
            };

            union InnerValue{
                bool booleanValue;
                bool booleanValue;
                char characterValue;
                int8_t int8Value;
                int16_t int16Value;
                int32_t int32Value;
                int64_t int64Value;
                float floatValue;
                double doubleValue;
            };
            Value():_type(Type::Invalid){
            }
            Value(bool value) : _type(Type::Boolean) {
                _value.booleanValue = value;
            }

            Value(char value) : _type(Type::Character) {
                _value.characterValue = value;
            }

            Value(int8_t value) : _type(Type::Int8) {
                _value.int8Value = value;
            }

            Value(int16_t value) : _type(Type::Int16) {
                _value.int16Value = value;
            }

            Value(int32_t value) : _type(Type::Int32) {
                _value.int32Value = value;
            }

            Value(int64_t value) : _type(Type::Int64) {
                _value.int64Value = value;
            }

            Value(float value) : _type(Type::Float) {
                _value.floatValue = value;
            }

            Value(double value) : _type(Type::Double) {
                _value.doubleValue = value;
            }

            Value(const std::string& value) : _type(Type::String) {
                _stringValue = value;
            }

            Value(const char* value) : Value(std::string(value)) {
            }
            bool ToBoolean() const {
                if(_type!=Type::Boolean){
                    throw TypeMismatchException("The type of value is not boolean");
                }
            }
            int8_t ToInt8() const {
                if ( _type != Type::Int8 ) {
                    throw TypeMismatchException("The type of value is not int8");
                }

                return _value.int8Value;
            }

            int16_t ToInt16() const {
                if ( _type != Type::Int16 ) {
                    throw TypeMismatchException("The type of value is not int16");
                }

                return _value.int16Value;
            }

            int32_t ToInt32() const {
                if ( _type != Type::Int32 ) {
                    throw TypeMismatchException("The type of value is not int32");
                }

                return _value.int32Value;
            }

            int64_t ToInt64() const {
                if ( _type != Type::Int64 ) {
                    throw TypeMismatchException("The type of value is not int64");
                }

                return _value.int64Value;
            }

            char ToCharacter() const {
                if ( _type != Type::Character ) {
                    throw TypeMismatchException("The type of value is not character");
                }

                return _value.characterValue;
            }

            const std::string& ToString() const {
                if ( _type != Type::String ) {
                    throw TypeMismatchException("The type of value is not string");
                }

                return _stringValue;
            }
            Variant toVariant() const;
            static Value FromVariant(const Variant& variant);
        private:
            Type _type;
            InnerValue _value;
            std::string _stringValue;
        };

    class Values:public std::vector<Value>{
    public:
        Values()=default;
        Values(std::initializer_list<Value> values):std::vector<Value>(values){
        }
        Value& operator[](size_t index){
            return std::vector<Value>::operator[](index);
        }
        const Value& operator[](size_t index) const {
            return std::vector<Value>::operator[](index);
        }
    };
    }
}
