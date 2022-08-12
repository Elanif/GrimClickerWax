// GrimClickerWax.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<cstdint>
#include<string>
#include<vector>
#include<fstream>
#include<array>
#include<sstream>

constexpr std::size_t skill_number=6u;

struct shardbonus {
    std::array<std::uint16_t, skill_number> s;
    
        std::uint64_t total_cost;
    };
std::vector<shardbonus> shard_vector = {};

int main()
{
    bool exit = false;
    std::string input_file = "shard_array.txt";
    std::ifstream shard_array(input_file);
    if (!shard_array.is_open()) {
        exit = true;
        std::cout << "Couldn't open " << input_file << "\n\r";
        return -1;
    }
    else {
        bool end_of_file = false;
        shardbonus s;
        std::string line;
        while (std::getline(shard_array, line)) {
            std::stringstream ss(line);

            for (std::size_t i=0; i<skill_number; ++i)
                ss >> s.s[i];

            shard_vector.push_back(s);
            if (shard_array.bad() || shard_array.eof()) break;
        }
    }
    std::uint64_t wax_remaining=1;
    std::uint64_t wax_stored=0;
    while (!exit) {
        std::cout << "How much wax do you have? Enter 0 to reset the stored wax, or else to exit ";
        std::string wax_string;
        std::cin >> wax_string;
        std::int64_t wax_remaining_int=-1;
        try {
            wax_remaining_int = std::stoll(wax_string);
        }
        catch (std::exception& e) {
            exit = true;
        }
        if (exit) break;
        if (wax_remaining_int < 0) {
            exit = true;
            break;
        }
    }
    std::cout << "Exiting\n\r";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
