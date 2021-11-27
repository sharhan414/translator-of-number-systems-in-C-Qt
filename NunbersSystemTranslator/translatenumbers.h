#ifndef TRANSLATENUMBERS_H
#define TRANSLATENUMBERS_H
#include <string>
/*this class is for transferring from any number system to any one.
 * this class does not contain any protection .
  if you need protection, then add those of it,
 the variable "KolSimvPslZp" stores the values of the number of characters after the decimal point or period

*/
class TranslateNumbers final
{
public:
    using lDouble=long double;
    using llInt=long long int;
    TranslateNumbers(){}
    lDouble TranslateNumbersSystemTo10(int,std::string);
    std::string TranlateNonNaluralsPart(lDouble,int);
    std::string TranslateToNumbersSystem(int,lDouble);
    void setKolSilv(int);
private:
    std::string::size_type CharToInt(char);
    char IntToChar(std::string::size_type);
    int KolSimvPslZp=18;
};

#endif // TRANSLATENUMBERS_H
