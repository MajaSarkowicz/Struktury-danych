#include <random>
#include <vector>
#include <iostream>
#include <chrono>
#include "test_consts.hpp"

using namespace std;

template <typename T> T populate_structure(int seed, int size){
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
    T structure;
    for(int i = 0; i<size; i++){
        structure.add_back(dist(rng));
    }
    return structure;
}

template <typename T> vector<T> generate_test_structures(int batch){
    vector<T> structures;
    for(int i = 0; i<size(MEASUREMENT_POINTS); i++){
        structures.push_back(populate_structure<T>(batch + i, MEASUREMENT_POINTS[i]));
    }
    return structures;
}

template <typename T> vector<T> create_reiteration_copies(T structure, int reiterations){
    vector<T> reiter_copies;
    for(int i = 0; i < reiterations; i++){
        reiter_copies.push_back(structure);
    }
    return reiter_copies;
}

template <typename T> vector<double> run_add_front_tests(vector<T> cases, int reiterations){
    vector<double> times;
    double avg_time, run_time;
    for(int i = 0; i < cases.size(); i++){
        vector<T> reiter_copies = create_reiteration_copies<T>(cases[i], reiterations);
        auto start = chrono::steady_clock::now();
        for(int j = 0; j<reiterations; j++){
            reiter_copies[j].add_front(13);
        }
        auto end = chrono::steady_clock::now();
        run_time = chrono::duration<double>(end - start).count();
        avg_time = run_time/reiterations;
        times.push_back(avg_time)
    }
    return times;
}

template <typename T> vector<double> run_add_back_tests(vector<T> cases, int reiterations){
    vector<double> times;
    double avg_time, run_time;
    for(int i = 0; i < cases.size(); i++){
        vector<T> reiter_copies = create_reiteration_copies<T>(cases[i], reiterations);
        auto start = chrono::steady_clock::now();
        for(int j = 0; j<reiterations; j++){
            reiter_copies[j].add_back(34636);
        }
        auto end = chrono::steady_clock::now();
        run_time = chrono::duration<double>(end - start).count();
        avg_time = run_time/reiterations;
        times.push_back(avg_time)
    }
    return times;
}
