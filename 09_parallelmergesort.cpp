#include <thread>
#include <iostream>
#include <numeric>
#include <vector>
#include <future>
#include <thread>

using namespace std;
vector<double> Mergesort(vector<double>&& vec);
vector<double> Mergesort(vector<double>& vec);

vector<double> Mergesort(vector<double>&& vec) {

	vector<double>& vecref = vec;
	return Mergesort(vecref);
}

vector<double> Mergesort(vector<double>& vec) {
	if (vec.size() <= 1)
		return vec;

	auto left_th = async([&](){ return Mergesort(vector<double>(vec.begin(), vec.begin() + vec.size()/2)); });
	auto right_th = async([&](){ return Mergesort(vector<double>(vec.begin() + vec.size()/2, vec.end()));});

	auto left = left_th.get();
	auto right = right_th.get();

	vector<double> merged;

	while (left.size() > 0 && right.size() > 0) {
		if (left[0] <= right[0]) {
			merged.push_back(left[0]);
			left.erase(left.begin());
		} else {
			merged.push_back(right[0]);
			right.erase(right.begin());
		}
	}

	while (left.size() > 0) {
		merged.push_back(left[0]);
		left.erase(left.begin());
	}

	while (right.size() > 0) {
		merged.push_back(right[0]);
		right.erase(right.begin());
	}

	vec = merged;
	return vec;
}

vector<double> GenerateVector(size_t n) {
	vector<double> vec;
	for (size_t i = 0; i < n; i++) {
		vec.push_back((double)rand()/RAND_MAX);
		vec[vec.size()-1] *= 1000;
	} 
	return vec;
}

void PrintVector(const vector<double>& vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		cout << vec[i] << ", ";
	}
	cout << endl;
}

int main() {

	vector<double> vec = GenerateVector(100);

	cout << "Before sorting:" << endl;
	PrintVector(vec);
	Mergesort(vec);
	cout << "After sorting:" << endl;
	PrintVector(vec);

	return 0;
}