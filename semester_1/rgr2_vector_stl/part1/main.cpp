#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
#include <stdexcept>

void ShowNumbers(const std::vector<int>& arr)
{
    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (i != 0)
        {
            std::cout << ' ';
        }
        std::cout << arr[i];
    }
    std::cout << '\n';
}

int main()
{
    try
    {
        std::vector<int> arr;

        std::cout << "Put numbers (stop with any non-number):\n";
        int x = 0;
        while (std::cin >> x)
        {
            arr.push_back(x);
        }

        if (arr.empty())
        {
            throw std::runtime_error("No numbers in array");
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Array: \n";
        ShowNumbers(arr);

        long long sum = std::accumulate(arr.begin(), arr.end(), 0LL);
        std::cout << "Sum: " << sum << '\n';
        std::cout << "Count: " << arr.size() << '\n';

        int target = 0;
        std::cout << "Find number equal to: ";
        if (!(std::cin >> target))
        {
            throw std::runtime_error("Bad input for target number");
        }
        std::cout << "Equal to " << target << ": " 
                  << std::count(arr.begin(), arr.end(), target) << '\n';

        int n = 0;
        std::cout << "Find number bigger than: ";
        if (!(std::cin >> n))
        {
            throw std::runtime_error("Bad input for comparison number");
        }
        std::cout << "Bigger than " << n << ": " 
                  << std::count_if(arr.begin(), arr.end(), [n](int val) { return val > n; }) << '\n';

        if (arr.size() == 0)
        {
            throw std::runtime_error("Cannot calculate average for empty array");
        }
        int average = static_cast<int>(sum / static_cast<long long>(arr.size()));
        std::replace_if(arr.begin(), arr.end(), [](int val) { return val == 0; }, average);
        std::cout << "No zeros: \n";
        ShowNumbers(arr);

        size_t left = 1;
        size_t right = 1;
        std::cout << "Put left and right (from 1): ";
        if (!(std::cin >> left >> right))
        {
            throw std::runtime_error("Bad input for interval");
        }

        if (left < 1) left = 1;
        if (right < 1) right = 1;
        if (left > arr.size()) left = arr.size();
        if (right > arr.size()) right = arr.size();
        if (left > right) std::swap(left, right);

        if (left > arr.size() || right > arr.size() || left < 1 || right < 1)
        {
            throw std::runtime_error("Interval out of bounds");
        }

        long long partsum = std::accumulate(arr.begin() + (left - 1), 
                                            arr.begin() + right, 0LL);
        std::transform(arr.begin(), arr.end(), arr.begin(),
                       [partsum](int val) { 
                           long long result = static_cast<long long>(val) + partsum;
                           if (result > std::numeric_limits<int>::max() || 
                               result < std::numeric_limits<int>::min())
                           {
                               throw std::overflow_error("Overflow during addition");
                           }
                           return static_cast<int>(result);
                       });
        std::cout << "Part sum: " << partsum << '\n';
        ShowNumbers(arr);

        if (arr.empty())
        {
            throw std::runtime_error("Array empty after transformations");
        }
        
        auto minmax = std::minmax_element(arr.begin(), arr.end());
        if (minmax.first == arr.end() || minmax.second == arr.end())
        {
            throw std::runtime_error("Cannot find min or max");
        }
        long long diff = static_cast<long long>(*minmax.second) - static_cast<long long>(*minmax.first);
        if (diff > std::numeric_limits<int>::max() || diff < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Overflow in min-max difference");
        }
        int diff_int = static_cast<int>(diff);

        for (int& val : arr)
        {
            if ((std::abs(static_cast<long long>(val)) % 2) == 0)
            {
                val = diff_int;
            }
        }
        std::cout << "Max minus min: " << diff_int << '\n';
        ShowNumbers(arr);

        std::vector<int> newarr;
        std::vector<int> used;
        used.reserve(arr.size());

        for (int val : arr)
        {
            int aval = std::abs(val);
            if (std::find(used.begin(), used.end(), aval) == used.end())
            {
                used.push_back(aval);
                newarr.push_back(val);
            }
        }

        arr.swap(newarr);
        std::cout << "Unique by abs: \n";
        ShowNumbers(arr);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error\n";
        return 2;
    }

    return 0;
}