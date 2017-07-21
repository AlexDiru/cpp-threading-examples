#include <thread>
#include <iostream>

std::mutex m;

void foo() {
	std::unique_lock<std::mutex> lk{m};
	std::cout << "Daisaku" << std::endl;
}

struct Foo {
	void operator()() {
		std::unique_lock<std::mutex> lk{m};
		std::cout << "Kuze" << std::endl;
	}
};

int main() {

	std::thread t1 { foo };
	std::thread t2 { Foo() };

	t1.join();
	t2.join();

	std::cout << "Threading Completed" << std::endl;
}