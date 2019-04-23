#include <iostream>
#include <InstrucionParser.h>
#include "objectCodeMap.h"
#include "InstructionBuilder.h"
#include <ReadFile.h>
#include "Ob.h"
#include<bits/stdc++.h>
#include <string>
#include <string.h>
using namespace std;
/*
string HexFromDecimal(int num){
    int temp = num;
    int i = 0 , j , r ;
    string hex = "";
    while (temp != 0){
        r = temp % 16;
        if (r < 10){
            hex += r + 48;
        } else {
            hex += r + 55;
        }
        temp = temp / 16 ;
    }
    reverse(hex.begin(), hex.end());
    return hex;
}*/
int main()
{
    int c = 'a';
    cout<<c<<endl;
    InstructionBuilder builder("hkma.txt");
    vector<InstrucionParser> v = builder.getInstructions();
    for(InstrucionParser i : v){
        printf("%x  ",i.getAddress());
        cout<<i.getLabel()<<" "<<i.getOperaion()<<" "<<i.getOperand()<<" "<<i.getComment()<<"\n";
    }

    for(int i = 0; i < builder.literals_data.size() ; i++){
            pair<int , string> temp = builder.literals_data[i];
            cout << temp.first << "      " << temp.second << " Literal" << endl;
    }

    return 0;
}

