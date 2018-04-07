#include<conio.h>
#include<iostream.h>
#include <stdlib.h>
#include <fstream.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

double total_price;
int codeS, goodsale =0, firstsale, codeTEMP;
int quantityS;
    void LineDraw()
    {
		unsigned int i;
		for(i=0;i<80;i++)
		{
		     cout<<"-";
		}
     }
     void CodeCheck()
     {

	while(1)
	    {
		 cin>>codeTEMP;
		 if(codeTEMP != 0)
		 {
		   break;
		 }
		 cout<<endl<<"code cannot be 0. Please try again : ";
	    }
	}

class item
{
    unsigned int i;
    char name[30];
    unsigned int code;
    float price;
    unsigned int quantity;
	public:
	void Add_Data()
	{
	    clrscr();
	    cout<<"\nEnter the item name  : ";
	    gets(name);
	    cout<<"\nEnter the item code : ";
	    CodeCheck();
	    code = codeTEMP;
	    cout<<"\nEnter the price of the item  : Rs.";
	    cin>>price;
	    cout<<"\nEnter item quantity  : ";
	    cin>>quantity;
	}

	void UpdateQTY(int a)
	{
	      quantity =a;
	}
	void UpdatePRICE(float a)
	{
	      price =a;
	}
	void UpdateNAME()
	{
	      gets(name);
	}
	void UpdateCODE(int a)
	{
	     code=a;
	}
	void Delete()
	{
	    code = 0;
	    price = 0;
	    quantity = 0;

	}
	void Calculate(int qty, float pc, float tx, char*  nm, int ftime)
	{

	    double temppriceD;
	    if(ftime == 0)
	    {
	    total_price = 0;
	    firstsale++;
	    clrscr();
	    LineDraw();
	    cout <<"\n\t\tYour Invoice\n";
	    LineDraw();
	    cout << "Item Name : " << nm << endl << "Item Price : Rs." << pc << endl << "Item quantity : " << qty <<endl;
	    temppriceD = floor((price * qty + (tx/100 * price*qty))*100+0.5) /100 ;
	    cout << "Items Total Price [including tax " << tx << " %] = Rs." << temppriceD << endl;
	    total_price+=temppriceD;
	    LineDraw();
	    cout << "Current Total Price = Rs." << total_price << endl;
	    LineDraw();
	    }
	    else
	    {
	    cout << "Item Name : " << nm << endl << "Item Price : Rs." << pc << endl << "Item quantity : " << qty <<endl;
	    temppriceD = floor((price * qty + (tx/100 * price*qty))*100+0.5) /100 ;
	    cout << "Items Total Price [including tax " << tx << " %] = Rs." << temppriceD << endl;
	    total_price+=temppriceD;
	    LineDraw();
	    cout << "Current Total Price = Rs." << total_price << endl;
	    LineDraw();
	    }
	}
	void Display(int cdD, float pcD, char* nmD, int qtD, int no)
	{
		LineDraw();
		cout<<"Item number : "<<no<<endl;
		LineDraw();
		cout<<"Item Name : "<<nmD<<endl;
		cout<<"Item Code : "<<cdD<<endl;
		cout<<"Item Price : " <<pcD<<endl;
		cout<<"Item Quantity : "<<qtD<<endl;
		LineDraw();
	}
	unsigned int codeU()
	{
	    return code;
	}
	unsigned int quantityU()
	{
	    return quantity;
	}
	char* nameU()
	{
	    return name;
	}
	float priceU()
	{
	    return price;
	}
}it;

void ModifyQty(int qtyA, int codeA)
{

		fstream f2("data.dat",ios::binary | ios::in|ios::out);
		while(f2)
		{
		     f2.read((char*)&it,sizeof(it));

		     if(codeA == it.codeU())
		     {
		 int pos=f2.tellg();
		 it.UpdateQTY(qtyA);
		 f2.seekp((pos-sizeof(it)));
		 f2.write((char*)&it, sizeof(it));
		 goodsale = 1;
		  break;
		     }
		     else if(f2.eof())
		     {
		f2.write((char*)&it, sizeof(it));
		goodsale=0;
		cout<<"Failed to update quantity. Try again!!"<<endl;
		getch();
		break;
		     }
		 }
		 f2.close();
	    }
