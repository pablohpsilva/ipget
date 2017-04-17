#include <iostream>
#include <stdlib.h>  //for atoi

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <regex>

/* Get GTK headers */
#if _GUI_
   #include <gtk-3.0/gtk/gtk.h>
#endif

#define RCVBUFSIZE 1024


//-----------------------------
// Warning we just can continue with 
// C++11 flag
#if __cplusplus != 201103L
	#pragma warning ( push ) 
		#pragma message ("You are compiling with no C++11 flags.\nBe warning you are not able to get some functionalitys.")
	#pragma warning ( pop ) 
#endif



using namespace std;

class GetIP
{
   public:
	GetIP();
	~GetIP();

	//Get an Internal IP and return it with provide type;
	void GetInternalIP(char*);

	//Get an External IP and return it with provide type;
	void  GetExternalIP();

	//Get an External IP and return it with DNS update;
	void GetExternalIpByDns ();


	/*--------------------------------------
	 * Check if String contains only numbers
	 * Works just with std=C++11 flag 
	 */
        inline bool CheckHostorIP(char* in, char* regex)
	{
	  return std::regex_match(in, std::regex(regex));
	}
	
	/*-------------------------------------------------------
	*
	* Write sring to file, to create a log file. 
	* will be formated string, and a rotate log.
	*-----------------------------------------------------*/
	void SaveToLog(string path, string message);
	
        /*-------------------------------------------------------
        *
        * Write sring to file, to create a log file.
        * will be formated string, and a rotate log.
        *------------------------------------------------------*/
        void ReadLog (string path, string message);

       


	//static void* Thread_Wrapper(void*);

	/* Variables */
        int fd;
        struct ifaddrs * ifAddrStruct = NULL;
        struct ifaddrs * ifa = NULL;
        void * pAddrTmp = NULL;

        int sockd;      //Sockted
        struct sockaddr_in servAddr;
        unsigned short servPort;
        char const *servIP;              // Server IP address (dotted quad)
        char const *request;             // String to send to server
        char recvBuffer[RCVBUFSIZE];     // Buffer for response string
        unsigned int requestLen;         // Length of string to send
        int bytesRcvd;                   // Bytes read in single recv()
        bool status = true;



};

class PortCheck : GetIP
{
  public:

      bool CheckPort(char* host, int port);
      
    
};

#if _GUI_

class GUI : GetIP
{
	public:
	/* Constructor with no Args, defaul is size/2 */
	GUI();
	~GUI();

	/*---------------------------------------------------
	 * Create Window frame with no options
	 *
	 * -------------------------------------------------*/
	void createFrame();
	static void activate (GtkApplication *app, gpointer user_data);
};
#endif
