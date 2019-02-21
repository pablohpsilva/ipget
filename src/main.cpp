#include "../include/ipget.hpp"
#include "../include/threading.h"
#include <pthread.h>

// faustogoncalves.it
#define __PROGRAM__VERSION "This program was made by Mainstream IT and Software enginier.\nAnd is under GNU license.\nVersion = 1.0.0\n"

using namespace std;

bool isClosing = false;

void getSignalSlot(int signalnum)
{
	cout << "Interrupt signal (" << signalnum << ") received.\n";

	// cleanup and close up stuff here
	// terminate program

	exit(signalnum);
}

void *CallbackThread(void *args)
{

	signal(SIGINT, getSignalSlot);

	while (!isClosing)
	{
		#ifdef DEBUG
			std::cout << "Getting signal\r\n";
		#endif
		sleep(1);
	}
}

int main(int argc, char *argv[])
{
	//TODO - Change the new 
	//Intanciate classes
	GetIP *ip = new GetIP();
	PortCheck *p_check = new PortCheck();

	//Run thread to get signal slot
	pthread_t thread1;
	int intresp = pthread_create(&thread1, NULL, CallbackThread, NULL);

	if (intresp)
	{
		fprintf(stderr, "Error - pthread_create() return code: %d\n", intresp);
		exit(EXIT_FAILURE);
	}

	//	pthread_start( thread1, NULL);

	//Args Opts
	for (int i = 0; i < argc; i++)
	{
		//	std::cout<< std::string(argv[i])<< std::endl;

		if (std::string(argv[i]) == "-x")
		{

			ip->GetExternalIP();
			return 0;
		}

		if (std::string(argv[i]) == "-X")
		{
			ip->GetExternalIpByDns();
			return 0;
		}

		if (std::string(argv[i]) == "-V")
		{
			std::cout << __PROGRAM__VERSION << std::endl;
			return 0;
		}
		if (std::string(argv[i]) == "-h")
		{
			std::cout << "usage: ipget <option> <paramter>\n"
									 "				      \n"
									 "options:			      \n"
									 "									\n"
									 "-x				Retrive external IP from web.\n"
									 "-X				Retrive Internal IP from web DNS.\n"
									 "-V				Show program version.\n"
									 "-h				Show this help.\n"
									 "-p	[ip] [port]		Check the status of given port from given machine.\n\n";
			return 0;
		}

		try
		{
			if (std::string(argv[i]) == "-p")
			{
				char *host = argv[i + 1];
				int port = std::stoi(argv[i + 2]);
				p_check->CheckPort(host, port);
				return 0;
			}
		}
		catch (std::exception &e)
		{
			std::cout << "An error has occured.\nSee description: " << e.what() << std::endl;
		}

		try
		{
			if (std::string(argv[i]) == "-p1")
			{
				std::string input;
				std::vector<std::string> hosts;
				std::vector<int> ports;

				hosts.push_back("127.0.0.1");
				hosts.push_back("192.168.1.1");
				hosts.push_back("google.com");
				hosts.push_back("127.0.0.1");
				hosts.push_back("127.0.0.1");
				hosts.push_back("127.0.0.1");
				hosts.push_back("127.0.0.1");
				hosts.push_back("127.0.0.1");
				hosts.push_back("127.0.0.1");
				hosts.push_back("127.0.0.1");
				hosts.push_back("127.0.0.1");
				hosts.push_back("127.0.0.1");

				ports.push_back(22);
				ports.push_back(21);
				ports.push_back(80);
				ports.push_back(90);
				ports.push_back(443);
				ports.push_back(3306);
				ports.push_back(10);
				ports.push_back(12);
				ports.push_back(13);
				ports.push_back(15);
				ports.push_back(25);
				ports.push_back(12);

				//Iterate from vector Host and Ports.
				for (auto &host : hosts)
				{
					std::cout << "This the list of Host from vectors Hosts: " << host << std::endl;
					for (auto &port : ports)
					{
						if (host != "")
							std::cout << "This is the port from vector ports: " << port << std::endl;
					}
				}

				return 0;
			}
		}
		catch (std::exception &e)
		{
			std::cout << "An error has occured.\nSee description: " << e.what() << std::endl
								<< __LINE__ << std::endl;
		}
	}
	ip->GetInternalIP("eth0");
	
	return 0;
}