#include <iostream>
#include "../Listy/dynamic_array.hpp"
#include "../Listy/singly_linked_list.hpp"
#include "../Listy/doubly_linked_list.hpp"
#include "manual_ops.hpp"
#include "benchmarks.hpp"

using namespace std;

bool MANUAL_MODE = false;
// Flaga okreslajaca tryb dzialania programu
// true - interaktywne operacje na strukturach danych
// false - automatyczne pomiary wydajnosci

template <typename T> void init_manual_menu(){
    // Interaktywne menu do wykonywania odseparowanych operacji na strukturze
    T structure;
    int choice = -1;
    while(choice != 0){
        cout << "Wybierz akcje" << endl
        << "1. Dodaj element na poczatku" << endl
        << "2. Dodaj element na koncu" << endl
        << "3. Dodaj element w wybranym miejscu" << endl
        << "4. Usun element z poczatku" << endl
        << "5. Usun element z konca" << endl
        << "6. Usun element z wybranego miejsca" << endl
        << "7. Szukaj" << endl
        << "8. Szukaj w przod" << endl
        << "9. Szukaj wstecz" << endl
        << "10. Wyswietl liste" << endl
        << "0. Wyjdz do menu" << endl
        << "> ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            manual_add_front<T, int>(structure);
            break;
        case 2:
            manual_add_back<T, int>(structure);
            break;
        case 3:
            manual_insert<T, int>(structure);
            break;
        case 4:
            manual_remove_front<T>(structure);
            break;
        case 5:
            manual_remove_back<T>(structure);
            break;
        case 6:
            manual_remove<T>(structure);
            break;
        case 7:
            manual_search<T, int>(structure);
            break;
        case 8:
            manual_search<T, int>(structure, false);
            break;
        case 9:
            manual_search<T, int>(structure, true);
            break;
        case 10:
            manual_print<T>(structure);
            break;
        default:
            break;
        }
    }
}

int main(){
    // Glowne menu wyboru struktury danych do testowania
    int choice = -1;
    while(choice != 0){
        cout << "Wybierz strukture:" << endl 
        << "1. Dynamic Array" << endl
        << "2. Singly Linked List" << endl
        << "3. Doubly Linked List" << endl
        << "0. Wyjdz" << endl
        << ">";
        cin >> choice;
        if(MANUAL_MODE){
            switch (choice)
            {
            case 1:
                init_manual_menu<DynamicArray<int>>();
                break;
            case 2:
                init_manual_menu<SLinkedList<int>>();
                break;
            case 3:
                init_manual_menu<DLinkedList<int>>();
            }
        }
        else{
            switch (choice)
            {
            case 1:
                run_test_suite<DynamicArray<int>>(4, 100, 100, 100);
                break;
            case 2:
                run_test_suite<SLinkedList<int>>(4, 100, 100, 100);
                break;
            case 3:
                run_test_suite<DLinkedList<int>>(4, 100, 100, 100);
            }
        }
    }
}