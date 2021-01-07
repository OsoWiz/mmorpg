#pragma once 

#include "common.h"
#include "../networking/connection.hpp"



class Connection;

//Represents a message sent between client and server.

struct msg_header {
    unsigned int id{};
    uint32_t size = 0;

};


class Message
{
    public:

        Message(std::shared_ptr<Connection> connection, msg_header header, const std::string& body)
            : _connection(connection),_header(header), _body(body) {}

        

        const std::string& GetBody() const
        {
            return _body; 
        }

        const msg_header& GetHeader() const
        {
            return _header;
        }

        uint32_t GetSize() const {
            return _header.size;
        }

        const std::shared_ptr<Connection>& GetConn() const {
            return _connection;
        }

    private:
        std::shared_ptr<Connection> _connection; 
        msg_header _header;
        std::string _body; 
};

