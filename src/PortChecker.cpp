/*************************************************
*
*	PortCheck Class definitions
*
*************************************************/
#include "../include/PortChecker.hpp"


bool PortChecker::CheckPort(char *host, int port)
{
	cout << "Trying to connect to host " << host << " with port: " << port << endl;

	//Try create a sock stream to get pass tru selected port, init a buffer;
	char *buffer;
	buffer = new char[1024];
	sockd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	// Error handling
	if (sockd < 0)
	{
		cout << "Error o opening sock.\nError description: " << strerror(errno) << endl;
		exit(EXIT_FAILURE);
	}
	//Allocate sockt addr for handling
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(host);
	; //for any ip address
	servAddr.sin_port = htons(port);

	// try connect with socket adn srvAdd struct
	if (connect(sockd, (const sockaddr *)&servAddr, sizeof(servAddr)) < 0)
	{
		if (errno == EADDRINUSE) //Treate error with errno
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
	std::function<bool(PortChecker&, char*, int)> fn = &PortChecker::CheckPort;

	//Iterate from vector Host and Ports.
	for (auto &host : hosts)
	{
		std::cout << "This the list of Host from vectors Hosts: " << host;

		for (auto &port : ports)
		{
			std::future<bool> fn = std::async(std::launch::async, fn, host.data(), port );
			std::cout << "This is the port from vector ports: " << port;
		}
	}
}
