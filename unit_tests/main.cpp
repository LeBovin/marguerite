//
// Created by flaviangontier on 9/24/18.
//

#include <iostream>
#include <unistd.h>
#include <cstring>
#include "../io/BinaryStreamWriter.hpp"
#include "../io/BinaryStreamReader.hpp"
#include "../net/Socket.hpp"
#include "../net/TcpServer.hpp"

void io_test()
{
    BinaryStreamWriter writer;

    std::cout << "=========WRITING TESTS==========" << std::endl;
    std::cout << "writing int in the stream:" << 32 << std::endl;
    writer.writeInt(32);
    std::cout << "writing string in the stream: " << "hello world" << std::endl;
    writer.writeString("hello world");
    std::cout << "=====WRITING TESTS FINISHED=====" << std::endl;

    std::cout << std::endl << std::endl;

    BinaryStreamReader reader(writer.getBuffer());
    std::cout << "========READING TESTS===========" << std::endl;
    std::cout << "reading int from the stream: " << (reader.readInt() == 32) << std::endl;
    std::cout << "reading string from the stream: " << (reader.readString() == "hello world") << std::endl;
    std::cout << "=====READING TESTS FINISHED=====" << std::endl;

}

int main(int argc, char **argv)
{
    io_test();
}