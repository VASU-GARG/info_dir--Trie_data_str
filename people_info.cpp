//TITLE: PEOPLE INFORMATION DIRECTORY USING TRIE
// MADE BY : VASU GARG , 20BCE0451

#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<cstdio>
#include<process.h>
#include <string.h>
#include <sstream>
#include <iomanip.h> 
#include <math.h> 
#include<map>
#include<fstream>
#include "windows.h"


using namespace std;

map<string, long long int> contacts;
map<string,string>address1;

//defining a structure 
//ch is an array of pointer
//islast is a boolean variable used to check if 
//we have reached end of a name or not
//if islast=True ---> end of a name
//if islast=False---> not the end of name

struct trie{
	struct trie *ch[26];
	bool islast;
};

//structure to attach a node with 26 other empty nodes
struct trie* getnode(void)
{
	struct trie* p=new trie;
	for(int i=0;i<26;i++)
	p->ch[i]=NULL;
	p->islast=false;
}

//root is a pointer which will point to the main node
struct trie *root=getnode();


//function to add a new contact
void add(string key)  
{
	struct trie *temp=root; // temp will initially point to the root node.
	for(int i=0;i<key.length();i++)     
	{
		int id=key[i]-'a'; 
		//if the node with the character key[i] is NULL
		//than it will make 26 new NULL nodes and attach it with node key[i]
		if(temp->ch[id]==NULL) 
		{  
			temp->ch[id]=getnode();
		}
		
		//temp will now point to the node having character key[i]
		temp=temp->ch[id];
	}
	temp->islast=true;
}


void get_sug(struct trie *cur,string prefix)
{
	if(cur->islast==true)
	cout<<prefix<<"  ------>  "<<contacts[prefix]<<"  ------>  "<<address1[prefix]<<"\n";
	for(int i='a';i<='z';i++)
	{
		struct trie *next=cur->ch[i-'a'];
		if(next!=NULL)
		get_sug(next,prefix+(char)i);
	
	}
}


//function to display the contacts on the basis of prefix.
void displaycontacts(string str)
{
	string prefix="";
	int i;
	struct trie *prev=root;
	for(i=0;i<str.length();i++)
	{
		prefix+=str[i];
		int id=prefix[i]-'a';
		struct trie *current=prev->ch[id];
		//if the node pointed by pointer current is NULL
		//it means no name with that prefix
		if(current==NULL)
		{
			i++;
			cout<<"Not found";
			break;
		}

		//if nodes of all the characters in the prefix are present in the tree
		//than it will search for the contacts with that prefix
		if(i==str.length()-1)
		{
		cout<<"\n\n";
		cout<<"The contacts available with the prefix  "<<prefix<<" are\n\n";

		//function to get all the suugessions
		get_sug(current,prefix);
		}
		prev=current;
	}
}


//function to display all the contacts
void displayAllContacts()
{
	system("cls");
	int i,j;
	fstream file;
	file.open("info.dat",ios::in);
	char line[100];
	string name="";
	string phn="";
	string address="";
	int index=0;
	//checking from start to end of file
	while(file.eof()==0)
	{
		name="";
		phn="";
		address="";
        file.getline(line,80);
		
	
	// storing the name in variable name
	for(i=0;i<strlen(line);i++)
	{
		if(line[i]=='-')
		{
			index = i;
			break;
		}
		else{
			name+=line[i];
		}
		
	}

	//storing the phone no. in var phn
	for(i=index+1;i<strlen(line);i++)
	{
		if(line[i]==':')
		{
			index = i;
			break;
		}
		else{
			phn+=line[i];
		}
	}

	//storing the address in the variable address
	for(i=index+1;i<strlen(line);i++)
	{
		address+=line[i];
	}


	//printing name,phone no. and address
	cout<<name<<endl;
	cout<<phn<<endl;
	cout<<address<<endl<<endl;
	cout<<"-------------------";
	cout<<endl;
	}
	file.close();


}


//main function begins
int main()
{

	ifstream file("info.dat");
	char line[80];
    string name1="";
	string phn="";
	string address="";
	int i,j,index;
	

	//implementing the names already stored in the file to the trie tree
	while(file.eof()==0)
	{
        name1="";
        phn="";
		address="";
        file.getline(line,80);
        for(i=0;i<strlen(line);i++)
        {

            if(line[i]=='-')
            {
                index =i;
                break;
            }
            else{
            name1+=line[i];
            }
        }
		for(i=index+1;i<strlen(line);i++)
		{
			if(line[i]==':')
			{
				index = i;
				break;
			}
			else{
				phn+=line[i];
			}
		}
		for(i=index+1;i<strlen(line);i++)
		{
			address+=line[i];
		}

		char* endptr = NULL;
        long long int phn_no = strtoll(phn.c_str(), &endptr, 10);
		add(name1);
		contacts[name1]=phn_no;
		address1[name1]=address;

	}
	file.close();

	system("color 4f");
	char option;
	do
	{
		system("cls");
		string name,choice,address;
		string search;
		long long int phno;

		//entering the contact's name

		system("cls");
		cout<<"PRESS 1 TO ADD A CONTACT"<<endl;
		cout<<"PRESS 2 TO SEARCH A CONTACT"<<endl;
		cout<<"PRESS 3 TO SEE YOUR CONTACT'S LIST"<<endl;
		cout<<"PRESS 4 TO EXIT"<<endl;
		cout<<"\n\n\tPlease Select Your Option (1-4) ";
	    option=getch();

		fstream file;
		switch (option)
		{
		case '1':
			system("cls");
			cout<<"ENTER THE CONTACT'S NAME-:  ";
		    cin>>name;
			cout<<"ENTER THE PHONE NUMBER OF THE CONTACT-:  ";
			cin>>phno;
			cout<<"ENTER THE ADDRESS -: ";
			cin.ignore();
			getline(cin,address);
			

			//opening the file and adding all the details in it
			file.open("info.dat",ios::out|ios::app);
			file.write(name.data(),name.size());
			file<<"-";
			file<<phno;
			file<<':';
			file.write(address.data(),address.size());
			file<<endl;
			file.close();
			add(name);
			contacts[name]=phno;
			address1[name]=address;
			cout<<"\n\ncontact information added.\n\n\nPress any key to go back to main menu";
			getch();
			break;
		
		case '2' :
			system("cls");
			
			cout<<"\nName or Prefix of the contact's name you want to search - ";
			cin>>search;
			system("cls");
			displaycontacts(search);
			cout<<"\n\npress any key to go back to main menu";
			getch();
			break;

		case '3':
			system("cls");
			displayAllContacts();
			cout<<"All contacts displayed. Press any key to go back to main menu";
			getch();
			break;

		
		case '4':
			exit(0);
			break;

		
		default:
			exit(0);
			break;
		}
		// getch();

	}while(option!='4');
	
}
// main function ends


		



