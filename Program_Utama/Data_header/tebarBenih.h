#ifndef TBR_BNIH
#define TBR_BNIH
#include <iostream>
#include "struct.h"
using namespace std;

int tebarBenih(Kolam *daftarKolam, Admin *daftarAdmin, int &id_admin)
{

    cout << "============ MENU TEBAR BENIH ============\n"
         << endl;
    int indexKolam;
    bool isValid = false;
    int jumlahBenih;
    int hargaBenih;
    int totalHargaBenih;
    // tampilkanKolam(); -> masih menunggu fitur
    cout << "Pilih Kolam yang ingin anda Tebar Benih";
    cin >> indexKolam;
    cin.ignore();

    Kolam kolamDipilih = daftarKolam[indexKolam];

    if (kolamDipilih.status_kolam == 0)
    {

        do
        {

            cout << "Input Jumlah Benih yang ingin anda Tebar (Kilogram): ";
            cin >> jumlahBenih;
            cin.ignore();
            if (jumlahBenih > kolamDipilih.kapasitas)
            {
                cout << "Jumlah Benih yang ditebar tidak boleh melebihi Kapasitas Kolam!" << endl;
                isValid = false;
            }
            else
            {

                cout << "Input Harga Benih (Rp/Kg): " << endl;
                cin >> hargaBenih;
                cin.ignore();

                totalHargaBenih = jumlahBenih * hargaBenih;
                isValid = true;
            }

        } while (isValid == false);
    }
    else
    {
        cout << "Mohon Maaf, Kolam yang anda pilih sudah terisi!";
        tebarBenih(daftarKolam, daftarAdmin, id_admin);
        return;
    }

    return totalHargaBenih;
}

#endif