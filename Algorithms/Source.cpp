#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>
#include <random>
#include <thread>
#include "matplotlibcpp.h"

using namespace std;
namespace plt = matplotlibcpp;

bool keepRunning = true;
bool isBubbleSortRunning = true, isQuickSortRunning = true;
vector<int> arrX_1, arrY_1, arrZ_1, arrX_2, arrY_2, arrZ_2;


template<typename Func, typename... Args>
double benchmark(Func&& func, Args&&... args) {
	auto begin = chrono::steady_clock::now();
	func(forward<Args>(args)...);
	auto end = chrono::steady_clock::now();

	return chrono::duration_cast<chrono::microseconds>(end - begin).count();
}



vector<int> generateRandomVector(int size) {
	vector<int> randomVec;
	random_device rd;
	default_random_engine eng(rd());
	uniform_int_distribution<int> dist(0, INT_MAX);

	for (int i = 0; i < size; i++) {
		randomVec.push_back(dist(eng));
	}
	return randomVec;
}

void generateRandomStringWithSubstring(int strSize, int subStrSize, string& str, string& subStr, int randomnessPercent = 5) {
	random_device rd;
	default_random_engine eng(rd());
	uniform_int_distribution<int> charDist(0, 25);
	uniform_int_distribution<int> randomDist(0, INT_MAX);

	for (int i = 0; i < strSize; i++) {
		if (rand() % 2) {
			str += char('a' + charDist(eng));
		}
		else {
			str += char('A' + charDist(eng));
		}
	}

	if (randomDist(eng) % randomnessPercent == 0) {
		for (int i = 0; i < subStrSize; i++) {
			if (rand() % 2) {
				subStr += char('a' + charDist(eng));
			}
			else {
				subStr += char('A' + charDist(eng));
			}
		}
	}
	else {
		uniform_int_distribution<int> startDist(0, strSize - subStrSize - 1);
		subStr = str.substr(startDist(eng), subStrSize);
	}
}


void plotThread() {
	plt::ion();

	while (keepRunning) {
		plt::clf();
		plt::plot(arrX_1, arrY_1, { {"label", "Quick Sort"} });
		plt::plot(arrX_2, arrY_2, { {"label", "Bubble Sort"} });

		plt::legend();
		plt::xlabel("Array Size");
		plt::ylabel("Time Taken (Microsecond)");

		int maxY = max({ arrY_1.back(), arrX_2.back(), arrY_2.back(), arrX_1.back() }) + 10000;

		plt::ylim(0, maxY);
		plt::xlim(0, maxY);
		plt::draw();
		plt::pause(0.001);
	}

}


