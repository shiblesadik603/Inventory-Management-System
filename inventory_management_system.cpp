
#include<bits/stdc++.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
#include <cstdlib>

using namespace std;

class item//class used
{
    int itemno;
    char iname[50];
    float price,qnt,tax,dis;
public:
    void getdata()
    {
        system("cls");
        cout << "/nPlease Enter The Item No. of The Item --> \t";
        cin >> itemno;
        cout << "/nPlease Enter The Name of The Item --> \t";
        cin >> iname;
        cout << "/nPlease Enter The Price of The Item --> \t";
        cin >> price;
        cout << "/nPlease Enter The Discount (%) --> \t";
        cin >> dis;
    }

    void showdata()
    {
        system("cls");
        cout << "\nThe Item No. of the Item : "<<itemno;
        cout << "\nThe Name of the Item : "<<iname;
        cout << "\nThe Price of the Item : "<<price;
        cout << "\nDiscout : "<<dis;
    }

    int retitemno()
    {
        return itemno;
    }
    float retprice()
    {
        return price;
    }

    char* retiname()
    {
        return iname;
    }
    int retdis()
    {
        return dis;
    }
};//class end here

fstream f;
item i;

void write_to_file()
{
    f.open("store.dat",ios::out|ios::app);
    i.getdata();
    f.write((char*)&i,sizeof(i));
    f.close();
    cout << "\n\nThe Item Has Been Created ";
    //getch();
}

void disp_all()//function to read all records from file
{
    system("cls");
    cout << "\n\n\n\t\tDISPLAY ALL RECORDS !!!\n\n";
    f.open("store.dat",ios::in);
    while(f.read((char*)&i,sizeof(i)))
    {
        //i.showdata();
        cout <<i.retitemno()<<"\t\t"<<i.retiname()<< "\t\t" <<i.retprice() << "\n";
        cout << "\n\n=================================\n";
        //getch();
    }
    f.close();
    cout << "Enter 0 to go back main menu!";
    int user;
    cin>>user;

}

void menu()//function to display all products price list
{
    system("cls");
    f.open("store.dat",ios::in);
    if(!f)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\nGo To Admin Menu to Create File";
        cout << "\n\n\n Program is closing .....";
        //getch();
        exit(0);
    }

    cout << "\n\n\t\t ITEM MENU\n\n";
    cout << "===============================================\n";
    cout << "ITEM.NO.\t\tNAME\t\tPRICE\n";
    cout << "===============================================\n";

    while(f.read((char*)&i,sizeof(i)))
    {
        cout <<i.retitemno()<<"\t\t"<<i.retiname()<< "\t\t" <<i.retprice() << "\n";
    }
    f.close();
}


void display_sp(int n)//function to read sepcific record from file
{
    int flag=0;
    f.open("store.dat",ios::in);
    while(f.read((char*)&i,sizeof(i)))
    {
        if(i.retitemno()==n)
        {
            system("cls");
            i.showdata();
            flag=1;
        }
    }
    f.close();
    if(flag==0)
    {
        cout << "\n\nRecord does not exist";
    }
    //getch();
}

void modify()//function to modify record of file
{
    int no,found=0;
    system("cls");
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Item No. of The Item";
    cin >> no;
    f.open("store.dat",ios::in|ios::out);
    while(f.read((char*)&i,sizeof(i)) && found==0)
    {
        if(i.retitemno()==no)
        {
            i.showdata();
            system("cls");

            cout << "\nPlease Enter The New Details of The Item" << "\n";
            i.getdata();
            int pos=-1*((int)sizeof(i));
            f.seekp(pos,ios::cur);
            f.write((char*)&i,sizeof(i));
            cout << "\n\n\t Record Updated";
            found=1;
        }
    }
    f.close();
    if(found==0)
    {
        cout << "\n\n Record Not Found ";
    }
    //getch();
}

void deleterec()//function to delete record of file
{
    int no;
    system("cls");
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The Item No. of The Item You Want To Delete";
    cin >> no;
    f.open("store.dat",ios::in|ios::out);
    fstream f2;
    f2.open("temp.dat",ios::out);
    f.seekg(0,ios::beg);
    while(f.read((char*)&i,sizeof(i)))
    {
        if(i.retitemno()!=no)
        {
            f2.write((char*)&i,sizeof(i));
        }
    }
    f2.close();
    f.close();
    remove("store.dat");
    rename("temp.dat","store.dat");
    cout << "\n\n\tRecord Deleted ..";
    //getch();
}


void place_order()//function to place order and generate bill
{
    system("cls");

    int order_arr[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='Y';
    menu();
    cout << "\n=========================";
    cout << "\n   PLACE YOUR ORDER";
    cout << "\n=========================\n";
    do
    {
        cout << "\n\nEnter The Item No. Of The Item : \n";
        cin >> order_arr[c];
        cout << "\nQuantity In Number : \n";
        cin >> quan[c];
        c++;
        cout << "\nDo You Want To Order Another Item ? (y/n) \t";
        cin >> ch;
    }
    while(ch=='y'||ch=='Y');
    cout << "\n\nThank You For Placing The Order";//getch();
    system("cls");
    cout << "\n\n************INVOICE************\n";
    cout << "\nItem No.\tName\tQuantity \tPrice \tAmount \tAmount After Discount\n";
    for(int x=0; x<=c; x++)
    {
        f.open("store.dat",ios::in);
        f.read((char*)&i,sizeof(i));
        while(!f.eof())
        {
            if(i.retitemno()==order_arr[x])
            {
                amt=i.retprice()*quan[x];
                damt=amt-(amt*i.retdis()/100);
                cout << "\n" << order_arr[x]<<"\t"<<quan[x]<< "\t\t"<<i.retprice()<<"\t"<<amt<<"\t\t"<<damt;
                total+=damt;
            }
            f.read((char*)&i,sizeof(i));
        }
        f.close();
    }
    cout << "\n\n\t\t\t\t\tTOTAL = "<< total;
    //getch();
}

void admin_menu()
{
    system("cls");
    char ch2;
    cout << "\n\n\tADMIN MENU";
    cout << "\n\t1.CREATE ITEM";
    cout << "\n\t2.DISPLAY ALL ITEMS";
    cout << "\n\t3.QUERY ";
    cout << "\n\t4.MODIFY ITEM";
    cout << "\n\t5.DELETE ITEM";
    cout << "\n\t6.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-6) \t";
    cin >> ch2;
    switch(ch2)
    {
    case '1':
        system("cls");
        write_to_file();
        break;
    case '2':
        disp_all();
        getchar();
        break;
    case '3':
        int num;
        system("cls");
        cout << "\n\n\tPlease Enter The Item No. ";
        cin >> num;
        display_sp(num);
        break;
    case '4':
        modify();
        break;
    case '5':
        deleterec();
        break;
    case '6':
        menu();
        //getch();
        break;
    default:
        cout <<"\a";
        admin_menu();
    }
}


int main()
{
    char ch;
    do
    {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t 1. CUSTOMER";
        cout << "\n\n\t 2. ADMINISTRATOR";
        cout << "\n\n\t 3. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3) \t";
        cin >> ch;
        switch(ch)
        {
        case '1':
            system("cls");
            place_order();
            //getch();
            break;
        case '2':
            admin_menu();
            break;
        case '3':
            exit(0);
            break;
        default :
            cout<< "\a";
        }
    }
    while(ch!='3');
    return 0;
}