void Sale_Item()
	{
	    goodsale = 0;
	    unsigned int Tquantity,  outofstock = 1;
	    cout<<"\nEnter item code : ";
	    cin>>codeS;
	    ifstream of1("data.dat",ios::binary |ios::in);
		while(of1)
		{
			of1.read((char*)&it,sizeof(it));
			if(codeS==it.codeU())
			{
			   Tquantity = it.quantityU();
			   break;
			}
			if(of1.eof())
			{
				cout<<"Item not Found"<<endl;
				goodsale=0;
				getch();
				return;
			}
		}
		 of1.close();
	    cout<<"\nEnter item quantity : "<<endl;
	    while(outofstock != 0)
	    {

		  cin>>quantityS;
		  if(Tquantity == 0)
		 {
			cout<<"There are no more item remaining"<<endl;
			getch();
			quantityS=0;
			goodsale=0;
			getch();
			break;
		 }
		 if(quantityS > Tquantity)
		 {
			cout<<"\nThere are only "<<Tquantity<<" remaining."<<endl<<"Please re-enter item quantity : ";
			quantityS = 0;
			outofstock = 1;
			goodsale=0;
		 }
		 else if(quantityS <= Tquantity)
		 {

		    outofstock=0;
		    goodsale=1;
		 }
	    }
		Tquantity -= quantityS;

		ModifyQty(Tquantity, codeS);
	}



