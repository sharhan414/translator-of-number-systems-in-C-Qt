#include "translatenumbers.h"
#include <cmath>
#include <algorithm>
#include <iterator>
using namespace std;

string TranslateNumbers::TranlateNonNaluralsPart(lDouble number, int system)
{
// функция для перевода ненатуральную часть числа в другую систему счисления
//function for transferring the non-natural part of a number to another number system
    string Answer;
    for(int i=0;i!=KolSimvPslZp;++i)
    {
        lDouble x=number*system;
        size_t y=size_t(x);
        number=x-y;
        Answer.push_back(IntToChar(y));
        if(!bool(number))
        {
            break;
        }
    }
    return Answer;
}
string TranslateNumbers::TranslateToNumbersSystem(int system,lDouble number){
    //функция для перевода из 10 число в это  систему счислени
    //a function to convert the number from 10 numbers in this "argument:system" number system
    string Answer="";
    llInt Natural=llInt(number);
    lDouble values=number-Natural;

    while(Natural!=0)
    {
        string::size_type ostatok=Natural%system;
        Natural/=system;
        char c=IntToChar(ostatok);
        Answer.push_back(c);
    }
    reverse(Answer.begin(),Answer.end());
    if(Answer.empty())
    {
        Answer="0";
    }

    if(values==0)
    {
        return Answer;
    }
    string s=TranlateNonNaluralsPart(values,system);
    return Answer+'.'+s;
}

void TranslateNumbers::setKolSilv(int x)
{
    KolSimvPslZp=x;
}

TranslateNumbers::lDouble TranslateNumbers::TranslateNumbersSystemTo10(int system1, string str)
{
//функция для перевода числа из любой системы счисления 10-ю с.с
//function for translating a number from any number system to 10 number system
    auto point=find(str.begin(),str.end(),'.');
    string text(str.begin(),point);
    reverse(text.begin(),text.end());
    lDouble Answer{0};

    for(string::size_type i=0;i!=text.size();++i)
    {
        string::size_type x=CharToInt(text[i]);
        Answer+=x*pow(lDouble(system1),i);
    }
    if(point!=str.end())
    {
        string endText(point+1,str.end());
        for(string::size_type i=0;i!=endText.size();++i)
        {
            string::size_type x=CharToInt(endText[i]);
            Answer+=x*(lDouble(1)/pow((lDouble)system1,(i+1)));
        }
    }
    return Answer;
}
string::size_type TranslateNumbers::CharToInt(char c)
{
    return allUseSimvols.find(c);
}
char TranslateNumbers::IntToChar(string::size_type x)
{
    return allUseSimvols[x];
}
