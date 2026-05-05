#ifndef STRUCT_H
#define STRUCT_H
#include <iostream>
using namespace std;

string daftarTipeKolam[3] = {"Kecil", "Sedang", "Besar"};

struct Kolam
{
    int id_kolam;
    bool status_kolam; // 0 atau false = kosong, 1 atau true = terisi
    int kapasitas;
    int populasi_ikan;
    string tipe_kolam[];
};

struct Staff
{
    int id_staff;
    string username;
    string password;
    bool regist_status;   // 0 atau false = ditolak, 1 atau true = diterima
    bool employed_status; // 0 atau false = dipecat, 1 atau true = masih bekerja
};

struct Admin
{
    int id_admin;
    string username;
    string password;
};

struct Balance
{
    int total_modal;
    int total_keuntungan;
};

Kolam daftarKolam[10];
Staff daftarStaff[10];
Admin daftarAdmin[3];
Balance AkumulasiSaldo;

#endif