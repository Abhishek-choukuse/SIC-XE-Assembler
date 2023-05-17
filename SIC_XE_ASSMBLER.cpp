#include<bits/stdc++.h>
using namespace std;

class assemble
{
	int pc,base,locctr,i,j,k,found;
	static int length,modification;
	string format4="11111111111111111111111111111111",format3="111111111111111111111111",format2="1111";
	string format4final="",format3final="",format1="11111111";
	string text="T000000************************************************************";
	
	void print_text_record()
	{
		string string1,str,str1;
		int size=0,pointer=9,space=0,printed=0;
		ifstream intake("input1.txt");
		intake.seekg(0);
		getline(intake,string1);
		ofstream outtake("OUTPUT.txt",ios::app);
		cout<<"Source code assembled succesfully!! Please check the file - ";
		cout<<"OUTPUT.txt to see the object program "<<endl;
		outtake<<"H"<<string1.substr(0,6)<<"000000"<<uppercase<<hex<<setfill('0')<<setw(6)<<length<<endl;
		ifstream in("TEXT_RECORD.txt");
		in.seekg(0);
		while(in.eof()==0) //traversing through the TEXT_RECORD file to print the object program
		{
			getline(in,str);
			if(str.length()==6 && space==0) //printing the text record when a gap is encountered in the object codes
			{
				space++;
				stringstream ss;
		        ss<<uppercase<<hex<<setfill('0')<<setw(2)<<(size/2);
		        str1=ss.str();
	        	text[7]=str1[0];
	        	text[8]=str1[1];
	        	outtake<<text.substr(0,size+9)<<endl;
	        	for(i=1 ; i<=6 ; i++)
	        	{
	        		text[i]=str[i-1];
				}
				size=0;
				pointer=9;
				printed=1;
			}
			else if(str.length()>6)
			{
				if(space>0)
				{
					for(i=1 ; i<=6 ; i++)
					{
						text[i]=str[i-1];
					}
					size=0;
					pointer=9;
					printed=0;
				}
				if((str.length()-7+size)>60) //printing the object codes when a text record is full
				{
					stringstream ss;
		            ss<<uppercase<<hex<<setfill('0')<<setw(2)<<(size/2);
		            str1=ss.str();
	        	    text[7]=str1[0];
	        	    text[8]=str1[1];
	        	    outtake<<text.substr(0,size+9)<<endl;
	        	    for(i=1 ; i<=6 ; i++)
	        	    {
	        		    text[i]=str[i-1];
				    }
				    size=0;
				    pointer=9;
				    printed=1;
				}
				for(i=7 ; i<str.length() ; i++)
				{
					text[pointer++]=str[i];
					size++;
					printed=0;
				}
				space=0;
			}
		}
		if(printed==0)  
		{
			stringstream ss;
		    ss<<uppercase<<hex<<setfill('0')<<setw(2)<<(size/2);
		    str1=ss.str();
		    text[7]=str1[0];
		    text[8]=str1[1];
		    outtake<<text.substr(0,size+9)<<endl;
		}
		if(modification>0) //printing MODIFICATION records if there are any format 4 instructions
		{
			ifstream infile("TEXT_RECORD.txt");
			infile.seekg(0);
			while(infile.eof()==0)
			{
				getline(infile,str);
				if(str.length()==15)
				{
					int jo=stoi(str.substr(0,6),0,16);
					jo+=1;
					stringstream ss;
				    ss<<uppercase<<hex<<setfill('0')<<setw(6)<<jo;
				    str1=ss.str();
				    outtake<<"M"<<str1<<"05"<<endl;
				}
			}
		}
		outtake<<"E000000"; //printing the END record
	}
	
	string check_register(string str) //function to check which type of register is used in format 2 instruction
	{
		string str1="*";
		if(str=="A")
		{
			str1="0";
		}
		else if(str=="X")
		{
			str1="1";
		}
		else if(str=="L")
		{
			str1="2";
		}
		else if(str=="B")
		{
			str1="3";
		}
		else if(str=="S")
		{
			str1="4";
		}
		else if(str=="T")
		{
			str1="5";
		}
		else if(str=="F")
		{
			str1="6";
		}
		return str1;
	}
	
