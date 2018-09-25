//
// Created by flaviangontier on 9/24/18.
//

#include <cstring>
#include <iostream>
#include "BinaryStreamReader.hpp"

BinaryStreamReader::BinaryStreamReader(const std::uint8_t *buffer, std::size_t length)
: BinaryStream(buffer, length)
{ }

BinaryStreamReader::BinaryStreamReader(const std::vector<uint8_t> buffer)
: BinaryStream(buffer)
{
}

int BinaryStreamReader::readInt()
{
    int ret = 0;

    readBytes(&ret, sizeof(ret));
    return (ret);
}
short BinaryStreamReader::readShort()
{
    short ret = 0;

    readBytes(&ret, sizeof(ret));
    return (ret);
}
const std::string BinaryStreamReader::readString()
{
    short len = readShort();
    char *buf = (char *)malloc(sizeof(char) * (len + 1));

    readBytes(buf, len);

    std::string ret(buf, len);
    free(buf);

    return (ret);
}

void BinaryStreamReader::readBytes(void *dest, std::size_t n)
{
    std::unique_lock<std::mutex> locker(m_lock);

    auto nextOffset = m_offset + n;
    if (nextOffset > m_length)
        throw std::runtime_error("out of range.");

    memcpy(dest, m_buffer.data() + m_offset, n);

    m_offset = nextOffset;
}
