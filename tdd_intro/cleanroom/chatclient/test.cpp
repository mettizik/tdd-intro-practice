#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"
#include "serversession.h"
#include "clientsession.h"

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
    MOCK_METHOD0(Accept, ISocketWrapper::SockPtr());
    MOCK_METHOD1(Read, void(std::string& nickName));
    MOCK_METHOD1(Write, void(const std::string& nickName));
    MOCK_METHOD0(Close, void());
};

class MockGui : public IGui
{
public:
    MOCK_METHOD1(Print, void(const std::string&));
};

namespace TestSubcase
{
    std::shared_ptr<MockSocketWrapper> SetupClientPreconditions(MockSocketWrapper& socket)
    {
        auto acceptedSocket = std::make_shared<MockSocketWrapper>();
        EXPECT_CALL(socket, Connect(sessionUtils::GetHost(), sessionUtils::GetPort())).WillOnce(Return(acceptedSocket));
        EXPECT_CALL(socket, Bind(sessionUtils::GetHost(), sessionUtils::GetPort())).Times(0);
        EXPECT_CALL(socket, Listen()).Times(0);
        return acceptedSocket;
    }

    std::shared_ptr<MockSocketWrapper> SetupServerPreconditions(MockSocketWrapper& socket, MockGui& gui)
    {
        EXPECT_CALL(socket, Bind(sessionUtils::GetHost(), sessionUtils::GetPort()));
        EXPECT_CALL(socket, Listen());
        auto acceptedSocket = std::make_shared<MockSocketWrapper>();
        EXPECT_CALL(socket, Accept()).WillOnce(Return(acceptedSocket));
        EXPECT_CALL(gui, Print(sessionUtils::GetListenMessage())).Times(1);
        return acceptedSocket;
    }
}

TEST(SocketConnectionTest, Connect_localhost_4444)
{
    MockSocketWrapper mock;
    EXPECT_CALL(mock, Connect(sessionUtils::GetHost(), sessionUtils::GetPort())).WillOnce(Return(ISocketWrapper::SockPtr{}));
    sessionUtils::Connect(mock);
}

TEST(SocketConnectionTest, ListenIfBindSuccess)
{
    MockSocketWrapper mock;
    EXPECT_CALL(mock, Bind(sessionUtils::GetHost(), sessionUtils::GetPort()));
    EXPECT_CALL(mock, Listen());
    EXPECT_CALL(mock, Accept()).WillOnce(Return(ISocketWrapper::SockPtr{}));
    sessionUtils::SetupServer(mock);
}

TEST(SocketConnectionTest, IfConnectSuccessListenAndBindIsNotCalled)
{
    MockSocketWrapper mock;
    MockGui gui;
    TestSubcase::SetupClientPreconditions(mock);
    ClientSession(mock, gui, "");
}

TEST(SocketConnectionTest, MessageIsDispayedAfterUnsuccesfulConnect)
{
    MockSocketWrapper mock;
    MockGui gui;
    TestSubcase::SetupServerPreconditions(mock, gui);
    ServerSession(mock, gui, "");
}

TEST(SocketConnectionTest, ClientHandshake)
{
    MockSocketWrapper mock;
    MockGui gui;
    auto clientMock = TestSubcase::SetupClientPreconditions(mock);
    EXPECT_CALL(*clientMock, Write("metizik:HELLO!"));
    EXPECT_CALL(*clientMock, Read(_)).WillOnce(SetArgReferee<0>("user:HELLO!"));
    ClientSession session(mock, gui, "metizik");
    session.PerformHandshake();
}

TEST(SocketConnectionTest, ServerAnswersOnHandshake)
{
    MockSocketWrapper mock;
    MockGui gui;
    std::shared_ptr<MockSocketWrapper> acceptedSocket = TestSubcase::SetupServerPreconditions(mock, gui);
    EXPECT_CALL(*acceptedSocket, Read(_)).WillOnce(SetArgReferee<0>("user:HELLO!"));
    EXPECT_CALL(*acceptedSocket, Write("server:HELLO!"));
    EXPECT_CALL(*acceptedSocket, Close()).Times(0);
    ServerSession server(mock, gui, "server");
    server.PerformHandshake();
}

TEST(SocketConnectionTest, ClientSessionHandshake)
{
    MockSocketWrapper mock;
    MockGui gui;
    auto clientMock = TestSubcase::SetupClientPreconditions(mock);
    EXPECT_CALL(*clientMock, Write(_));
    EXPECT_CALL(*clientMock, Read(_)).WillOnce(SetArgReferee<0>("server:HELLO!"));
    EXPECT_CALL(*clientMock, Close()).Times(0);
    ClientSession session(mock, gui, "metizik");
    session.PerformHandshake();
}

TEST(SocketConnectionTest, InvalidClientSessionHandshakeThrows)
{
    MockSocketWrapper mock;
    MockGui gui;
    auto clientMock = TestSubcase::SetupClientPreconditions(mock);
    EXPECT_CALL(*clientMock, Write(_));
    EXPECT_CALL(*clientMock, Read(_)).WillOnce(SetArgReferee<0>("123"));
    EXPECT_CALL(*clientMock, Close()).Times(1);
    ClientSession session(mock, gui, "metizik");
    EXPECT_THROW(session.PerformHandshake(), std::exception);
}

TEST(SocketConnectionTest, MainSessionHandshake)
{
    MockSocketWrapper mock;
    MockGui gui;
    std::shared_ptr<MockSocketWrapper> acceptedSocket = TestSubcase::SetupServerPreconditions(mock, gui);
    EXPECT_CALL(*acceptedSocket, Read(_)).WillOnce(SetArgReferee<0>("metizik:HELLO!"));
    EXPECT_CALL(*acceptedSocket, Close()).Times(0);
    ServerSession server(mock, gui, "server");
    server.PerformHandshake();
}

TEST(SocketConnectionTest, InvalidMainSessionHandshake)
{
    MockSocketWrapper mock;
    MockGui gui;
    std::shared_ptr<MockSocketWrapper> acceptedSocket = TestSubcase::SetupServerPreconditions(mock, gui);
    EXPECT_CALL(*acceptedSocket, Read(_)).WillOnce(SetArgReferee<0>("321"));
    EXPECT_CALL(*acceptedSocket, Close()).Times(1);
    ServerSession server(mock, gui, "server");
    EXPECT_THROW(server.PerformHandshake(), std::exception);
}

TEST(SocketConnectionTest, ReadHandshakeReadsFromSocketAndDoesNotThrowOnValidHandshake)
{
    MockSocketWrapper mock;
    EXPECT_CALL(mock, Read(_)).WillOnce(SetArgReferee<0>("name:HELLO!"));
    EXPECT_NO_THROW(sessionUtils::ReadHandShake(mock));
}

TEST(SocketConnectionTest, ReadHandshakeReadsFromSocketThrowsOnInValidHandshake)
{
    MockSocketWrapper mock;
    EXPECT_CALL(mock, Read(_)).WillOnce(SetArgReferee<0>("name:HELLO"));
    EXPECT_THROW(sessionUtils::ReadHandShake(mock), std::exception);
}

TEST(SocketConnectionTest, ReadHandshakeReadsFromSocketThrowsOnEmptyHandshake)
{
    MockSocketWrapper mock;
    EXPECT_CALL(mock, Read(_)).WillOnce(SetArgReferee<0>(""));
    EXPECT_THROW(sessionUtils::ReadHandShake(mock), std::exception);
}
