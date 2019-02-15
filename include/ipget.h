#include <iostream>
#include <stdlib.h> //for atoi
#include <csignal>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <regex>

#define RCVBUFSIZE 1024

//-----------------------------
// Warning we just can continue with
// C++11 flag
#if __cplusplus != 201103L
#pragma warning(push)
#pragma message("You are compiling with no C++11 flags.\nBe warning you are not able to get some functionalitys.")
#pragma warning(pop)
#endif

using namespace std;

class GetIP
{
public:
	GetIP();
	~GetIP();

	/**
	 * @brief Get internal IP;
	 * 
	 * Get an Internal IP and return it with provide type;
	 */
	void GetInternalIP(char *);

	/**
	 * @brief Get External IP
	 * Get an External IP and return it with provide type.
	 * @return Return the ip as string from process.
	 */
	std::string GetExternalIP();

	//Get an External IP and return it with DNS update;
	void GetExternalIpByDns();

	/**
	 * @brief Check Host or Ip
	 * Check if String contains only numbers
	 * @warning Works just with std=C++11 flag 
	 */
	inline bool CheckHostorIP(char *in, char *regex)
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
	void ReadLog(string path, string message);

	//static void* Thread_Wrapper(void*);

	/* Variables */
	int fd;
	struct ifaddrs *ifAddrStruct = NULL;
	struct ifaddrs *ifa = NULL;
	void *pAddrTmp = NULL;

	int sockd; //Sockted
	struct sockaddr_in servAddr;
	unsigned short servPort;
	char const *servIP;					 // Server IP address (dotted quad)
	char const *request;				 // String to send to server
	char recvBuffer[RCVBUFSIZE]; // Buffer for response string
	unsigned int requestLen;		 // Length of string to send
	int bytesRcvd;							 // Bytes read in single recv()
	bool status = true;
};

class PortCheck : GetIP
{
public:
	bool CheckPort(char *host, int port);
	bool CheckPortAsync(vector<string> hosts, vector<int> ports);
};