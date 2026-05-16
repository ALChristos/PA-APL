#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "../Data_header/Program_staff.h"
#include "../Data_header/Program_admin.h"
#include "../Data_header/struct.h"
#include "../Data_json/json.hpp"

using json = nlohmann::json;

const string FILE_STAFF = "Data_json/Data_staff.json";
const string FILE_KOLAM = "Data_json/Data_kolam.json";
const string FILE_PAKAN = "Data_json/Data_pakan.json";
const string FILE_KEUANGAN = "Data_json/Laporan_keuangan.json";

using namespace std;

json load_json(string PATH, string messages)
{
    json j;
    ifstream fileIn(PATH);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    if (j.empty())
    {
        cout << messages << endl;
    }

    return j;
}

void tebar_pakan(int &id_staff)
{
    Kolam kolam;

    json kolamj = load_json(FILE_KOLAM, "[INFO] Belum Ada Kolam Yang Dibuat!!!");
    json staffj = load_json(FILE_STAFF, "[INFO] Belum Ada Staff Yang Terdaftar!!!");
    json pakanj = load_json(FILE_PAKAN, "[INFO] Belum Stok Pakan yang Terdata!!!");

    if (kolamj.empty() || staffj.empty() || pakanj.empty())
    {
        system("pause");
        system("cls");
        return;
    }

    int harga_pakan;
    int stok_pakan;
    for (const auto &item : pakanj)
    {

        if (item["harga_per_kg"] <= 0)
        {
            cout << "\n[INFO] Mohon Maaf, Admin Belum Mengatur Harga Pakan!  " << endl;
            system("pause");
            system("cls");
            return;
        }
        else if (item["stok_kg"] <= 0)
        {
            cout << "\n[INFO] Mohon Maaf, Stok Pakan Saat ini masih Kosong!  " << endl;
            system("pause");
            system("cls");
            return;
        }
        harga_pakan = item["harga_per_kg"];
        harga_pakan /= 1000; // Satuan di data berupa kg, maka dikonversi dulu jadi gram
        stok_pakan = item["stok_kg"];
        stok_pakan *= 1000; // Satuan di data berupa kg, maka dikonversi dulu jadi gram
    }

    // system("cls");
    cout << "================================================================" << endl;
    cout << "====================== DAFTAR KOLAM  ===========================" << endl;
    cout << "================================================================" << endl;
    cout << "ID\t| Tipe\t | Kapasitas\t| Populasi\t| Status\t|" << endl;
    cout << "----------------------------------------------------------------" << endl;

    bool kolam_terisi = false;
    for (const auto &item : kolamj)
    {
        if (item["status_kolam"] == "Terisi")
        {
            cout << item["id"] << "\t|" << item["tipe"] << " | " << item["kapasitas"] << "\t\t|" << item["populasi"] << "\t\t|" << item["status_kolam"] << "\t|" << endl;
            cout << "----------------------------------------------------------------" << endl;
            kolam_terisi = true;
        }
    }

    if (!kolam_terisi)
    {
        cout << "\n[INFO] Tidak Ada Kolam Terisi Saat Ini. Silahkan Bongkar/Buat Kolam Baru!" << endl;
        system("pause");
        system("cls");
        return;
    }

    int id_kolam = -1;
    string input_pilihan;

    while (true)
    {
        try
        {
            cout << "\nMasukkan ID Kolam Yang Ingin Di Beri Pakan (0 untuk batal): ";
            getline(cin >> ws, input_pilihan);
            id_kolam = stoi(input_pilihan);

            if (id_kolam == 0)
            {
                system("cls");
                return;
            }
            break;
        }
        catch (const exception &e)
        {
            cout << "[ERROR] ID Tidak Valid! Masukkan Angka." << endl;
        }
    }

    string usernameStaff;

    for (const auto &item : staffj)
    {
        if (item["id"] == id_staff)
        {
            usernameStaff = item["nama"];
        }
    }

    bool ditemukan = false;
    string hari, fase_kolam;
    int interval_hari, total_pakan_perhari, total_harga_pakan, id_kolam_target, total_berat_kolam, populasi, total_pakan_interval;

    for (auto &item : kolamj)
    {
        if (item["id"] == id_kolam && item["status_kolam"] == "Terisi")
        {

            ditemukan = true;
            bool input_sukses = true;

            id_kolam_target = item["id"];
            fase_kolam = item["fase_kolam"];
            populasi = item["populasi"];

            while (input_sukses)
            {

                try
                {
                    int umur_kolam = item["umur_kolam"];
                    total_pakan_interval = 0;

                    cout << "Interval Hari Pemberian Pakan (dimulai dari hari ke: " << umur_kolam << "): ";
                    getline(cin >> ws, hari);

                    interval_hari = stoi(hari);

                    if (interval_hari <= 0)
                    {
                        cout << "[ERROR] Interval Hari Harus Lebih Dari 0!!!" << endl;
                        continue;
                    }

                    bool is_remaja, is_dewasa, is_panen = false;

                    for (int i = 0; i < interval_hari; i++)
                    {
                        umur_kolam += 1;
                        if (umur_kolam > 20)
                        {
                            item["fase_kolam"] = "Remaja";
                            item["total_berat_kolam"] = populasi * 50;
                            is_remaja = true;
                        }
                        else if (umur_kolam > 60)
                        {
                            item["fase_kolam"] = "Dewasa";
                            item["total_berat_kolam"] = populasi * 100;
                            is_dewasa = true;
                        }
                        else if (umur_kolam > 90)
                        {
                            item["fase_kolam"] = "Panen";
                            item["total_berat_kolam"] = populasi * 150;
                            item["status_kolam"] = "Panen";
                            is_panen = true;
                        }

                        total_harga_pakan = item["total_harga_pakan"];
                        total_berat_kolam = item["total_berat_kolam"];
                        total_pakan_perhari = total_berat_kolam * 0.05;
                        total_pakan_interval += total_pakan_perhari;
                        total_harga_pakan += (total_pakan_perhari * harga_pakan);
                    }

                    if (total_pakan_interval > stok_pakan)
                    {
                        cout << "\n[ERROR] Mohon Maaf, Stok Pakan tidak Mencukupi!!!" << endl;
                        continue;
                    }

                    if (is_remaja)
                    {
                        cout << "\n[INFO] Kolam dengan ID: " << item["id"] << "Telah Memasuki Fase Remaja!! " << endl;
                    }
                    else if (is_dewasa)
                    {
                        cout << "\n[INFO] Kolam dengan ID: " << item["id"] << "Telah Memasuki Fase Dewasa!! " << endl;
                    }
                    else if (is_panen)
                    {
                        cout << "\n[INFO] Kolam dengan ID: " << item["id"] << "Telah Memasuki Fase Panen!! " << endl;
                    }

                    item["umur_kolam"] = umur_kolam;
                    item["total_harga_pakan"] = total_harga_pakan;

                    for (auto &item_pakan : pakanj)
                    {
                        stok_pakan -= total_pakan_interval;
                        stok_pakan /= 1000;
                        item_pakan["stok_kg"] = stok_pakan;
                    }
                    input_sukses = false;
                }
                catch (const exception &e)
                {
                    cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
                }
            }
            break;
        }
    }

    if (ditemukan)
    {
        ofstream fileOut(FILE_KOLAM);
        fileOut << kolamj.dump(4);
        fileOut.close();
        cout << "\n[BERHASIL] Kolam Dengan ID " << id_kolam << " Telah Diberi Pakannya!!!!" << endl;

        cout << "\nBerikut Untuk Laporannya: " << endl;
        cout << "\n=================================" << endl;
        cout << "        LAPORAN TEBAR PAKAN      " << endl;
        cout << "=================================" << endl;
        cout << "Kolam          : " << id_kolam_target << endl;
        cout << "Rentang Hari   : " << interval_hari << endl;
        cout << "Total Pakan    : " << total_pakan_interval << " gram" << endl;
        cout << "Total Biaya    : " << total_harga_pakan << endl;
        cout << "Dicatat oleh   : " << usernameStaff << endl;
        cout << "=================================" << endl;
    }
    else
    {
        cout << "\n[ERROR] ID Kolam Tidak Ditemukan atau Kolam Sudah Terisi!!!" << endl;
    }

    system("pause");
    system("cls");
}

