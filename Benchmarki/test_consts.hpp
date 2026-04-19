// Rozmiary struktur do testowania wydajnosci
const int MEASUREMENT_POINTS[8] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000};

// Indeksy pozycji testowych: poczatek, srodek, koniec dla kazdego rozmiaru
const int SEARCH_ADD_INDEXES[8][3] = {
    {0, 2600, 4999},
    {0, 7546, 9999},
    {0, 7546, 14999},
    {0, 13521, 19999},
    {0, 15000, 24999},
    {0, 15300, 29999},
    {0, 25454, 34999},
    {0, 20003, 39999}
};