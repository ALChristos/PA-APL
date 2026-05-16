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
const string FILE_REKBER = "Data_json/Rekber_admin.json";
const string FILE_PAKAN = "Data_json/Data_pakan.json";

json load_data_pakan()
{
    Pakan pakan;

    json j;
    ifstream fileIn(FILE_PAKAN);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    if (j.empty())
    {
        pakan.harga_per_kg = 0;
        pakan.stok_kg = 0;
        pakan.total_modal_pakan = 0;

        json kolamjson = {
            {"stok_kg", pakan.stok_kg},
            {"harga_per_kg", pakan.harga_per_kg},
            {"total_modal_pakan", pakan.total_modal_pakan},
        };

        j.push_back(kolamjson);
    }

    return j;
}

void lihat_staff(int id)
{
    json j;
    ifstream fileIn(FILE_STAFF);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    bool valid = false;

    cout << "=======================================================" << endl;
    cout << "============== DAFTAR STAFF BERDASARKAN ID ============" << endl;
    cout << "=======================================================" << endl;
    cout << "ID\t| Username\t| Status\t|" << endl;
    cout << "------------------------------------------------------" << endl;

    for (const auto &item : j)
    {
        if (item["id"] == id)
        {
            cout << item["id"] << "\t|" << item["nama"] << "\t|" << item["status_kerja"] << "\t|" << endl;
            cout << "------------------------------------------------------" << endl;

            valid = true;
        }
    }

    if (valid)
    {
        cout << "\n[SUCCESS] Staff Dengan (ID: " << id << ") Ditemukan!!!" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        cout << "[ERROR] Staff Dengan (ID: " << id << ") Tidak Ditemukan!!!" << endl;
        system("pause");
        system("cls");
        return;
    }
}

