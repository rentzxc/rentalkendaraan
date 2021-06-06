//FILE HEADER YANG DIGUNAKAN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

//FILE GLOBAL
FILE *reg;
FILE *cartemp;
FILE *fgettime;
FILE *rentedcar;
FILE *datamobil;
FILE *customer;

//PROTOTYPE FUNGSI
int regpage();
int logpage();
int mainpage();
int adminpage();

//PROTOTYPE PROSEDUR
void rent();
void mask();
void gettime();
void process();
void datarent();
void datacustomer();


//VARIABEL GLOBAL
char times;
char user[32];
char pass[16];
char fuser[32];
char fpass[16];
char pickcar[16];
char removecar[16];
int i, back, frontmode, mainmode, adminmode, processmode, matching, 
matchlog, totalcar;

//STRUCT GLOBAL
struct {
        char d[2], m[2], y[4];
    }t;

struct {
        char tipe[50], tahun[16], asuransi[32], fee[16];  
    }carsdata;

struct {
        char userr[32], nama[50], alamat[50], ktp[20], sim[20], kk[20], 
        hp[12], tanggalmulai[32], bulanmulai[32], tahunmulai[32], 
        tanggalkembali[32], bulankembali[32], tahunkembali[32];  
    }datacust;

//FRONTPAGE
int main()
{
	//HEADER PROGRAM
    printf("-------------------------------------------------\n");
    printf("|        Car Rent Program Called D'RENT         |\n");
    printf("-------------------------------------------------\n");
    //PILIH MODE 
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit Program\n");
    printf("------------------------------------\n");
    printf("Choose the number then press Enter : ");scanf("%d",&frontmode);
    //KONDISI PERCABANGAN UNTUK MODE
    switch (frontmode)
    {
        case 1: regpage();
        case 2: logpage();
        case 3: return 0;break;
        default: system("cls");printf("Menu Not Available\n");
        system("pause");
        system("cls");
        main();
    }
}

//REGISTRATION PAGE
int regpage()
{
    matching=0;
    system("cls");
    printf("             ==== Register Page ====\n");
    printf("-------------------------------------------------\n");
    printf("Enter Username : ");scanf("%s",&user);
    printf("Enter Password : ");mask(pass);
    reg = fopen("datareg.txt","a+");
    while ((fscanf(reg, "%s %s ",&fuser,&fpass))!=EOF)
    {
        if (strcmp(user,fuser)==0)
        {
            matching=1;
            break;
        }
    }

    if (matching==1)
    {
        printf("\n\n* Username already taken, Try again with different username :)\n\n");
        system("pause");
        regpage();
    }
    else
    {
        fprintf(reg,"%s %s ",user,pass);
        printf("\n\n* Username successfully Registered\n\n");
        fclose(reg);
        system("pause");
        system("cls");
        main();
    }
}

//LOGIN PAGE
int logpage()
{
    system("cls");
    matchlog=0;
    printf("             ==== Login Page ====\n");
    printf("-------------------------------------------------\n");
    printf("Enter Username : ");scanf("%s",&user);
    printf("Enter Password : ");mask(pass);
    if (strcmp(user, "admin")==0 && strcmp(pass,"admin")==0)
    {
        printf("\n\n  Login Successfull! \n\n");
        system("pause");
        system("cls");
        adminpage();
    }
    reg = fopen("datareg.txt","r");
    while ((fscanf(reg, "%s %s ",&fuser,&fpass))!=EOF)
    {
        if (strcmp(user,fuser)==0 && strcmp(pass,fpass)==0)
        {

            printf("\n\n Login Successfull! \n\n");
            matchlog=1;
            system("pause");
            system("cls");
            mainpage();
            break; 
        }
    }
    
    if (matchlog!=1)
    {
        printf("\n\n Username atau password salah\n");
        printf("      Silahkan coba lagi\n\n");
        system("pause");
        system("cls");
        logpage();
    }
    fclose(reg);
}

