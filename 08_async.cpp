#include <thread>
#include <iostream>
#include <numeric>
#include <vector>
#include <future>
#include <algorithm>

using namespace std;

//Get the result from f
double SumVector(const vector<double>& vec) {
	if (vec.size() < 1000) {
		cout << "Small Vector - Single Threaded Computation" << endl;
		return accumulate(vec.begin(), vec.end(), 0.0);
	}

	cout << "Large Vector - Multi Threaded Computation" << endl;

	auto v0 = vec.begin();
	auto sz = vec.size();

	//For some reason I can't get the parameters in the Bjarne C++ book to work
	//Can only figure out wrapping accumulate in a lambda function
	auto vec_quart = vec.size()/4;
	auto f0 = std::async(std::launch::async, [&]{ return std::accumulate(vec.begin(), vec.begin() + vec_quart, 0.0); });
	auto f1 = std::async(std::launch::async, [&]{ return std::accumulate(vec.begin() + vec_quart, vec.begin() + vec_quart*2, 0.0);});
	auto f2 = std::async(std::launch::async, [&]{ return std::accumulate(vec.begin() + vec_quart * 2, vec.begin() + vec_quart*3, 0.0);});
	auto f3 = std::async(std::launch::async, [&]{ return std::accumulate(vec.begin() + vec_quart * 3, vec.begin() + vec.size(), 0.0);});

	//Why doesn't this work?
	//auto f0_other = std::async(std::launch::async, std::accumulate, vec.begin(), vec.begin() + vec_quart, 0.0);

	return f0.get() + f1.get() + f2.get() + f3.get();
}

vector<double> GenerateVector(int n) {
	vector<double> v;
	for (int i = 0; i < n; i++)
		v.push_back(i);
	return v;
}

int main() {

	cout << "500 element sum: " << SumVector(GenerateVector(500)) << endl;
	cout << "50000 element sum: " << SumVector(GenerateVector(50000)) << endl;

	return 0;
}