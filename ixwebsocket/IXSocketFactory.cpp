/*
 *  IXSocketFactory.cpp
 *  Author: Benjamin Sergeant
 *  Copyright (c) 2019 Machine Zone, Inc. All rights reserved.
 */

#include "IXSocketFactory.h"

# ifdef __APPLE__
#  include <ixwebsocket/IXSocketAppleSSL.h>
# elif defined(_WIN32)
#  include <ixwebsocket/IXSocketSChannel.h>
# else
#  include <ixwebsocket/IXSocketOpenSSL.h>
# endif

namespace ix
{
    std::shared_ptr<Socket> createSocket(bool tls,
                                         std::string& errorMsg)
    {
        errorMsg.clear();
        std::shared_ptr<Socket> socket;

        if (!tls)
        {
            socket = std::make_shared<Socket>();
        }
        else
        {
# ifdef __APPLE__
            socket = std::make_shared<SocketAppleSSL>();
# elif defined(_WIN32)
            socket = std::make_shared<SocketSChannel>();
# else
            socket = std::make_shared<SocketOpenSSL>();
# endif
        }

        if (!socket->init(errorMsg))
        {
            socket.reset();
        }

        return socket;
    }

    std::shared_ptr<Socket> createSocket(int fd,
                                         std::string& errorMsg)
    {
        errorMsg.clear();

        std::shared_ptr<Socket> socket = std::make_shared<Socket>(fd);
        if (!socket->init(errorMsg))
        {
            socket.reset();
        }

        return socket;
    }
}