void lihat_staff()
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

    string pilihan_menu, input_id;
    int pilihan, id;
    bool loop = true;

    while (loop)
    {
        system("cls");
        cout << "============================" << endl;
        cout << "===== MENU LIHAT STAFF =====" << endl;
        cout << "============================" << endl;
        cout << "1. Lihat Staff Berdasarkan ID Staff" << endl;
        cout << "2. Lihat Staff Yang Aktif Bekerja" << endl;
        cout << "3. Lihat Staff Yang Belum Aktif Bekerja" << endl;
        cout << "4. Keluar" << endl;
        cout << "Masukan Pilihan: ";
        getline(cin >> ws, pilihan_menu);

        try
        {
            pilihan = stoi(pilihan_menu);
        }
        catch (const exception &e)
        {
            pilihan = 0;
        }

        switch (pilihan)
        {
        case 1:
            system("cls");

            while (true)
            {
                try
                {
                    cout << "Masukan ID Kolam Yang Ingin Di Lihat (Input 0 Untuk Batal): " << endl;
                    getline(cin >> ws, input_id);

                    id = stoi(input_id);

                    if (id == 0)
                    {
                        return;
                        system("cls");
                    }

                    break;
                }
                catch (const exception &e)
                {
                    cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
                    system("pause");
                    system("cls");
                }
            }

            lihat_staff(id);

            break;

        case 2:
            system("cls");
            cout << "=======================================================" << endl;
            cout << "================== DAFTAR STAFF AKTIF =================" << endl;
            cout << "=======================================================" << endl;
            cout << "ID\t| Username\t| Status\t|" << endl;
            cout << "------------------------------------------------------" << endl;

            for (int i = 0; i < j.size(); i++)
            {
                for (int k = 0; k < j.size() - 1 - i; k++)
                {
                    if (j[k]["id"] > j[k + 1]["id"])
                    {
                        swap(j[k], j[k + 1]);
                    }
                }
            }

            for (const auto &item : j)
            {
                if (item["status_terima"] == true)
                {
                    cout << item["id"] << "\t|" << item["nama"] << "\t| Aktif Bekerja\t |" << endl;
                    cout << "------------------------------------------------------" << endl;
                }
            }

            system("pause");
            system("cls");
            break;

        case 3:
            system("cls");
            cout << "=======================================================" << endl;
            cout << "=============== DAFTAR STAFF BELUM AKTIF ==============" << endl;
            cout << "=======================================================" << endl;
            cout << "ID\t| Username\t| Status\t|" << endl;
            cout << "------------------------------------------------------" << endl;

            for (int i = 0; i < j.size(); i++)
            {
                for (int k = 0; k < j.size() - 1 - i; k++)
                {
                    if (j[k]["id"] > j[k + 1]["id"])
                    {
                        swap(j[k], j[k + 1]);
                    }
                }
            }

            for (const auto &item : j)
            {
                if (item["status_terima"] == false)
                {
                    cout << item["id"] << "\t|" << item["nama"] << "\t| Tidak Akitf\t |" << endl;
                    cout << "------------------------------------------------------" << endl;
                }
            }

            system("pause");
            system("cls");
            break;

        case 4:
            loop = false;
            system("cls");
            break;

        default:
            cout << "[ERROR] Pilihan Tidak Valid, Silahkan Input Pilihan Yang Sesuai!!!" << endl;
            system("pause");
            break;
        }
    }

    system("pause");
    system("cls");
    return;
}

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

    int staff_aktif = 0;
    for (const auto &item : j)
    {
        if (item["status_terima"] == true && item["status_kerja"] == true)
        {
            staff_aktif++;
        }
    }

    if (staff_aktif >= 10)
    {
        cout << "[INFO] Kuota Karyawan Sudah Penuh (10/10)!!!" << endl;
        cout << "Tidak Bisa ACC Staff Baru Sebelum Ada Yang Di-PHK!!!" << endl;
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

    for (int i = 0; i < j.size(); i++)
    {
        for (int k = 0; k < j.size() - 1 - i; k++)
        {
            if (j[k]["id"] > j[k + 1]["id"])
            {
                swap(j[k], j[k + 1]);
            }
        }
    }

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

    for (int i = 0; i < j.size(); i++)
    {
        for (int k = 0; k < j.size() - 1 - i; k++)
        {
            if (j[k]["id"] > j[k + 1]["id"])
            {
                swap(j[k], j[k + 1]);
            }
        }
    }

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

void lihat_kolam(int id)
{
    json j;
    ifstream fileIn(FILE_KOLAM);

    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();
    }

    bool valid = false;

    cout << "================================================================" << endl;
    cout << "================= DAFTAR KOLAM BERDASARKAN ID ==================" << endl;
    cout << "================================================================" << endl;
    cout << "ID\t| Tipe\t | Kapasitas\t| Populasi\t| Status\t|" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (const auto &item : j)
    {
        if (item["id"] == id)
        {
            cout << item["id"] << "\t|" << item["tipe"] << " | " << item["kapasitas"] << "\t\t|" << item["populasi"] << "\t\t|" << item["status_kolam"] << "\t|" << endl;
            cout << "----------------------------------------------------------------" << endl;

            valid = true;
        }
    }

    if (valid)
    {
        cout << "\n[SUCCESS] Kolam Dengan (ID: " << id << ") Ditemukan!!!" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        cout << "\n[ERROR] Kolam Dengan (ID: " << id << ") Tidak Ditemukan!!!" << endl;
        system("pause");
        system("cls");
        return;
    }
}

