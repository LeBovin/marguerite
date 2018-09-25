//
// Created by flaviangontier on 9/24/18.
//

#ifndef MARGUERITE_BINARYSTREAMREADER_HPP
#define MARGUERITE_BINARYSTREAMREADER_HPP

#include "BinaryStream.hpp"

class BinaryStreamReader : public BinaryStream
{
public:
    BinaryStreamReader(const std::vector<uint8_t> buffer);
    BinaryStreamReader(const std::uint8_t *buffer, std::size_t length);

    int readInt();
    short readShort();
    const std::string readString();
    void readBytes(void *dest, std::size_t n);
};


#endif //MARGUERITE_BINARYSTREAMREADER_HPP
