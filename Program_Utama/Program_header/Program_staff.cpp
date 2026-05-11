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
const string FILE_KEUANGAN = "Data_json/Laporan_keuangan.json";

using namespace std;

void catatMortalitas(int &id_staff)
{
    cout << "============ MENU PENCATATAN MORTALITAS ============\n"
         << endl;

    Kolam kolam;
    Staff staff;

    json kolamj;
    ifstream fileklm(FILE_KOLAM);

    int id_kolam_target;

    if (fileklm.is_open())
    {
        fileklm >> kolamj;
        fileklm.close();
    }

    if (kolamj.empty())
    {
        cout << "[INFO] Belum Ada Kolam Yang Dibuat!!!" << endl;
        system("pause");
        system("cls");
        return;
    }

    json staffj;
    ifstream filestf(FILE_STAFF);

    if (filestf.is_open())
    {
        filestf >> staffj;
        filestf.close();
    }

    if (staffj.empty())
    {
        cout << "[INFO] Belum Ada Kolam Yang Dibuat!!!" << endl;
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

    for(int i = 0; i < kolamj.size(); i++){
        for(int k = 0; k < kolamj.size() - 1 - i; k++){
            if (kolamj[k]["id"] > kolamj[k + 1]["id"]){
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
    string totalMatiInput;
    int totalMati;
    int populasiAkhir;
    int jumlahBenih, hargaBenih, totalHargaBenih;

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

                    int populasi = item["populasi"];
                    populasiAkhir = populasi - totalMati;
                    item["populasi"] = populasiAkhir;
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

void catat_panen(int &id_staff){
    json j;
    ifstream fileklm(FILE_KOLAM);

    if(fileklm.is_open())
    {
        fileklm >> j;
        fileklm.close();
    }

    if(j.empty())
    {
        cout << "[INFO] Belum Ada Kolam Yang Dibuat!!!" << endl;
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

    for(int i = 0; i < j.size(); i++){
        for(int k = 0; k < j.size() - 1 - i; k++){
            if (j[k]["id"] > j[k + 1]["id"]){
                swap(j[k], j[k + 1]); 
            }
        }
    }
    
    for (const auto &item : j)
    {
        if(item["status_kolam"] == "Terisi"){
            cout << item["id"] << "\t|" << item["tipe"] << " | " << item["kapasitas"] << "\t\t|" << item["populasi"] << "\t\t|" << item["status_kolam"] << "\t|" << endl;
            cout << "----------------------------------------------------------------" << endl;
        }
    }

    // COMING SOON, BUTUH DATA PAKAN 10 HARI PERTAMA AGAR PROGRAM DAPAT BERJALAN DENGAN ERROR HANDLING
}