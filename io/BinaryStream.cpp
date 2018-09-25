/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#include <cstring>
#include <iostream>
#include "BinaryStream.hpp"

BinaryStream::BinaryStream()
: m_length(4), m_offset(0)
{
    m_buffer.resize(m_length);
}

BinaryStream::BinaryStream(const std::vector<uint8_t> &buffer)
: BinaryStream(buffer.data(), buffer.size())
{
}

BinaryStream::BinaryStream(const std::uint8_t *buffer, std::size_t size)
: m_length(size),
  m_offset(0)
{
    if (size == 0)
        size = 4;
	m_buffer.resize(size);
	memcpy(m_buffer.data(), buffer, size);
}


void BinaryStream::clear()
{
	if (m_offset == 0)
		return;

	std::unique_lock<std::mutex> locker(m_lock);
	m_offset = 0;
}

void BinaryStream::forward(std::size_t n)
{
	auto nextOffset = m_offset + n;
	if (nextOffset >= m_length)
		throw std::runtime_error("out of range.");

	std::unique_lock<std::mutex> locker(m_lock);
	m_offset = nextOffset;
}

size_t BinaryStream::getOffset() const
{
	return m_offset;
}
size_t BinaryStream::getLength() const
{
	return m_length;
}
