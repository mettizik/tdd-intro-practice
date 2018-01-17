#include <gtest/gtest.h>
#include <gmock/gmock.h>

/*
Implement chat application, that communicates via TCP sockets.
 There is list of requirenments to this application:
 * It receives user nickname through commandline interface on start
 * On start it checks if port 4444 is bound
    * if it is - connects to other client
    * if not - binds a port and waits for inbound connection
    * message "No one is here..." displayed in UI
 * After establishing connection - handshake is performed:
    * client writes message with it's nickname and ':HELLO!' string to socket ("metizik:HELLO!")
    * server responses with it's nickname and ':HELLO!' magic ("user:HELLO!")
    * client and server save each other's nicknames
 * It must send messages via created connection, until it is dropped
    * User inputs message through console interface and presses ENTER
    * Line with message and '@username:' prefix is displayed ("metizik: Hello!")
    * Text message is sent to socket
 * It must receive messages via created connection until it is dropped
    * Message received through socket
    * Line with message and '@username:' prefix is displayed ("metizik: Hello!")
*/
