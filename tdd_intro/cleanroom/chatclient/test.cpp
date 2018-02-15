#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ISocketWrapper.h"
#include "IGui.h"

using namespace testing;
/*
Implement chat application, that communicates via TCP sockets.
 There is list of requirenments to this application:
 * It receives user nickname through commandline arguments on start
 * It runs only for two clients
 * On start it checks if port 4444 is bound
    * if it is - connects to other client
    * if not - binds a port and waits for inbound connection
        * message "No one is here..." is displayed in UI
 * After establishing connection - handshake is performed:
    * client writes message with it's nickname and ':HELLO!' string to socket ("metizik:HELLO!")
    * server responses with it's nickname and ':HELLO!' magic ("user:HELLO!")
        * if server receives malformated message - it drops connection with this client
        * if client receives malformated message - it drops connection and exits
            * Error message is shown
    * Listening socket must be closed
        (i) More than one client is not allowed to connect

 * It must send messages via created connection, until it is dropped
    * Application outputs "me: " prefix for user input
    * User inputs message through console interface and presses ENTER
    * Text message is sent to socket
 * It must receive messages via created connection, until it is dropped
    * Message received through socket
    * Line with message and '@friend_name: ' prefix is displayed ("metizik: Hello!")
 * END of message is determined by '\0' byte
 * When connection is dropped by one of users
    * "You are alone now" message is displayed to user
    * Application exits

  (i) Client starts dialog

 OPTIONAL requirement:
    * If user enters '!exit!' message, application must close connection and exit
    * If user runs app with 'me' nickname - error with text "Username me is reserved and can not be used"  is displayed and application exits
*/

class MockSocketWrapper : public ISocketWrapper
{
public:
    MOCK_METHOD2(Connect, ISocketWrapper::SockPtr(const std::string& addr, int16_t port));
    MOCK_METHOD2(Bind, void(const std::string& addr, int16_t port));
    MOCK_METHOD0(Listen, void());
};

class MockGui : public IGui
{
public:
    MOCK_METHOD1(Print, void(const std::string&));
};

const std::string s_host = "localhost";
const int16_t s_port = 4444;
const std::string s_listenMessage = "No one is here…";

void Connect(ISocketWrapper& socket)
{
    socket.Connect(s_host, s_port);
}

void SetupServer(ISocketWrapper& socket)
{
    socket.Bind(s_host, s_port);
    socket.Listen();
}

void InitSession(ISocketWrapper& socket, IGui& gui)
{
    try
    {
        Connect(socket);
    }
    catch(const std::runtime_error& /*ex*/)
    {
        SetupServer(socket);
        gui.Print(s_listenMessage);
    }
}

namespace TestSubcase
{
    void SuccesfulConnect(MockSocketWrapper& socket)
    {
        EXPECT_CALL(socket, Connect(s_host, s_port)).WillOnce(Return(ISocketWrapper::SockPtr{}));
        EXPECT_CALL(socket, Bind(s_host, s_port)).Times(0);
        EXPECT_CALL(socket, Listen()).Times(0);
    }

    void UnsuccesfulConnect(MockSocketWrapper& socket)
    {
        EXPECT_CALL(socket, Connect(s_host, s_port)).WillOnce(Throw(std::runtime_error("")));
        EXPECT_CALL(socket, Bind(s_host, s_port));
        EXPECT_CALL(socket, Listen());
    }
}

TEST(SocketConnectionTest, Connect_localhost_4444)
{
    MockSocketWrapper mock;
    EXPECT_CALL(mock, Connect(s_host, s_port)).WillOnce(Return(ISocketWrapper::SockPtr{}));
    Connect(mock);
}

TEST(SocketConnectionTest, ListenIfBindSuccess)
{
    MockSocketWrapper mock;
    EXPECT_CALL(mock, Bind(s_host, s_port));
    EXPECT_CALL(mock, Listen());
    SetupServer(mock);
}

TEST(SocketConnectionTest, IfConnectSuccessListenAndBindIsNotCalled)
{
    MockSocketWrapper mock;
    MockGui gui;
    TestSubcase::SuccesfulConnect(mock);
    InitSession(mock, gui);
}

TEST(SocketConnectionTest, MessageIsDispayedAfterUnsuccesfulConnect)
{
    MockSocketWrapper mock;
    MockGui gui;
    TestSubcase::UnsuccesfulConnect(mock);
    EXPECT_CALL(gui, Print(s_listenMessage)).Times(1);
    InitSession(mock, gui);
}
