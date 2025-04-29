#pragma once
#include <vector>
#include <iostream>
#include <random>
using namespace std;

class Generator {
    private:
        mt19937 random_generator_;
        int returnRandom(int min, int max) {
            // min,max - включает
            if (max < min) swap(max, min);
            std::uniform_int_distribution<int> range(min, max);
            return range(random_generator_);
        }
    public:
        Generator() {
            random_device device;
            random_generator_.seed(device());
        }
        int get_int(int mn, int mx) {
            return returnRandom(min(mn, mx), max(mx, mn));
        }
        vector<int> get_arr_unic_int(int mn, int mx, int size) {
            vector<int> arr(size);
            for (int i = 0; i < size; i++) {
                arr[i] = returnRandom(min(mn, mx), max(mx, mn));
                bool need_repeat = false;
                for (int j = 0; j < i; j++) {
                    if (arr[i] == arr[j]) {
                        need_repeat = true;
                    }
                }
                if (need_repeat) i--;
            }
            return arr;
        }
        vector<int> get_arr_int(int mn, int mx, int size) {
            vector<int> arr(size);
            for (int i = 0; i < size; i++) {
                arr[i] = returnRandom(min(mn, mx), max(mx, mn));
            }
            return arr;
        }
    };