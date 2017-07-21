#include <thread>
#include <iostream>
#include <future>

using namespace std;

//Place the result in p
void Produce(promise<int> &p) {
	try {
		int res;

		res = 3 + 2;

		p.set_value(res);

	} catch (...) {
		//Failed to compute the result
		p.set_exception(current_exception());
	}
}

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

	promise<int> prom;
	future<int> futu = prom.get_future();

	thread t1 { Produce, ref(prom) };
	thread t2 { Consume, ref(futu) };

	t1.join();
	t2.join();
}