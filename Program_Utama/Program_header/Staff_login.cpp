#include <iostream>
#include <fstream>
#include <string>
#include "../Data_header/Staff_login.h"
#include "../Data_header/struct.h"
#include "../Data_json/json.hpp"

using namespace std;
using json = nlohmann::json;

const string FILE_STAFF = "Data_json/Data_staff.json";

void staff_regis()
{
    Staff staff_baru;

    system("cls");
    cout << "============================" << endl;
    cout << "===== REGISTRASI STAFF =====" << endl;
    cout << "============================" << endl;
    cout << "Masukkan Username : ";
    cin >> staff_baru.username;
    cout << "Masukkan Password : ";
    cin >> staff_baru.password;
    staff_baru.regis_status = false;
    staff_baru.employed_status = false;

    json j;
    ifstream fileIn(FILE_STAFF);
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
        cout << "\n[ERROR] Registrasi Ditolak!!! Kuota Staff Tambak Lele FULL" << endl;
        system("pause");
        system("cls");
        return;
    }

    for (const auto &item : j)
    {
        if (item["nama"] == staff_baru.username)
        {
            cout << "[ERROR] Username Sudah Terdaftar!!! Silakan Gunakan Username Lain!!!" << endl;
            system("pause");
            system("cls");
            return;
        }
    }

    if (j.empty())
    {
        staff_baru.id_staff = 1;
    }
    else
    {
        staff_baru.id_staff = j.back()["id"].get<int>() + 1;
    }

    json staffjson = {
        {"id", staff_baru.id_staff},
        {"nama", staff_baru.username},
        {"pass", staff_baru.password},
        {"status_terima", staff_baru.regis_status},
        {"status_kerja", staff_baru.employed_status}};
    j.push_back(staffjson);

    ofstream fileOut(FILE_STAFF);
    fileOut << j.dump(4);
    fileOut.close();

    cout << "[BERHASIL] Registrasi Berhasil! Akun Anda (ID: " << staff_baru.id_staff << ") Silahkan Tunggu Persetujuan Dari Admin" << endl;
    system("pause");
    system("cls");
}

bool status_regis()
{
    string cek_username;

    system("cls");
    cout << "=================================" << endl;
    cout << "===== CEK STATUS REGISTRASI =====" << endl;
    cout << "=================================" << endl;
    cout << "Masukkan Username: ";
    cin >> cek_username;

    json j;
    ifstream fileIn(FILE_STAFF);
    if (fileIn.is_open())
    {
        fileIn >> j;
        fileIn.close();

        for (auto &item : j)
        {
            if (item["nama"] == cek_username)
            {
                if (item["status_terima"] == true)
                {
                    cout << "[SELAMAT] Anda Diterima Sebagai Karyawan Tambak Lele :) !!!" << endl;
                    system("pause");
                    system("cls");
                    return true;
                }
                else
                {
                    cout << "[WAKWAW] Anda Ditolak Sebagai Karyawan Tambak Lele :( !!!" << endl;
                    system("pause");
                    system("cls");
                    return false;
                }
            }
        }
    }
    else{
        cout << "[ERROR] Username Tidak Ditemukan!!!" << endl;
        system("pause");
        system("cls");
        return false;
    }
}

bool login_staff()
{
    string log_username, log_pass;
    int batas_login = 0;

    system("cls");
    while (batas_login < 3)
    {
        cout << "=======================" << endl;
        cout << "===== LOGIN STAFF =====" << endl;
        cout << "=======================" << endl;
        cout << "Username : ";
        cin >> log_username;
        cout << "Password : ";
        cin >> log_pass;

        json j;
        ifstream fileIn(FILE_STAFF);
        if (fileIn.is_open())
        {
            fileIn >> j;
            fileIn.close();

            for (const auto &item : j)
            {
                if (item["nama"] == log_username && item["pass"] == log_pass)
                {
                    if (item["status_terima"] == true && item["status_kerja"] == true)
                    {
                        cout << "[BERHASIL] Login Berhasil! Selamat Datang, " << log_username << endl;
                        system("pause");
                        system("cls");
                        return true;
                    }
                    else if (item["status_terima"] == true && item["status_kerja"] == false)
                    {
                        cout << "[GAGAL] Anda Sudah Di Pecat Oleh Admin!!!" << endl;
                        system("pause");
                        system("cls");
                        return false;
                    }
                    else
                    {
                        cout << "[GAGAL] Login Gagal! Akun Anda belum disetujui oleh Admin!!!" << endl;
                        system("pause");
                        system("cls");
                        return false;
                    }
                }
                else
                {
                    batas_login += 1;
                    int sisa_percobaan = 3 - batas_login;
                    if (batas_login < 3)
                    {
                        cout << "[GAGAL] Login Gagal! Username atau Password Salah, Silahkan Coba Lagi (Sisa Percobaan: " << sisa_percobaan << "x )" << endl;
                        system("pause");
                        system("cls");
                    }
                    else
                    {
                        cout << "[KACAU] Anda Telah Salah 3x!!!" << endl;
                        system("pause");
                        system("cls");
                        return false;
                    }
                }
            }
        }
        return false;
    }
}

void menu_staff()
{
    int pilihan;
    bool staff_menu = true;

    while (staff_menu)
    {
        system("cls");

        cout << "======================================" << endl;
        cout << "===== RUANG KENDALI ADMIN TAMBAK =====" << endl;
        cout << "======================================" << endl;
        cout << "1. Update Jatah Pakan" << endl;
        cout << "2. Catat Kematian Ikan" << endl;
        cout << "3. Catat Kolam Siap Panen" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            staff_menu = false;
            system("pause");
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