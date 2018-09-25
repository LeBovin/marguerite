//
// Created by flaviangontier on 9/24/18.
//

#include <cstring>
#include <iostream>
#include "BinaryStreamWriter.hpp"

BinaryStreamWriter::BinaryStreamWriter()
: BinaryStream()
{ }

BinaryStreamWriter::BinaryStreamWriter(const std::vector<uint8_t> &buffer)
: BinaryStream(buffer.data(), buffer.size())
{ }

BinaryStreamWriter::BinaryStreamWriter(const std::uint8_t *buffer, std::size_t size)
: BinaryStream(buffer, size)
{ }

void BinaryStreamWriter::writeInt(int value)
{
    writeBytes(&value, sizeof(int));
}

void BinaryStreamWriter::writeShort(short value)
{
    writeBytes(&value, sizeof(short));
}

void BinaryStreamWriter::writeString(const std::string &str)
{
    short len = str.length();

    writeShort(len);
    writeBytes(str.data(), str.length());
}

void BinaryStreamWriter::writeBytes(const void *buffer, std::size_t n)
{
    std::unique_lock<std::mutex> locker(m_lock);

    auto nextOffset = m_offset + n;

    if (nextOffset > m_length)
    {
        m_length = nextOffset;
        m_buffer.resize(m_length);
    }

    memcpy(m_buffer.data() + m_offset, buffer, n);
    m_offset += n;
}

std::vector<uint8_t> BinaryStreamWriter::getBuffer()
{
    return (std::vector<uint8_t>(m_buffer));

}