		string hexadecimal_to_binary(char str) //function to convert a hexadecimal number to its binary representation
		{
			string str1;
			if(str=='1')
			{
				str1="0001";
			}
			else if(str=='2')
			{
				str1="0010";
			}
			else if(str=='3')
			{
				str1="0011";
			}
			else if(str=='4')
			{
				str1="0100";
			}
			else if(str=='5')
			{
				str1="0101";
			}
			else if(str=='6')
			{
				str1="0110";
			}
			else if(str=='7')
			{
				str1="0111";
			}
			else if(str=='8')
			{
				str1="1000";
			}
			else if(str=='9')
			{
				str1="1001";
			}
			else if(str=='A')
			{
				str1="1010";
			}
			else if(str=='B')
			{
				str1="1011";
			}
			else if(str=='C')
			{
				str1="1100";
			}
			else if(str=='D')
			{
				str1="1101";
			}
			else if(str=='E')
			{
				str1="1110";
			}
			else if(str=='F')
			{
				str1="1111";
			}
			else if(str=='0')
			{
				str1="0000";
			}
			return str1;
		}
		
		int check_indexed_addressing(string str) //function to check if any instruction has made use of indexed addressing
		{
			int flag1=0,flag2=0;
			for(i=0 ; i<str.length() ; i++)
			{
				if(str[i]==',')
				{
					flag1=1;
				}
				if(str[i]=='X')
				{
					flag2=1;
				}
			}
			if(flag1==1 && flag2==1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		
		public :
		
		void generate_SYMTAB(string str , int n) //function to generate symtab
		{
			ifstream infile("SYMTAB.txt");
			ofstream outfile("SYMTAB.txt",ios::app);
			string test,str1,str2;
			int flag1=0,flag2=0,check=0;
			if(str[0]=='*') //entering symbols in the symbol defining statements in the SYMTAB	
			{
				outfile<<str.substr(7,7)<<uppercase<<hex<<setfill('0')<<setw(4)<<n<<endl;
			}
			else 
			{
				if(str[7]=='E' && str[8]=='Q' && str[9]=='U' && str[15]!='*')
				{
					for(i=15 ; i<str.length() ; i++)
					{
						if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/')
						{
							j=i;
							check=1; //checking if the expressions have made use of any arithmetic operations to
							         //define a statement
						}
					}
					if(check==1)
					{
						i=j;
						infile.seekg(0);
						while(infile.eof()==0)
						{
							getline(infile,test);
							if(str.substr(15,i-15)==test.substr(0,i-15))
							{
								flag1=1;
								str1=test.substr(7,test.length()-7);
							}
						}
						ifstream in("SYMTAB.txt");
						in.seekg(0);
						while(in.eof()==0)
						{
							getline(in,test);
							if(str.substr(i+1,str.length()-i-1)==test.substr(0,str.length()-i-1))
							{
								flag2=1;
								str2=test.substr(7,test.length()-7);
							}
						}
						if(flag1==1 && flag2==1)
						{
							int con1=stoi(str1,0,16);
							int con2=stoi(str2,0,16);
							if(str[i]=='+')
							{
								outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<con1+con2<<endl;
							}
							else if(str[i]=='-')
							{
								outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<con1-con2<<endl;
							}
							else if(str[i]=='*')
							{
								outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<con1*con2<<endl;
							}
							else if(str[i]=='/')
							{
								outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<con1/con2<<endl;
							}
						}
						else if(flag1==1 && flag2==0)
						{
							if(isdigit(str[i+1]))
							{
								str2=str.substr(i+1,str.length()-i-1);
								int con1=stoi(str1,0,16);
							    int con2=stoi(str2,0,16);
							    if(str[i]=='+')
						    	{
								outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<con1+con2<<endl;
						    	}
							    else if(str[i]=='-')
							    {
								outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<con1-con2<<endl;
							    }
							    else if(str[i]=='*')
							    {
								outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<con1*con2<<endl;
							    }
							    else if(str[i]=='/')
							    {
								outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<con1/con2<<endl;
							    }
							}
							else
							{
								cout<<"error in the code!! "<<str.substr(i+1,str.length()-i-1)<<" is not a valid ";
								cout<<"symbol or a number.";
								exit(0);
							}
						}
						else if(flag1==0 && flag2==1)
						{
							if(isdigit(str[15]))
							{
								str1=str.substr(15,i-15);
								int con1=stoi(str1,0,16);
							    int con2=stoi(str2,0,16);
							    if(str[i]=='+')
						    	{
								outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<con1+con2<<endl;
						    	}
							    else if(str[i]=='-')
							    {
								outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<con1-con2<<endl;
							    }
							    else if(str[i]=='*')
							    {
								outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<con1*con2<<endl;
							    }
							    else if(str[i]=='/')
							    {
								outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<con1/con2<<endl;
							    }
							}
							else
							{
								cout<<"error in the code!! "<<str.substr(15,i-15)<<" is not a valid ";
								cout<<"symbol or a number.";
								exit(0);
							}
						}
						else
						{
							cout<<"error in the code. Symbol not found/assignment of symbol through operations of ";
							cout<<"constants";
							exit(0);
						}
					}
					else
					{
						if(isdigit(str[15]))
						{
							str1=str.substr(15,str.length()-15);
							outfile<<str.substr(0,6)<<" "<<str1<<endl;
						}
						else 
						{
							ifstream take("SYMTAB.txt");
							take.seekg(0);
							while(take.eof()==0)
							{
								getline(take,test);
								if(str.substr(15,str.length()-15)==test.substr(0,str.length()-15))
								{
									str1=test.substr(7,test.length()-7);
									flag1=1;
								}
							}
							if(flag1==1)
							{
								int con1=stoi(str1,0,16);
								outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<con1<<endl;
							}
							else
							{
								cout<<endl<<"error in the code!! "<<str.substr(15,i-15)<<" is not a number ";
								cout<<"or a valid symbol!!";
								exit(0);
							}
						}
					}
				}
				else
				{
					ifstream intake("SYMTAB.txt");
					intake.seekg(0);
					while(intake.eof()==0)
					{
						getline(intake,test);
						if(test.substr(0,6)==str.substr(0,6))
						{
							cout<<endl<<"error in the code!! "<<"duplicate symbol found for "<<str.substr(0,6);
							exit(0);
						}
					}
					outfile<<str.substr(0,6)<<" "<<uppercase<<hex<<setfill('0')<<setw(4)<<n<<endl;
				}
			}
		}
		
		void pass1()
		{
			locctr=0,found=0;
			int start=1,mul=1,total;
			ifstream in("input1.txt");
			ifstream infile("OPTAB.txt");
			ofstream ofs("SYMTAB.txt",ofstream::out|ofstream::trunc); //clearing the contents of SYMTAB
			ofstream air("TEXT_RECORD.txt",ofstream::out|ofstream::trunc); //clearing contents of text record
			ofstream clear("OUTPUT.txt",ofstream::out|ofstream::trunc);//clearing the contents of OUTPUT file
			string str,optstr;
			in.seekg(0);  //initialising input1.txt file pointer to beginning
			while(in.eof()==0) //reading the assembly code line by line
			{
				found=0;
				getline(in,str);
				if(start==1 && str.substr(7,5)=="START") //check first line of the code
				{
				    start=2;
				    found=1; //variable to check if a symbol is found in the OPTAB
				}
				else if(start==1 && str.substr(7,5)!="START")
				{
					cout<<endl<<"error in the code.'START' missing in the beginning."; 
					exit(0);
				}
				total=0;
				mul=1;
				if(str[7]=='R' && str[8]=='E' && str[9]=='S' && str[10]=='W')
				{
					found=1;
					generate_SYMTAB(str,locctr); //generate symtab for the new symbol
					for(i=str.length()-1 ; i>=15 ; i--)  //calculating the number of integers for RESW
		    		{
						if(!isalpha(str[i]))
						{
							total+=(str[i]-48)*mul;
							mul*=10;
						}
					}
					locctr+=3*total;
				}
				else if(str[7]=='R' && str[8]=='E' && str[9]=='S' && str[10]=='B')
				{
					found=1;
					generate_SYMTAB(str,locctr); //generate symtab for the new symbol
					for(i=str.length()-1 ; i>=15 ; i--)  //calculating the number of characters in RESB
					{
						if(!isalpha(str[i]))
						{
							total+=(str[i]-48)*mul;
							mul*=10;
						}
					}
					locctr+=total;
				}
				else if(str[7]=='W' && str[8]=='O' && str[9]=='R' && str[10]=='D')
				{
					found=1;
					generate_SYMTAB(str,locctr); //generate symtab for the new symbol
					locctr+=3;
				}
				else if(str[7]=='B' && str[8]=='Y' && str[9]=='T' && str[10]=='E')
				{
					found=1;
					generate_SYMTAB(str,locctr); //generate symtab for the new symbol
					if(str[15]=='C')
					{
						locctr+=str.length()-18;  //calculating the number of characters in c'string'
					}
					else
					{
						locctr+=1;  //device input/output command
					}
				}
				else if(str[7]=='E' && str[8]=='Q' && str[9]=='U')
				{
					found=1;
					generate_SYMTAB(str,locctr);
				}
				else if(str[7]=='B' && str[8]=='A' && str[9]=='S' && str[10]=='E')
				{
					found=1;
				}
				else if(str[7]=='L' && str[8]=='T' && str[9]=='O' && str[10]=='R' &&str[11]=='G')
				{
					found=1;
				}
				else if(str[7]=='E' && str[8]=='N' && str[9]=='D')
				{
					found=1;
				}
				else if(str[7]=='R' && str[8]=='S' && str[9]=='U' && str[10]=='B')
				{
					found=1;
				}
				else if(str[0]=='*')
				{
					found=1;
					generate_SYMTAB(str,locctr); //generate symtab for the new symbol
					if(str[8]=='C')
					{
						locctr+=str.length()-11;  //calculating the number of characters in c'string'
					}
					else
					{
						locctr+=1;   //device input/output
					}
				}
				else
				{
					if(str[0]!=' ')
					{
						generate_SYMTAB(str,locctr); //generate symtab for the new symbol
					}
					infile.seekg(0);  //initialing OPTAB.txt file pointer to beginning
					while(infile.eof()==0)
					{
						getline(infile,optstr);
						if(str[7]=='+')
						{
							j=8;
						}
						else
						{
							j=7;
						}
						if(optstr.substr(0,7)==str.substr(j,7)) //searching OPTAB for the mnemonic code
						{
							found=1;
							if(optstr[9]=='1')  //mnemonic code of format 1
							{
								locctr++;  
							}
							else if(optstr[9]=='2') //mnemonic code of format 2
							{
								locctr+=2;
							}
							else
							{
								if(str[7]=='+')  //mnemonic code of format 4
								{
									locctr+=4;
								}
								else
								{
									locctr+=3;  //mnemonic code of format 3
								}
							}
						}
					}
				}
				if(found==0)
				{
					cout<<"no matching pnemonic found in the OPTAB for "<<str.substr(7,7);
					exit(0);
				}
			}
			length=locctr;
		}
		
		void pass2()
		{
			ofstream out("TEXT_RECORD.txt",ios::app);
			pc=0,locctr=0,i=0,j=0;
			int end1=0;
			int p,displacement,rsub;
			ifstream in("input1.txt");
			in.seekg(0);
			string str,str1,str2,test,string1,string2;
			char op1,op2;
			while(in.eof()==0)
			{
				found=0;
				rsub=0;
				getline(in,str);
				if(str[15]=='#' || str[15]=='@')
				{
					k=16; //checking if the instruction has made use of immediate or indirect addressing
				}
				else
				{
					k=15;
				}
				if(str[7]=='B' && str[8]=='A' && str[9]=='S' && str[10]=='E')
				{
					str1=str.substr(15,str.length()-15);
					ifstream infile("SYMTAB.txt");
					infile.seekg(0);
					while(infile.eof()==0)
					{
						getline(infile,test);
						if(str1==test.substr(0,str.length()-15))
						{
							found=1;
							str2=test.substr(7,test.length()-7);
						}
					}
					int jo=stoi(str2,0,16);
					base=jo; //assigning the BASE register with thr value defined in the instruction
				}
				if(str[7]=='L' && str[8]=='T' && str[9]=='O' && str[10]=='R' &&str[11]=='G')
				{
					found=1;
				}
				if(str[7]=='E' && str[8]=='Q' && str[9]=='U')
				{
					found=1;
					out<<uppercase<<hex<<setfill('0')<<setw(6)<<locctr<<endl;
				}
				if(str[7]=='R' && str[8]=='E' && str[9]=='S' && str[10]=='B')
				{
					found=1;
					str1=str.substr(15,str.length()-15);
					int jo=stoi(str1,0,10);
					pc+=jo;
					out<<uppercase<<hex<<setfill('0')<<setw(6)<<locctr<<endl;
					locctr+=jo;
				}
				if(str[7]=='R' && str[8]=='E' && str[9]=='S' && str[10]=='W')
				{
					found=1;
					str1=str.substr(15,str.length()-15);
					int jo=stoi(str1,0,10);
					pc+=jo*3;
					out<<uppercase<<hex<<setfill('0')<<setw(6)<<locctr<<endl;
					locctr+=3*jo;
				}
				if(str[7]=='E' && str[8]=='N' && str[9]=='D')
				{
					found=1;
					end1=1;
				}
				if(str[7]=='B' && str[8]=='Y' && str[9]=='T' && str[10]=='E')
				{
					found=1;
					if(str[15]=='C')
					{
						str1=str.substr(17,str.length()-18);
						found=1;
						pc+=str1.length();
						stringstream literal;
						for(i=0 ; i<str1.length() ; i++)
						{
							literal<<uppercase<<hex<<setw(2)<<setfill('0')<<static_cast<int>(str1[i]);
						}
						str2=literal.str();
						//text record
						out<<uppercase<<hex<<setfill('0')<<setw(6)<<locctr;
						out<<" "<<str2<<endl;
						locctr+=str1.length();
					}
					else if(str[15]=='X')
					{
						str1=str.substr(17,2);
						found=1;
						pc+=1;
						//text string
						out<<uppercase<<hex<<setfill('0')<<setw(6)<<locctr;
						out<<" "<<str1<<endl;
						locctr+=1;
					}
					else
					{
						cout<<"error in the code!! "<<str.substr(15,str.length()-15)<<" has an error for defining";
						cout<<" BYTE !!";
						exit(0);
					}
				}
				if(str[7]=='W' && str[8]=='O' && str[9]=='R' && str[10]=='D')
				{
					found=1;
					pc+=3;
					str1=str.substr(15,str.length()-15);
					int jo=stoi(str1,0,10);
					out<<uppercase<<hex<<setfill('0')<<setw(6)<<locctr;
					out<<" ";
					out<<uppercase<<hex<<setfill('0')<<setw(6)<<jo<<endl;
					locctr+=3;
				}
				if(str[0]=='*')
				{
					if(str[8]=='C')
					{
						str1=str.substr(10,str.length()-11);
						found=1;
						pc+=str1.length();
						stringstream literal;
						for(i=0 ; i<str1.length() ; i++)
						{
							literal<<uppercase<<hex<<setw(2)<<setfill('0')<<static_cast<int>(str1[i]);
						}
						str2=literal.str();
						//text record
						out<<uppercase<<hex<<setfill('0')<<setw(6)<<locctr;
						out<<" "<<str2<<endl;
						locctr+=str1.length();
					}
					else if(str[8]=='X')
					{
						str1=str.substr(10,2);
						found=1;
						pc+=1;
						//text string
						out<<uppercase<<hex<<setfill('0')<<setw(6)<<locctr;
						out<<" "<<str1<<endl;
						locctr+=1;
					}
					if(found==0)
					{
						cout<<"error in the code!! "<<str.substr(15,str.length()-15)<<" is not a literal!!";
						exit(0);
					}
				}
				if(str[7]=='S' && str[8]=='T' && str[9]=='A' && str[10]=='R' && str[11]=='T')
				{
					found=1;
				}
				else if(str[7]=='R' && str[8]=='S' && str[9]=='U' && str[10]=='B')
				{
					pc+=3;
					out<<uppercase<<hex<<setfill('0')<<setw(6)<<locctr;
					out<<" "<<"4F0000"<<endl;
					found=1;
					locctr+=3;
					rsub=1;
				}
				else if(str[7]=='+') //if the instruction is a format 4 instruction
				{
					int ind=k;
					modification++; //incrementing the static modification variable to keep a track for MODIFICATION
					                //record
					pc+=4;
					format4[11]='1';
					format4[10]='0';
					format4[9]='0';
					j=check_indexed_addressing(str);
					if(j==0)
					{
						format4[8]='0';
					}
					else
					{
						format4[8]='1';
						ind+=2;
					}
					if(str[15]=='#')
					{
						format4[7]='1';
						format4[6]='0';
					}
					else if(str[15]=='@')
					{
						format4[7]='0';
						format4[6]='1';
					}
					else
					{
						format4[7]='1';
						format4[6]='1';
					}
					ifstream intake("OPTAB.txt");
					intake.seekg(0);
					while(intake.eof()==0)
					{
						getline(intake,test);
						if(str.substr(8,6)==test.substr(0,6))
						{
							str1=hexadecimal_to_binary(test[16]);
							str2=hexadecimal_to_binary(test[17]);
							for(i=0 ; i<4 ; i++)
							{
								format4[i]=str1[i];
							}
							format4[4]=str2[0];
							format4[5]=str2[1];
						}
					}
					ifstream infile("SYMTAB.txt");
					infile.seekg(0);
					while(infile.eof()==0)
					{
						getline(infile,test);
						if(str.substr(k,str.length()-ind)==test.substr(0,str.length()-ind))
						{
							found=1;
							if(test.length()-7>5)
							{
								cout<<"error in the code!! The address of the symbol "<<str.substr(k,str.length()-k);
								cout<<" cannot fit even in a format 4 instruction!!";
								exit(0);
							}
							else if(test.length()-7==5)
							{
								p=12;
								str1=test.substr(7,5);
								for(i=0 ; i<5 ; i++)
								{
									str2=hexadecimal_to_binary(str1[i]);
									for(j=p ; j<p+4 ; j++)
									{
										format4[j]=str2[j-p];
									}
									p+=4;
								}
							}
							else
							{
								p=16;
								for(i=12 ; i<16 ; i++)
								{
									format4[i]='0';
								}
								str1=test.substr(7,4);
								for(i=0 ; i<4 ; i++)
								{
									str2=hexadecimal_to_binary(str1[i]);
									for(j=p ; j<p+4 ; j++)
									{
										format4[j]=str2[j-p];
									}
									p+=4;
								}
							}
						}
					}
					if(found==0)
					{
						    if(isdigit(str[16]))
							{
								found=1;
								str1=str.substr(16,str.length()-16);
								displacement=stoi(str1,0,10);
								if(displacement<=1048575 && displacement>=(-1048576))
								{
									string1=bitset<20>(displacement).to_string();
									for(i=12 ; i<32 ; i++)
									{
										format4[i]=string1[i-12];
									}
								}
								else
								{
									cout<<"error in the code!! The constant "<<str.substr(16,str.length()-16);
									cout<<"is too big to be fit in the 20 bit address of format 4 instruction!!";
									exit(0);
								}
							}
					}
                    for(i=0 ; i<32 ; i+=4)
                    {
                    	bitset<4>bits(format4.substr(i,4));
                    	int jo=bits.to_ulong();
                    	format4final+="0123456789ABCDEF"[jo];
					}
					out<<uppercase<<hex<<setfill('0')<<setw(6)<<locctr;
					out<<" "<<format4final<<endl;
                    locctr+=4;
                    format4final="";
				}
				else
				{
					ifstream intake("OPTAB.txt");
					intake.seekg(0);
					while(intake.eof()==0)
					{
						getline(intake,test);
						if(str.substr(7,6)==test.substr(0,6))
						{
							op1=test[16];
							op2=test[17];
							if(test[9]=='1')
							{
								j=1;
							}
							else if(test[9]=='2')
							{
								j=2;
							}
							else
							{
								j=3;
							}
						}
					}
					if(j==3 && rsub==0)
					{
						int ind=k;
						pc+=3;
						str1=hexadecimal_to_binary(op1);
						str2=hexadecimal_to_binary(op2);
						for(i=0 ; i<4 ; i++)
						{
							format3[i]=str1[i];
						}
						format3[4]=str2[0];
						format3[5]=str2[1];
						if(str[15]=='#')
						{
							format3[6]='0';
							format3[7]='1';
						}
						else if(str[15]=='@')
						{
							format3[6]='1';
							format3[7]='0';
						}
						else
						{
							format3[6]='1';
							format3[7]='1';
						}
						j=check_indexed_addressing(str);
						if(j==0)
						{
							format3[8]='0';
						}
						else
						{
							format3[8]='1';
							ind+=2;
						}
						format3[11]='0';
						ifstream infile("SYMTAB.txt");
						infile.seekg(0);
						while(infile.eof()==0)
						{
							getline(infile,test);
					        if(str.substr(k,str.length()-ind)==test.substr(0,str.length()-ind))
					     	{
					     		found=1;
					     		str1=test.substr(7,test.length()-7);
					     		displacement=stoi(str1,0,16);
					     		if((displacement-pc)<=4095 && (displacement-pc)>=(-4096))
					     		{
					     			format3[10]='1';
					     			format3[9]='0';
					     			displacement=displacement-pc;
					     			string1=bitset<12>(displacement).to_string();
					     			for(i=12 ; i<24 ; i++)
					     			{
					     				format3[i]=string1[i-12];
									}
								}
								else if((displacement-base)<=4095 && (displacement-base)>=(-4096))
								{
									format3[10]='0';
					     			format3[9]='1';
									displacement=displacement-base;
					     			string1=bitset<12>(displacement).to_string();
					     			for(i=12 ; i<24 ; i++)
					     			{
					     				format3[i]=string1[i-12];
									}
								}
								else
								{
									cout<<"error in the code!! The symbol address of "<<str.substr(k,str.length()-k);
									cout<<" cannot be fit in 12 bit format 3 instruction by PC relative or ";
									cout<<"base relative addressing!! Please try using format 4 instruction";
									exit(0);
								}
							}
						}
						if(found==0)
						{
							if(isdigit(str[16]))
							{
								found=1;
								format3[9]='0';
								format3[10]='0';
								format3[8]='0';
								str1=str.substr(16,str.length()-16);
								displacement=stoi(str1,0,10);
								if(displacement<=4095 && displacement>=(-4096))
								{
									string1=bitset<12>(displacement).to_string();
									for(i=12 ; i<24 ; i++)
									{
										format3[i]=string1[i-12];
									}
								}
								else
								{
									cout<<"error in the code!! The constant "<<str.substr(16,str.length()-16);
									cout<<"is too big to be fit in the 12 bit address of format 3 instruction!!";
									exit(0);
								}
							}
						}
						for(i=0 ; i<24 ; i+=4)
                        {
                    	   bitset<4>bits(format3.substr(i,4));
                    	   int jo=bits.to_ulong();
                    	   format3final+="0123456789ABCDEF"[jo];
					    }
					    if(rsub==0)
					    {
					    	out<<uppercase<<hex<<setfill('0')<<setw(6)<<locctr;
					        out<<" "<<format3final<<endl;
						    locctr+=3;
                            format3final="";
						}
					}
					else if(j==2)
					{
						pc+=2;
						found=1;
						format2[0]=op1;
						format2[1]=op2;
						if(check_register(str.substr(15,1))=="*")
						{
							cout<<"error in the code!! "<<str.substr(15,1)<<" is not a valid register!!";
							exit(0);
						}
						else
						{
							string1=check_register(str.substr(15,1));
							format2[2]=string1[0];
						}
						if(str.length()>16)
						{
							if(check_register(str.substr(17,1))=="*")
							{
								cout<<"error in the code!! "<<str.substr(17,1)<<" is not a valid register!!";
							    exit(0);
							}
							else
							{
								string1=check_register(str.substr(17,1));
								format2[3]=string1[0];
							}
						}
						else
						{
							format2[3]='0';
						}
				        out<<uppercase<<hex<<setfill('0')<<setw(6)<<locctr;
					    out<<" "<<format2<<endl;
						locctr+=2;
					}
					else if(j==1)
					{
						pc+=1;
						str1=hexadecimal_to_binary(op1);
						str2=hexadecimal_to_binary(op2);
						for(i=0 ; i<4 ; i++)
						{
							format1[i]=str1[i];
						}        
						for(i=4 ; i<8 ; i++)
						{
							format1[i]=str2[i];
						}  
						out<<uppercase<<hex<<setfill('0')<<setw(6)<<locctr;
					    out<<" "<<format1<<endl;
						locctr+=1;
					}
				}
				if(found==0)
				{
					cout<<"error in the code!! "<<str.substr(k,str.length()-k)<<" symbol not defined in the code!!";
					exit(0);
				}
			}
			if(end1==0)
			{
				cout<<endl<<"error in the code!! END assembler directive missing in the source code!!";
				exit(0);
			}
			print_text_record();
		}
		
};
int assemble::length=0;
int assemble::modification=0;

int main()
{
	assemble A1;
	A1.pass1();
	A1.pass2();
	return 0;
}