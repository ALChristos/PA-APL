#ifndef CT_MRTLTS
#define CT_MRTLTS
#include <iostream>
#include "struct.h"
using namespace std;

void catatMortalitas(Kolam *daftarKolam, Staff *daftarStaff, int &id_staff)
{
    cout << "============ MENU PENCATATAN MORTALITAS ============\n"
         << endl;

    int indexKolam;
    // tampilkanKolam(); -> Masih Menunggu Fitur
    cout << "Pilih Kolam yang ingin anda catat Mortalitasnya";
    cin >> indexKolam;
    cin.ignore();

    if (daftarKolam[indexKolam].status_kolam == 1)
    {
        int totalMati;
        cout << "Input Jumlah Ikan yang Mati: ";
        cin >> totalMati;
        cin.ignore();

        daftarKolam[indexKolam].populasi_ikan -= totalMati;
        int populasiAkhir = daftarKolam[indexKolam].populasi_ikan;

        cout << "================================" << endl
             << "              REPORT            " << endl
             << "================================" << endl
             << "Populasi Akhir: " << populasiAkhir << endl
             << "Jumlah Mati: " << totalMati << endl
             << "Staff Pencatat: " << (daftarStaff + id_staff)->username << endl
             << "================================" << endl;
    }
    else
    {
        cout << "Mohon Maaf, Kolam yang anda pilih masih kosong!";
        catatMortalitas(daftarKolam, daftarStaff, id_staff);
        return;
    }
}

#endif