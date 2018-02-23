#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ISocketWrapper.h"
#include "IGui.h"
#include "sessionutils.h"
#include "serversession.h"
#include "clientsession.h"
#include "Application.h"

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

class MockChatSession : public IChatSession
{
public:
    MOCK_METHOD1(PerformHandshake, std::string(const std::string&));
    MOCK_METHOD1(SendMessage, void(const std::string&));
    MOCK_METHOD1(ReadMessage, void(std::string&));
};

class MockGui : public IGui
{
public:
    MOCK_METHOD1(Print, void(const std::string&));
    MOCK_METHOD0(Read, std::string());
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
    sessionUtils::CreateNewSession(mock, gui);
}

TEST(SocketConnectionTest, MessageIsDispayedAfterUnsuccesfulConnect)
{
    MockSocketWrapper mock;
    MockGui gui;
    TestSubcase::SetupServerPreconditions(mock, gui);
    sessionUtils::CreateNewSession(mock, gui);
}

TEST(SocketConnectionTest, ClientHandshake)
{
    auto clientMock = std::make_shared<MockSocketWrapper>();
    EXPECT_CALL(*clientMock, Write("metizik:HELLO!"));
    EXPECT_CALL(*clientMock, Read(_)).WillOnce(SetArgReferee<0>("user:HELLO!"));
    ClientSession session(clientMock);
    session.PerformHandshake("metizik");
}

TEST(SocketConnectionTest, ServerAnswersOnHandshake)
{
    MockSocketWrapper mock;
    MockGui gui;
    std::shared_ptr<MockSocketWrapper> acceptedSocket = TestSubcase::SetupServerPreconditions(mock, gui);
    EXPECT_CALL(*acceptedSocket, Read(_)).WillOnce(SetArgReferee<0>("user:HELLO!"));
    EXPECT_CALL(*acceptedSocket, Write("server:HELLO!"));
    EXPECT_CALL(*acceptedSocket, Close()).Times(0);
    sessionUtils::StartSession(mock, gui, "server");
}

TEST(SocketConnectionTest, ClientSessionHandshake)
{
    auto clientMock = std::make_shared<MockSocketWrapper>();
    EXPECT_CALL(*clientMock, Write(_));
    EXPECT_CALL(*clientMock, Read(_)).WillOnce(SetArgReferee<0>("server:HELLO!"));
    EXPECT_CALL(*clientMock, Close()).Times(0);
    ClientSession session(clientMock);
    session.PerformHandshake("metizik");
}

TEST(SocketConnectionTest, InvalidClientSessionHandshakeThrows)
{
    auto clientMock = std::make_shared<MockSocketWrapper>();
    EXPECT_CALL(*clientMock, Write(_));
    EXPECT_CALL(*clientMock, Read(_)).WillOnce(SetArgReferee<0>("123"));
    EXPECT_CALL(*clientMock, Close()).Times(1);
    ClientSession session(clientMock);
    EXPECT_THROW(session.PerformHandshake("metizik"), std::exception);
}

TEST(SocketConnectionTest, MainSessionHandshake)
{
    MockSocketWrapper mock;
    MockGui gui;
    std::shared_ptr<MockSocketWrapper> acceptedSocket = TestSubcase::SetupServerPreconditions(mock, gui);
    EXPECT_CALL(*acceptedSocket, Read(_)).WillOnce(SetArgReferee<0>("metizik:HELLO!"));
    EXPECT_CALL(*acceptedSocket, Close()).Times(0);
    sessionUtils::StartSession(mock, gui, "server");
}

