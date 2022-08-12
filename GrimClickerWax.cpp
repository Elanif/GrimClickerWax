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
        shardbonus s{};
        shard_vector.push_back({ });
        std::string line;
        while (std::getline(shard_array, line)) {
            std::stringstream ss(line);
            ss >> s.total_cost;

            for (std::size_t i = 0; i < skill_number; ++i)
                ss >> s.s[i];

            shard_vector.push_back(s);
            if (shard_array.bad() || shard_array.eof()) break;
        }
    }
    std::uint64_t wax_remaining = 1;
    std::uint64_t wax_stored = 0;
    std::size_t last_updated = 0;
    while (!exit) {
        if (wax_stored>0) {
            std::cout << wax_stored << " stored wax.";
        }
        std::cout << "How much wax do you have? Enter 0 to reset the stored wax, exit to exit ";
        std::string wax_string;
        std::cin >> wax_string;
        if (wax_string=="exit") break;
        std::int64_t wax_remaining_int = -1;
        try {
            wax_remaining_int = std::stoll(wax_string);
        }
        catch (std::exception& e) {
            continue;
        }
        if (wax_remaining_int < 0) {
            continue;
        }
        else if (wax_remaining_int == 0) {
            wax_remaining = 0;
            wax_stored = 0;
            last_updated = 0;
            continue;
        }
        wax_remaining = wax_remaining_int;
        std::size_t i = last_updated+1;
        while (i < shard_vector.size() && shard_vector[i].total_cost  < shard_vector[last_updated].total_cost + wax_remaining)
            ++i;
        last_updated=--i;
        std::cout <<"\n\r"<< i<<"\n\r";
        wax_stored = shard_vector[i].total_cost;
    }
    std::cout << "Exiting\n\r";
}
