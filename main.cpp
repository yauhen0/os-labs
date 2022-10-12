#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>



void mulBlock(const std::vector <std::vector <int>>& m1, const std::vector <std::vector <int>>& m2, std::vector < std::vector <int>>& m3, int K, int P, int s, int blockSize)
{
	for (int i = K; i < std::min(K + blockSize, s); ++i)
		for (int j = P; j < std::min(P + blockSize, s); ++j)
			for (int k = 0; k < s; ++k)
				m3[i][j] += m1[i][k] * m2[k][j];
}

void mulSeq(const std::vector <std::vector <int>>& m1, const std::vector <std::vector <int>>& m2, std::vector < std::vector <int>>& m3, int s, int blockSize)
{
	for (int blockI = 0; blockI < s; blockI += blockSize)
		for (int blockJ = 0; blockJ < s; blockJ += blockSize)
			mulBlock(m1, m2, m3, blockI, blockJ, s, blockSize);
}

void mulThread(const std::vector <std::vector <int>>& m1, const std::vector <std::vector <int>>& m2, std::vector < std::vector <int>>& m3, int s, int blockSize)
{
	std::vector<std::thread> threads;
	for (int K = 0; K < s; K += blockSize)
		for (int P = 0; P < s; P += blockSize)
			threads.emplace_back(mulBlock, std::cref(m1), std::cref(m2), std::ref(m3), P, P, s, blockSize);
	for (auto& thrd : threads)
		thrd.join();
}


std::vector<double> v1;
std::vector<double> v2;

void test(std::vector< std::vector<int>>& m1, std::vector< std::vector<int>>& m2, std::vector< std::vector<int>>& m3, int s)
{
	std::ofstream out("res.txt");
	auto t1 = std::chrono::high_resolution_clock::now();
	for (int i = 1; i < s; ++i)
	{
		mulThread(m1, m2, m3, s, i);
		auto tempTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> tempDuration = tempTime - t1;
		v1.push_back(tempDuration.count());
	}
	auto t1end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> durationThread = t1end - t1;

	auto t2 = std::chrono::high_resolution_clock::now();
	for (int i = 1; i < s; ++i)
	{
		mulSeq(m1, m2, m3, s, i);
		auto tempTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> tempDuration = tempTime - t2;
		v2.push_back(tempDuration.count());
	}
	auto t2end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> durationSeq = t2end - t2;

	for (int i = 0; i < v1.size(); ++i)
	{
		out << "size " << i + 1 << " " << v2[i] / v1[i] << '\n';
	}
}

int main()
{
	int s = 30;
	std::vector< std::vector<int>> m1 = { {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
						{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30},
	};
	std::vector< std::vector<int>> m2 = m1;
	std::vector< std::vector<int>> m3(s, std::vector<int>(s));

	test(m1, m2, m3, s);
}