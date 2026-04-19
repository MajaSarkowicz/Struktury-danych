#include <random>
#include <vector>
#include <iostream>
#include <chrono>
#include "test_consts.hpp"
#include <fstream>
#include <string>
#include <climits>

using namespace std;

template <typename T> vector<T> create_reiteration_copies(T structure, int reiterations){
    // Tworzenie wielu kopii struktury do wielokrotnych pomiarow
    vector<T> reiter_copies;
    for(int i = 0; i < reiterations; i++){
        reiter_copies.push_back(structure);
    }
    return reiter_copies;
}

template <typename T, typename Func> double run_test(const T& structure, Func f, int reiterations, int struct_size_id, int get_index){
    // Pomiar czasu wykonania operacji wielokrotnie i zwrocenie sredniej
    auto reiter_copies = create_reiteration_copies<T>(structure, reiterations);
    auto start = chrono::steady_clock::now();
    int test_value = SEARCH_ADD_INDEXES[struct_size_id][get_index];
    for (int i = 0; i < reiterations; i++) {
        f(reiter_copies[i], struct_size_id, test_value);
    }
    auto end = chrono::steady_clock::now();
    return chrono::duration<double>(end - start).count() / reiterations;
}

template <typename T, typename Func> vector<double> run_seed(const vector<T>& seed_structures, Func f, int reiterations, int get_index=0){
    // Wykonanie testu dla wszystkich rozmiarow struktur i zwrocenie wynikow
    vector<double> results;
    for(int i = 0; i < seed_structures.size(); i++){
        results.push_back(run_test<T>(seed_structures[i], f, reiterations, i, get_index));
    }
    return results;
}

template <typename T> T populate_structure(int seed, int size){
    // Tworzenie struktury z losowymi danymi
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
    T structure;
    for(int i = 0; i<size; i++){
        structure.add_back(dist(rng));
    }
    return structure;
}

template <typename T> vector<T> generate_test_structures(int batch){
    // Generowanie zestawu struktur o roznych rozmiarach do testowania
    vector<T> structures;
    for(int i = 0; i<size(MEASUREMENT_POINTS); i++){
        structures.push_back(populate_structure<T>(batch + i, MEASUREMENT_POINTS[i]));
    }
    return structures;
}

template <typename T> void vector_to_file(vector<T> batch, fstream& file, bool newline=true){
    // Zapisywanie wynikow pomiarow do pliku CSV
    for(int i = 0; i < batch.size(); i++){
        file << batch.at(i);
        if(i != batch.size()-1){
            file << ",";
        }
    }
    if(newline){
        file << "\n";
    }
}

template <typename T> void run_test_suite(int seeds, int add_reiterations, int insert_reiterations, int search_reiterations){
    // Uruchomienie pelnego zestawu testu z wiele iteracjami i zapisanie wynikow
    vector<T> structures;
    vector<vector<double>> seed_times;
    for(int i = 0; i<seeds; i++){
        fstream seed_file("seed" + to_string(i) + ".csv", ios::out);
        seed_file << "population,";
        for(int i = 0; i < size(MEASUREMENT_POINTS); i++){
            seed_file << MEASUREMENT_POINTS[i];
            if(i != size(MEASUREMENT_POINTS)-1){
                seed_file << ",";
            }
        }
        seed_file << "\n";
        structures.clear();
        seed_times.clear();
        structures = generate_test_structures<T>(i);
        
        //add_front tests
        seed_file << "add_front,";
        vector_to_file(run_seed<T>(structures, [](auto& object, int i, int test_value){
            object.add_front(9757);
        }, add_reiterations), seed_file);

        //add_back tests
        seed_file << "add_back,";
        vector_to_file(run_seed<T>(structures, [](auto& object, int i, int test_value){
            object.add_back(335367);
        }, add_reiterations), seed_file);

        //insert tests
        seed_file << "insert,";
        vector_to_file(run_seed<T>(structures, [](auto& object, int i, int test_value){
            object.insert(245454, SEARCH_ADD_INDEXES[i][1]);
        }, insert_reiterations), seed_file);

        //remove first tests
        seed_file << "remove_first,";
        vector_to_file(run_seed<T>(structures, [](auto& object, int i, int test_value){
            object.remove(SEARCH_ADD_INDEXES[i][0]);
        }, insert_reiterations), seed_file);

        //remove middle tests
        seed_file << "remove_middle,";
        vector_to_file(run_seed<T>(structures, [](auto& object, int i, int test_value){
            object.remove(SEARCH_ADD_INDEXES[i][1]);
        }, insert_reiterations), seed_file);

        //remove last tests
        seed_file << "remove_middle,";
        vector_to_file(run_seed<T>(structures, [](auto& object, int i, int test_value){
            object.remove(SEARCH_ADD_INDEXES[i][2]);
        }, insert_reiterations), seed_file);

        //forward search first tests
        seed_file << "search_first_fw,";
        vector_to_file(run_seed<T>(structures, [](auto& object, int i, int test_value){
            object.search(test_value, false);
        }, search_reiterations), seed_file);

        //forward search middle tests
        seed_file << "search_middle_fw,";
        vector_to_file(run_seed<T>(structures, [](auto& object, int i, int test_value){
            object.search(test_value, false);
        }, search_reiterations, 1), seed_file);
        
        //forward search last tests
        seed_file << "search_last_fw,";
        vector_to_file(run_seed<T>(structures, [](auto& object, int i, int test_value){
            object.search(test_value, false);
        }, search_reiterations, 2), seed_file);

        //backward search first tests
        seed_file << "search_first_bw,";
        vector_to_file(run_seed<T>(structures, [](auto& object, int i, int test_value){
            object.search(test_value, true);
        }, search_reiterations), seed_file);

        //backward search middle tests
        seed_file << "search_middle_bw,";
        vector_to_file(run_seed<T>(structures, [](auto& object, int i, int test_value){
            object.search(test_value, true);
        }, search_reiterations, 1), seed_file);
        
        //backward search last tests
        seed_file << "search_last_bw,";
        vector_to_file(run_seed<T>(structures, [](auto& object, int i, int test_value){
            object.search(test_value, true);
        }, search_reiterations, 2), seed_file);

        seed_file.close();
    }
}