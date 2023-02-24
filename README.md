# Proof-of-Concept Exploits

This repository contains a collection of PoC exploits for various vulnerabilities in popular software and systems. These PoCs are intended for educational and research purposes only, and should never be used to target or exploit systems without explicit permission from the owner.

## Available PoCs

The following PoCs are currently available in this [repository](https://github.com/SirCryptic/PoC):

### [CVE-2022-20855](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2022-20855)

Description: Microsoft Exchange Server ProxyShell vulnerability (CVE-2022-20855) allows an attacker to execute arbitrary code on a Microsoft Exchange server by sending a specially crafted HTTP request to the server.

### [CVE-2022-24115](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2022-24115)

Description: The GNU Bash shell is vulnerable to a command injection vulnerability (CVE-2022-24115) that allows an attacker to execute arbitrary commands on a vulnerable system by sending a specially crafted HTTP request with a malicious user agent header.

### [CVE-2017-9834](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2017-9834)

Description: The Struts2 framework is vulnerable to a remote code execution vulnerability (CVE-2017-9834) that allows an attacker to execute arbitrary code on a vulnerable server by sending a specially crafted Content-Type header in a HTTP request.

### [CVE-2023-21773](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2023-21773)

This is a proof of concept (PoC) for the Windows Kernel Elevation of Privilege Vulnerability (CVE-2023-21773).

Description: The vulnerability allows a local attacker to elevate privileges on a vulnerable system. The vulnerability exists due to an incorrect implementation of the kernel access control list (ACL) check. A local attacker can exploit this vulnerability by running a specially crafted application and gaining elevated privileges.
The PoC demonstrates how to exploit the vulnerability to elevate privileges on a vulnerable system. The PoC uses the `NtSetInformationProcess` function to modify the access token of the current process, granting the process SeDebugPrivilege. The PoC then spawns a new process with the elevated privileges using the `CreateProcessWithTokenW` function.

### If i dont update the readme with CVE's availble or info on them i genuinly cba , im sure you can understand if not meh yolo

## Disclaimer

The author of this repository is not responsible for any damage caused by the use or misuse of these PoC exploits. These PoCs are intended for educational and research purposes only, and should never be used to target or exploit systems without explicit permission from the owner.