int main()
{

    unsigned int choice, quantityF;
    float priceF;
    float tax = 6.0;
    clrscr();
    while(1)
    {
	clrscr();
	total_price=0;
	cout<<"\n\t\t\tWELCOME TO INVENTORY MANAGEMENT SYSTEM\n";
	LineDraw();
	cout<<"Enter your choice : \n"<<endl<<"\t1.Add a Item"<<endl<<"\t2.Edit\\Delete a Item"<<endl<<"\t3.Sale an Item"<<endl<<"\t4.Change tax rate"<<endl<<"\t5.Display all items"<<endl<<"\t6.Quit"<<endl;
	LineDraw();
	cin>>choice;
		while(choice==1)
		{
			ofstream of1("data.dat",ios::binary |ios::app);
			it.Add_Data();

			of1.write((char*)&it,sizeof(it));
			of1.close();
			break;
		}
		while(choice==2)
		{
		    clrscr();
	    int a;
	    LineDraw();
	    cout<<"What would you like to do ?"<<endl<<"\t1.Edit a item"<<endl<<"\t2.Delete a item"<<endl<<"\t3.Back to main menu"<<endl;
	    LineDraw();
	    cout<<"\nYour choice : ";
	    cin>>a;
	    while(a==1)
	    {
		LineDraw();
		int b;
		int codeE, qtyE;
		char nameE;
		float priceE;
		cout<<"What would you like to do ?"<<endl<<"\t1.Add more quantity to an item"<<endl<<"\t2.Edit item's price"<<endl<<"\t3.Edit item's name"<<endl<<"\t4.Back to Menu"<<endl;
		LineDraw();
		cout<<endl<<"Your choice : ";
		cin>>b;
		while(b==1)
		{
		    LineDraw();
		    cout<<"Enter Item Code : ";
		    cin>>codeE;
		    fstream f1("data.dat",ios::binary | ios::in|ios::out);
		    while(f1)
		    {
			 f1.read((char*)&it,sizeof(it));

			 if(codeE == it.codeU())
			 {
			     int pos=f1.tellg();
			     cout<<endl<<it.codeU()<< ":"<<it.nameU()<< " item's current quantity is "<<it.quantityU()<<endl<<"Enter new item quantity : ";
			     cin>>qtyE;
			     it.UpdateQTY(qtyE);
			     f1.seekp((pos-sizeof(it)));
			     f1.write((char*)&it, sizeof(it));
			     cout<<endl<<"Item's quantitiy successfully updated."<<endl;
			     getch();
			     break;
			 }
			 else if(f1.eof())
			 {
			    f1.write((char*)&it, sizeof(it));
			    cout<<endl<<"Failed to update quantity. Try again!!"<<endl;
			    getch();
			    break;
			 }
		     }
		     f1.close();
		     break;
		}
		while(b==2)
		{
		    LineDraw();
		    cout<<"Enter Item Code : ";
		    cin>>codeE;
		    fstream f1("data.dat",ios::binary | ios::in|ios::out);
		    while(f1)
		    {
			 f1.read((char*)&it,sizeof(it));

			 if(codeE == it.codeU())
			 {
			     int pos=f1.tellg();
			     cout<<endl<<it.codeU()<< ":"<<it.nameU()<< " item's current price is Rs. "<<it.priceU()<<endl<<"Enter new item's price : Rs."<<endl;
			     cin>>priceE;
			     it.UpdatePRICE(priceE);
			     f1.seekp((pos-sizeof(it)));
			     f1.write((char*)&it, sizeof(it));
			     cout<<endl<<"Item's price successfully updated."<<endl;
			     getch();
			     break;
			 }
			 else if(f1.eof())
			 {
			    f1.write((char*)&it, sizeof(it));
			    cout<<endl<<"Failed to update price. Try again!!"<<endl;
			    getch();
			    break;
			 }
		     }
		     f1.close();
		     break;
		}
		while(b==3)
		{
		    LineDraw();
		    cout<<"Enter Item Code : ";
		    cin>>codeE;
		    fstream f1("data.dat",ios::binary | ios::in|ios::out);
		    while(f1)
		    {
			 f1.read((char*)&it,sizeof(it));

			 if(codeE == it.codeU())
			 {
			     int pos=f1.tellg();
			     cout<<endl<<it.codeU()<< " item's current name is "<<it.nameU()<<endl<<"Enter item's new name :";
			     it.UpdateNAME();
			     f1.seekp((pos-sizeof(it)));
			     f1.write((char*)&it, sizeof(it));
			     cout<<endl<<"Item's name successfully updated."<<endl;
			     getch();
			     break;
			 }
			 else if(f1.eof())
			 {
			    f1.write((char*)&it, sizeof(it));
			    cout<<endl<<"Failed to update name. Try again!!"<<endl;
			    getch();
			    break;
			 }
		     }
		     f1.close();
		     break;
		}
		if(b==4)
		{
		    break;
		}
	    }
	    while(a==2)
	    {
		LineDraw();
		int codeE;
		cout<<"Enter Item Code to Delete : ";
		cin>>codeE;
		fstream f1("data.dat",ios::binary | ios::in|ios::out);
		   while(f1)
		    {
			 f1.read((char*)&it,sizeof(it));

			 if(codeE == it.codeU())
			 {
			     int pos=f1.tellg();
			     f1.seekp((pos-sizeof(it)));
			     it.Delete();
			     f1.write((char*)&it, sizeof(it));
			     cout<<endl<<"Item deleted."<<endl;
			     getch();
			     break;
			 }
			 else if(f1.eof())
			 {
			    f1.write((char*)&it, sizeof(it));
			    cout<<endl<<"Not found. Try again!!"<<endl;
			    getch();
			    break;
			 }
		     }
		     f1.close();
		     break;
	    }
	    if(a==3)
	    {
		break;
	    }
	    }
		while(choice==3)
		{
	    firstsale = 0;
	    int firstsaleA = 0;
	    while(1)
	    {

			    if(firstsaleA != 0)
			    {
			       char a;
			       cout<<endl<<"Do you want to buy another item ? (Y/N)"<<endl;
			       cin>>a;
			       if(a != 'y' && a !='Y')
			       {
				       break;
			       }
			    }
			    else
			     clrscr();
			    firstsaleA++;
			    ifstream of1("data.dat",ios::binary);
			    Sale_Item();
			    if(quantityS <= 0 || goodsale !=1 )
				 {
					 continue;
				 }


				char* nameFF;
				while(of1)
				{
					of1.read((char*)&it,sizeof(it));

					if(codeS ==it.codeU())
					{
						nameFF = it.nameU();
						quantityF = quantityS;
						priceF = it.priceU();
						break;
					}

					if(of1.eof())
					{
						cout<< "not found";
						getch();
						continue;
					}

				}

				if(priceF)
				{
					it.Calculate(quantityF,priceF,tax,nameFF,firstsale);
				}
			}
		     cout<<"\nThanks you for purchasing. Your total price is : Rs."<<total_price<<endl;
		     getch();
		     break;
		}
		if(choice==4)
		{
			cout<<"\nEnter new tax rate : ";
			cin>>tax;
		}
		while(choice==5)
		{
				clrscr();
				unsigned int counter = 0;
				ifstream of1("data.dat",ios::binary);
				while(of1)
				{
					of1.read((char*)&it,sizeof(it));
					if(it.codeU() != 0)
					{
						counter++;
						it.Display(it.codeU(), it.priceU(), it.nameU(),it.quantityU(), counter);
					}
					if(of1.eof())
					{
						break;
					}

				}
				getch();
				break;


		}
		if(choice==6)   {
		exit(0);
		}
    }
}
