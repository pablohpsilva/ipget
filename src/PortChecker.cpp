/*************************************************
*
*	PortCheck Class definitions
*
*************************************************/
#include "../include/PortChecker.hpp"
#include <functional>
#include <future>

using namespace std;

bool PortChecker::CheckPort(const string &host, int port)
{
	cout << "Trying to connect to host " << host << " with port: " << port << endl;

	// Try create a sock stream to get pass tru selected port, init a buffer;
	char *buffer;
	buffer = new char[1024];
	sockd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	// Error handling
	if (sockd < 0)
	{
		cout << "Error o opening sock.\nError description: " << strerror(errno) << endl;
		exit(EXIT_FAILURE);
	}
	// Allocate socket addr for handling
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(host.c_str());
	; //for any ip address
	servAddr.sin_port = htons(port);

	// try connect with socket adn srvAdd struct
	if (connect(sockd, (const sockaddr *)&servAddr, sizeof(servAddr)) < 0)
	{
		if (errno == EADDRINUSE) //Treat error with errno
		{
			cout << "Port is already used, please try run ps aux | grep <port> to get more details";
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("could not bind to process (%d) %s\n", errno, strerror(errno));
			return false;
		}
	}

	cout << "Port " << port << " opened" << endl;
	return true;
}

bool PortChecker::CheckPortAsync(std::vector<std::string> hosts, std::vector<int> ports)
{
	
	//Iterate from vector Host and Ports.
	//TODO: Check if all ports are opened.
    std::vector<future<bool>> call;
    for(int i =0; i <= hosts.size(); i++)
    {
        call[i] = std::async(std::launch::async, &PortChecker::CheckPort,this, hosts[i], ports[i]);
    }
    return  false;
}