void catatMortalitas(int &id_staff)
{
    cout << "============ MENU PENCATATAN MORTALITAS ============\n"
         << endl;

    Kolam kolam;
    Staff staff;

    json kolamj = load_json(FILE_KOLAM, "[INFO] Belum Ada Kolam Yang Dibuat!!!");
    json staffj = load_json(FILE_STAFF, "[INFO] Belum Ada Staff Yang Terdaftar!!!");

    if (kolamj.empty() || staffj.empty())
    {
        system("pause");
        system("cls");
        return;
    }

    system("cls");
    int id_kolam = -1;
    string input_pilihan;

    system("cls");
    cout << "================================================================" << endl;
    cout << "================ DAFTAR KOLAM KOSONG ===========================" << endl;
    cout << "================================================================" << endl;
    cout << "ID\t| Tipe\t | Kapasitas\t| Populasi\t| Status\t|" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (int i = 0; i < kolamj.size(); i++)
    {
        for (int k = 0; k < kolamj.size() - 1 - i; k++)
        {
            if (kolamj[k]["id"] > kolamj[k + 1]["id"])
            {
                swap(kolamj[k], kolamj[k + 1]);
            }
        }
    }

    for (const auto &item : kolamj)
    {

        cout << item["id"] << "\t|" << item["tipe"] << " | " << item["kapasitas"] << "\t\t|" << item["populasi"] << "\t\t|" << item["status_kolam"] << "\t|" << endl;
        cout << "----------------------------------------------------------------" << endl;
    }

    while (true)
    {
        try
        {
            cout << "\nMasukkan ID Kolam Yang Ingin Di Catat Mortalitasnya (0 untuk batal): ";
            getline(cin >> ws, input_pilihan);
            id_kolam = stoi(input_pilihan);

            if (id_kolam == 0)
            {
                system("cls");
                return;
            }
            break;
        }
        catch (const exception &e)
        {
            cout << "[ERROR] ID Tidak Valid! Masukkan Angka." << endl;
        }
    }

    bool ditemukan = false;
    string totalMatiInput, fase_kolam;
    int totalMati;
    int populasiAkhir;
    int jumlahBenih, hargaBenih, totalHargaBenih, id_kolam_target;

    for (auto &item : kolamj)
    {
        if (item["id"] == id_kolam)
        {
            ditemukan = true;
            bool input_sukses = true;

            id_kolam_target = item["id"];

            while (input_sukses)
            {
                try
                {
                    cout << "Input Jumlah Ikan yang Mati: ";
                    getline(cin >> ws, totalMatiInput);
                    totalMati = stoi(totalMatiInput);
                    if (0 > totalMati)
                    {
                        cout << "[ERROR] Total Mati Harus Lebih Dari 0!!!" << endl;
                        continue;
                    }
                    else if (item["populasi"] < totalMati)
                    {
                        cout << "[ERROR] Total Mati melebihi populasi Kolam (" << item["populasi"] << ")!" << endl;
                        continue;
                    }

                    fase_kolam = item["fase_kolam"];
                    int populasi = item["populasi"];
                    populasiAkhir = populasi - totalMati;
                    item["populasi"] = populasiAkhir;

                    if (fase_kolam == "Benih")
                    {
                        item["total_berat_kolam"] = populasiAkhir * 1;
                    }
                    else if (fase_kolam == "Remaja")
                    {
                        item["total_berat_kolam"] = populasiAkhir * 50;
                    }
                    else if (fase_kolam == "Dewasa")
                    {
                        item["total_berat_kolam"] = populasiAkhir * 100;
                    }
                    else
                    {
                        item["total_berat_kolam"] = populasiAkhir * 150;
                    }

                    input_sukses = false;
                }
                catch (const exception &e)
                {
                    cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
                }
            }
            break;
        }
    }

    string usernameStaff;

    for (auto &item : staffj)
    {
        if (item["id"] == id_staff)
        {
            usernameStaff = item["nama"];
        }
    }

    if (ditemukan)
    {
        ofstream fileOut(FILE_KOLAM);
        fileOut << kolamj.dump(4);
        fileOut.close();
        cout << "\n[BERHASIL] Kolam Dengan ID " << id_kolam << " Telah Di Catat Mortalitasnya!!!" << endl;

        cout << "\nBerikut Untuk Laporannya: " << endl;
        cout << "\n=================================" << endl;
        cout << "        LAPORAN MORTALITAS        " << endl;
        cout << "=================================" << endl;
        cout << "Kolam          : " << id_kolam_target << endl;
        cout << "Total Mati     : " << totalMati << endl;
        cout << "Populasi Akhir : " << populasiAkhir << endl;
        cout << "Dicatat oleh   : " << usernameStaff << endl;
        cout << "=================================" << endl;
    }
    else
    {
        cout << "\n[ERROR] ID Kolam Tidak Ditemukan!!!" << endl;
    }

    system("pause");
    system("cls");
}

