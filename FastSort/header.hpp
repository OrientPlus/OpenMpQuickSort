#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <algorithm>
#include <string>
#include <filesystem>
#include <fstream>

#include <omp.h>

namespace fs = std::filesystem;

template <typename T>
class FastSort
{
public:
	void loadFromFile(std::string filename)
    {
        fs::path src_path(filename);
        if (!fs::exists(src_path)) {
            std::cout << "The file '" << filename << "'does not exist." << std::endl;
            return;
        }

        std::ifstream input_file(src_path);
        if (!input_file.is_open()) {
            std::cout << "The file could not be opened." << std::endl;
            return;
        }

        T tmp;
        while (input_file >> tmp) {
            data.push_back(tmp);
        }
        input_file.close();

        return;
    }

	void saveToFile(std::string filename)
    {
        fs::path src_path(filename);

        std::ofstream output_file(src_path);
        if (!output_file.is_open()) {
            std::cout << "The file could not be opened." << std::endl;
            return;
        }

        for (auto value : data) {
            output_file << value << " ";
        }
        output_file.close();
    }

	void generateRandom(size_t size)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

        data.resize(size);
        for (size_t i = 0; i < size; i++)
            data[i] = distrib(gen);

        return;
    }

	void quickSort()
    {
        omp_set_num_threads(5);

#pragma omp parallel shared(data)
        {
#pragma omp single nowait
            {
                sort(data, 0, data.size() - 1);
            }
        }
    }

private:
	T partition(std::vector<T>& data, T low, T high)
    {
        T pivot = data[low];
        T i = low - 1;
        T j = high + 1;
        while (true) {
            do {
                i++;
            } while (data[i] < pivot);
            do {
                j--;
            } while (data[j] > pivot);
            if (i >= j)
                return j;
            std::swap(data[i], data[j]);
        }
    }

	void sort(std::vector<T>& data, T left, T right)
    {
        if (left < right) {
            T pivot_index = partition(data, left, right);
#pragma omp task shared(data)
            sort(data, left, pivot_index);
#pragma omp task shared(data)
            sort(data, pivot_index + 1, right);
        }
    }

	std::vector<T> data;

};