/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef MYLIB_SOCKET_HPP
#define MYLIB_SOCKET_HPP

#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <netinet/in.h>

#ifdef _WIN32
#include <winsock2.h>
#endif

namespace marguerite
{
	namespace net
	{
	    enum class IpType
        {
	        V4 = 2,
	        V6 = 10,
        };

	    enum class ProtocolType
		{
	    	TCP = 1,
	    	UDP = 2
		};

		class Socket
		{
		private:
			//FIELDS
			int m_port;
			int m_sockfd;
			std::string m_host;
			sockaddr_in m_sockaddr;
			bool m_binded;
			bool m_listening;
			bool m_connected;

		public:
			//CTOR DTOR
            Socket(int ip_type, int protocol_type);
			Socket(int sockfd, const sockaddr_in &addr);
            Socket(IpType ip_type, ProtocolType protocol_type);
			~Socket();

			//FUNCTIONS
			void mListen(std::size_t capacity);
			std::shared_ptr<Socket> mAccept();
			void mBind(const std::string &host, int port);
			void mConnect(const std::string &host, int port);
			std::vector<uint8_t> mReceive(std::size_t amount);
			void mReceive(uint8_t *dest, std::size_t amount);
			void mSend(const std::vector<uint8_t> &buffer);
			void mSend(const uint8_t *buffer, std::size_t n);

			//PROPERTIES
            int getSockfd() const;
			int available() const;

		};
	};
};


#endif //MYLIB_SOCKET_HPP