void bubbleSort(vector<int>& arr) {
	for (int i = 0; i < arr.size() - 1; i++) {
		for (int j = 0; j < arr.size() - i - 1; j++) {
			if (arr[j] >= arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void quickSort(vector<int>& arr, int low, int high) {
	if (low >= high)
		return;

	int pivot = arr[high];
	int idx = low;

	for (int i = low; i <= high; i++) {
		if (arr[i] < pivot) {
			swap(arr[i], arr[idx]);
			idx++;
		}
	}

	swap(arr[high], arr[idx]);

	quickSort(arr, low, idx - 1);
	quickSort(arr, idx + 1, high);
}



vector<int> bruteForceSearch(const string& str, const string& subStr) {
	vector<int> foundIndices;

	for (int i = 0; i < str.size(); i++) {
		bool found = true;
		for (int j = 0; j < subStr.size(); j++) {
			if (i + j >= str.size()) {
				found = false;
				break;
			}

			if (str[i + j] != subStr[j]) {
				found = false;
			}

		}
		if (found) {
			foundIndices.push_back(i);
		}
	}

	return foundIndices;
}

vector<int> boyerMoore(const string& str, const string& subStr) {
	vector<int> foundIndices;
	vector<int> indices(256, -1);

	for (int i = 0; i < subStr.size(); i++) {
		indices[subStr[i]] = i;
	}

	for (int i = 0; i <= str.size() - subStr.size();) {
		bool found = true;
		int j = subStr.size() - 1;
		for (; j >= 0; j--) {
			if (str[i + j] != subStr[j]) {
				found = false;
				i += max(1, j - indices[str[i + j]]);
				break;
			}
		}

		if (found) {
			foundIndices.push_back(i);

			if (i + j < str.size()) {
				i += str.size() - indices[str[i + j]];
			}
			else {
				i += 1;
			}
		}
	}

	return foundIndices;
}



void quickSortBenchmark() {
	int arraySize = 500;

	for (int i = 0; i < 400; i++) {
		vector<int> randomVec = generateRandomVector(arraySize);

		int quickSortTime = 0;

		for (int j = 0; j < 10; j++) {
			vector<int> vecCopy = randomVec;
			quickSortTime += benchmark([](vector<int>& arr, int low, int high) { quickSort(arr, low, high); }, vecCopy, 0, vecCopy.size() - 1);
		}

		quickSortTime /= 10;

		arrX_1.push_back(arraySize);
		arrY_1.push_back(quickSortTime);

		arraySize += 500;
	}
}

void bubbleSortBenchmark() {
	int arraySize = 500;

	for (int i = 0; i < 30; i++) {
		vector<int> randomVec = generateRandomVector(arraySize);

		int bubbleSortTime = 0;

		for (int j = 0; j < 10; j++) {
			vector<int> vecCopy = randomVec;
			bubbleSortTime += benchmark([](vector<int>& arr) { bubbleSort(arr); }, vecCopy);
		}

		bubbleSortTime /= 10;

		arrX_2.push_back(arraySize);
		arrY_2.push_back(bubbleSortTime);
		arraySize += 500;
	}
}

void bruteForceSearchBenchmark() {
	for (int strSize = 2; strSize < 10000; strSize += 1000) {
		for (int subStrSize = 1; subStrSize < strSize; subStrSize += 1000) {
			string str, subStr;
			generateRandomStringWithSubstring(strSize, subStrSize, str, subStr);

			int searchTime = 0;

			for (int k = 0; k < 10; k++) {
				searchTime += benchmark([](const string& str, const string& subStr) { bruteForceSearch(str, subStr); }, str, subStr);
			}

			arrX_1.push_back(strSize);
			arrY_1.push_back(subStrSize);
			arrZ_1.push_back(searchTime / 10);
		}
	}
	isQuickSortRunning = false;
}

void boyerMooreBenchmark() {
	for (int strSize = 2; strSize < 30000; strSize += 1000) {
		for (int subStrSize = 1; subStrSize < strSize; subStrSize += 1000) {
			string str, subStr;
			generateRandomStringWithSubstring(strSize, subStrSize, str, subStr);

			int searchTime = 0;
			for (int k = 0; k < 10; k++) {
				searchTime += benchmark([](const string& str, const string& subStr) { boyerMoore(str, subStr); }, str, subStr);
			}
			arrX_2.push_back(strSize);
			arrY_2.push_back(subStrSize);
			arrZ_2.push_back(searchTime / 10);
		}
	}
	isBubbleSortRunning = false;
}

int main() {
Start:
	cout << "Select benchmark comparison type:\n1. Sorting algorithms (Bubble sort vs Quick sort)\n2. Searching algorithms (Brute Force vs Boyer Moore)\n";

	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
	{
		thread bubbleSortThread(bubbleSortBenchmark);
		thread quickSortThread(quickSortBenchmark);
		thread pltThread(plotThread);

		quickSortThread.join();
		bubbleSortThread.join();

		//keepRunning = false;

		pltThread.join();

		break;
	}
	case 2:
	{
	case2:
		cout << "Would you like to use precalculated benchmark? (Y/N)\n";

		char precalcChoice;
		cin >> precalcChoice;

		precalcChoice = tolower(precalcChoice);

		switch (precalcChoice) {
		case 'y': {
			ifstream inFile("precalculated.txt");

			if (!inFile.is_open()) {
				cout << "No pre-calculated data found";
				break;
			}

			int quickSortSize, bubbleSortSize;
			inFile >> quickSortSize >> bubbleSortSize;

			arrX_1 = arrY_1 = arrZ_1 = vector<int>(quickSortSize);
			arrX_2 = arrY_2 = arrZ_2 = vector<int>(bubbleSortSize);

			for (int i = 0; i < quickSortSize; i++) {
				inFile >> arrX_1[i] >> arrY_1[i] >> arrZ_1[i];
			}

			for (int i = 0; i < bubbleSortSize; i++) {
				inFile >> arrX_2[i] >> arrY_2[i] >> arrZ_2[i];
			}

			map<string, string> font = {
					{"fontname", "Verdana"},
					{"fontsize", "15"}
			};

			plt::scatter(arrX_2, arrY_2, arrZ_2);
			plt::set_title("Boyer Moore Algorithm", font);
			plt::set_xlabel("String Size", font);
			plt::set_ylabel("Pattern Size", font);
			plt::set_zlabel("Time Taken (Microsecond)", font);

			plt::scatter(arrX_1, arrY_1, arrZ_1);
			plt::set_title("Brute Force Algorithm", font);
			plt::set_xlabel("String Size", font);
			plt::set_ylabel("Pattern Size", font);
			plt::set_zlabel("Time Taken (Microsecond)", font);

			plt::show();

			break;
		}
		case 'n': {
			bool saveResults = false;

			cout << "Do you want to save results? (Y/N)";
			char saveChoice;
			cin >> saveChoice;
			saveChoice = tolower(saveChoice);

			if (saveChoice == 'y') {
				saveResults = true;
			}

			thread boyerMooreThread(boyerMooreBenchmark);
			thread bruteForceSearchThread(bruteForceSearchBenchmark);

			while (isQuickSortRunning || isBubbleSortRunning) {
				cout << "\r Running.  ";
				this_thread::sleep_for(chrono::milliseconds(333));
				cout << "\r Running.. ";
				this_thread::sleep_for(chrono::milliseconds(333));
				cout << "\r Running...";
				this_thread::sleep_for(chrono::milliseconds(333));
			}

			boyerMooreThread.join();
			bruteForceSearchThread.join();

			map<string, string> font = {
					{"fontname", "Verdana"},
					{"fontsize", "15"}
			};

			plt::scatter(arrX_2, arrY_2, arrZ_2);
			plt::set_title("Boyer Moore Algorithm", font);
			plt::set_xlabel("String Size", font);
			plt::set_ylabel("Pattern Size", font);
			plt::set_zlabel("Time Taken (Microsecond)", font);

			plt::scatter(arrX_1, arrY_1, arrZ_1);
			plt::set_title("Brute Force Algorithm", font);
			plt::set_xlabel("String Size", font);
			plt::set_ylabel("Pattern Size", font);
			plt::set_zlabel("Time Taken (Microsecond)", font);


			if (saveResults) {
				ofstream outFile("precalculated.txt");
				outFile << arrX_1.size() << " " << arrX_2.size() << "\n";

				for (int i = 0; i < arrX_1.size(); i++) {
					outFile << arrX_1[i] << " " << arrY_1[i] << " " << arrZ_1[i] << "\n";
				}

				for (int i = 0; i < arrX_2.size(); i++) {
					outFile << arrX_2[i] << " " << arrY_2[i] << " " << arrZ_2[i] << "\n";
				}

				outFile.close();
			}
			plt::show();

			break;
		}
		default:
			goto case2;
		}
		break;
	}
	default:
		goto Start;
	}

	return 0;
}
