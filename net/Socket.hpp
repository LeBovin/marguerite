/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef MYLIB_SOCKET_HPP
#define MYLIB_SOCKET_HPP

#include <string>
#include <functional>
#include <netinet/in.h>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#endif

namespace marguerite
{
	namespace net
	{
        using socketAcceptCallback = std::function<void(int, const sockaddr_in &)>;

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
            Socket(IpType ip_type, ProtocolType protocol_type);
			~Socket();

			//FUNCTIONS
			void mListen(std::size_t capacity);
			void mAccept(socketAcceptCallback callback);
			void mBind(const std::string &host, int port);
			void mConnect(const std::string &host, int port);
			void mReceive(std::size_t amount);
			void mSend(const std::vector<uint8_t> &buffer);
			void mSend(const uint8_t *buffer, std::size_t n);

			//PROPERTIES
			std::size_t avaible() const;

		};
	};
};


#endif //MYLIB_SOCKET_HPP
