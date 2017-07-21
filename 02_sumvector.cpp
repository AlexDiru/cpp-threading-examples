#include <thread>
#include <iostream>
#include <vector>

void SumVector(const std::vector<double>& vec, double& result) {
	double sum = 0;
	for (int i = 0; i < vec.size(); i++)
		sum += vec[i];

	result = sum;
}

int main() {

	std::vector<double> v1 { 1, 2, 3.2, 7, 9, 10 };
	std::vector<double> v2 { 4, 5, 9.5, 7, 9, 10 };

	double res1;
	double res2;

	std::thread t1 { SumVector, std::cref(v1), std::ref(res1) };
	std::thread t2 { SumVector, std::cref(v2), std::ref(res2) };
	
	//Doesn't work: (needs ref and cref)
	//std::thread t1 { SumVector, v1, res1 };
	//std::thread t2 { SumVector, v2, res2 };

	t1.join();
	t2.join();

	std::cout << "Res 1: " << res1 << std::endl;
	std::cout << "Res 2: " << res2 << std::endl;

	std::cout << "Threading Completed" << std::endl;
}
