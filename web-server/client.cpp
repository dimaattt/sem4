#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

#define PORT 8000
#define BACKLOG 5
#define BUFSIZE 1024
#define BASE_ADDR "127.0.0.1"

class SocketAddress
{
    struct sockaddr_in saddr_; // см содержимое структуры
public:
    SocketAddress()
    {
        saddr_.sin_family = AF_INET;
        saddr_.sin_port = htons(PORT);
        saddr_.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        cout << "empty constr" << endl;
    }
    SocketAddress(const char *ip, short port)
    {
        saddr_.sin_family = AF_INET;
        saddr_.sin_port = htons(port);
        saddr_.sin_addr.s_addr = inet_addr(ip);
    }

    int GetAdrLen() const { return sizeof(saddr_); }

    struct sockaddr *GetAddr() const
    {
        return (sockaddr *)&saddr_;
    }
};

class Socket
{
protected:
    int sd_;
    explicit Socket(int sd) : sd_(sd) {}

public:
    Socket() { sd_ = socket(AF_INET, SOCK_STREAM, 0); }
    ~Socket()
    {
        close(sd_);
    }

    int GetSd() const { return sd_; }
};

class ConnectedSocket : public Socket
{
public:
    ConnectedSocket() = default;
    explicit ConnectedSocket(int sd) : Socket(sd) {}

    void Write(const string &str)
    {
        int send_result = send(sd_, str.c_str(), str.length(), 0);
        if (send_result < 0)
        {
            cerr << "errr with write" << endl;
            exit(1);
        }
    }
    void Read(string &str)
    {
        char buf[BUFSIZE];
        int recv_result = recv(sd_, buf, BUFSIZE, 0);
        if (recv_result < 0)
        {
            cerr << "errr with read" << endl;
            exit(1);
        }

        str = buf;
    }
};

class ClientSocket : public ConnectedSocket
{
public:
    void Connect(const SocketAddress &serverAddr)
    {
        int connect_result = connect(sd_, serverAddr.GetAddr(), serverAddr.GetAdrLen());
        if (connect_result < 0)
        {
            cerr << "err with connect" << endl;
            exit(1);
        }
    }
};

vector<string> split_lines(const string &str)
{
    vector<string> tmp;
    string cur_line = "";

    for (char c : str)
    {
        if (c == '\n')
        {
            tmp.push_back(cur_line);
            cur_line = "";
        }
        else
        {
            cur_line += c;
        }
    }

    if (!cur_line.empty())
    {
        tmp.push_back(cur_line);
    }

    return tmp;
}

string add_lines(const vector<string> &lines)
{
    string tmp;
    for (const auto &l : lines)
    {
        tmp += l;
        tmp += '\n';
    }

    return tmp;
}

void client_connection()
{
    ClientSocket s;
    SocketAddress saddr(BASE_ADDR, PORT);
    s.Connect(saddr);

    string req = "MAMA";
    s.Write(req);
    cout << req << endl;

    string res;
    s.Read(res);
    cout << res << '\n';

    vector<string> lines = split_lines(res);
}
int main()
{
    client_connection();
    return 0;
}