void catat_panen(int &id_staff)
{

    json kolamj = load_json(FILE_KOLAM, "[INFO] Belum Ada Kolam Yang Dibuat!!!");
    json staffj = load_json(FILE_STAFF, "[INFO] Belum Ada Staff Yang Terdaftar!!!");

    if (kolamj.empty() || staffj.empty())
    {
        system("pause");
        system("cls");
        return;
    }

    system("cls");
    cout << "================================================================" << endl;
    cout << "================ DAFTAR KOLAM SIAP PANEN =======================" << endl;
    cout << "================================================================" << endl;
    cout << "ID\t| Tipe\t | Kapasitas\t| Populasi\t| Status\t|" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (int i = 0; i < kolamj.size(); i++)
    {
        for (int k = 0; k < kolamj.size() - 1 - i; k++)
        {
            if (kolamj[k]["id"] > kolamj[k + 1]["id"])
            {
                swap(kolamj[k], kolamj[k + 1]);
            }
        }
    }

    for (const auto &item : kolamj)
    {
        if (item["status_kolam"] == "Terisi")
        {
            cout << item["id"] << "\t|" << item["tipe"] << " | " << item["kapasitas"] << "\t\t|" << item["populasi"] << "\t\t|" << item["status_kolam"] << "\t|" << endl;
            cout << "----------------------------------------------------------------" << endl;
        }
    }

    // COMING SOON, BUTUH DATA PAKAN 10 HARI PERTAMA AGAR PROGRAM DAPAT BERJALAN DENGAN ERROR HANDLING
}