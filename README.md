The given C++ program - (SIC_XE_Assembler.cpp) has the following features -
1) Can generate object program for an SIC/XE assembly level source code
2) Supports program relocation
3) Supports symbol defining statements (includes expressions)

Please keep in mind that this C++ program DOES NOT support other features like program blocks and control sections.

Please follow these steps to make proper use of this program :-

1) The computer/laptop in which this code is executed should support C++ program and its compilation. Applications like
   DEV-C++/VSCODE or any other IDE which supports C++ can be used for this. 
   
2) The input SIC/XE source code has to be written in the file INPUT1.txt
   The zip folder also has other text files - SYMTAB.txt , OPTAB.txt , TEXT_RECORD.txt and OUTPUT.txt . These files 
   have to be stored in the laptop/PC at the same location. Upon successful compilation, prompts maybe be displayed  
   which ask the user if they want to save the changes in the files. You have to click on the "OK" option.
   
3) Please note that certain space is assigned for each part of the instruction in INPUT1.txt file:-
   i)   columns 1-6  -> statement name (Like COPY)
   ii)  columns 8-14 -> mnemonic/assembler directive
   iii) columns 16-/ -> symbols/number/registers

   It should be noted that above stated instruction should be followed strictly. For example, your statement name
   should fit within first 6 columns and should not be more than that. Similar is the case for spaces assigned for 
   mnemonic names and symbol names. Failing to do so might give an error message or incorrect output.
   There is no restriction on length for the last space for symbol/number/register names.
    
4) Please make sure that you DON'T write anything other than valid SIC/XE source code on INPUT1.txt file. Failing to
   do so will result in incorrect output or error code. Always save the file first if you have made any changes in 
   INPUT1.txt file to generate object program for the newly written SIC/XE assembly code.
   
Please keep in mind that this C++ program will act just like an SIC/XE assembler and has restrictions on the 
address/displacement for format-4 and format-3 instructions respectively. The program will show an error message if any
of these values go out of range.

If the assembly code was not found to have any errors, the object code will be generated in the OUTPUT.txt file. In the
case where the assembly source code is found to have any errors, no object program will be generated in the OUTPUT.txt
file and an error message will be displayed in the console along with the type of error.

It may happen that the object program has been stored in OUTPUT.txt file, but its change is not visible if the file
was previously not empty and the program was run for a new assembly source code. In that case, just close 
the OUTPUT.txt file and open it again, and the object program for the newly written assembly source code will be 
displayed on the file.