//MAINPAGE
int mainpage()
{
    //datamobil = fopen("datamobil.txt","r");    //OPEN FILE MODE READ
    //ambilwaktu = fopen("ambilwaktu.txt","r");
    printf("\n|        ######    Welcome to D'RENT    ######          |\n");
    printf("|-------------------------------------------------------|\n");
    printf("|            A Place for you to rent a car              |\n");
    printf("|-------------------------------------------------------|\n");
    printf("|    1. Rent a Car                                      |\n");
    printf("|    2. Check Rent Status                               |\n");
    printf("|    3. Exit Program                                    |\n");
    printf("|                                                       |\n");
    printf("|                                                       |\n");
    printf("|                      Contact admin : dren7@gmail.com  |\n");
    printf("|-------------------------------------------------------|\n");
    printf(" Choose the number then pres Enter : ");scanf("%d",&mainmode);
    switch (mainmode)
    {
        case 1: rent();
        //case 2: check();
        case 3: return 0;break;
        default:system("cls");printf("Menu Not Available\n");
        system("pause");
        system("cls");
        mainpage();
    }
}

//RENT
void rent()
{
    customer = fopen("datacustomer.dat","rb");
    while(fread(&datacust, sizeof(datacust),1,customer)==1)
    {
		if (strcmp(datacust.userr, user)==0) 
        {
            system("cls");
            printf("\n|------------------------------------------------------------------------|\n");
		    printf("|             Maaf. Akun ini sedang dalam masa sewa kendaraan,           |\n");
            printf("|                  tunggu hingga masa sewa anda berakhir.                |\n");
            printf("|           Atau jika anda berkenan untuk menyewa kendaraan lain,        |\n");
            printf("| harap untuk melakukan pengembalian manual kendaraan yang sedang disewa |\n");
            printf("|    terlebih dahulu dengan menghubungi admin untuk proses konfirmasi    |\n");
            printf("|                    Terima kasih atas perhatiannya :)                   |\n");
            printf("|------------------------------------------------------------------------|\n\n");
            fclose(customer);
            system("pause");
            mainpage();
	    }
    }
    fclose(customer);
    datamobil = fopen("datamobil.dat","rb");
    while ((fread(&carsdata,sizeof(carsdata),1,datamobil)==0))
    {
        system("cls");
        printf("------ List of Ready Cars ------\n\n");
        printf("There is no Datas yet,\n    Kindly wait for the update :D \n\n");
        fclose(datamobil);
        system("pause");
        system("cls");
        mainpage();
        
    }
    fclose(datamobil);
    fgettime = fopen("gettime.txt","r");
    if ( (times=fgetc(fgettime)) == EOF)  
    {
        system("cls");
        printf("Maaf Toko Sedang Tutup :(\n");
        printf("  Coba Lagi Setelah beberapa saat\n\n"); 
        fclose(fgettime);
        system("pause");
        system("cls");
        mainpage();
    }
    else
    {
        system("cls");
        datamobil = fopen("datamobil.dat","rb");
        printf("------ List of Ready Cars ------\n\n");
        i = 1;
        while(fread(&carsdata, sizeof(carsdata),1,datamobil)==1)
        {
            printf("Mobil ke-%d\n",i);
            printf("Type        : %s\n",carsdata.tipe); 
            printf("Year        : %s\n",carsdata.tahun); 
            printf("Asurance    : %s\n",carsdata.asuransi);
            printf("Fee/day (Rp): %s\n",carsdata.fee);
            printf("\n");
            i++;
        }
        fclose(datamobil);
        printf("Enter the car's type : ");scanf("%s",&pickcar);system("cls");
        datamobil = fopen("datamobil.dat","rb");
        rentedcar = fopen("rentedcar.dat","ab+");
        cartemp = fopen("cartemp.dat","wb");
        while(fread(&carsdata, sizeof(carsdata),1,datamobil)==1)
        {
		    if (strcmp(carsdata.tipe,pickcar)==0) 
            {
		        fwrite(&carsdata,sizeof(carsdata),1,rentedcar);
	        }
            else fwrite(&carsdata,sizeof(carsdata),1,cartemp);    
        }
        fclose(datamobil);
            fclose(rentedcar);
            fclose(cartemp);
            remove("datamobil.dat");
            rename("cartemp.dat","datamobil.dat");
            //datacustomer();
            system("pause");
            system("cls");
            main();
    }
}

    

