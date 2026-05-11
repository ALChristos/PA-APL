#ifndef STRUCT_H
#define STRUCT_H
#include <iostream>
using namespace std;

struct Kolam
{
    int id_kolam;
    string status_kolam;
    string tipe_kolam;
    int kapasitas;
    int populasi_ikan;
    int total_mati;
    int total_harga_benih;
};

struct Staff
{
    int id_staff;
    string username;
    string password;
    bool regis_status;
    bool employed_status;
    double saldo;
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

struct Keuangan
{
    int id_transaksi;
    double pengeluaran;
    double untung_bersih;
    string keterangan;
};

#endif