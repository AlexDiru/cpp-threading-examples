#include <thread>
#include <iostream>

void foo() {
	std::cout << "Daisaku" << std::endl;
}

struct Foo {
	void operator()() {
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

//This is bad because std::cout is not synchronised so we
//could have DaKiusazek\nu\n