//FILE HEADER YANG DIGUNAKAN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

//VARIABLE GLOBAL
char count, temp;
char string[255];
char username[32];
char password[16];
char fusername[32];
char fpassword[16];
char fdatamobil[255];
int mode = 0, mode1 = 0, mode2 = 0, matching=0, matchlog = 0, 
count_lines=0, line_number = 1, j=1, times, pick, pick1, i, k, n, oneset;

//STRUCT
struct {
        char tipe[50], tahun[16], asuransi[32], fee[16];  
    }carsdata[100];
struct {
        char d[2], m[2], y[4];
    }inputwaktu[100];
struct {
        char nama[50], alamat[50], ktp[20], sim[20], kk[20], 
        tanggal[32], bulan[32], tahun[32], duration[32];  
    }datacustomer[100];

//PROTOTYPE FUNGSI
int gettime();
int reg_page();
int log_page();
int main_page();
int admin_page();

//PROTOTYPE PROSEDUR
void mask();
void case1();
void case2();
void case3();
void addrmv();
void data_customer();


// FILE GLOBAL
FILE *fpoint;
FILE *custpoint;
FILE *datamobil;
FILE *datamobil1;
FILE *ambilwaktu;


//FRONT PAGE
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
    printf("Choose the number then press Enter : ");scanf("%d",&mode);
    //KONDISI PERCABANGAN UNTUK MODE
    switch (mode)
    {
        case 1: reg_page();
        case 2: log_page();
        case 3: ambilwaktu = fopen("ambilwaktu.txt","w");return 0;break;
        default: system("cls");printf("Menu Not Available\n");
        system("pause");
        system("cls");
        main();
    }
}

//MAIN PAGE
int main_page()
{
    datamobil = fopen("datamobil.txt","r");    //OPEN FILE MODE READ
    ambilwaktu = fopen("ambilwaktu.txt","r");
    printf("\n|        ######    Welcome to D'RENT    ######          |\n");
    printf("|-------------------------------------------------------|\n");
    printf("|            A Place for you to rent a car              |\n");
    printf("|-------------------------------------------------------|\n");
    printf("|    1. Rent a Car                                      |\n");
    printf("|    2. Check Rent Status                               |\n");
    printf("|    3. Exit Program                                    |\n");
    printf("|-------------------------------------------------------|\n");
    printf(" Choose the number then pres Enter : ");scanf("%d",&mode1);
    switch (mode1)
    {
        case 1: fclose(datamobil);case1();
        case 2: fclose(datamobil);case2();
        case 3: fclose(datamobil);ambilwaktu = fopen("ambilwaktu.txt","w");return 0;break;
        default:fclose(datamobil);system("cls");printf("Menu Not Available\n");
        system("pause");
        system("cls");
        main_page();
    }
    fclose(datamobil);
}

//ADMIN PAGE
int admin_page()
{
    datamobil = fopen("datamobil.txt","r");
    printf("|-------------------------------------------------------|\n");
    printf("|                 ONLY ADMIN CAN ACCESS                 |\n");
    printf("|-------------------------------------------------------|\n");
    printf("|List To Do :                                           |\n");
    printf("|    1. Update Date & Time                              |\n");
    printf("|    2. Add/Remove Cars Stock                           |\n");
    printf("|    3. List of Rented Cars                             |\n");
    printf("|    4. Back                                            |\n");
    printf("|-------------------------------------------------------|\n");
    printf(" Choose the number then pres Enter : ");scanf("%d",&mode2);
    switch (mode2)
    {
    case 1: fclose(datamobil);gettime();   
    case 2: fclose(datamobil);addrmv();
    case 4: fclose(datamobil);system("cls");main();break;
    default: fclose(datamobil);system("cls");printf("Menu Not Available\n");
             system("pause");
             system("cls");
             admin_page();
    }
    fclose(datamobil);
}

//REGISTER PAGE
int reg_page()
{
    matching=0;
    system("cls");
    printf("             ==== Register Page ====\n");
    printf("-------------------------------------------------\n");
    printf("Enter Username : ");scanf("%s",&username);
    printf("Enter Password : ");mask(password);
    fpoint = fopen("datareg.txt","a+");
    while ((fscanf(fpoint, "%s %s ",&fusername,&fpassword))!=EOF)
    {
        if (strcmp(username,fusername)==0)
        {
            matching=1;
            break;
        }
    }

    if (matching==1)
    {
        printf("\n\n* Username already taken, Try again with different username :)\n\n");
        system("pause");
        reg_page();
    }
    else
    {
        fprintf(fpoint,"%s %s ",username,password);
        printf("\n\n* Username successfully Registered\n\n");
        fclose(fpoint);
        system("pause");
        system("cls");
        main();
    }
}

