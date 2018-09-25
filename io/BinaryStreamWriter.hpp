//
// Created by flaviangontier on 9/24/18.
//

#ifndef MARGUERITE_BINARYSTREAMWRITER_HPP
#define MARGUERITE_BINARYSTREAMWRITER_HPP

#include "BinaryStream.hpp"

class BinaryStreamWriter : public BinaryStream
{
public:
    BinaryStreamWriter();
    BinaryStreamWriter(const std::vector<uint8_t> &buffer);
    BinaryStreamWriter(const std::uint8_t *buffer, std::size_t size);

    void writeInt(int value);
    void writeShort(short value);
    void writeString(const std::string &str);
    void writeBytes(const void *buffer, std::size_t n);

    std::vector<uint8_t> getBuffer();
};


#endif //MARGUERITE_BINARYSTREAMWRITER_HPP
