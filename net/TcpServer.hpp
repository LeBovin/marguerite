//
// Created by flaviangontier on 9/26/18.
//

#ifndef MARGUERITE_TCPSERVER_HPP
#define MARGUERITE_TCPSERVER_HPP

#include <string>
#include "Socket.hpp"

namespace marguerite
{
    namespace net
    {
        class TcpServer
        {
        public:
            //CTOR DTOR
            TcpServer(const std::string &host, int port, std::size_t max = 100);
            ~TcpServer();

            //FUNCTIONS
            void stop();
            void start();

        private:
            //FIELDS
            int m_epollfd;
            bool m_running;
            std::size_t m_max;
            Socket m_listener;
            std::unordered_map<int, std::shared_ptr<Socket>> m_clients;

            //functions
            virtual void onClientAccepted(std::shared_ptr<Socket> socket);
            virtual void onMessageReceived(std::shared_ptr<Socket> socket, std::vector<uint8_t> message);
            virtual void onClientDisconnected(std::shared_ptr<Socket> socket);
        };
    }
}


#endif //MARGUERITE_TCPSERVER_HPP
