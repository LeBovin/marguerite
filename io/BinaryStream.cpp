/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#include <cstring>
#include "BinaryStream.hpp"

BinaryStream::BinaryStream(const std::vector<uint8_t> &buffer)
: BinaryStream(buffer.data(), buffer.size())
{
}

BinaryStream::BinaryStream(const std::uint8_t *buffer, std::size_t size)
: m_length(size),
  m_offset(0)
{
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


int BinaryStream::readInt()
{
	int ret = 0;

	fastReadBytes(&ret, sizeof(ret));
}
short BinaryStream::readShort()
{
	short ret = 0;

	fastReadBytes(&ret, sizeof(ret));
}
const std::string &BinaryStream::readString()
{
	short length = 0;
	fastReadBytes(&length, sizeof(length));

	std::unique_ptr<char[]> buffer(new char[length]);
	fastReadBytes(buffer.get(), length);

	std::string ret(buffer.get());
	return (ret);
}

void BinaryStream::fastReadBytes(void *dest, std::size_t n)
{
	std::unique_lock<std::mutex> locker(m_lock);

	memcpy(dest, m_buffer.data(), n);
	m_offset += n;
}

const std::vector<uint8_t> &BinaryStream::readBytes(std::size_t n)
{
	std::unique_lock<std::mutex> locker(m_lock);

	auto nextOffset = m_offset + n;
	if (nextOffset >= m_length)
		throw std::runtime_error("out of range.");

	std::vector<uint8_t> ret(n);
	memcpy(ret.data(), m_buffer.data() + m_offset, n);

	m_offset += n;
}

size_t BinaryStream::getOffset() const
{
	return m_offset;
}
size_t BinaryStream::getLength() const
{
	return m_length;
}
