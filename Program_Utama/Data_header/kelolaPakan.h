#ifndef KELOLA_PKN
#define KELOLA_PKN

#include <iostream>
#include <fstream>
#include <string>
#include "struct.h"
#include "../Data_json/json.hpp"

using namespace std;
using json = nlohmann::json;

const string FILE_PAKAN = "../Data_json/Data_pakan.json";

// ============================================================
// STRUCT PAKAN 
// ============================================================
struct Pakan
{
    int id_pakan;
    string nama_pakan;
    int stok_kg;        // stok total dalam kg
    int harga_per_kg;
};

struct JatahPakan
{
    int id_kolam;
    int jatah_per_hari_gram; // jatah pakan per hari dalam gram
    string nama_pakan;
    string waktu_update;
};

// ============================================================
// HELPER: Simpan data pakan ke JSON
// ============================================================
static void simpanDataPakan(const json& j)
{
    ofstream fileOut(FILE_PAKAN);
    if (fileOut.is_open())
    {
        fileOut << j.dump(4);
        fileOut.close();
    }
    else
    {
        cout << "[ERROR] Gagal menyimpan data pakan!" << endl;
    }
}

// ============================================================
// HELPER: Load data pakan dari JSON
// ============================================================
static json loadDataPakan()
{
    json j;
    ifstream fileIn(FILE_PAKAN);
    if (fileIn.is_open())
    {
        if (fileIn.peek() != ifstream::traits_type::eof())
        {
            fileIn >> j;
        }
        fileIn.close();
    }

    if (j.is_null() || !j.is_array())
    {
        j = json::array();
    }

    return j;
}

// ============================================================
// 1. LIHAT STOK PAKAN
// ============================================================
static void lihatStokPakan()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "========= DAFTAR STOK PAKAN ============" << endl;
    cout << "========================================" << endl;

    json j = loadDataPakan();

    if (j.empty())
    {
        cout << "[INFO] Belum ada data pakan yang tersedia." << endl;
        system("pause");
        return;
    }

    cout << left;
    cout << "------------------------------------------------------------" << endl;
    printf("%-5s %-20s %-12s %-15s\n", "ID", "Nama Pakan", "Stok (Kg)", "Harga/Kg (Rp)");
    cout << "------------------------------------------------------------" << endl;

    for (const auto& item : j)
    {
        printf("%-5d %-20s %-12d %-15d\n",
               item["id_pakan"].get<int>(),
               item["nama_pakan"].get<string>().c_str(),
               item["stok_kg"].get<int>(),
               item["harga_per_kg"].get<int>());
    }

    cout << "------------------------------------------------------------" << endl;
    system("pause");
}

