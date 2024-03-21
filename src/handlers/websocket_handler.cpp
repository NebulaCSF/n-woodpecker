/*
* Nebula Atom

* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "handlers/websocket_handler.h"
#include "handlers/root_handler.h"
#include <memory>

using namespace Atom::Handlers;

WebSocketHandler::WebSocketHandler()
{

}

WebSocketHandler::~WebSocketHandler()
{

}

void WebSocketHandler::AddFunctions_()
{

}

void WebSocketHandler::Process_()
{
    try
    {
        websocket_ = std::make_unique<WebSocket>(*get_request(), *get_response());
        websocket_->setReceiveTimeout(Poco::Timespan());
        app_.logger().information("-- WebSocket connection established.");

        HandleNewConnection_(get_request(), *this);
        Transfer_();
        HandleConnectionClosed_(*this);
    }
    catch (WebSocketException& error)
    {
        app_.logger().log(error);
        switch (error.code())
        {
            case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
                get_response()->set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
            case WebSocket::WS_ERR_NO_HANDSHAKE:
            case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
            case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
                get_response()->setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
                get_response()->setContentLength(0);
                get_response()->send();
                break;
        }
    }
    catch(std::exception& error)
    {
        app_.logger().error("- Error on websocket_handler.cpp on Process_(): " + std::string(error.what()));
        JSONResponse_(HTTP::Status::kHTTP_INTERNAL_SERVER_ERROR, "Internal server error. " + std::string(error.what()));
    }
}

void WebSocketHandler::HandleGETMethod_()
{
    
}

void WebSocketHandler::HandlePOSTMethod_()
{
    
}

void WebSocketHandler::HandlePUTMethod_()
{
    
}

void WebSocketHandler::HandleDELMethod_()
{
    
}

void WebSocketHandler::Transfer_()
{
    char buffer[1024];
    int flags, n;

    do
    {
        n = websocket_->receiveFrame(buffer, sizeof(buffer), flags);
        if(n > 0 && (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE)
        {
            if ((flags & WebSocket::FRAME_OP_BITMASK) == WebSocket::FRAME_OP_PING)
                websocket_->sendFrame(buffer, n, WebSocket::FRAME_OP_PONG);
            else
            {
                std::string message(buffer, n);
                HandleNewMessage_(*this, message);
            }
        }
    }
    while (n > 0 && (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);

    app_.logger().information("-- WebSocket connection closed.");

}

void WebSocketHandler::Send_(std::string message) const
{
    char buffer[1024];
    int n = 0;
    for(auto it : message)
    {
        buffer[n] = it;
        n++;
    }
    websocket_->sendFrame(buffer, n);
}