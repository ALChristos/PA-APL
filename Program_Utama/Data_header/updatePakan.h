#ifndef UPDT_PKN
#define UPDT_PKN
#include <iostream>
#include "struct.h"
using namespace std;

void updatePakan()
{
    cout << "============ MENU TEBAR BENIH ============\n"
         << endl;
    int indexKolam;
    // tampilkanKolam(); -> masih menunggu fitur
    cout << "Pilih Kolam yang ingin anda Tebar Benih";
    cin >> indexKolam;
    cin.ignore();

    if (daftarKolam[indexKolam].status_kolam == 0)
    {
        // coming soon
    }
    else
    {
        cout << "Mohon Maaf, Kolam yang anda pilih sudah terisi!";
        updatePakan();
        return;
    }
}

#endif