#include <stdlib.h>
#include <iostream>

using namespace std;

int main() {
    cout << "<html><body>\n";
    cout << "Welcome to CGI test program\n";
    cout << "SERVER_ADDR: " << getenv("SERVER_ADDR") << endl;
    cout << "SERVER_PORT: " << getenv("SERVER_PORT") << endl;
    cout << "SERVER_PROTOCOL: " << getenv("SERVER_PROTOCOL") << endl;
    cout << "CONTENT_TYPE: " << getenv("CONTENT_TYPE") << endl;
    cout << "QUERY_STRING: " << getenv("QUERY_STRING") << endl;
    cout << "SCRIPT_NAME: " << getenv("SCRIPT_NAME") << endl;

    cout << "</body></html>\n";
    return 0;
}