//DATA CUSTOMER
void datacustomer()
{
    customer = fopen("datacustomer.dat","ab+");
    printf("Silahkan isi data berikut\n");
    printf("Nama User  : ");fflush(stdin);gets(datacust.userr);
    printf("Nama Penyewa   : ");gets(datacust.nama);
    printf("Alamat Lengkap : ");gets(datacust.alamat);
    printf("No. KTP        : ");gets(datacust.ktp);
    printf("No. SIM        : ");gets(datacust.sim);
    printf("No. KK         : ");gets(datacust.kk);
    printf("No. HP         : ");gets(datacust.hp);
    printf("\n Data pribadi sudah dilengkapi \n\n");

    printf("Tentukan waktu mulai sewa \n");
    printf("Tanggal       : ");gets(datacust.tanggalmulai);
    printf("Bulan         : ");gets(datacust.bulanmulai);
    printf("Tahun         : ");gets(datacust.tahunmulai);
    
    printf("Tentukan waktu pengembalian \n");
    printf("Tanggal       : ");gets(datacust.tanggalkembali);
    printf("Bulan         : ");gets(datacust.bulankembali);
    printf("Tahun         : ");gets(datacust.tahunkembali);
    fwrite(&datacust, sizeof(datacust),1, customer);
    fclose(customer);
    rewind(customer);
    printf("\n\n Data Berhasil Ditambahkan\n\n");
    system("pause");
    system("cls");
    mainpage();
}

//ADMIN PAGE
int adminpage()
{
    //datamobil = fopen("datamobil.txt","r");
    printf("|-------------------------------------------------------|\n");
    printf("|                 ONLY ADMIN CAN ACCESS                 |\n");
    printf("|-------------------------------------------------------|\n");
    printf("|List To Do :                                           |\n");
    printf("|    1. Update Date & Time                              |\n");
    printf("|    2. Add/Remove Cars Stock                           |\n");
    printf("|    3. List of Rented Cars                             |\n");
    printf("|    4. Extend Rent Duration                            |\n");
    printf("|    5. Return Manual                                   |\n");
    printf("|    6. Back                                            |\n");
    printf("|-------------------------------------------------------|\n");
    printf(" Choose the number then pres Enter : ");scanf("%d",&adminmode);
    
    switch (adminmode)
    {
    case 1: gettime();   
    case 2: process();
    case 3: datarent();
    case 6: system("cls");main();break;
    default: system("cls");printf("Menu Not Available\n");
             system("pause");
             system("cls");
             adminpage();
    }
}

//LIST RENTED CARS
void datarent()
{
    system("cls");
    rentedcar = fopen("rentedcar.dat","rb");
    printf("------ List of Rented Cars ------\n\n");
    i = 1;
    while(fread(&carsdata, sizeof(carsdata),1,rentedcar)==1)
    {
        printf("Mobil ke-%d\n",i);
        printf("Type        : %s\n",carsdata.tipe); 
        printf("Year        : %s\n",carsdata.tahun); 
        printf("Asurance    : %s\n",carsdata.asuransi);
        printf("Fee/day (Rp): %s\n",carsdata.fee);
        printf("\n");
        i++;
    }
    fclose(rentedcar);
    printf("---------------------------------\n\n");
    printf("0. Back\n\n");
    printf("Press 0 to go back : ");scanf("%d",back);
    switch (back)
    {
    case 0:
        system("cls");
        adminpage();
    default:
        system("cls");
        printf(" Menu not available\n\n");
        system("pause");
        datarent();
    }

}

