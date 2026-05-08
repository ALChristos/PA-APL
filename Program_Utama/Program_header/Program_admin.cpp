#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "../Data_header/Program_admin.h"
#include "../Data_header/struct.h"
#include "../Data_json/json.hpp"

using namespace std;
using json = nlohmann::json;

const string FILE_STAFF = "Data_json/Data_staff.json";
const string FILE_KOLAM = "Data_json/Data_kolam.json";
const string FILE_KEUANGAN = "Data_json/Laporan_keuangan.json";

void acc_staff()
{
    json j;
    ifstream fileIn(FILE_STAFF);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    if (j.empty())
    {
        cout << "[INFO] Belum Ada Staff Di Database!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    system("cls");
    cout << "======================================================" << endl;
    cout << "============== DAFTAR STAFF MENUNGGU ACC =============" << endl;
    cout << "======================================================" << endl;
    cout << "ID\t| Username\t| Status\t|" << endl;
    cout << "------------------------------------------------------" << endl;

    bool ada_pending = false;
    for (const auto &item : j)
    {
        if (item["status_terima"] == false)
        {
            cout << item["id"] << "\t|" << item["nama"] << "\t| Menunggu\t |" << endl;
            cout << "------------------------------------------------------" << endl;
            ada_pending = true;
        }
    }

    if (!ada_pending)
    {
        cout << "\n[INFO] Tidak Ada Staff Baru Yang Mendaftar!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    int id_pilihan = -1;
    string input_id;

    while (true)
    {
        try
        {
            cout << "\nMasukkan ID Staff yang ingin di-ACC (0 untuk batal): ";
            getline(cin >> ws, input_id);

            id_pilihan = stoi(input_id);

            if (id_pilihan == 0)
            {
                break;
                return;
            }
        }
        catch (const exception &e)
        {
            cout << "[ERROR] ID Tidak Valid!!!" << endl;
            system("pause");
            system("cls");

            cout << "======================================================" << endl;
            cout << "============== DAFTAR STAFF MENUNGGU ACC =============" << endl;
            cout << "======================================================" << endl;
            cout << "ID\t| Username\t| Status\t|" << endl;
            cout << "------------------------------------------------------" << endl;

            for (const auto &item : j)
            {
                if (item["status_terima"] == false)
                {
                    cout << item["id"] << "\t|" << item["nama"] << "\t| Menunggu\t |" << endl;
                    cout << "------------------------------------------------------" << endl;
                }
            }
        }

        break;
    }

    bool ditemukan = false;
    for (auto &item : j)
    {
        if (item["id"] == id_pilihan && item["status_terima"] == false)
        {
            item["status_terima"] = true;
            item["status_kerja"] = true;
            ditemukan = true;
            break;
        }
    }

    if (ditemukan)
    {
        ofstream fileOut(FILE_STAFF);
        fileOut << j.dump(4);
        fileOut.close();
        cout << "[BERHASIL] Staff Dengan ID " << id_pilihan << " Telah Diterima Bekerja!!!" << endl;
    }
    else
    {
        cout << "[ERROR] ID Tidak Ditemukan / Sudah Pernah Di ACC Sebelumnya!!!" << endl;
    }

    system("pause");
    system("cls");
}

void pecat_staff()
{
    json j;
    ifstream fileIn(FILE_STAFF);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    if (j.empty())
    {
        cout << "[INFO] Belum Ada Staff Di Database!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    system("cls");
    cout << "=======================================================" << endl;
    cout << "================ DAFTAR STAFF AKTIF ===================" << endl;
    cout << "=======================================================" << endl;
    cout << "ID\t| Username\t| Status\t|" << endl;
    cout << "-------------------------------------------------------" << endl;

    bool ada_aktif = false;
    for (const auto &item : j)
    {
        if (item["status_terima"] == true && item["status_kerja"] == true)
        {
            cout << item["id"] << "\t|" << item["nama"] << "\t| Aktif Bekerja\t|" << endl;
            cout << "-------------------------------------------------------" << endl;
            ada_aktif = true;
        }
    }

    if (!ada_aktif)
    {
        cout << "\n[INFO] Belum Ada Staff Yang Berstatus Aktif!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    int id_pilihan = -1;
    string input_id;

    while (true)
    {
        try
        {
            cout << "\nMasukkan ID Staff Yang Ingin Di PHK (0 untuk batal): ";
            getline(cin >> ws, input_id);

            id_pilihan = stoi(input_id);

            if (id_pilihan == 0)
            {
                system("cls");
                return;
            }
            break;
        }
        catch (const exception &e)
        {
            cout << "[ERROR] ID Tidak Valid!!!" << endl;
            system("pause");
            system("cls");

            cout << "=======================================================" << endl;
            cout << "================ DAFTAR STAFF AKTIF ===================" << endl;
            cout << "=======================================================" << endl;
            cout << "ID\t| Username\t| Status\t|" << endl;
            cout << "-------------------------------------------------------" << endl;

            for (const auto &item : j)
            {
                if (item["status_terima"] == true && item["status_kerja"] == true)
                {
                    cout << item["id"] << "\t|" << item["nama"] << "\t| Aktif Bekerja\t|" << endl;
                    cout << "-------------------------------------------------------" << endl;
                }
            }
        }

        break;
    }

    bool ditemukan = false;
    for (auto &item : j)
    {
        if (item["id"] == id_pilihan && item["status_terima"] == true && item["status_kerja"] == true)
        {
            item["status_kerja"] = false;
            ditemukan = true;
            break;
        }
    }

    if (ditemukan)
    {
        ofstream fileOut(FILE_STAFF);
        fileOut << j.dump(4);
        fileOut.close();
        cout << "[BERHASIL] Staff Dengan ID " << id_pilihan << " Telah Di PHK!!!" << endl;
    }
    else
    {
        cout << "[ERROR] ID Tidak Ditemukan / Staff Sudah Tidak Aktif!!!" << endl;
    }

    system("pause");
    system("cls");
}

void buat_kolam()
{
    Kolam kolam;

    json j;
    ifstream fileIn(FILE_KOLAM);
    if (fileIn.is_open())
    {
        if (fileIn.peek() != std::ifstream::traits_type::eof())
        {
            fileIn >> j;
        }
        fileIn.close();
    }

    if (j.is_null())
    {
        j = json::array();
    }

    if (j.size() >= 10)
    {
        cout << "\n[ERROR] Kuota Kolam Tambak Lele FULL!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    system("cls");
    cout << "============================" << endl;
    cout << "======== BUAT KOLAM ========" << endl;
    cout << "============================" << endl;
    cout << "Masukkan Tipe Kolam (Kecil, Sedang, Besar): ";
    getline(cin >> ws, kolam.tipe_kolam);

    kolam.status_kolam = "Kosong";
    kolam.populasi_ikan = 0;
    kolam.totalHargaBenih = 0;

    for (char &huruf : kolam.tipe_kolam)
    {
        huruf = tolower(huruf);
    }

    if (kolam.tipe_kolam == "kecil")
    {
        kolam.kapasitas = 500;
    }
    else if (kolam.tipe_kolam == "sedang")
    {
        kolam.kapasitas = 1500;
    }
    else if (kolam.tipe_kolam == "besar")
    {
        kolam.kapasitas = 3000;
    }
    else
    {
        cout << "[ERROR] Pilihan Tidak Valid!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    if (j.empty())
    {
        kolam.id_kolam = 1;
    }
    else
    {
        kolam.id_kolam = j.back()["id"].get<int>() + 1;
    }

    json kolamjson = {
        {"id", kolam.id_kolam},
        {"tipe", kolam.tipe_kolam},
        {"kapasitas", kolam.kapasitas},
        {"populasi", kolam.populasi_ikan},
        {"status_kolam", kolam.status_kolam},
        {"hargaBenih", kolam.totalHargaBenih}};

    j.push_back(kolamjson);

    ofstream fileOut(FILE_KOLAM);
    fileOut << j.dump(4);
    fileOut.close();

    cout << "[BERHASIL] Berhasil Menambah Kolam!!! (ID: " << kolam.id_kolam << ")" << endl;
    system("pause");
    system("cls");
}

void bongkar_kolam()
{
    json j;
    ifstream fileIn(FILE_KOLAM);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    if (j.empty())
    {
        cout << "[INFO] Belum Ada Kolam Yang Dibuat!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    system("cls");
    cout << "================================================================" << endl;
    cout << "================ DAFTAR KOLAM KOSONG ===========================" << endl;
    cout << "================================================================" << endl;
    cout << "ID\t| Tipe\t | Kapasitas\t| Populasi\t| Status\t|" << endl;
    cout << "----------------------------------------------------------------" << endl;

    bool kolam_kosong = false;
    for (const auto &item : j)
    {
        if (item["status_kolam"] == "Kosong")
        {
            cout << item["id"] << "\t|" << item["tipe"] << " | " << item["kapasitas"] << "\t\t|" << item["populasi"] << "\t\t|" << item["status_kolam"] << "\t|" << endl;
            cout << "----------------------------------------------------------------" << endl;
            kolam_kosong = true;
        }
    }

    if (!kolam_kosong)
    {
        cout << "\n[INFO] Belum Ada Kolam Yang Berstatus Kosong!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    int id_pilihan = -1;
    string input_id;

    while (true)
    {
        try
        {
            cout << "\nMasukkan ID Kolam Yang Ingin Di Bongkar/Hapus (0 untuk batal): ";
            getline(cin >> ws, input_id);

            id_pilihan = stoi(input_id);

            if (id_pilihan == 0)
            {
                system("cls");
                break;
                return;
            }
        }
        catch (const exception &e)
        {
            cout << "[ERROR] ID Tidak Valid!!!" << endl;
            system("pause");
            system("cls");

            cout << "================================================================" << endl;
            cout << "================ DAFTAR KOLAM KOSONG ===========================" << endl;
            cout << "================================================================" << endl;
            cout << "ID\t| Tipe\t | Kapasitas\t| Populasi\t| Status\t|" << endl;
            cout << "----------------------------------------------------------------" << endl;

            for (const auto &item : j)
            {
                if (item["status_kolam"] == "Kosong")
                {
                    cout << item["id"] << "\t|" << item["tipe"] << " | " << item["kapasitas"] << "\t\t|" << item["populasi"] << "\t\t|" << item["status_kolam"] << "\t|" << endl;
                    cout << "----------------------------------------------------------------" << endl;
                }
            }
        }

        break;
    }

    bool ditemukan = false;
    for (auto it = j.begin(); it != j.end(); ++it)
    {
        if ((*it)["id"] == id_pilihan && (*it)["status_kolam"] == "Kosong")
        {
            j.erase(it);
            ditemukan = true;
            break;
        }
    }

    if (ditemukan)
    {
        ofstream fileOut(FILE_KOLAM);
        fileOut << j.dump(4);
        fileOut.close();
        cout << "[BERHASIL] Kolam Dengan ID " << id_pilihan << " Telah Di Bongkar!!!" << endl;
    }
    else
    {
        cout << "[ERROR] ID Kolam Tidak Ditemukan / Kolam Sudah Dibongkar!!!" << endl;
    }

    system("pause");
    system("cls");
}

void tebar_benih()
{
    Kolam kolam;

    cout << "============ MENU TEBAR BENIH ============\n"
         << endl;
    int id_kolam;
    bool isValid = false;
    int jumlahBenih;
    int hargaBenih;
    int totalHargaBenih;

    json j;
    ifstream fileIn(FILE_KOLAM);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    if (j.empty())
    {
        cout << "[INFO] Belum Ada Kolam Yang Dibuat!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    system("cls");
    cout << "================================================================" << endl;
    cout << "================ DAFTAR KOLAM KOSONG ===========================" << endl;
    cout << "================================================================" << endl;
    cout << "ID\t| Tipe\t | Kapasitas\t| Populasi\t| Status\t|" << endl;
    cout << "----------------------------------------------------------------" << endl;

    bool kolam_kosong = false;
    for (const auto &item : j)
    {
        if (item["status_kolam"] == "Kosong")
        {
            cout << item["id"] << "\t|" << item["tipe"] << " | " << item["kapasitas"] << "\t\t|" << item["populasi"] << "\t\t|" << item["status_kolam"] << "\t|" << endl;
            cout << "----------------------------------------------------------------" << endl;
            kolam_kosong = true;
        }
    }
    cout << "Pilih Kolam yang ingin anda Tebar Benih: ";
    cin >> id_kolam;
    cin.ignore();

    for (auto &item : j)
    {
        if (item["id"] == id_kolam)
        {
            do
            {
                cout << "Input Jumlah Benih yang ingin anda Tebar (gram): ";
                cin >> jumlahBenih;
                cin.ignore();
                if (jumlahBenih > item["kapasitas"])
                {
                    cout << "Jumlah Benih yang ditebar tidak boleh melebihi Kapasitas Kolam!" << endl;
                    isValid = false;
                }
                else
                {

                    cout << "Input Harga Benih (Rp/Gram): " << endl;
                    cin >> hargaBenih;
                    cin.ignore();

                    totalHargaBenih = jumlahBenih * hargaBenih;

                    item["hargaBenih"] = totalHargaBenih;
                    item["status_kolam"] = "Terisi";
                    item["populasi"] = jumlahBenih;

                    isValid = true;
                }

            } while (isValid == false);
            ofstream fileOut(FILE_KOLAM);
            fileOut << j.dump(4);
            fileOut.close();
            cout << "[BERHASIL] Kolam Dengan ID " << id_kolam << " Telah Di Tebar Benih!!!" << endl;
            return;
        }
        else
        {
            cout << "[ERROR] ID Kolam Tidak Ditemukan !!!" << endl;
            system("pause");
            tebar_benih();
        }
    }
}

void pantau_tambak()
{
}

void laporan_keuangan()
{
}
