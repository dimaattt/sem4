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
    }
    SocketAddress(const char *ip, short port)
    {
        saddr_.sin_family = AF_INET;
        saddr_.sin_port = htons(PORT);
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

    void Shutdown()
    {
        shutdown(sd_, SHUT_RDWR);
    }
};

class ServerSocket : public Socket
{
public:
    ServerSocket() : Socket() {}

    void Bind(const SocketAddress &server_addr)
    {
        int bind_result = bind(sd_, server_addr.GetAddr(), server_addr.GetAdrLen());
        if (bind_result < 0)
        {
            cerr << "errr with bind" << endl;
            exit(1);
        }
    }

    void Listen()
    {
        int listen_result = listen(sd_, BACKLOG);
        if (listen_result < 0)
        {
            cerr << "errr with listen" << endl;
            exit(1);
        }
    }

    int Accept(SocketAddress &client_addr)
    {
        int len = client_addr.GetAdrLen();
        int client_sd = accept(sd_, (struct sockaddr *)&client_addr, (socklen_t *)&len);
        if (client_sd < 0)
        {
            cerr << "errr with accept" << endl;
            exit(1);
        }
        return client_sd;
    }
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
            cerr << "errr with write (string)" << endl;
            exit(1);
        }
    }
    void Read(string &str)
    {
        char buf[BUFSIZE];
        int recv_result = recv(sd_, buf, BUFSIZE, 0);
        if (recv_result < 0)
        {
            cerr << "errr with read (string) " << errno << endl;
            exit(1);
        }

        str = buf;
    }

    void Write(const vector<uint8_t> &bytes)
    {
        int send_result = send(sd_, bytes.data(), bytes.size(), 0);
        if (send_result < 0)
        {
            cerr << "errr with write (vector)" << endl;
            exit(1);
        }
    }
    void Read(vector<uint8_t> &bytes)
    {
        char buf[BUFSIZE];
        int recv_result = recv(sd_, buf, BUFSIZE, 0);
        if (recv_result < 0)
        {
            cerr << "errr with read (vector)" << endl;
            exit(1);
        }

        bytes = vector<uint8_t>(buf, buf + recv_result);
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

void process_connection(int cd, const SocketAddress &client_addr)
{
    ConnectedSocket cs(cd);
    string req;
    cs.Read(req);
    vector<string> lines = split_lines(req);

    for (int i = 0; i < lines.size(); i++)
    {
        cout << "loop: " << lines[i] << " len = " << lines[i].length() << endl;
        lines[i] = "avs";
    }

    string resp;
    resp = add_lines(lines);
    cs.Write(resp);
    cs.Shutdown();
}

void server_loop()
{
    ServerSocket server_socket;
    SocketAddress server_address(BASE_ADDR, PORT);
    server_socket.Bind(server_address);
    cout << "binded succsessfull!" << endl;
    server_socket.Listen();
    for (;;)
    {
        SocketAddress client_addr;
        int cd = server_socket.Accept(client_addr);
        process_connection(cd, client_addr);
    }
}

int main()
{
    server_loop();
    return 0;
}