//LOGIN PAGE
int log_page()
{
    system("cls");
    matchlog=0;
    printf("             ==== Login Page ====\n");
    printf("-------------------------------------------------\n");
    printf("Enter Username : ");scanf("%s",&username);
    printf("Enter Password : ");mask(password);
    if (strcmp(username, "admin")==0 && strcmp(password,"admin")==0)
    {
        printf("\n\n  Login Successfull! \n\n");
        system("pause");
        system("cls");
        admin_page();
        return 0;
    }
    fpoint = fopen("datareg.txt","r");
    while ((fscanf(fpoint, "%s %s ",&fusername,&fpassword))!=EOF)
    {
        if (strcmp(username,fusername)==0 && strcmp(password,fpassword)==0)
        {
            custpoint = fopen("datacustomer.txt","a+");
            fprintf(custpoint,"Nama User : %s\n",username);
            fclose(custpoint);
            printf("\n\n Login Successfull! \n\n");
            matchlog=1;
            system("pause");
            system("cls");
            main_page();
            break; 
        }
    }
    
    if (matchlog!=1)
    {
        printf("\n\n Username atau password salah\n");
        printf("      Silahkan coba lagi\n\n");
        system("pause");
        system("cls");
        log_page();
    }
    fclose(fpoint);
}

//DATE & TIME
int gettime() 
{
    system("cls");
    time_t getdate;
    getdate = time(NULL);
    time (&getdate);
    printf ( "\n The current date/time is: %s", ctime (&getdate));
    ambilwaktu = fopen("ambilwaktu.txt","w");
    printf("\nDay      : ");fflush(stdin);gets(inputwaktu->d);
    printf("Month    : ");gets(inputwaktu->m);
    printf("Year     : ");gets(inputwaktu->y);
    fprintf(ambilwaktu,"%s, %s, %s",inputwaktu->d, inputwaktu->m, inputwaktu->y);
    fclose(ambilwaktu);
    printf("\n\nDate & Time has been Updated\n\n");
    system("pause");
    system("cls");
    admin_page(); 
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

//DATA CUSTOMER
void data_customer()
{
    custpoint = fopen("datacustomer.txt","a+");
    printf("Silahkan isi data berikut\n");
    printf("Nama Peminjam  : ");fflush(stdin);gets(datacustomer->nama);
    fprintf(custpoint,"Nama Peminjam  : %s\n",datacustomer->nama);
    printf("Alamat Lengkap : ");gets(datacustomer->alamat);
    fprintf(custpoint,"Alamat Lengkap : %s\n",datacustomer->alamat);
    printf("No. KTP        : ");gets(datacustomer->ktp);
    fprintf(custpoint,"No. KTP        : %s\n",datacustomer->ktp);
    printf("No. SIM        : ");gets(datacustomer->sim);
    fprintf(custpoint,"No. SIM        : %s\n",datacustomer->sim);
    printf("No. KK         : ");gets(datacustomer->kk);
    fprintf(custpoint,"No. KK         : %s\n",datacustomer->kk);
    printf("\n Data sudah dilengkapi \n\n");
    printf("Tentukan waktu penyewaan \n");
    printf("Tanggal       : ");gets(datacustomer->tanggal);
    fprintf(custpoint,"Tanggal        : %s\n",datacustomer->tanggal);
    printf("Bulan         : ");gets(datacustomer->bulan);
    fprintf(custpoint,"Bulan          : %s\n",datacustomer->bulan);
    printf("Tahun         : ");gets(datacustomer->tahun);
    fprintf(custpoint,"Tahun          : %s\n",datacustomer->tahun);
        
    printf("Tentukan waktu pengembalian \n");
    printf("Tanggal       : ");gets(datacustomer->tanggal);
    fprintf(custpoint,"Tanggal        : %s\n",datacustomer->tanggal);
    printf("Bulan         : ");gets(datacustomer->bulan);
    fprintf(custpoint,"Bulan          : %s\n",datacustomer->bulan);
    printf("Tahun         : ");gets(datacustomer->tahun);
    fprintf(custpoint,"Tahun          : %s\n\n",datacustomer->tahun);
    printf("Durasi (hari) : ");gets(datacustomer->duration);
    fprintf(custpoint,"Durasi (hari)  : %s\n",datacustomer->duration);    
    fclose(custpoint);
    printf("\n\n Data Berhasil Ditambahkan\n");
    system("pause");
    system("cls");
}

//CASE1
void case1()
{
    for (count = getc(datamobil); count != EOF; count = getc(datamobil))
    if (count == '\n')
    count_lines = count_lines + 1;
    fclose(datamobil);
    datamobil = fopen("datamobil.txt","r");
    if ( (times=fgetc(ambilwaktu)) == EOF)  
    {
        system("cls");
        printf("Maaf Toko Sedang Tutup :(\n");
        printf("  Coba Lagi Setelah beberapa saat\n\n"); 
        fclose (ambilwaktu);
        system("pause");
        system("cls");
        main_page();
    }
    else if (fgets(string, sizeof(string), datamobil) == NULL)
    {
        system("cls");
        printf("------ List of Ready Cars ------\n\n");
        printf("There is no Datas yet,\n    Kindly wait for the update :D \n\n");
        system("pause");
        system("cls");
        main_page();
    }
    else
    {
    	count_lines = 0;
    	for (count = getc(datamobil); count != EOF; count = getc(datamobil))
    	if (count == '\n')
    	count_lines = count_lines + 1;
    	fclose(datamobil);
        system("cls");
        datamobil = fopen("datamobil.txt","r");
        printf("------ List of Ready Cars ------\n\n");
        // = count_lines/4;
        j = 1;
        for (i=0; i <= count_lines; i++)
        {
            printf("Mobil ke-%d\n",j);
            fgets(fdatamobil, sizeof(fdatamobil), datamobil);
            printf("%s\n",fdatamobil);
            j=j+1;
        }
        fclose(datamobil);
        printf("Choose the number then press Enter : ");scanf("%d",&pick);system("cls");
        switch (pick)
        {
        case 1:
            for (k=1; k <= (count_lines/count_lines);k++)
            {
            	datamobil = fopen("datamobil.txt","r");
                custpoint = fopen("datacustomer.txt","a+");
                fgets(fdatamobil, sizeof(fdatamobil), datamobil);
                printf("You Choose %s\n",fdatamobil);
                fprintf(custpoint, "%s",fdatamobil);
                fclose(custpoint);
                fclose(datamobil);
                data_customer();
            }
            break;
            
        case 2:
            for (k=1; k <= (count_lines); k++)
            {
                fgets(fdatamobil, sizeof(fdatamobil), datamobil);
                printf("You Choose %s\n",fdatamobil);
                system("cls");
                if (k==3)
                {
                    fgets(fdatamobil, sizeof(fdatamobil), datamobil);
                    printf("You Choose %s\n",fdatamobil);
                    data_customer();
                }   
            }
            break;

        case 3:
            for (k=1; k <= (count_lines); k++)
            {
                fgets(fdatamobil, sizeof(fdatamobil), datamobil);
                printf("You Choose %s\n",fdatamobil);
                system("cls");
                if (k==6)
                {
                    fgets(fdatamobil, sizeof(fdatamobil), datamobil);
                    printf("You Choose %s\n",fdatamobil);
                    data_customer();
                }  
            }
            break;
        }
    }
}

//CASE2
void case2()
{
    
}

//ADD REMOVE
void addrmv()
{
    system("cls"); count_lines = 0; j=1;
    printf("------ Car Lists ------\n\n");
    datamobil = fopen("datamobil.txt","r");
    for (count = getc(datamobil); count != EOF; count = getc(datamobil))
    if (count == '\n') // Increment count if this character is newline
    count_lines = count_lines + 1;
    fclose(datamobil);
    datamobil = fopen("datamobil.txt","r");
    //oneset = count_lines/4;
    for (i=0; i < count_lines; i++)
    {
        printf("Mobil ke-%d\n",j);
        fgets(fdatamobil, sizeof(fdatamobil), datamobil);
        printf("%s\n",fdatamobil);
        j=j+1;
    }
    fclose(datamobil);
    printf("------------------------------------\n");
    printf("1. Add Stock\n");
    printf("2. Remove Stock\n");
    printf("3. Back\n");
    printf("\nEnter your choice : ");scanf("%d",&mode2);
    switch (mode2)
    {
    case 1: system("cls");
            printf("Total Car's Data : ");scanf("%d",&n); 
            for (i=1; i<=n; i++) 
            {
            datamobil = fopen("datamobil.txt","a+");
            custpoint = fopen("datacustomer.txt","a+");
            printf("Car's Data-%d \n",i);
            printf("Type        : ");fflush(stdin);gets(carsdata[i].tipe);
			fprintf(custpoint,"You choose type : %s",carsdata[i].tipe);fclose(custpoint); 
            printf("Year        : ");gets(carsdata[i].tahun); 
            printf("Asurance    : ");gets(carsdata[i].asuransi);
            printf("Fee/day (Rp): ");gets(carsdata[i].fee);
            printf("\n");
            fprintf(datamobil,"Tipe : %s\tYear : %s\tAsurance : %s\tFee/day (Rp): %s\n",
            carsdata[i].tipe,carsdata[i].tahun,carsdata[i].asuransi,carsdata[i].fee);
            //fprintf(datamobil,"Type     : %s\nYear     : %s\nAsurance : %s\nFee/day (Rp): %s\n",
            //carsdata[i].tipe,carsdata[i].tahun,carsdata[i].asuransi,carsdata[i].fee);
            fclose(datamobil);
            } 
            printf(" Data berhasil ditambahkan\n\n");
            system("pause");
            system("cls");
            addrmv();
    case 2: printf("Type car number you want to remove : ");scanf("%d",&pick1);
            char *filename;
            filename = "datamobil.txt";
            datamobil = fopen(filename,"r");
            datamobil1 = fopen("replica.tmp","w");
    while (temp != EOF) {
    temp = getc(datamobil);	
    if (temp == '\n')
    line_number++;
    if (line_number != pick1){
    putc(temp, datamobil1); 
       } 
    }

    fclose(datamobil1);
    fclose(datamobil);    
    remove("datamobil.txt");
    rename("replica.tmp", "datamobil.txt");
    system("pause");
    addrmv();
            
    case 3: system("cls");admin_page();break;
    default:system("cls");printf("Menu Not Available\n");
            system("pause");
            system("cls");
            addrmv();
        
    }    
}
