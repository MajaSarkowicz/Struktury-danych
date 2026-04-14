using namespace std;

template <typename T, typename DT> void manual_add_front(T& structure){
    DT elem;
    size_t index;
    cout << "Podaj element do dodania: \n> ";
    cin >> elem;
    structure.add_front(elem);
}
template <typename T, typename DT> void manual_add_back(T& structure){
    DT elem;
    size_t index;
    cout << "Podaj element do dodania: \n> ";
    cin >> elem;
    structure.add_back(elem);
}

template <typename T, typename DT> void manual_insert(T& structure){
    DT elem;
    size_t index;
    cout << "Podaj element do dodania: \n> ";
    cin >> elem;
    cout << "Podaj indeks: \n> ";
    cin >> index;
    structure.insert(elem, index);
}


template <typename T> void manual_remove_front(T& structure){
    structure.remove_front();
}

template <typename T> void manual_remove_back(T& structure){
    structure.remove_back();
}

template <typename T> void manual_remove(T& structure){
    size_t index;
    cout << "Podaj indeks: \n> ";
    cin >> index;
    structure.remove(index);
}

template <typename T, typename DT> void manual_search(T& structure){
    DT elem;
    cout << "Podaj element do wyszukania: \n> ";
    cin >> elem;
    cout << "Znaleziono " << elem << " na indeksie " << structure.search(elem, true) << " (-1 dla braku elementu)" << endl;
}

template <typename T, typename DT> void manual_search(T& structure, bool backwards){
    DT elem;
    cout << "Podaj element do wyszukania: \n> ";
    cin >> elem;
    cout << "Znaleziono " << elem << " na indeksie " << structure.search(elem, backwards) << " (-1 dla braku elementu)" << endl;
}

template <typename T> void manual_print(T& structure){
    structure.print();
}