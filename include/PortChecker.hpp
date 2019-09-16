#pragma once

#include "ipget.hpp"
#include <future>
#include <iostream>
class PortChecker : GetIP
{
public:
	bool CheckPort(char *host, int port);
	bool CheckPortAsync(vector<string> hosts, vector<int> ports);
};