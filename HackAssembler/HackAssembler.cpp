#include <iostream>
#include "Destinations.h"
#include "Jumps.h"
#include "Source.h"
#include "Binex.h"
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <iomanip>

//Converts an integer to a binary string
string int2binStr(int value)
{
    char symb[16] = { 0 };
    _itoa_s(value, symb, 2);
    string str(symb);
    string binStr = string(16 - str.length(), '0') + str;
    return binStr;
}

//Converts a binary string to an integer (If needed)
int binStr2int(string value)
{
    int num = stoi(value, 0, 2);
    return num;
}

//Converts a integer to a Hex String
string int2HexStr(int value)
{
    char symb[4] = { 0 };
    _itoa_s(value, symb, 16);
    string str(symb);
    return str;
}

//Function that searches a map by value and returns key if it matches given number
//Used for symbol
string mapSearch(map<string, int> symb, int num)
{
    for (auto it = symb.begin(); it != symb.end(); ++it)
    {
        if (it->second == num)
        {
            return it->first;
        }
    }
}

// Utility comparator function to pass to the sort() module //FOUND ON EDUCATOR.IO
bool sortByVal(const pair<string, int>& a, const pair<string, int>& b)
{
    return (a.second < b.second);
}


int main(int argc, char* argv[])
{
    Destinations destinations = Destinations();
    Jumps jumps = Jumps();
    Sources sources = Sources();
    Binex binex = Binex();

    string inFileName;
    string lstFileName;
    string hexFileName;

    vector<string> rawData;
    vector<string> Pass1;
    vector<string> Pass2;
    vector<string> HexPass;

    //LabelMap: to be used for locating loops
    map<string, int> labelMap;
    //Symbols: to be used for addresses of memory locations
    map<string, int> symbols;

    //Load R0-R15 into Symbol table
    for (int i = 0; i <= 15; i++)
    {
        symbols.insert(pair<string, int>("R" + to_string(i), i));
    }

    //RAW DATA BEGINS
    cout << "RAW DATA" << endl;
    //Begin checking file paths and opening necessary files
    if (argc <= 1)
    {
        cout << "Missing parameters" << endl;
    }
    else
    {
        inFileName = "C:\\mydata\\" + (string)argv[1];
        lstFileName = "C:\\mydata\\" + (string)argv[2] + ".lst";
        hexFileName = "C:\\mydata\\" + (string)argv[2] + ".hex";

        //Getting in raw instruction data and putting it into raw data vector.
        ifstream inFile;
        inFile.open(inFileName);
        if (inFile.is_open())
        {
            string text;

            while (!inFile.eof())
            {
                getline(inFile,text,'\n');
                rawData.push_back(text);
            }
        }
        else
        {
            cout << "Couldn't open file" << endl;
        }
        
        inFile.close();
    }

    //Outputting RawData to Debug console for error checking
    for (int i = 0; i < rawData.size(); i++)
    {
        cout << rawData.at(i) << endl;
    }
    cout << endl;
    //RAWDATA ENDS


    //PASS 1 BEGINS
    cout << "PASS 1" << endl;
    //PASS 1 checks for different parameters within our raw data vector, takes out comments & blank spaces, and extracts any symbols/loops
    //from Raw Data vector and passes it to PASS 1 Vector
    for (int i = 0; i < rawData.size(); i++)
    {
        string tmpText = rawData.at(i);
        if (tmpText.find("//") == string::npos)
        {
            if (tmpText.find('(') == string::npos && tmpText.find(')') == string::npos)
            {
                if (tmpText == "")
                {
                    continue;
                }
                else
                {
                    transform(tmpText.begin(), tmpText.end(), tmpText.begin(), ::toupper);
                    //If not a comment or symbol or blank space, valid instruction to be pushed onto vector.
                    Pass1.push_back(tmpText);
                }
            }
            else
            {
                //If Parenthesis were detected, loop is recorded and pushed onto
                int LP = 0;
                int RP = tmpText.find(')');
                tmpText = tmpText.substr(LP + 1, RP - 1);
                transform(tmpText.begin(), tmpText.end(), tmpText.begin(), ::toupper);
                labelMap.insert(pair<string, int>(tmpText, Pass1.size()));

            }
        }
        else if (tmpText.find("//") == 0)
        {
            continue;
        }
        else
        {
            string newText = tmpText.substr(0, tmpText.find("//"));
            transform(tmpText.begin(), tmpText.end(), tmpText.begin(), ::toupper);
            Pass1.push_back(newText);
        }
    }
    //TEST PASS1
    for (int i = 0; i < Pass1.size(); i++)
    {
        cout << Pass1.at(i) << endl;
    }
    cout << endl;
    //End of PASS 1
    
    
    //PASS 2 BEGINS
    cout << "PASS 2" << endl;
    string BitInst = "";
    int symbolCount = 16;
    
    //PASS 2 parses through the filtered instructions left in PASS 1 vector and checks the format of the instruction.
    //Based on the layout of the instruction, it converts the instruction's parts into their binary form based on our established classes
    for (int i = 0; i < Pass1.size(); i++)
    {
        string tmpText = Pass1.at(i);
        //Checks to see whether instructions contains an '=' or ';'. If not found, checks for @ sign to see if instruction is an address or '@'
        if (tmpText.find('=') == string::npos && tmpText.find(';') == string::npos)
        {
            if (tmpText.find('@') == string::npos)
            {
                cout << "ERROR: INSTRUCTION INVALID" << endl;
                return 1;
            }
            else
            {
                //Found '@', check to see if the address is already in our symbols table, if it is, just push the address in binary onto Pass2 vector,
                //If it's a new address, insert the pair into symbols table, then add the address's binary to Pass2.
                tmpText = tmpText.substr(tmpText.find('@') + 1, tmpText.size());

                map<string, int>::iterator it;
                it = symbols.find(tmpText);
                if (it == symbols.end())
                {
                    symbols.insert(pair<string, int>(tmpText, symbolCount));

                    tmpText = int2binStr(symbolCount);
                    Pass2.push_back(tmpText);
                    symbolCount++;
                }
                else
                {
                    tmpText = int2binStr(it->second);
                    Pass2.push_back(tmpText);
                }
            }
        }
        else
        {
            //STARTS PROCESSING INSTRUCTION
            //Prefix stays at 111
            string prefix = "100";
            bool tf = false; // Will be used to tell us whether there is an ';' in our instruction to allow us to control for the size

            //Jump instruction is detected and is converted to Binary using the Find function
            string jump = "000";
            if (tmpText.find(';') != string::npos)
            {
                tf = true; //To be used for source size...
                jump = tmpText.substr(tmpText.find(';') + 1, tmpText.size());
                jump = jumps.Find(jump);
            }
            
            string source = "000000";
            string dest = "NULL";
            //Based on TF value, resizes tmpText without the JUMP instruction. Then gets source instruction. Based on whether there is an '=' or ';', gets the destination.
            if (tf == true)
            {
                //If instruction has ';' & '=', jump instruction is removed to allow for string to be seperated into destination and source components
                if (tmpText.find('=') != string::npos)
                {
                    string jmpTxt = tmpText.substr(tmpText.find(';'), tmpText.size());
                    tmpText.resize(tmpText.size() - jmpTxt.size());
                    source = tmpText.substr(tmpText.find('=') + 1, tmpText.size());

                    dest = tmpText.substr(0, tmpText.find('='));
                }
                //If instruction only has ';' with no '=', instruction only contains destination and jump, so destination is extracted
                else
                {
                    dest = tmpText.substr(0, tmpText.find(';'));
                    if (dest == "0")
                    {
                        dest = "NULL";
                    }
                }
            }
            //If no ';' was found, then we can just extract destination and source from both sides of '=' sign since we dont have to take jump instr off
            else
            {
                source = tmpText.substr(tmpText.find('=') + 1, tmpText.size());
                dest = tmpText.substr(0, tmpText.find('='));
            }

            //Bit 12 Operation based on whether Source contains an 'M'
            string bit12 = "0";
            if (source.find('M') != string::npos)
            {
                bit12 = "1";
            }

            //The left side of the equal sign is parsed
            dest = destinations.Find(dest);

            if (source != "000000")
            {
                source = sources.Find(source);
            }
            
            //Adding all binary together and push to vector
            BitInst = prefix + bit12 + source + dest + jump;
            Pass2.push_back(BitInst);
        }
        cout << Pass2.at(i) << endl; //PASS 2 VECTOR
        //End of Pass 2
    }
    cout << endl;

    //HexPass Begins
    cout << "HexPass" << endl;
    for (int i = 0; i < Pass2.size(); i++)
    {
        string tmpText = Pass2.at(i);
        string strTemp2;

        while (tmpText.size() > 0)
        {
            //Getting first 4 characters out of string
            string newTmp = tmpText.substr(0, 4);

            //Convert characters to int, then converting int to hex string
            int intTemp = binStr2int(newTmp);
            string strTemp = int2HexStr(intTemp);

            //Erasing the first 4 letters of the string to start the next 4 letters
            tmpText.erase(0, 4);
            
            //Adds the strings together to get 4 digit hex
            strTemp2 += strTemp;
        }
        transform(strTemp2.begin(), strTemp2.end(), strTemp2.begin(), ::toupper);
        HexPass.push_back(strTemp2);
    }
    //Displaying HexPass Vector to debug console
    for (int i = 0; i < HexPass.size(); i++)
    {
        cout << HexPass.at(i) << endl;
    }
    cout << endl;
    //END OF HEXPASS

    //ListFile Begins
    cout << "ListFile" << endl;
    //Outputting LabelMap to debug console for error checking
    for (auto& item : labelMap)
    {
        cout << item.first << " Line: " << item.second << endl;
    }

    //Opening Hex File & filling
    ofstream hexOutFile;
    hexOutFile.open(hexFileName);
    if (hexOutFile.is_open())
    {
        hexOutFile << "v2.0 raw" << endl;
        for (int i = 0; i < HexPass.size(); i++)
        {
            hexOutFile << HexPass.at(i) << endl;
        }
        
        hexOutFile.close();
    }
    else
    {
        cout << "Hexfile could not open." << endl;
    }

    //Opening List File & filling
    ofstream lstOutFile;
    lstOutFile.open(lstFileName);
    if (lstOutFile.is_open())
    {
        //Outputting Instructions
        lstOutFile << "////////////////////////////////////////" << endl;
        lstOutFile << "//            Instructions            //" << endl;
        lstOutFile << "////////////////////////////////////////" << endl;

        for (int i = 0; i < Pass2.size(); i++)
        {
            lstOutFile << Pass2.at(i) << "   " << HexPass.at(i) << "   " << Pass1.at(i) << endl;
        }
        lstOutFile << endl << endl;


        //Outputting Symbols by Name
        lstOutFile << "/////////////////" << endl;
        lstOutFile << "/SYMBOLS BY NAME/" << endl;
        lstOutFile << "/////////////////" << endl;

        for (auto& item : symbols)
        {
            lstOutFile << item.first << "          " << item.second << endl;
        }
        lstOutFile << endl << endl;


        //Outputting Symbols by Address
        lstOutFile << "////////////////////" << endl;
        lstOutFile << "/SYMBOLS BY ADDRESS/" << endl;
        lstOutFile << "////////////////////" << endl;
        
        for (int i = 0; i < symbolCount; i++)
        {
            lstOutFile << i << "          " << mapSearch(symbols, i) << endl;
        }
        lstOutFile << endl << endl;


        //Outputting Labels by Name
        lstOutFile << "////////////////" << endl;
        lstOutFile << "/LABELS BY NAME/" << endl;
        lstOutFile << "////////////////" << endl;

        for (auto& item : labelMap)
        {
            lstOutFile << item.first << "          " << item.second << endl;
        }
        lstOutFile << endl << endl;


        //Outputting Labels by Address
        lstOutFile << "///////////////////" << endl;
        lstOutFile << "/LABELS BY ADDRESS/" << endl;
        lstOutFile << "///////////////////" << endl;

        //Temp Vector for holding our map
        vector<pair<string, int>> tempVec;

        //Copies key-value pairs from the map to the vector
        //FOUND SOLUTION FOR COPYING MAP INTO VECTOR ON EDUCATOR.IO
        map<string, int> ::iterator it2;
        for (it2 = labelMap.begin(); it2 != labelMap.end(); it2++) 
        {
            tempVec.push_back(make_pair(it2->first, it2->second));
        }

        sort(tempVec.begin(), tempVec.end(), sortByVal);
        
        for (int i = 0; i < tempVec.size(); i++)
        {
            lstOutFile << tempVec[i].second << "          " << tempVec[i].first << endl;
        }  
    }
    else
    {
        cout << "List file could not open." << endl;
    }
 }

