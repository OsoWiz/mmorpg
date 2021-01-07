#pragma once

#include "../networking/common.h"
#include "../networking/tsqueue.h"
#include "../networking/message.h"




class Connection : public std::enable_shared_from_this<Connection> {
public:


    enum class owner
    {
        server,
        client
    };

    Connection(owner parent, asio::io_context& context, asio::ip::tcp::socket s, tsqueue<Message>& inc) : asioContext(context), socket(std::move(s)), incomingMessages(inc)
    {
        ownertype = parent;
    }

    ~Connection() {}

    uint32_t GetID() const { return id; }

    void ConnectToServer(const asio::ip::tcp::resolver::results_type& endpoints) { // Connects to server
        if (ownertype == owner::client) {
            asio::async_connect(socket, endpoints, [this](std::error_code errorcode, asio::ip::tcp::endpoint endpoint) {
                if (!errorcode) ReadHeader();
                });
        }
    }

    void ConnectToClient(uint32_t userid = 0) { // Connects to client

        if (ownertype == owner::server) {
            if (socket.is_open()) {
                id = userid;
                ReadHeader();
            }
        }
    }

    bool IsConnected() const { return socket.is_open(); }

    void Disconnect() {
        if (IsConnected()) asio::post(asioContext, [this]() {socket.close(); });
    }

    void Send(const Message& msg) {
        asio::post(asioContext,
            [this, msg]()
            {
                bool writingMessage = !outgoingMessages.empty();
                outgoingMessages.push_back(msg);
                if (!writingMessage) WriteHeader();
            });
    }

private:


    void WriteHeader() {
        asio::async_write(socket, asio::buffer(&outgoingMessages.front().GetHeader(), sizeof(msg_header)),
            [this](std::error_code errorcode, std::size_t length) {
                if (!errorcode) {
                    if (outgoingMessages.front().GetSize() > 0) { WriteBody(); }
                    else {
                        outgoingMessages.pop_front();
                        if (!outgoingMessages.empty()) {
                            WriteHeader();
                        }
                    }
                }
                else {
                    std::cout << id << ": Write Header failed." << std::endl;
                    socket.close();

                }
            });
    }

    void WriteBody() {
        asio::async_write(socket, asio::buffer(&outgoingMessages.front().GetBody(), outgoingMessages.front().GetSize()),
            [this](std::error_code errorcode, std::size_t length) {
                if (!errorcode) {
                    outgoingMessages.pop_front();
                    if (!outgoingMessages.empty()) {
                        WriteHeader();
                    }
                }
                else {
                    std::cout << id << ": Write Body failed." << std::endl;
                }
            });
    }

    void ReadHeader() {
        asio::async_read(socket, asio::buffer(&tempHeader, sizeof(msg_header)),
            [this](std::error_code errorcode, std::size_t length)
            {
                //std::cout << "Read Header called" << std::endl;
                if (!errorcode) {
                    if (tempHeader.size > 0) {
                        ReadBody();
                    }
                    else {
                        AddToIncomingMessages();
                    }
                }
                else {
                    std::cout << id << "Reading header failed." << std::endl;
                    socket.close();
                }
            });
    }

    void ReadBody() {
        asio::async_read(socket, asio::buffer(&tempBody, tempHeader.size),
            [this](std::error_code errorcode, std::size_t length)
            {
                if (!errorcode) {
                    AddToIncomingMessages();
                }
                else {
                    std::cout << id << " Reading body failed." << std::endl;
                    socket.close();
                }
            });
    }

    void AddToIncomingMessages() {
        if (ownertype == owner::server) incomingMessages.push_back(Message(this->shared_from_this(), tempHeader, tempBody));
        else incomingMessages.push_back(Message(nullptr, tempHeader, tempBody));
        ReadHeader();
    }


protected:


    asio::io_context& asioContext;
    asio::ip::tcp::socket socket;

    tsqueue<Message> outgoingMessages;
    tsqueue<Message>& incomingMessages;

    msg_header tempHeader;
    std::string tempBody;
    owner ownertype = owner::server;

    uint32_t id = 0;

};