// ============================================================
// 2. TAMBAH STOK PAKAN
// ============================================================
static void tambahStokPakan()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "========== TAMBAH STOK PAKAN ===========" << endl;
    cout << "========================================" << endl;

    json j = loadDataPakan();

    int pilihan;
    cout << "1. Tambah Jenis Pakan Baru" << endl;
    cout << "2. Isi Ulang Stok Pakan yang Ada" << endl;
    cout << "Pilihan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1)
    {
        // --- Tambah jenis pakan baru ---
        Pakan pakan_baru;

        cout << "\nNama Pakan   : ";
        getline(cin, pakan_baru.nama_pakan);
        cout << "Stok (Kg)    : ";
        cin >> pakan_baru.stok_kg;
        cout << "Harga/Kg (Rp): ";
        cin >> pakan_baru.harga_per_kg;
        cin.ignore();

        // Validasi input positif
        if (pakan_baru.stok_kg <= 0 || pakan_baru.harga_per_kg <= 0)
        {
            cout << "[ERROR] Stok dan harga harus lebih dari 0!" << endl;
            system("pause");
            system("cls");
            return;
        }

        // Cek duplikat nama
        for (const auto& item : j)
        {
            if (item["nama_pakan"].get<string>() == pakan_baru.nama_pakan)
            {
                cout << "[ERROR] Jenis pakan '" << pakan_baru.nama_pakan << "' sudah terdaftar!" << endl;
                system("pause");
                system("cls");
                return;
            }
        }

        pakan_baru.id_pakan = j.empty() ? 1 : j.back()["id_pakan"].get<int>() + 1;

        json pakanJson = {
            {"id_pakan",     pakan_baru.id_pakan},
            {"nama_pakan",   pakan_baru.nama_pakan},
            {"stok_kg",      pakan_baru.stok_kg},
            {"harga_per_kg", pakan_baru.harga_per_kg}
        };
        j.push_back(pakanJson);
        simpanDataPakan(j);

        cout << "\n[BERHASIL] Pakan '" << pakan_baru.nama_pakan
             << "' berhasil ditambahkan! (ID: " << pakan_baru.id_pakan << ")" << endl;
    }
    else if (pilihan == 2)
    {
        // --- Isi ulang stok pakan yang ada ---
        if (j.empty())
        {
            cout << "[INFO] Belum ada jenis pakan. Silakan tambah jenis pakan baru terlebih dahulu." << endl;
            system("pause");
            system("cls");
            return;
        }

        lihatStokPakan();

        int id_target, tambah_stok;
        cout << "Masukkan ID Pakan yang ingin diisi ulang: ";
        cin >> id_target;
        cout << "Jumlah Penambahan Stok (Kg)             : ";
        cin >> tambah_stok;
        cin.ignore();

        if (tambah_stok <= 0)
        {
            cout << "[ERROR] Jumlah tambahan stok harus lebih dari 0!" << endl;
            system("pause");
            system("cls");
            return;
        }

        bool ditemukan = false;
        for (auto& item : j)
        {
            if (item["id_pakan"].get<int>() == id_target)
            {
                int stok_lama = item["stok_kg"].get<int>();
                item["stok_kg"] = stok_lama + tambah_stok;
                ditemukan = true;

                simpanDataPakan(j);
                cout << "\n[BERHASIL] Stok '" << item["nama_pakan"].get<string>()
                     << "' berhasil diperbarui: " << stok_lama
                     << " Kg -> " << item["stok_kg"].get<int>() << " Kg" << endl;
                break;
            }
        }

        if (!ditemukan)
        {
            cout << "[ERROR] ID Pakan tidak ditemukan!" << endl;
        }
    }
    else
    {
        cout << "[ERROR] Pilihan tidak valid!" << endl;
    }

    system("pause");
    system("cls");
}

