#include "../include/ipget.hpp"


using namespace std;

GetIP::GetIP()
{
	if(!sqlSmartPtr.get())
	{
		sqlSmartPtr = this->generateUniquePtr<SQLiteManager>();
	}
	else
	{
		#if DEBUG
			std::cout << "We have a valid pointer, dont need instanciated." << std::endl;
		#endif
	}
}
GetIP::~GetIP()
{

}

void GetIP::GetInternalIP(char *InterfaceName)
{
#ifdef DEBUG

	cout << "DEBUG ON " << endl;
#endif
	//getIfaddr struct info
	if (getifaddrs(&ifAddrStruct) == -1)
	{
		cout << "Error initilize ifaddrs pointer" << endl;
	}
#ifdef DEBUG
	cout << "MemoryAddr of ifAddrStruct: " << &ifAddrStruct << endl;
#endif

	for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
	{
		// check if has valid args, and if iface is a valid AF_INET provide info about it
		if (ifa->ifa_addr == NULL)
		{
			cout << "Interface " << ifa->ifa_name << " with no ip address value. " << endl;
			continue;
		}

		//		if (ifa->ifa_addr->sa_family != AF_INET) { cout << "Interface " << ifa->ifa_name << " has no valid IPV4 address." << endl; continue; }

		//		if ((ifa->ifa_flags & IFF_UP) == 0) { cout << "Interface " << ifa->ifa_name << " is not present." << endl; continue; }

		//		if (ifa->ifa_flags & IFF_POINTOPOINT) {	cout << "Interface " << ifa->ifa_name << " is not a point to point." << endl; continue; }

		if (ifa->ifa_addr->sa_family == AF_INET)
		{
			//Revice Memory adress from addr
			pAddrTmp = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;

			//Buffer to Recive ip addr
			char addressBuffer[INET_ADDRSTRLEN];
			char *ifname = ifa->ifa_name;
			//Formate result and pass buffer
			inet_ntop(AF_INET, pAddrTmp, addressBuffer, INET_ADDRSTRLEN);
			std::cout << "INTERFACE " << ifname << " = " << addressBuffer << endl;
		}
	}

	if (ifAddrStruct != NULL)
		freeifaddrs(ifAddrStruct);
}

