/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef MYLIB_SOCKET_HPP
#define MYLIB_SOCKET_HPP

#include <string>
#include <netinet/in.h>

namespace marguerite
{
	namespace net
	{
		class Socket
		{
		private:
			//FIELDS
			int m_port;
			std::string m_host;
			sockaddr_in m_sockaddr;

		public:
			//CTOR DTOR
			Socket(const std::string &host, int port, bool block);

		};
	};
};


#endif //MYLIB_SOCKET_HPP
