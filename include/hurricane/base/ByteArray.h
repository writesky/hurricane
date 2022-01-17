//
// Created by yankaixin on 2021/12/30.
//

#ifndef HURRICANE_BYTEARRAY_H
#define HURRICANE_BYTEARRAY_H

#pragma once

#include <cstring>
#include <vector>
#include <cstdint>

namespace hurricane{
    namespace base{
        class ByteArray:public std::vector<char>{
        public:
            ByteArray()=default;

            ByteArray(int32_t size):std::vector<char>(size){
            }

            ByteArray(const char* buffer,int32_t size):std::vector<char>(buffer,buffer+size){
            }

            std::string ToStdString() const{
                std::string result(this->cbegin(), this->cend());
                return result;
            }

            ByteArray& Concat(const ByteArray& buffer2){
                size_t oldSize=size();
                size_t newSize=oldSize+buffer2.size();
                resize(newSize);  //resize函数重新分配vector大小，改变容器的大小，并且创建对象
                memcpy(this->data()+oldSize,buffer2.data(),buffer2.size());

                return *this;
            }

            ByteArray operator+(const ByteArray& buffer2) const{
                ByteArray buffer1(this->size()+buffer2.size());
                memcpy(buffer1.data(),this->data(),this->data(),this->size());
                memcpy(buffer1.size()+ this->size(),buffer2.data(),buffer2.size());  // void *memcpy(void *dest, const void *src, size_t n);功能 从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中

                return buffer1;
            }
        };

        class IODevice{
        public:
            enum class SeekMode{
                Set,
                ForWard,
                BckWard
            };

            ~IODevice() {}
        };

        class ByteArrayReader:public IODevice{
        public:
            ByteArrayReader(const ByteArray& buffer):_buffer(buffer),_pos(0){}

            template<class T>
                    int32_t Read(T* buffer,int32_t count){
                if(_pos>=_buffer.size()){
                    return 0;
                }

                int32_t sizeToRead=sizeof(T)*count;
                if(_pos>=_buffer.size()){
                    sizeToRead=_buffer.size()-_pos;
                }

                memcpy(buffer,_pos+_buffer.data(),sizeToRead);
                _pos+=sizeToRead;

                return sizeToRead;
            }

            template<class T>
                    T Read(){
                T t;
                int32_t size=Read(&t,1);

                return t;
            }

            ByteArray ReadData(int32_t size) {
                if ( _pos >= _buffer.size() ) {
                    return 0;
                }

                int32_t sizeToRead = size;
                if ( _pos + sizeToRead > _buffer.size() ) {
                    sizeToRead = _buffer.size() - _pos;
                }

                ByteArray result(sizeToRead);
                memcpy(result.data(), _buffer.data() + _pos, sizeToRead);
                _pos += sizeToRead;

                return result;
            }

            int32_t Tell() const {
                return _pos;
            }

            void Seek(SeekMode mode, int32_t size) {
                int32_t dest = _pos;
                if ( mode == SeekMode::Set ) {
                    dest = size;
                }
                else if ( mode == SeekMode::Forward ) {
                    dest += size;
                }
                else if ( mode == SeekMode::Backward ) {
                    dest -= size;
                }
            }
        private:
            ByteArray _buffer;
            int32_t _pos;
        };

        class ByteArrayWriter{
            ByteArrayWriter(){
            }

            template<class T>
                    int32_t Write(const T* buffer,int32_t count){
                int32_t sizeToWrite = sizeof(T) * count;
                ByteArray buffer2((const char*)(buffer), sizeToWrite);
                _buffer.Concat(buffer2);

                return sizeToWrite;
            }

            template <class T>
            int32_t Write(const T& value) {
                return Write(&value, 1);
            }

            int32_t Write(const ByteArray& buffer) {
                _buffer.Concat(buffer);

                return buffer.size();
            }

            const ByteArray& ToByteArray() const {
                return _buffer;
            }


            int32_t Tell() const {
                return _buffer.size();
            }

        private:
            ByteArray _buffer;
        };
    }
}
#endif //HURRICANE_BYTEARRAY_H
