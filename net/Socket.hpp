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

using socketAcceptCallback = std::function<void(int, const sockaddr_in &)>;

namespace marguerite
{
	namespace net
	{
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

		public:
			//CTOR DTOR
			Socket();
			~Socket();

			//FUNCTIONS
			void mListen(std::size_t capacity);
			void mAccept(socketAcceptCallback callback);
			void mBind(const std::string &host, int port);
			void mConnect(const std::string &host, int port);

		};
	};
};


#endif //MYLIB_SOCKET_HPP