//PROCESS DATA
void process()
{
    system("cls");
    printf("------ Car Lists ------\n\n"); 
    datamobil = fopen("datamobil.dat","rb");
    i = 1;
    while(fread(&carsdata, sizeof(carsdata),1,datamobil)==1)
    {
        printf("Mobil ke-%d\n",i);
		printf("Type        : %s\n",carsdata.tipe); 
        printf("Year        : %s\n",carsdata.tahun); 
        printf("Asurance    : %s\n",carsdata.asuransi);
        printf("Fee/day (Rp): %s\n",carsdata.fee);
        printf("\n");
		i++;
	}
    fclose(datamobil);
    printf("------------------------------------\n");
    printf("1. Add Stock\n");
    printf("2. Remove Stock\n");
    printf("3. Back\n");
    printf("\nEnter your choice : ");scanf("%d",&processmode);
    switch (processmode)
    {
    case 1: system("cls");
            printf("Total Car's Data : ");scanf("%d",&totalcar); 
            for (i=1; i<=totalcar; i++) 
            {
            datamobil = fopen("datamobil.dat","ab+");
            printf("Car's Data-%d \n",i);
            printf("Type        : ");fflush(stdin);gets(carsdata.tipe); 
            printf("Year        : ");gets(carsdata.tahun); 
            printf("Asurance    : ");gets(carsdata.asuransi);
            printf("Fee/day (Rp): ");gets(carsdata.fee);
            printf("\n");
            fwrite(&carsdata, sizeof (carsdata), 1, datamobil);
            fclose(datamobil);
            } 
            printf(" Data successfully added!\n\n");
            system("pause");
            system("cls");
            rewind(datamobil);
            process();
            
    case 2: printf("Enter car's type you want to remove : ");scanf("%s",&removecar);
            datamobil = fopen("datamobil.dat","rb");
            cartemp = fopen("cartemp.dat","wb");
            while(fread(&carsdata, sizeof(carsdata),1,datamobil)==1)
            {
		        if (strcmp(carsdata.tipe,removecar)!=0) 
                {
		        fwrite(&carsdata,sizeof(carsdata),1,cartemp);
	            }
            }
            fclose(datamobil);
            fclose(cartemp);
            remove("datamobil.dat");
            rename("cartemp.dat","datamobil.dat");
            system("cls");
            printf(" Data successfully removed!\n\n");
            system("pause");
            system("cls");
            process();
    case 3: system("cls");adminpage();break;
    default:system("cls");printf("Menu Not Available\n");
            system("pause");
            system("cls");
            process();
    }
}

//MASKING PASSWORD
void mask(char *temp)
{
    int key = 0, index = 0;
    do {
        key = getch(); /* Simpan karakter yang ditekan ke dalam variabel key */
        switch (key) {
                /* 0 adalah kode awal untuk tombol fungsi (function key), seperti F1, F2, ..., F12 
                 * Misalkan jika tombol F1 ditekan, maka fungsi getch akan mengembalikan
                 * nilai 0 dan menyimpan sebuah kode yang menandakan tombol F1 ditekan ke buffer.
                 */
            case 0:
                /* 224 adalah kode awal untuk tombol panah, home, page up, page down, end dan lain-lain. 
                 * Misalkan jika tombol panah ditekan, fungsi getch akan 
                 * mengembalikan nilai 224 dan menyimpan sebuah kode
                 * yang menandakan tombol yang ditekan ke buffer.
                 */
            case 224:
                /* Fungsi getch di sini digunakan untuk membersihkan buffer */
                getch();
                break;
                /* Jika tombol back space ditekan, maka mundurkan cursor satu langkah */
            case '\b':
                if (index > 0) {
                    index = index - 1; /* Kurangi index temp sebesar 1 */
                    temp[index] = 0; /* set temp[index] menjadi kosong (NUL) */
                    printf("\b \b"); /* Mundurkan cursor satu langkah */
                }
                break;
            default:
                /* Hanya karakter printable yang dapat ditekan, seperti huruf, angka dan karakter spesial */
                if (key > 31 && key < 127) {
                    temp[index] = key; /* Simpan karakter ke dalam temp[index] */
                    index = index + 1; /* Naikkan nilai index sebesar 1 */
                    printf("*");
                }
        }
        /* 13 adalah kode ASCII untuk karakter enter.
         * Perulangan akan terus dilakukan sampai tombol enter ditekan.
         */
    } while (key != 13);
     
    /* Menambahkan NULL di akhir temp yang menandakan akhir dari sebuah string */
    temp[index] = '\0';
}

//DATE & TIME
void gettime() 
{
    system("cls");
    time_t getdate;
    getdate = time(NULL);
    time (&getdate);
    printf ( "\n The current date/time is: %s", ctime (&getdate));
    fgettime = fopen("gettime.txt","w");
    printf("\nDay      : ");fflush(stdin);gets(t.d);
    printf("Month    : ");gets(t.m);
    printf("Year     : ");gets(t.y);
    fprintf(fgettime,"%s %s %s",t.d, t.m, t.y);
    fclose(fgettime);
    printf("\n\nDate & Time has been Updated\n\n");
    system("pause");
    system("cls");
    adminpage(); 
}
