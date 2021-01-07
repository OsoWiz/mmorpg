#pragma once

#include "../networking/common.h"
#include "../networking/connection.hpp"
#include "../networking/message.h"

class Client
{
    public:

        Client() {}

        //When client is destroyed, disconnect.
        ~Client()
        {
            Disconnect();
        }

        //Connect to the server. 
        bool Connect(const std::string& host, const int port)
        {

            try
            {
                asio::ip::tcp::resolver resolver(context);
                asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));
                
                connection = std::make_unique<Connection>(Connection::owner::client, context, asio::ip::tcp::socket(context), _messages);

                connection->ConnectToServer(endpoints);

                thrContext = std::thread([this]() {context.run();});

            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return false;
            }
            return true; 

        }

        void Disconnect()
        {
            std::cout << "client Disconnect called" << std::endl;
            if (isConnected())
            {
                connection->Disconnect();
            }
			
            context.stop();
            if (thrContext.joinable())
                thrContext.join();

            connection.release();
        }

        bool isConnected() {
            if (connection) return connection->IsConnected();
            else {
                std::cout << "returned false??" << std::endl; return false;
            }
        }

        //Sends message to server. 
        void Send(const Message& msg)
        {
            if (isConnected()) { connection->Send(msg); }
        }

        tsqueue<Message>& Incoming() { return _messages; }

        void PingServer()
        {
            std::cout << "Ping server called" << std::endl;
            msg_header test;

            test.id = 123;
            test.size = 0;
            Message msg = Message(nullptr, test, "");

            Send(msg);
        }

        void Move(int x, int y, int id) {

            std::cout << "Move called" << std::endl;
            
            msg_header head;
            head.id = 1;
            
            std::stringstream ss;
            
            ss << x << "/" << y << "/" << id << "/";
            std::string s = ss.str();
            
            head.size = uint32_t(sizeof(s) + s.size());
            
            Send(Message(nullptr, head, s));
        }

    protected:
        std::unique_ptr<Connection> connection;
        asio::io_context context;
        std::thread thrContext;

    private:
        //Messages from server are stored here.
        tsqueue<Message> _messages;
};