void lihat_kolam()
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

    bool loop = true;
    string pilihan_menu, input_id, input_tipe, input_status;
    int pilihan, id;

    while (loop)
    {
        system("cls");
        cout << "============================" << endl;
        cout << "===== MENU LIHAT KOLAM =====" << endl;
        cout << "============================" << endl;
        cout << "1. Lihat Seluruh Kolam" << endl;
        cout << "2. Lihat Kolam Berdasarkan ID Kolam" << endl;
        cout << "3. Lihat Kolam Berdasarkan Tipe Kolam" << endl;
        cout << "4. Lihat Kolam Berdasarkan Status Kolam" << endl;
        cout << "5. Keluar" << endl;
        cout << "Masukan Pilihan: ";
        getline(cin >> ws, pilihan_menu);

        try
        {
            pilihan = stoi(pilihan_menu);
        }
        catch (const exception &e)
        {
            pilihan = 0;
        }

        switch (pilihan)
        {
        case 1:
            system("cls");

            for (int i = 0; i < j.size(); i++)
            {
                for (int k = 0; k < j.size() - 1 - i; k++)
                {
                    if (j[k]["id"] > j[k + 1]["id"])
                    {
                        swap(j[k], j[k + 1]);
                    }
                }
            }

            cout << "================================================================" << endl;
            cout << "================ DAFTAR KOLAM SELURUH KOLAM ====================" << endl;
            cout << "================================================================" << endl;
            cout << "ID\t| Tipe\t | Kapasitas\t| Populasi\t| Status\t|" << endl;
            cout << "----------------------------------------------------------------" << endl;

            for (const auto &item : j)
            {
                cout << item["id"] << "\t|" << item["tipe"] << " | " << item["kapasitas"] << "\t\t|" << item["populasi"] << "\t\t|" << item["status_kolam"] << "\t|" << endl;
                cout << "----------------------------------------------------------------" << endl;
            }
            system("pause");
            system("cls");
            break;

        case 2:
        {
            system("cls");

            while (true)
            {
                try
                {
                    cout << "Masukan ID Kolam Yang Ingin Di Lihat: ";
                    getline(cin >> ws, input_id);

                    id = stoi(input_id);

                    if (id == 0)
                    {
                        system("cls");
                        return;
                    }

                    break;
                }
                catch (const exception &e)
                {
                    cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
                    system("pause");
                    system("cls");
                }
            }

            lihat_kolam(id);

            break;
        }

        case 3:
        {
            system("cls");

            while (true)
            {
                cout << "Masukan Tipe Kolam Yang Ingin Di lihat (Kecil, Sedang, Besar): ";
                getline(cin >> ws, input_tipe);

                for (char &huruf : input_tipe)
                {
                    huruf = tolower(huruf);
                }

                if (input_tipe != "kecil" && input_tipe != "sedang" && input_tipe != "besar")
                {
                    cout << "[ERROR] Input Tidak Valid!!!" << endl;
                    cout << "[INFO] Silahkan Coba Lagi!!!" << endl;
                    system("pause");
                    system("cls");
                    continue;
                }

                cout << "========================================================================" << endl;
                cout << "==================== DAFTAR KOLAM BERDASARKAN TIPE =====================" << endl;
                cout << "========================================================================" << endl;
                cout << "ID\t| Tipe\t | Kapasitas\t| Populasi\t| Status\t|" << endl;
                cout << "------------------------------------------------------------------------" << endl;

                for (int i = 0; i < j.size(); i++)
                {
                    for (int k = 0; k < j.size() - 1 - i; k++)
                    {
                        if (j[k]["id"] > j[k + 1]["id"])
                        {
                            swap(j[k], j[k + 1]);
                        }
                    }
                }

                bool ada_data = false;
                for (const auto &item : j)
                {
                    if (item["tipe"] == input_tipe)
                    {
                        cout << item["id"] << "\t|" << item["tipe"] << " \t| " << item["kapasitas"] << "\t\t|" << item["populasi"] << "\t\t|" << item["status_kolam"] << "\t|" << endl;
                        cout << "------------------------------------------------------------------------" << endl;
                        ada_data = true;
                    }
                }

                if (!ada_data)
                {
                    cout << "[INFO] Tidak Ada Kolam Dengan (Tipe: " << input_tipe << ") Saat Ini!!!" << endl;
                }

                system("pause");
                system("cls");
                break;
            }
            break;
        }

        case 4:
        {
            system("cls");

            while (true)
            {
                cout << "Masukan Tipe Kolam Yang Ingin Di lihat (Kosong, Terisi, Panen): ";
                getline(cin >> ws, input_status);

                for (char &huruf : input_status)
                {
                    huruf = tolower(huruf);
                }

                input_status[0] = toupper(input_status[0]);

                if (input_status != "Kosong" && input_status != "Terisi" && input_status != "Panen")
                {
                    cout << "[ERROR] Input Tidak Valid!!!" << endl;
                    cout << "[INFO] Silahkan Coba Lagi!!!" << endl;
                    system("pause");
                    system("cls");
                    continue;
                }

                cout << "========================================================================" << endl;
                cout << "==================== DAFTAR KOLAM BERDASARKAN STATUS ===================" << endl;
                cout << "========================================================================" << endl;
                cout << "ID\t| Tipe\t | Kapasitas\t| Populasi\t| Status\t|" << endl;
                cout << "------------------------------------------------------------------------" << endl;

                for (int i = 0; i < j.size(); i++)
                {
                    for (int k = 0; k < j.size() - 1 - i; k++)
                    {
                        if (j[k]["id"] > j[k + 1]["id"])
                        {
                            swap(j[k], j[k + 1]);
                        }
                    }
                }

                bool ada_data = false;
                for (const auto &item : j)
                {
                    if (item["status_kolam"] == input_status)
                    {
                        cout << item["id"] << "\t|" << item["tipe"] << " \t| " << item["kapasitas"] << "\t\t|" << item["populasi"] << "\t\t|" << item["status_kolam"] << "\t|" << endl;
                        cout << "------------------------------------------------------------------------" << endl;
                        ada_data = true;
                    }
                }

                if (!ada_data)
                {
                    cout << "[INFO] Tidak Ada Kolam Dengan (Status: " << input_status << ") Saat Ini!!!" << endl;
                }

                system("pause");
                system("cls");
                break;
            }
            break;
        }

        case 5:
            system("cls");
            loop = false;
            break;

        default:
            cout << "[ERROR] Pilihan Tidak Valid, Silahkan Input Pilihan Yang Sesuai!!!" << endl;
            system("pause");
            break;
        }
    }
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
    kolam.total_harga_benih = 0;
    kolam.total_mati = 0;
    kolam.umur_kolam = 0;
    kolam.fase_kolam = "";
    kolam.total_berat_kolam = 0;
    kolam.total_harga_pakan = 0;
    kolam.total_modal = 0;

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
        {"total_harga_benih", kolam.total_harga_benih},
        {"total_mati", kolam.total_harga_benih},
        {"fase_kolam", kolam.fase_kolam},
        {"total_berat_kolam", kolam.total_berat_kolam},
        {"umur_kolam", kolam.umur_kolam},
        {"total_harga_pakan", kolam.total_harga_pakan},
        {"total_modal", kolam.total_modal}};

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
                return;
            }
            break;
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
        cout << "\n[INFO] Tidak Ada Kolam Kosong Saat Ini. Silahkan Bongkar/Buat Kolam Baru!" << endl;
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
            cout << "\nMasukkan ID Kolam Yang Ingin Di Tebar Benih (0 untuk batal): ";
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
    string jumlah, harga;
    int jumlahBenih, hargaBenih, totalHargaBenih;

    for (auto &item : j)
    {
        if (item["id"] == id_kolam && item["status_kolam"] == "Kosong")
        {
            ditemukan = true;
            bool input_sukses = true;

            while (input_sukses)
            {
                try
                {
                    cout << "Input Jumlah Benih yang ingin anda Tebar (gram): ";
                    getline(cin >> ws, jumlah);

                    jumlahBenih = stoi(jumlah);

                    if (jumlahBenih <= 0)
                    {
                        cout << "[ERROR] Jumlah Benih Harus Lebih Dari 0!!!" << endl;
                        continue;
                    }

                    if (jumlahBenih > item["kapasitas"])
                    {
                    }

                    cout << "Input Harga Benih (Rp/Gram): ";
                    getline(cin >> ws, harga);

                    hargaBenih = stoi(harga);

                    if (hargaBenih <= 0)
                    {
                        cout << "[ERROR] Harga Benih Harus Lebih Dari 0!!!" << endl;
                        continue;
                    }

                    int populasi;

                    totalHargaBenih = jumlahBenih * hargaBenih;
                    item["total_harga_benih"] = totalHargaBenih;
                    item["status_kolam"] = "Terisi";
                    item["populasi"] = jumlahBenih;
                    item["fase_kolam"] = "Benih";

                    populasi = item["populasi"];
                    item["total_berat_kolam"] = populasi * 1;

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
        fileOut << j.dump(4);
        fileOut.close();
        cout << "\n[BERHASIL] Kolam Dengan ID " << id_kolam << " Telah Di Tebar Benih!!!" << endl;
    }
    else
    {
        cout << "\n[ERROR] ID Kolam Tidak Ditemukan atau Kolam Sudah Terisi!!!" << endl;
    }

    system("pause");
    system("cls");
}

void update_stok_pakan()
{

    json j = load_data_pakan();

    string jumlah;
    int jumlah_pakan_tambahan;

    for (auto &item : j)
    {
        bool input_sukses = true;
        int stok_pakan = item["stok_kg"];

        while (input_sukses)
        {

            try
            {
                cout << "Input Jumlah Pakan yang ingin anda Tambah (Kilogram): ";
                getline(cin >> ws, jumlah);

                jumlah_pakan_tambahan = stoi(jumlah);

                if (jumlah_pakan_tambahan <= 0)
                {
                    cout << "[ERROR] Jumlah Pakan yang ditambah Harus Lebih Dari 0!!!" << endl;
                    continue;
                }

                stok_pakan += jumlah_pakan_tambahan;

                item["stok_kg"] = stok_pakan;

                input_sukses = false;
            }
            catch (const exception &e)
            {
                cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
            }
        }
    }

    ofstream fileOut(FILE_PAKAN);
    fileOut << j.dump(4);
    fileOut.close();
    cout << "\n[BERHASIL] Stock Pakan Telah Berhasil Diupdate!" << endl;

    system("pause");
    system("cls");
}

void update_harga_pakan()
{
    json j = load_data_pakan();

    string Harga;
    int harga_pakan, stok_pakan;

    for (auto &item : j)
    {
        bool input_sukses = true;
        stok_pakan = item["stok_kg"];

        while (input_sukses)
        {

            try
            {
                cout << "Input Harga Pakan yang ingin anda Tambah: ";
                getline(cin >> ws, Harga);

                harga_pakan = stoi(Harga);

                if (harga_pakan <= 0)
                {
                    cout << "[ERROR] Harga Pakan yang ditambah Harus Lebih Dari 0!!!" << endl;
                    continue;
                }

                item["harga_per_kg"] = harga_pakan;
                item["total_modal_pakan"] = stok_pakan * harga_pakan;

                input_sukses = false;
            }
            catch (const exception &e)
            {
                cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
            }
        }
    }

    ofstream fileOut(FILE_PAKAN);
    fileOut << j.dump(4);
    fileOut.close();
    cout << "\n[BERHASIL] Harga Pakan Telah Berhasil Diupdate!" << endl;

    system("pause");
    system("cls");
}

void tampilkan_data_pakan()
{
    json j = load_data_pakan();

    for (auto &item : j)
    {
        int stok = item["stok_kg"];
        int harga = item["harga_per_kg"];
        int total_harga = item["total_modal_pakan"];

        cout << "\n=================================" << endl;
        cout << "         DATA STOCK PAKAN        " << endl;
        cout << "=================================" << endl;
        cout << "Stok           : " << stok << " Kg" << endl;
        cout << "Harga          : " << harga << endl;
        cout << "Total Hraga    : " << total_harga << endl;
        cout << "=================================" << endl;
    }

    system("pause");
    system("cls");
}

void jual_ikan()
{
    json j, r, s;
    ifstream fileklm(FILE_KOLAM);
    ifstream filejl(FILE_REKBER);
    ifstream files(FILE_STAFF);

    if (filejl.is_open())
    {
        filejl >> r;
        filejl.close();
    }

    if (files.is_open())
    {
        files >> s;
        files.close();
    }

    if (fileklm.is_open())
    {
        fileklm >> j;
        fileklm.close();
    }

    if (j.empty())
    {
        cout << "[INFO] Belum Ada Kolam Yang Dibuat!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    bool kolam_panen = true;
    for (const auto &item : j)
    {
        if (item["status_kolam"] == "Panen")
        {
            kolam_panen = false;
        }
    }

    if (kolam_panen)
    {
        cout << "[INFO] Belum Ada Kolam Dengan Status Panen Saat Ini!!!" << endl;
        system("pause");
        system("clear");
        return;
    }
    else if (!kolam_panen)
    {
        system("cls");
        cout << "================================================================" << endl;
        cout << "================ DAFTAR KOLAM SIAP PANEN =======================" << endl;
        cout << "================================================================" << endl;
        cout << "ID\t| Tipe\t | Kapasitas\t| Populasi\t| Status\t|" << endl;
        cout << "----------------------------------------------------------------" << endl;

        for (int i = 0; i < j.size(); i++)
        {
            for (int k = 0; k < j.size() - 1 - i; k++)
            {
                if (j[k]["id"] > j[k + 1]["id"])
                {
                    swap(j[k], j[k + 1]);
                }
            }
        }

        for (const auto &item : j)
        {
            if (item["status_kolam"] == "Panen")
            {
                cout << item["id"] << "\t|" << item["tipe"] << " | " << item["kapasitas"] << "\t\t|" << item["populasi"] << "\t\t|" << item["status_kolam"] << "\t|" << endl;
                cout << "----------------------------------------------------------------" << endl;
            }
        }

        string input_id;
        int id;

        while (true)
        {
            try
            {
                cout << "Masukan ID Kolam Yang Ingin Dipanen & Dijual (0 Untuk Batal): ";
                getline(cin >> ws, input_id);

                id = stoi(input_id);

                if (id == 0)
                {
                    system("cls");
                    return;
                }

                break;
            }
            catch (const exception &e)
            {
                cout << "[ERROR] Input Harus Berupa Angka!!!" << endl;
                cout << "[INFO] Silahkan Coba Lagi!!!" << endl;
                system("pause");
                system("cls");

                cout << "================================================================" << endl;
                cout << "================ DAFTAR KOLAM SIAP PANEN =======================" << endl;
                cout << "================================================================" << endl;
                cout << "ID\t| Tipe\t | Kapasitas\t| Populasi\t| Status\t|" << endl;
                cout << "----------------------------------------------------------------" << endl;

                for (int i = 0; i < j.size(); i++)
                {
                    for (int k = 0; k < j.size() - 1 - i; k++)
                    {
                        if (j[k]["id"] > j[k + 1]["id"])
                        {
                            swap(j[k], j[k + 1]);
                        }
                    }
                }

                for (const auto &item : j)
                {
                    if (item["status_kolam"] == "Panen")
                    {
                        cout << item["id"] << "\t|" << item["tipe"] << " | " << item["kapasitas"] << "\t\t|" << item["populasi"] << "\t\t|" << item["status_kolam"] << "\t|" << endl;
                        cout << "----------------------------------------------------------------" << endl;
                    }
                }
            }
        }

        bool ditemukan = false;
        for (auto &item : j)
        {
            if (item["id"] == id && item["status_kolam"] == "Panen")
            {
                double jumlah_ikan = item["populasi"];
                double harga_benih = item["total_harga_benih"];

                double harga_pakan; // <-- ERROR KARENA BELUM ADA NILAINYA
                double modal = harga_benih + harga_pakan;
                double harga_ikan = (modal + (modal * 2)) / jumlah_ikan;
                double total_kotor = jumlah_ikan * harga_ikan;
                double gaji_staff_total = total_kotor * 0.5;
                double keuntungan_bersih = total_kotor - (gaji_staff_total + modal);

                // Gaji Staff
                int jumlah_staff_aktif = 0;
                for (auto &st : s)
                {
                    if (st["status_kerja"] == true)
                    {
                        jumlah_staff_aktif++;
                    }
                }

                if (jumlah_staff_aktif > 0)
                {
                    double gaji_per_orang = gaji_staff_total / jumlah_staff_aktif;

                    for (auto &st : s)
                    {
                        if (st["status_kerja"] == true)
                        {
                            int saldo = st["saldo"];
                            st["saldo"] = saldo + gaji_per_orang;
                        }
                    }

                    cout << "\n[SUCCESS] Gaji Total (Rp. " << gaji_staff_total << ") Telah Dibagikan Kepada " << jumlah_staff_aktif << " Staff!!!" << endl;
                }
                else
                {
                    keuntungan_bersih += gaji_staff_total;
                    cout << "\n[GREAT] Tidak Ada Staff Aktif. Jatah Gaji Masuk Ke Reking Perusahaan!!!" << endl;
                }

                // REKBER ADMIN
                double saldo_admin_lama = r.value("rekening_admin", 0.0);
                r["rekening_admin"] = saldo_admin_lama + keuntungan_bersih;
                cout << "[SUKSES] Keuntungan Bersih (Rp. " << keuntungan_bersih << ") Masuk Ke Rekening Admin!!!" << endl;

                // Reset Kolam
                item["hargaBenih"] = 0;
                item["populasi"] = 0;
                item["status_kolam"] = "Kosong";
                item["total_harga_benih"] = 0;
                item["total_mati"] = 0;

                ditemukan = true;
                break;
            }
        }

        if (ditemukan)
        {
            ofstream outkolam(FILE_KOLAM);
            outkolam << j.dump(4);
            outkolam.close();

            ofstream outrekening(FILE_REKBER);
            outrekening << r.dump(4);
            outrekening.close();

            ofstream outstaff(FILE_STAFF);
            outstaff << s.dump(4);
            outstaff.close();

            cout << "[BERHASIL] Ikan Di Kolam Dengan (ID: " << id << ") Telah Terjual Semua !!!" << endl;
            system("pause");
            system("cls");
        }
        else
        {
            cout << "[ERROR] ID Kolam Tidak Ditemukan!!!" << endl;
            system("pause");
            system("cls");
        }
    }
}

void laporan_keuangan()
{
}
