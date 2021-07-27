#include <iostream>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Windows.h>

using namespace Poco::Net;
int main() {
	SocketAddress server_addr("127.0.0.1:313");
	StreamSocket sock(server_addr); // вот тут подключение
	SocketStream ss(sock);
	uint32_t size_text;
	std::string text;
	std::cout << "Enter string: ";
	std::cin >> text;
	size_text = text.size();
	sock.sendBytes(&size_text, sizeof(size_text));
	Sleep(1000);
	sock.sendBytes(text.c_str(), text.size());
	sock.receiveBytes(&(text[0]), size_text);
	std::cout << text << std::endl;
	return 0;
}