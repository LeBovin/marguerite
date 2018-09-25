/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#include <unistd.h>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <asm/ioctls.h>
#include <sys/ioctl.h>
#include "Socket.hpp"

marguerite::net::Socket::Socket(IpType ip_type, ProtocolType protocol_type)
: Socket((int)ip_type, (int)protocol_type)
{ }

marguerite::net::Socket::Socket(int ip_type, int protocol_type)
: m_binded(false),
  m_listening(false),
  m_connected(false)
{

#ifdef _WIN32
	WSADATA wsa;
	SOCKET sock;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		std::runtime_error("cannot start winsock.");
#endif

	m_sockfd = socket(ip_type, protocol_type, 0);
	if (m_sockfd == -1)
		throw std::runtime_error("cannot create socket.");
}

marguerite::net::Socket::~Socket()
{
	if (m_sockfd != -1)
		close(m_sockfd);
}


void marguerite::net::Socket::mBind(const std::string &host, int port)
{
	int optname = 1;
	if (setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optname, sizeof(optname)) == -1)
		throw std::runtime_error("cannot re-use address or port.");

	sockaddr_in laddr;
	laddr.sin_family = AF_INET;
	laddr.sin_addr.s_addr = inet_addr(host.c_str());
	laddr.sin_port = htons(port);

	if (bind(m_sockfd, (sockaddr *)&laddr, sizeof(laddr)) == -1)
		throw std::runtime_error("cannot bind the socket.");

	m_binded = true;
}

void marguerite::net::Socket::mAccept(socketAcceptCallback callback)
{
	if (!m_binded || !m_listening)
		throw std::runtime_error("trying to accept incoming connection on unbinded or non-listening socket.");

	sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	int sockfd = accept(m_sockfd, (sockaddr *)&addr, &addrlen);

	if (sockfd == -1)
		throw std::runtime_error("accepting incoming connection failed.");

	callback(sockfd, addr);
}

void marguerite::net::Socket::mListen(std::size_t capacity)
{
	if (!m_binded)
		throw std::runtime_error("try to listen on unbinded socket.");

	if (listen(m_sockfd, capacity) == -1)
		throw std::runtime_error("cannot listen on given socket.");

	m_listening = true;
	m_connected = true;
}

void marguerite::net::Socket::mConnect(const std::string &host, int port)
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(host.c_str());
	addr.sin_port = htons(port);

	if (connect(m_sockfd, (sockaddr *)&addr, sizeof(addr)) == -1)
		throw std::runtime_error("cannot connect to given remote addr/port.");

	m_connected = true;
}
std::size_t marguerite::net::Socket::avaible() const
{
	if (!m_connected || !m_listening)
		return 0;

	std::size_t amount;
	if (ioctl(m_sockfd, FIONREAD, &amount) == -1)
		throw std::runtime_error("cannot get amount of avaible data on the socket.");

	return (amount);
}
