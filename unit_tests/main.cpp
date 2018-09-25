//
// Created by flaviangontier on 9/24/18.
//

#include <iostream>
#include <unistd.h>
#include "../io/BinaryStreamWriter.hpp"
#include "../io/BinaryStreamReader.hpp"
#include "../net/Socket.hpp"

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

void network_test()
{
    std::cout << "=========NETWORK TESTS==========" << std::endl;
    marguerite::net::Socket sock(marguerite::net::IpType::V4, marguerite::net::ProtocolType::TCP);
    auto callback = [](int sockfd, const sockaddr_in &addr)
    {
        std::cout << "new connection accepted." << std::endl;
        close(sockfd);
    };
    std::cout << "binding the socket..." << std::endl;
    sock.mBind("127.0.0.1", 6666);
    std::cout << "socked binded." << std::endl;
    std::cout << "listening on the socket..." << std::endl;
    sock.mListen(1);
    std::cout << "listening setup." << std::endl;
    std::cout << "waiting for new connection..." << std::endl;
    sock.mAccept(callback);
    std::cout << "=====NETWORK TESTS FINISHED=====" << std::endl;
}

int main(int argc, char **argv)
{
    io_test();
    network_test();
}