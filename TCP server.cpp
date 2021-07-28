#include <iostream>
#include <string>
#include <Poco/Net/StreamSocket.h>	
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HostEntry.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/ThreadPool.h>

using namespace Poco::Net;

class Target 
	: public Poco::Runnable {
public:
	Target(StreamSocket sock) : sock(sock) {
		std::cout << "Connection accept" << std::endl;
		size_text = 0;
	}
	~Target() {
		delete this;
	}
	void run() override {
		sock.receiveBytes(&size_text, sizeof(size_text));
		std::cout << size_text << std::endl;
		std::string text(size_text, ' ');
		sock.receiveBytes(&(text[0]), size_text);
		std::reverse(text.begin(), text.end());
		sock.sendBytes(text.c_str(), text.size());
		sock.close();
	}
private:	
	StreamSocket sock;
	uint32_t size_text;
	std::string text;
};

int main() {
	Poco::ThreadPool threadPool;
	std::vector<Target*> targets;
	ServerSocket server(313);
	Target* target;
	while (true) {
		StreamSocket sock = server.acceptConnection();
		target = new Target(sock);
		try {
			threadPool.start(*target);
		}
		catch (Poco::NoThreadAvailableException& e) {
			targets.push_back(target);
		}
	}
	threadPool.joinAll();
	return 0;
}