// ============================================================
// 3. SET JATAH PAKAN PER KOLAM
// ============================================================
static void setJatahPakan(Kolam* daftarKolam, int jumlahKolam)
{
    system("cls");
    cout << "========================================" << endl;
    cout << "======= SET JATAH PAKAN PER KOLAM ======" << endl;
    cout << "========================================" << endl;

    // Tampilkan kolam yang aktif (terisi)
    cout << "\nDaftar Kolam Aktif:" << endl;
    cout << "------------------------------------" << endl;
    printf("%-5s %-12s %-15s\n", "ID", "Status", "Populasi Ikan");
    cout << "------------------------------------" << endl;

    bool adaKolamAktif = false;
    for (int i = 0; i < jumlahKolam; i++)
    {
        if (daftarKolam[i].status_kolam == true)
        {
            printf("%-5d %-12s %-15d\n",
                   daftarKolam[i].id_kolam,
                   "Aktif",
                   daftarKolam[i].populasi_ikan);
            adaKolamAktif = true;
        }
    }

    if (!adaKolamAktif)
    {
        cout << "[INFO] Tidak ada kolam yang sedang aktif." << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "------------------------------------" << endl;

    // Tampilkan pilihan pakan
    json j = loadDataPakan();
    if (j.empty())
    {
        cout << "[ERROR] Stok pakan belum tersedia! Silakan tambah stok pakan terlebih dahulu." << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << "\nPilih ID Kolam  : ";
    int id_kolam_target;
    cin >> id_kolam_target;

    // Validasi kolam
    bool kolamValid = false;
    for (int i = 0; i < jumlahKolam; i++)
    {
        if (daftarKolam[i].id_kolam == id_kolam_target && daftarKolam[i].status_kolam == true)
        {
            kolamValid = true;
            break;
        }
    }

    if (!kolamValid)
    {
        cout << "[ERROR] ID Kolam tidak valid atau kolam sedang kosong!" << endl;
        system("pause");
        system("cls");
        return;
    }

    // Tampilkan daftar pakan
    cout << "\nDaftar Pakan Tersedia:" << endl;
    cout << "------------------------------" << endl;
    for (const auto& item : j)
    {
        printf("  [%d] %s (Stok: %d Kg)\n",
               item["id_pakan"].get<int>(),
               item["nama_pakan"].get<string>().c_str(),
               item["stok_kg"].get<int>());
    }
    cout << "------------------------------" << endl;

    int id_pakan_target, jatah_gram;
    cout << "Pilih ID Pakan          : ";
    cin >> id_pakan_target;
    cout << "Jatah Pakan/Hari (gram) : ";
    cin >> jatah_gram;
    cin.ignore();

    if (jatah_gram <= 0)
    {
        cout << "[ERROR] Jatah pakan harus lebih dari 0!" << endl;
        system("pause");
        system("cls");
        return;
    }

    string nama_pakan_dipilih = "";
    for (const auto& item : j)
    {
        if (item["id_pakan"].get<int>() == id_pakan_target)
        {
            nama_pakan_dipilih = item["nama_pakan"].get<string>();
            break;
        }
    }

    if (nama_pakan_dipilih.empty())
    {
        cout << "[ERROR] ID Pakan tidak ditemukan!" << endl;
        system("pause");
        system("cls");
        return;
    }

    // Simpan/update jatah pakan di file terpisah
    const string FILE_JATAH = "../Data_json/Data_jatahPakan.json";
    json jJatah;
    ifstream fileJatahIn(FILE_JATAH);
    if (fileJatahIn.is_open())
    {
        if (fileJatahIn.peek() != ifstream::traits_type::eof())
            fileJatahIn >> jJatah;
        fileJatahIn.close();
    }
    if (jJatah.is_null() || !jJatah.is_array())
        jJatah = json::array();

    // Update jika sudah ada, tambah baru jika belum
    bool sudahAda = false;
    for (auto& item : jJatah)
    {
        if (item["id_kolam"].get<int>() == id_kolam_target)
        {
            item["jatah_per_hari_gram"] = jatah_gram;
            item["nama_pakan"]          = nama_pakan_dipilih;
            sudahAda = true;
            break;
        }
    }

    if (!sudahAda)
    {
        json jatahBaru = {
            {"id_kolam",             id_kolam_target},
            {"jatah_per_hari_gram",  jatah_gram},
            {"nama_pakan",           nama_pakan_dipilih}
        };
        jJatah.push_back(jatahBaru);
    }

    ofstream fileJatahOut(FILE_JATAH);
    fileJatahOut << jJatah.dump(4);
    fileJatahOut.close();

    cout << "\n[BERHASIL] Jatah pakan untuk Kolam " << id_kolam_target
         << " berhasil diset: " << jatah_gram << " gram/hari ("
         << nama_pakan_dipilih << ")" << endl;

    system("pause");
    system("cls");
}

// ============================================================
// 4. CATAT PEMBERIAN PAKAN (kurangi stok)
// ============================================================
static void catatPemberianPakan(Kolam* daftarKolam, int jumlahKolam, Staff* daftarStaff, int& id_staff)
{
    system("cls");
    cout << "========================================" << endl;
    cout << "======== CATAT PEMBERIAN PAKAN =========" << endl;
    cout << "========================================" << endl;

    // Load jatah pakan
    const string FILE_JATAH = "../Data_json/Data_jatahPakan.json";
    json jJatah;
    ifstream fileJatahIn(FILE_JATAH);
    if (fileJatahIn.is_open())
    {
        if (fileJatahIn.peek() != ifstream::traits_type::eof())
            fileJatahIn >> jJatah;
        fileJatahIn.close();
    }

    if (jJatah.is_null() || jJatah.empty())
    {
        cout << "[ERROR] Belum ada jatah pakan yang diset untuk kolam manapun!" << endl;
        system("pause");
        system("cls");
        return;
    }

    // Tampilkan kolam yang punya jatah pakan
    cout << "\nKolam yang memiliki jatah pakan:" << endl;
    cout << "----------------------------------------------------" << endl;
    printf("%-10s %-20s %-15s\n", "ID Kolam", "Nama Pakan", "Jatah/Hari");
    cout << "----------------------------------------------------" << endl;
    for (const auto& item : jJatah)
    {
        printf("%-10d %-20s %-15d gram\n",
               item["id_kolam"].get<int>(),
               item["nama_pakan"].get<string>().c_str(),
               item["jatah_per_hari_gram"].get<int>());
    }
    cout << "----------------------------------------------------" << endl;

    int id_kolam_target;
    cout << "Pilih ID Kolam yang diberi pakan: ";
    cin >> id_kolam_target;
    cin.ignore();

    // Cari jatah kolam yang dipilih
    int jatah_gram     = 0;
    string nama_pakan  = "";
    bool jatahDitemukan = false;

    for (const auto& item : jJatah)
    {
        if (item["id_kolam"].get<int>() == id_kolam_target)
        {
            jatah_gram      = item["jatah_per_hari_gram"].get<int>();
            nama_pakan      = item["nama_pakan"].get<string>();
            jatahDitemukan  = true;
            break;
        }
    }

    if (!jatahDitemukan)
    {
        cout << "[ERROR] ID Kolam tidak ditemukan dalam data jatah pakan!" << endl;
        system("pause");
        system("cls");
        return;
    }

    // Kurangi stok pakan
    json jPakan = loadDataPakan();
    bool stokCukup = false;

    for (auto& item : jPakan)
    {
        if (item["nama_pakan"].get<string>() == nama_pakan)
        {
            double jatah_kg = jatah_gram / 1000.0;

            if (item["stok_kg"].get<int>() >= (int)jatah_kg || jatah_gram < 1000)
            {
                // Stok dicatat berkurang jika >= 1 kg habis
                if (jatah_gram >= 1000)
                {
                    item["stok_kg"] = item["stok_kg"].get<int>() - (int)jatah_kg;
                }
                stokCukup = true;
                simpanDataPakan(jPakan);

                // Tampilkan laporan
                cout << "\n================================" << endl;
                cout << "         LAPORAN PAKAN          " << endl;
                cout << "================================" << endl;
                cout << "Kolam         : " << id_kolam_target << endl;
                cout << "Pakan         : " << nama_pakan << endl;
                cout << "Jatah         : " << jatah_gram << " gram" << endl;
                cout << "Stok Tersisa  : " << item["stok_kg"].get<int>() << " Kg" << endl;
                cout << "Dicatat oleh  : " << (daftarStaff + id_staff)->username << endl;
                cout << "================================" << endl;

                if (item["stok_kg"].get<int>() <= 5)
                {
                    cout << "\n[PERINGATAN] Stok pakan '" << nama_pakan
                         << "' hampir habis! Sisa: " << item["stok_kg"].get<int>() << " Kg" << endl;
                }
            }
            else
            {
                cout << "[ERROR] Stok pakan tidak mencukupi!" << endl
                     << "         Stok tersisa: " << item["stok_kg"].get<int>() << " Kg" << endl
                     << "         Dibutuhkan  : " << jatah_kg << " Kg" << endl;
            }
            break;
        }
    }

    if (!stokCukup)
    {
        cout << "[ERROR] Pakan '" << nama_pakan << "' tidak ditemukan di stok!" << endl;
    }

    system("pause");
    system("cls");
}

// ============================================================
// MENU UTAMA KELOLA PAKAN
// ============================================================
void kelolaPakan(Kolam* daftarKolam, int jumlahKolam, Staff* daftarStaff, int& id_staff)
{
    int pilihan;
    bool menu_aktif = true;

    while (menu_aktif)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "========== MENU KELOLA PAKAN ===========" << endl;
        cout << "========================================" << endl;
        cout << "1. Lihat Stok Pakan" << endl;
        cout << "2. Tambah Stok Pakan" << endl;
        cout << "3. Set Jatah Pakan Per Kolam" << endl;
        cout << "4. Catat Pemberian Pakan" << endl;
        cout << "5. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
            case 1:
                lihatStokPakan();
                break;

            case 2:
                tambahStokPakan();
                break;

            case 3:
                setJatahPakan(daftarKolam, jumlahKolam);
                break;

            case 4:
                catatPemberianPakan(daftarKolam, jumlahKolam, daftarStaff, id_staff);
                break;

            case 5:
                menu_aktif = false;
                system("cls");
                break;

            default:
                cout << "[ERROR] Pilihan Tidak Valid, Silahkan Input Pilihan Yang Sesuai!!!" << endl;
                system("pause");
                system("cls");
                break;
        }
    }
}

#endif // KELOLA_PKN
