#include <iostream>
#include <fstream>
#include <string>
#include "../Data_header/Admin_login.h"
#include "../Data_header/struct.h"
#include "../Data_json/json.hpp"
#include "../Data_header/kelolaPakan.h"

using namespace std;
using json = nlohmann::json;

// Mengubah Path json
const string FILE_ADMIN = "Data_json/Data_admin.json";

bool login_admin()
{
    string nama, pass;
    int batas_login = 0;

    while (batas_login < 3)
    {
        system("cls");
        cout << "=======================" << endl;
        cout << "===== LOGIN ADMIN =====" << endl;
        cout << "=======================" << endl;
        cout << "Username : ";
        cin >> nama;
        cout << "Password : ";
        cin >> pass;

        json j;
        ifstream fileIn(FILE_ADMIN);

        // Menambah pesan status file
        if (!fileIn)
        {
            cout << "FILE GAGAL DIBUKA!" << endl;
            return false;
        }

        if (fileIn.is_open())
        {

            if (fileIn.peek() != std::ifstream::traits_type::eof())
            {
                fileIn >> j;
            }
            fileIn.close();

            for (const auto &item : j)
            {
                if (item["username"] == nama && item["password"] == pass)
                {
                    cout << "[BERHASIL] Login Berhasil! Selamat Datang, Juragan " << nama << "!" << endl;
                    system("pause");
                    system("cls");
                    return true;
                }
            }
        }

        batas_login++;
        int sisa_percobaan = 3 - batas_login;

        if (batas_login < 3)
        {
            cout << "[GAGAL] Username atau Password Admin Salah! (Sisa Percobaan: " << sisa_percobaan << "x )" << endl;
            system("pause");
        }
        else
        {
            cout << "[KACAU] Anda Telah Salah 3x. Kembali ke Menu Utama!!!" << endl;
            system("pause");
            system("cls");
            return false;
        }
    }

    return false;
}

void menu_admin()
{
    int pilihan;
    bool admin_menu = true;

    while (admin_menu)
    {
        system("cls");

        cout << "======================================" << endl;
        cout << "===== RUANG KENDALI ADMIN TAMBAK =====" << endl;
        cout << "======================================" << endl;
        cout << "1. Kelola Kolam" << endl;
        cout << "2. Tebar Benih Ikan" << endl;
        cout << "3. Kelola Pakan Ikan" << endl;
        cout << "4. Cek Laporan" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            break;

        case 2:
            break;

            case 3:
                kelolaPakan(daftarKolam, 10, daftarAdmin, id_admin);
                break;

        case 4:
            break;

        case 5:
            admin_menu = false;
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