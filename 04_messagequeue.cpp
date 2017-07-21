#include <iostream>
#include <string>
#include <queue>
#include <thread>

using namespace std;

class Message {
	std::string Data;
	int ID;
public:
	Message(const std::string& data) {
		Data = data;
		static int id = 0;
		ID = id;
		id++;
	}

	const std::string& GetData() const { return Data; }
	const int GetID() const { return ID; }
};

queue<Message> messageQueue;
condition_variable cv;
mutex m;

void workerfunction() {

	while (true) {
		//Acquire mutex
		unique_lock<mutex> lk {m};
		//Release mutex until we have messages
		cv.wait(lk, []{ return messageQueue.size() > 0; });

		auto message = messageQueue.front();
		messageQueue.pop();
		lk.unlock();

		cout << "Processing: " << message.GetData() << " (" << message.GetID() << ")" << endl;
	}
}

int main() {
	thread worker(workerfunction);

	//Producer
	while (true) {
		Message msg{"Hello World!"};

		//Need to make sure worker is not accessing the queue otherwise we get a seg fault
		unique_lock<mutex> lk {m}; 
		messageQueue.push(msg);
	}
}

