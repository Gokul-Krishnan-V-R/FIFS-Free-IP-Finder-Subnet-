# FIFS-Free-IP-Finder-Subnet-
FIFS (Free IP Finder in Subnet) is a simple yet valuable C program designed to send ICMP echo requests, commonly known as "pings," to a specified IP address or host within a subnet. This utility allows users to quickly check the reachability of network devices and assess network connectivity. 


                                                                     FREE IP FINDER
---------------------------------------------------------------------------------------------------------------------

Prerequisites
------------------
This program requires a Unix-like operating system.
Root privileges may be required to send ICMP packets.

Usage
------------------

Clone the repository:
bash
Copy code
use git clone 
Compile the program:

Copy code
gcc -o ping ping.c -lpthread
Run the program:

bash
Copy code
./ping <host>
Replace <host> with the IP address or hostname you want to ping.

Example
------------------

shell
Copy code
$ ./ping example.com
Ping to example.com successful.



                                                                  License
----------------------------------------------------------------------------------------------------
This project is licensed under the MIT License - see the LICENSE file for details.

