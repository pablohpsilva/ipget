#!/bin/bash

OUT_C='-e'
#ECHO COLORS
G_OUT='\e[92m'
R_OUT='\e[31m'
B_OUT='\e[34m'

DEFAULT='\e[39m'
END_F='\e[0m'

#PRINTF COLORS
RED='\x1b[31m'
GREEN="\x1b[32m"
BLUE="\x1b[34m"
CLEAR='\x1b[0m'

trap err_out ERR;


#Function to get error handling
function err_out()
{
	errorcode = $?;
	printf "script return error code %d " "$errorcode";
}


#Formated outputs 
function OK_OUT ()
{
	printf "%10s %b [ OK ]%b \n\r" "" "$GREEN" "$CLEAR"
}

function FAIL_OUT ()
{
	printf "%10s %b[ FAIL ] %b \n" "" "$RED" "$CLEAR ";
}

#Function to detect OS type and install depencies for it
function os_detect ()
{
	print "Now we will try find your current linux distro..."
	os_type=`cat /etc/os-release | grep "^ID" | cut -d'=' -f2`;
	
	# gentoo
        if [ "$os_type" == "gentoo" ]; then
		printf "Its seem ur system dont have %s instaled, do you wanna install for you?[Yes/No]" "$1";	   
		read answer;

		if [ "$answer" == "yes" ]; then
	                emerge -v $1;
			#exit if emerge has failed
			if [ "$?" -gt "0" ]; then
				exit 1;
			else
				printf "the %d was installed continuing" "$1";
			fi;
                else
			printf "A manual %s instalation is requied to continue.\nAborting." "$1";
			exit 1;
	        fi;
	else
		printf "yout system is not supported by automatic install so you need install dependices by hand.\n"
	fi;
	
	# debian 
	if [ "$os_type" == "debian" ]; then
		printf "Its seem ur system dont have %s instaled, do you wanna install for you?[Yes/No]" "$1";
                read answer;

                if [ "$answer" == "yes" ]; then
                        apt-get install $1; 
                        #exit if apt has failed
                        if [ "$?" -gt "0" ]; then
                                exit 1;
                        else
                                printf "the %d was installed continuing" "$1";
                        fi;
                else
                        printf "A manual %s instalation is requied to continue.\nAborting." "$1";
                        exit 1;
                fi;

	else
		printf "yout system is not supported by automatic install so you need install dependices by hand.\n"
        fi;

	#ubuntu
	if [ "$os_type" == "ubuntu" ]; then
		print "It's seem your system don't have %s instaled,l do you wanna install it for you?[Yes/No]" "$1";
	fi;
}

printf "Configuring for compilation...\n"
printf "Detecting libs:\n";
sleep 1;
printf "ifaddrs: "

if [ -f "/usr/include/ifaddrs.h" ]; then 
#DEPRECIETED -> printf "%10s %s [ OK  ] %s \n" "$GREEN" "$CLEAR";
#	sleep 1
	OK_OUT;

else
#DEPRECIETED -> printf "%b[ !!! FAIL !!! ] %b \n" "$RED" "$CLEAR ";
	FAIL_OUT;

fi;

printf "if.h: "
if [ -f "/usr/include/net/if.h" ]; then
#       sleep 1
       OK_OUT;
else
       FAIL_OUT;

fi;

printf "inet.h: "
if [ -f "/usr/include/arpa/inet.h" ]; then
#       sleep 1
       OK_OUT;
else
       FAIL_OUT;

fi;

printf "pthread.h"
if [ -f "/usr/include/pthread.h" ]; then
#	sleep 1
	OK_OUT;
else
	FAIL_OUT
fi;

#printf "gl.h"
#if [ -f "/usr/include/GL/gl.h" ]; then 
#	OK_OUT;
#else
#	FAIL_OUT
#fi;

printf "regex.h"
if [ -f "/usr/include/regex.h" ]; then
#	sleep 1
	OK_OUT;
else
	FAIL_OUT
fi;

printf "Initalizing search for compiler dependencies...\n"
sleep 1
printf "Detecting compiler g++ "

if [ -f "/usr/bin/g++" ]; then
	OK_OUT;
else
	FAIL_OUT;
	os_detect "g++"
fi;

printf "sqlite3 dev"
if [ -f "/usr/include/sqlite3.h" ]; then
	OK_OUT;
else
	FAIL_OUT;
	os_detect "libsqlite3-dev"
fi;

printf "gtk+3.0 dev"
if [ -f "/usr/include/gtk/gtk.h" ]; then
	OK_OUT;
else
	FAIL_OUT;
	os_detect "libgtk-3-dev";
fi;


printf "All depedencies are solved, please do a [%s%bmake%b] to compile the program.\n" "" "$GREEN" "$CLEAR";