TEST(SocketConnectionTest, InvalidMainSessionHandshake)
{
    MockSocketWrapper mock;
    MockGui gui;
    std::shared_ptr<MockSocketWrapper> acceptedSocket = TestSubcase::SetupServerPreconditions(mock, gui);
    EXPECT_CALL(*acceptedSocket, Read(_)).WillOnce(SetArgReferee<0>("321"));
    EXPECT_CALL(*acceptedSocket, Close()).Times(1);
    EXPECT_THROW(sessionUtils::StartSession(mock, gui, "server"), std::exception);
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

TEST(SessionTests, ServerSessionCreateDoesNotThrowAndReturnsServerObject)
{
    MockSocketWrapper mock;
    MockGui gui;
    std::shared_ptr<MockSocketWrapper> acceptedSocket = TestSubcase::SetupServerPreconditions(mock, gui);
    EXPECT_CALL(*acceptedSocket, Read(_)).WillOnce(SetArgReferee<0>("client:HELLO!"));
    EXPECT_CALL(*acceptedSocket, Close()).Times(0);
    EXPECT_NE(nullptr, dynamic_cast<ServerSession*>(sessionUtils::StartSession(mock, gui, "server").get()));
}

TEST(SessionTests, ClientSessionCreateDoesNotThrowAndReturnsClientObject)
{
    MockSocketWrapper mock;
    MockGui gui;
    auto clientMock = TestSubcase::SetupClientPreconditions(mock);
    EXPECT_CALL(*clientMock, Write(_));
    EXPECT_CALL(*clientMock, Read(_)).WillOnce(SetArgReferee<0>("server:HELLO!"));
    EXPECT_CALL(*clientMock, Close()).Times(0);
    EXPECT_NE(nullptr, dynamic_cast<ClientSession*>(sessionUtils::StartSession(mock, gui, "client").get()));
}

TEST(SessionTests, ClientSessionSendMessageWritesToSocketUsedToInitializeObject)
{
    std::shared_ptr<MockSocketWrapper> socket = std::make_shared<MockSocketWrapper>();
    EXPECT_CALL(*socket, Write("hello"));
    ClientSession session(socket);
    session.SendMessage("hello");
}

TEST(SessionTests, ServerSessionSendMessageWritesToSocketUsedToInitializeObject)
{
    std::shared_ptr<MockSocketWrapper> socket = std::make_shared<MockSocketWrapper>();
    MockGui gui;
    EXPECT_CALL(*socket, Write("hello"));
    ServerSession session(socket);
    session.SendMessage("hello");
}

TEST(SessionTests, ServerSessionReadsMessageFromSocket)
{
    std::shared_ptr<MockSocketWrapper> socket = std::make_shared<MockSocketWrapper>();
    MockGui gui;
    EXPECT_CALL(*socket, Read(_)).WillOnce(SetArgReferee<0>("hello"));
    ServerSession session(socket);
    std::string msg;
    session.ReadMessage(msg);
    EXPECT_EQ("hello", msg);
}

TEST(SessionTests, ClientSessionReadsMessageFromSocket)
{
    std::shared_ptr<MockSocketWrapper> socket = std::make_shared<MockSocketWrapper>();
    EXPECT_CALL(*socket, Read(_)).WillOnce(SetArgReferee<0>("hello"));
    ClientSession session(socket);
    std::string msg;
    session.ReadMessage(msg);
    EXPECT_EQ("hello", msg);
}

TEST(SessionTests, ApplicationCreatesWithSessionAndPerformsHandshakeWithNickname)
{
    MockChatSession mockChat;
    EXPECT_CALL(mockChat, PerformHandshake("metizik")).Times(1);
    Application app(mockChat, "metizik");
}


TEST(SessionTests, PrintQueryForInput)
{
    MockChatSession mockChat;
    MockGui mockGui;
    EXPECT_CALL(mockGui, Print("me: ")).Times(1);
    Application app(mockChat, "metizik");
    app.StartCommunication(mockGui);
}

TEST(SessionTests, ApplicationSendsUserInput)
{
    MockChatSession mockChat;
    MockGui mockGui;
    {
        InSequence dummy;
        EXPECT_CALL(mockGui, Print("me: ")).Times(1);
        EXPECT_CALL(mockGui, Read()).WillOnce(Return("hello world"));
        EXPECT_CALL(mockChat, SendMessage("hello world")).Times(1);
    }
    Application app(mockChat, "metizik");
    app.StartCommunication(mockGui);
}

TEST(SessionTests, ApplicationWaitsForAnswerAndReadsIt)
{
    MockChatSession mockChat;
    MockGui mockGui;
    {
        InSequence dummy;
        EXPECT_CALL(mockChat, SendMessage(_)).Times(1);
        EXPECT_CALL(mockChat, ReadMessage(_)).Times(1);
    }
    Application app(mockChat, "metizik");
    app.StartCommunication(mockGui);
}

TEST(SessionTests, ClientRetreivesServerNick)
{
    std::shared_ptr<MockSocketWrapper> socket = std::make_shared<MockSocketWrapper>();
    EXPECT_CALL(*socket, Read(_)).WillOnce(SetArgReferee<0>("server:HELLO!"));
    ClientSession session(socket);
    EXPECT_EQ("server", session.PerformHandshake(""));
}

TEST(SessionTests, ServerRetreivesClientNick)
{
    std::shared_ptr<MockSocketWrapper> socket = std::make_shared<MockSocketWrapper>();
    EXPECT_CALL(*socket, Read(_)).WillOnce(SetArgReferee<0>("client:HELLO!"));
    ServerSession session(socket);
    EXPECT_EQ("client", session.PerformHandshake(""));
}


TEST(SessionTests, ApplicationPrintsReceivedMessage)
{
    MockChatSession mockChat;
    MockGui mockGui;
    {
        InSequence dummy;
        EXPECT_CALL(mockChat, ReadMessage(_)).WillOnce(SetArgReferee<0>("and to you!"));
        EXPECT_CALL(mockGui, Print("server: and to you!")).Times(1);
    }
    Application app(mockChat, "metizik");
    app.StartCommunication(mockGui);
}
