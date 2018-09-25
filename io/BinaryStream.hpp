/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef MARGUERITE_BINARYSTREAM_HPP
#define MARGUERITE_BINARYSTREAM_HPP


#include <cstdint>
#include <vector>
#include <mutex>
#include <memory>

class BinaryStream
{
public:
	//CTOR DTOR
	BinaryStream();
	BinaryStream(const std::vector<uint8_t> &buffer);
	BinaryStream(const std::uint8_t *buffer, std::size_t size);
	~BinaryStream() = default;

	//PUBLIC FUNCTIONS
	void clear();
	void forward(std::size_t n);

	//PROPERTIES
	size_t getOffset() const;
	size_t getLength() const;

protected:
	//FIELDS
	std::mutex m_lock;
	std::size_t m_offset;
	std::size_t m_length;
	std::vector<uint8_t> m_buffer;
};


#endif //MARGUERITE_BINARYSTREAM_HPP
