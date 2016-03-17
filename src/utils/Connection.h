/*
*********************************************************************************
*                            In the name of Almighty                            *
*                                                                               *
*           Connection.h : Robocup 3D Soccer Simulation Team Zigorat            *
*                     (This team was previously named Gcyrus)                   *
*                                                                               *
*  Date: 03/20/2007                                                             *
*  Author: Mahdi Hamdarsi                                                       *
*  Comments: Class decleration for TDataPorter, TConnection, TRoboCupConnection *
*            utilities for network manipulation                                 *
*                                                                               *
*********************************************************************************
*/

#ifndef CONNECTION
#define CONNECTION

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <netdb.h>
#include <iostream>
using namespace std;

enum ConnectionT
{
  CONN_TCP,
  CONN_UDP,
  CONN_ILLEGAL
};



/***************************************************************************/
/***************************  Class TDataPorter  ***************************/
/***************************************************************************/

/*! TDataPorter is class tha encapsulates socket connection operations, 
    like opening, reusing, sending & recieving data across sockets */
class TDataPorter
{
  protected:
    int         m_SocketFD;          /*!< Socket file desriptor of the connection */
    ConnectionT m_ConnectionType;    /*!< Type of the connection, ie. TCP/UDP */

  public:
      TDataPorter                    ( ConnectionT conn, int socket_fd = -1 );
    ~ TDataPorter                    (                                      );
    
    ConnectionT getConnectionType    (                                      ) const;

    int         getSocketFD          (                                      ) const;
    bool        setSocketFD          ( int socket_fd, ConnectionT conn      );

    int         sendMessage          ( const void * msg, int iLength        ) const;
    int         sendMessageUDP       ( const void * msg, int iLength,
                                          const sockaddr_in * remote        ) const;
    int         recvMessage          ( void * msg, int iMaxLength, int to   ) const;
    int         writeMessage         ( const char * msg                     ) const;
    int         writeMessage         ( const void * msg, int iLength        ) const;
    int         readMessage          ( void * msg, int iLength              ) const;
    
    bool        active               (                                      ) const;
    int         waitForData          ( fd_set &fds, int iSecs               ) const;
    
    bool        open                 (                                      );
    bool        reOpen               (                                      );
    bool        closeAll             (                                      );
};



/***************************************************************************/
/***************************  Class TConnection  ***************************/
/***************************************************************************/

/*! TConnection is a class that encapsulates connection handling routines,
    like starting listening, accepting connections, sending & receiving 
    data, and making connection to existing listening servers, currently
    supports to modes of communication: TCP/IP & UDP/IP */
class TConnection
{
protected:
  sockaddr_in   m_SelfAddress;       /*!< Self socket information */
  sockaddr_in   m_Remote;            /*!< Remote connection which is established */
  TDataPorter * m_SocketFD;          /*!< Socket descriptor of this data porter */

public:
  bool          connected            (                                      ) const;
  ConnectionT   getConnectionType    (                                      ) const;
  int           getLocalPort         (                                      ) const;
  bool          setLocalPort         ( int iPort                            );
  
  int           getSocketFD          (                                      ) const;

  bool          openConnection       ( const char *str, int iPort           );
  bool          startServer          ( int port                             );
  bool          waitForConnection    (                                      );
  bool          closeConnection      (                                      );

  bool          waitForData          ( int time_out = 0                     ) const;
  bool          sendMessage          ( const char * strMsg                  ) const;
  bool          sendData             ( const void * data, int iLength       ) const;
  bool          writeMessage         ( const char * msg                     ) const;
  bool          writeMessage         ( const void * msg, int iLength        ) const;

  bool          recvMessage          ( char * strMsg, int iMaxLen,
                                       int time_out, bool close_empty=false );
  bool          readMessage          ( void * msg, int iMaxLength           ) const;

    TConnection                      ( ConnectionT conn, 
                                       const char * strHost = "",
                                       int iPort = -1                       );
  ~ TConnection                      (                                      );
};

/********************************************************************/
/*******************  Class TRoboCupConnection  *********************/
/********************************************************************/

/*! TRoboCupConnection is a class that encapsulates spark simulation server 
    handling methods. like recieving and sending data to simulation server. */
class TRoboCupConnection : public TConnection
{
public:
    TRoboCupConnection               ( const char *strHost = "", 
                                                           int iPort = -1   );
  ~ TRoboCupConnection               (                                      );

  bool sendCommand                   ( const char * msg                     ) const;
  bool getMessage                    ( char * msg, int iMaxLen              ) const;
};              

#endif // CONNECTION

