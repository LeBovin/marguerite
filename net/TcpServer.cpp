//
// Created by flaviangontier on 9/26/18.
//

#include <iostream>
#include <sys/epoll.h>
#include <cstring>
#include "TcpServer.hpp"

marguerite::net::TcpServer::TcpServer(const std::string &host, int port, std::size_t max)
: m_listener(IpType::V4, ProtocolType::TCP), m_max(max)
{
    try
    {
        m_listener.mBind(host, port);
        m_listener.mListen(max);
    }
    catch (std::exception &ex)
    {
        std::cerr << "cannot setup the server listener. error:" << ex.what() << std::endl;
    }

    m_epollfd = epoll_create(max);
    if (m_epollfd == -1)
        throw std::runtime_error("cannot create epoll queue.");

    epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = m_listener.getSockfd();

    if (epoll_ctl(m_epollfd, EPOLL_CTL_ADD, evt.data.fd, &evt) == -1)
        throw std::runtime_error("cannot add listener socket to epoll.");
}

marguerite::net::TcpServer::~TcpServer()
{

}

void marguerite::net::TcpServer::stop()
{
    m_running = false;
}

void marguerite::net::TcpServer::start()
{
    epoll_event events[m_max];
    int listenerfd = m_listener.getSockfd();

    m_running = true;
    while (m_running)
    {
        int fds = epoll_wait(m_epollfd, events, m_max, -1);
        if (fds == -1)
            throw std::runtime_error("cannot check incoming activity.");

        for (int index = 0; index < fds; index++)
        {
            int sockfd = events[index].data.fd;
            if (sockfd == listenerfd)
            {
                auto client = m_listener.mAccept();
                int newfd = client->getSockfd();

                epoll_event evt;
                evt.data.fd = newfd;
                evt.events = EPOLLIN;
                epoll_ctl(m_epollfd, EPOLL_CTL_ADD, newfd, &evt);

                m_clients.insert({newfd, client});
                onClientAccepted(client);
            }
            else
            {
                auto client = m_clients[sockfd];
                auto amount = client->available();
                if (amount == 0)
                {
                    onClientDisconnected(client);
                    continue;
                }

                auto message = client->mReceive(amount);
                if (message.empty())
                    onClientDisconnected(client);
                else
                    onMessageReceived(client, std::move(message));
            }
        }
    }
}

void marguerite::net::TcpServer::onClientDisconnected(std::shared_ptr<marguerite::net::Socket> socket)
{
    epoll_event evt;

    evt.events = EPOLLIN;
    evt.data.fd = socket->getSockfd();
    if (epoll_ctl(m_epollfd, EPOLL_CTL_DEL, socket->getSockfd(), &evt) == -1)
        throw std::runtime_error("cannot remove fd from epoll.");
    m_clients.erase(socket->getSockfd());
    std::cout << "client disconnected." << std::endl;
}

void marguerite::net::TcpServer::onClientAccepted(std::shared_ptr<Socket> socket)
{
    std::cout << "new client accepted." << std::endl;
}

void marguerite::net::TcpServer::onMessageReceived(std::shared_ptr<Socket> socket, std::vector<uint8_t> message)
{
    char *str = (char *)malloc(sizeof(char) * (message.size() + 1));
    str[message.size()] = 0;
    memcpy(str, message.data(), message.size());

    std::cout << "new message received: " << str << std::endl;
}
