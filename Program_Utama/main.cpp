#include <iostream>
#include <string>
#include "Data_header/Staff_login.h"
#include "Data_header/Admin_login.h"

using namespace std;

int main()
{
    string pilihan;
    int input_pilihan = 0;

    while (true)
    {
        cout << "\n========================================================" << endl;
        cout << "================ SELMAT DATANG DI MENU =================" << endl;
        cout << "= SISTEM MANAJEMEN INFORMASI & PENGELOLAAN TAMBAK LELE =" << endl;
        cout << "========================================================" << endl;
        cout << "1. Login Admin" << endl;
        cout << "2. Login Staff" << endl;
        cout << "3. Keluar" << endl;
        cout << "Masukan Pilihan: ";
        getline(cin >> ws, pilihan);

        try{
            input_pilihan = stoi(pilihan);
        }
        catch(const exception& e){
            input_pilihan = 0;
        }

        switch (input_pilihan)
        {
        case 1:
        {
            bool log_admin = login_admin();

            if (log_admin == true)
            {
                menu_admin();
            }
            else
            {
                return 0;
            }

            break;
        }

        case 2:
        {
            bool login = true;

            while (login)
            {
                system("cls");
                cout << "========================" << endl;
                cout << "=== MENU LOGIN STAFF ===" << endl;
                cout << "========================" << endl;
                cout << "1. Login" << endl;
                cout << "2. Registrasi" << endl;
                cout << "3. Keluar Menu Login Staff" << endl;
                cout << "Masukan Pilihan: ";
                getline(cin >> ws, pilihan);

                try{
                    input_pilihan = stoi(pilihan);
                }
                catch(const exception& e){
                    input_pilihan = 0;
                }

                switch (input_pilihan)
                {
                case 1:
                {
                    bool log_staff = login_staff();

                    if (log_staff == true)
                    {
                        menu_staff();
                    }

                    break;
                }

                case 2:
                {

                    system("cls");
                    string pil_regis;
                    int pilihan_regis = 0;
                    bool loop = true;

                    while(loop){
                        cout << "=============================" << endl;
                        cout << "=== MENU REGISTRASI STAFF ===" << endl;
                        cout << "=============================" << endl;
                        cout << "1. Registrasi" << endl;
                        cout << "2. Cek Status Registrasi" << endl;
                        cout << "3. Keluar Menu Registras Staff" << endl;
                        cout << "Masukan Pilihan: ";
                        getline(cin >> ws, pil_regis);
                        
                        try{
                            pilihan_regis = stoi(pil_regis);
                        }
                        catch(const exception& e){
                            pilihan_regis = 0;
                        }

                        switch (pilihan_regis)
                        {
                        case 1:
                            staff_regis();
                            break;
    
                        case 2:
                            status_regis();
                            break;
    
                        case 3:
                            system("cls");
                            loop = false;
                            break;
    
                        default:
                            cout << "[ERROR] Pilihan Tidak Valid, Silahkan Input Pilihan Yang Sesuai!!!" << endl;
                            system("pause");
                            system("cls");
                            break;
                        }
                    }

                    break;
                }

                case 3:
                {
                    system("cls");
                    login = false;
                    break;
                }
                default:
                {
                    cout << "[ERROR] Pilihan Tidak Valid, Silahkan Input Pilihan Yang Sesuai!!!" << endl;
                    system("pause");
                    system("cls");
                    break;
                }
                }
            }

            break;
        }

        case 3:
        {
            cout << "Terima Kasih Telah Menggunakan Program Ini :)" << endl;
            return 0;
        }

        default:
        {
            cout << "[ERROR] Pilihan Tidak Valid, Silahkan Input Pilihan Yang Sesuai!!!" << endl;
            system("pause");
            system("cls");
            break;
        }
        }
    }
    return 0;
}
