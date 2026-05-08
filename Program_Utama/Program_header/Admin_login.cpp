#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "../Data_header/Admin_login.h"
#include "../Data_header/Program_admin.h"
#include "../Data_header/Program_staff.h"
#include "../Data_header/struct.h"
#include "../Data_json/json.hpp"
// #include "../Data_header/kelolaPakan.h"

using namespace std;
using json = nlohmann::json;

// Mengubah Path json
const string FILE_ADMIN = "Data_json/Data_admin.json";

bool login_admin()
{
    string nama, pass;
    int batas_login = 0;
    bool login_admin = true;

    while (batas_login < 3)
    {
        system("cls");
        cout << "=======================" << endl;
        cout << "===== LOGIN ADMIN =====" << endl;
        cout << "=======================" << endl;
        cout << "Username : ";
        getline(cin >> ws, nama);
        cout << "Password : ";
        getline(cin >> ws, pass);

        json j;
        ifstream fileIn(FILE_ADMIN);

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
            cout << "[FATAL] Anda Telah Salah Login 3x Sebagai ADMIN!!!" << endl;
            system("pause");
            system("cls");
            return false;
        }
    }

    return false;
}

void menu_admin()
{
    int pilihan = 0;
    string pilihan_menu;
    bool admin_menu = true;

    while (admin_menu)
    {
        system("cls");

        cout << "===========================================" << endl;
        cout << "===== RUANG KENDALI ADMIN TAMBAK LELE =====" << endl;
        cout << "===========================================" << endl;
        cout << "1. Kelola Kolam" << endl;
        cout << "2. Kelola Staff" << endl;
        cout << "3. Tebar Benih Ikan" << endl;
        cout << "4. Kelola Pakan Ikan" << endl;
        cout << "5. Cek Laporan" << endl;
        cout << "6. Keluar" << endl;
        cout << "Masukan Pilihan: ";
        getline(cin >> ws, pilihan_menu);

        try{
            pilihan = stoi(pilihan_menu);
        }
        catch(const exception& e){
            pilihan = 0;
        }

        switch (pilihan)
        {
        case 1:{
            bool loop = true;
            
            while(loop){
                system("cls");
                cout << "============================" << endl;
                cout << "===== MENU KEOLA KOLAM =====" << endl;
                cout << "============================" << endl;
                cout << "1. Buat Kolam" << endl;
                cout << "2. Lihat Kolam" << endl;
                cout << "3. Bongkar / Hapus Kolam" << endl;
                cout << "4. Keluar" << endl;
                cout << "Masukan Pilihan: ";
                getline(cin >> ws, pilihan_menu);

                try{
                    pilihan = stoi(pilihan_menu);
                }
                catch(const exception& e){
                    pilihan = 0;
                }
    
                switch(pilihan){
                    case 1:
                        buat_kolam();
                        break;

                    case 2:
                        lihat_kolam();
                        break;
    
                    case 3:
                        bongkar_kolam();
                        break;
    
                    case 4:
                        system("cls");
                        loop = false;
                        break;
    
                    default:
                        cout << "[ERROR] Pilihan Tidak Valid, Silahkan Input Pilihan Yang Sesuai!!!" << endl;
                        system("pause");
                        break;
                }
            }

            break;
        }

        case 2:{
            bool loop = true;
            
            while(loop){
                system("cls");
                cout << "============================" << endl;
                cout << "===== MENU KEOLA STAFF =====" << endl;
                cout << "============================" << endl;
                cout << "1. Pecat Staff" << endl;
                cout << "2. Lihat Staff" << endl;
                cout << "3. ACC Staff" << endl;
                cout << "4. Keluar" << endl;
                cout << "Masukan Pilihan: ";
                getline(cin >> ws, pilihan_menu);

                try{
                    pilihan = stoi(pilihan_menu);
                }
                catch(const exception& e){
                    pilihan = 0;
                }
    
                switch(pilihan){
                    case 1:
                        pecat_staff();
                        break;

                    case 2:
                        lihat_staff();
                        break;
    
                    case 3:
                        acc_staff();
                        break;
    
                    case 4:
                        system("cls");
                        loop = false;
                        break;
    
                    default:
                        cout << "[ERROR] Pilihan Tidak Valid, Silahkan Input Pilihan Yang Sesuai!!!" << endl;
                        system("pause");
                        break;
                }
            }
            break;
        }

        case 3:
            // kelolaPakan(daftarKolam, 10, daftarAdmin, id_admin);
            break;

        case 4:
            break;

        case 5:
            break;

        case 6:
            admin_menu = false;
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