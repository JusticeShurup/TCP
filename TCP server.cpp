#include <iostream>
#include <string>
#include <Poco/Net/StreamSocket.h>	
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HostEntry.h>
#include <Poco/Net/SocketStream.h>

using namespace Poco::Net;

void reverse() {

}

int main() {

	ServerSocket server(313);
	while (true) {
		StreamSocket sock = server.acceptConnection();
		SocketStream ss(sock);
		uint32_t size_text;
		sock.receiveBytes(&size_text, sizeof(size_text));
		std::string text(size_text, ' ');
		sock.receiveBytes(&(text[0]), size_text);
		std::reverse(text.begin(), text.end());
		sock.sendBytes(text.c_str(), text.size());
	}
	return 0;
}