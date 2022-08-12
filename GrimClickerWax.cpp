// GrimClickerWax.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<cstdint>
#include<string>
#include<vector>
#include<fstream>
#include<array>
#include<sstream>
#include<windows.h>
#include<WinUser.h>

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
        --i;
        //focus window, check if correct resolution if not correct it with SetWindowPos function (winuser.h)
        std::array<std::size_t, skill_number> permutation = { 3,5,0,4,2,1 };
        for (const auto& p : permutation) {
            //move mouse on option[p] with offset
            std::uint16_t level_diff = shard_vector[i].s[p] - shard_vector[last_updated].s[p];
            //click on it level_diff times
        }
        last_updated=i;
        std::cout <<"\n\r"<< i<<"\n\r";
        wax_stored = shard_vector[i].total_cost;
        INPUT click[1] = {};
        click[0].type = INPUT_MOUSE;
        click[0].mi.dx = 1400/2560.*65536;
        click[0].mi.dy = 700 / 1440. * 65536;
        click[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;

        SendInput(1, click, sizeof(click));


        HWND gc_handle = FindWindowW(NULL, TEXT("GRIM CLICKER"));
        RECT gc_rect{};
        bool rect_gained = GetWindowRect(gc_handle, &gc_rect);
        std::cout << (gc_rect.right - gc_rect.left) << " " << (gc_rect.bottom - gc_rect.top) << "\n\r";

    }
    std::cout << "Exiting\n\r";
}