std::string GetIP::GetExternalIP()
{

	struct timeval timeout;
    timeout.tv_sec = 20;
    timeout.tv_usec = 10;

    
#if DEBUG
	cout << "Receiving Data...." << endl;
#endif

	servIP = "78.47.139.102"; //External IP server addr
	servPort = 80;			  //port (html)
	std::string response;
	// TO-DO request = "GET http://ifconfig.me/ip.html  HTTP/1.1\r\nHost: www.ifconfig.me\r\n\r\n"; //URL to get info
	request = "GET http://myexternalip.com/raw  HTTP/1.1\r\nHost: myexternalip.com\r\n\r\n";
	// Safe create a usable stream ip with port
	try
	{
		#if DEBUG
			std::cout << "Creating socket!" << std::endl;
		#endif
		sockd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sockd < 0)
		{
			cout << "DEBUG VALUE " << sockd << endl;
			throw;
		}
	}
	catch (int e)
	{
		cout << "Error on opening a stream.." << endl;
	}

	// Enable socket timeout error
	if (setsockopt (sockd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
        std::cout<< "setsockopt failed\n" << std::endl;

    if (setsockopt (sockd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		std::cout<<"setsockopt failed\n" << std::endl;

	//fill buffer of servAddr
	memset(&servAddr, 0, sizeof(servAddr));
	//Set addr params
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(servIP);
	servAddr.sin_port = htons(servPort);

	//safe try to connect in our stream
	try
	{
		#if DEBUG
			std::cout << "Trying to estabilish a connection..." << std::endl;
		#endif
		//Get Connect sock
		int retval = connect(sockd, (struct sockaddr *)&servAddr, sizeof(servAddr));
		//Verify if connect has sucesffulll
		if (retval < 0)
		{
			cout << "Error while trying connect thought socket";
			throw;
		}
		//Calculate s/ize of request
		requestLen = strlen(request);
		//Send pacted
		try
		{
			#if DEBUG
				std::cout << "Starting sending request." << std::endl;
			#endif
			int retval_send = send(sockd, request, requestLen, 0);
			if(retval_send != requestLen)
			{
				throw;
			}
		}
		catch(std::exception& ex)
		{
			std::cout << "Exception Launched.\nError code: %s" << ex.what();
		}
		//Calculate data
		bytesRcvd = recv(sockd, recvBuffer, sizeof(recvBuffer) - 1, 0);
		recvBuffer[bytesRcvd] = '\0';
		// has C++ so regex on it
		//#if __cplusplus != 201103L
		//Instantiate string with recvBuffer char to string conversion
		string buffer(recvBuffer);
		//Create regex object
		regex ip("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");

		//Create regex match
		std::smatch sm;
		//see if the resuls is valid
		regex_search(buffer, sm, ip, std::regex_constants::match_default);

#if DEBUG
		cout << "debug info : " << buffer << endl;
		cout << "string literal with" << sm.size() << " matches" << endl;
		std::cout << "the matches were: ";
		for (unsigned i = 0; i < sm.size(); ++i)
		{
			std::cout << "[" << sm.str(i) << "] ";
		}
#endif
		//Forloop auto iterator with initialization list
		for (auto &x : sm)
		{
			response.append(x);
			cout << "EXTERNAL_IP = " << x << endl;
		}
//#endif

//Set this fucntion to C++11 lower
#if __cplusplus < 201103L
		//formate output
		char end[250];
		char _retval[18];
		//Copy midle buffer in index
		copy(recvBuffer + 210, recvBuffer + 228, end);
		//format string
		end[16] = '\0';

		//take out first poss
		copy(end + 2, end + 17, _retval);
		for (int i = 18; i < sizeof(_retval); i--)
		{
			_retval[i] = '\0';
		}
		cout << "EXTERNAL_IP = " << _retval << endl;
#endif
	}
	catch (int e)
	{
		cout << "Error on recive information" << endl;
	}
	// Always close the socket and return result.
	close(sockd);

	//SQLiteManager* dbInstance = new SQLiteManager();
	//std::string result = dbInstance->executeCmd<std::string>("SELECT * FROM IP_EXTERNAL", ECmdSelect::SELECT, nullptr);
	//delete dbInstance;

	return response;
}

void GetIP::GetExternalIpByDns()
{
	cout << "Initializing ..." << endl;

	char buffer[1024];
	sockd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockd < 0)
	{
		cout << "Error o opening sock.\nError description: " << endl;
		exit(EXIT_FAILURE);
	}

	const char *GoogleDnsIp = "8.8.8.8";
	uint16_t DnsPort = 53;
	//Alocate amount of memory to reduce usage ve
	memset(&servAddr, 0, sizeof(servAddr));

	// Pass ard to sockaddr struct
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(GoogleDnsIp);
	servAddr.sin_port = htons(DnsPort);

	cout << "Triyng to connect to " << GoogleDnsIp << "." << endl;

	try
	{
		//connect ( sockd, (struct sockaddr*) &servAddr, sizeof(servAddr));
		//Get erro  buffer
		char *errobuf = new char[256];

		connect(sockd, (const sockaddr *)&servAddr, sizeof(servAddr));
		char *error_val = strerror_r(errno, errobuf, 256); // Get Error no

		if (errno > 0)
		{
			cout << "Error:\n"
				 << error_val << endl;
			exit(EXIT_FAILURE);
		}
		cout << "Connected.\nGetting IP external..." << endl;

		sockaddr_in servAddr2;
		socklen_t servAddrlen2 = sizeof(servAddr2);

		getsockname(sockd, (sockaddr *)&servAddr2, &servAddrlen2);
		error_val = strerror_r(errno, errobuf, 256);

		size_t bufflen = sizeof(buffer);

		const char *retval = inet_ntop(AF_INET, &servAddr2.sin_addr, buffer, bufflen);
		if (retval == 0)
			error_val = strerror_r(errno, errobuf, 256);

		cout << "IP_EXTERNAL = " << retval << endl;
		delete errobuf;
	}
	catch (exception &e)
	{
		cout << "Error:\n"
			 << "Could not open a sucessfull connection to " << GoogleDnsIp << "\nReason: " << e.what() << endl;
	}
	close(sockd);
}


#if _GUI_
/**
 *
 * Gui Init for window. 
 *
 */

void GUI::createFrame()
{
}

void GUI::activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Window");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
	gtk_widget_show_all(window);
}
#endif
