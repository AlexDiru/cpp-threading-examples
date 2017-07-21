#include <thread>
#include <iostream>
#include <future>

using namespace std;

//Get the result from f
void Consume(future<int> &f) {
	try {
		int res = f.get();

		cout << "Future = " << res << endl;
	} catch (...) {
		cerr << "Couldn't access value in future" << endl;
	}
}

int main() {

	packaged_task<int()> prom([]() { return 5; });
	future<int> futu = prom.get_future();

	thread t1 { move(prom) };
	thread t2 { Consume, ref(futu) };

	t1.join();
	t2.join();

	return 0;
}