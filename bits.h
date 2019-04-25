#ifndef BITS_H
#define BITS_H

#endif // BITS_H


#include <QGraphicsScene>
#include <QFileDialog>
#include <QWidget>
#include <QDebug>
#include <iostream>
#include <cmath>
#include <string>
#include <typeinfo>
#include <bitset>

using namespace std;

string DecToBin2(int number, int step)
{
    string result = bitset<8>(number << step).to_string();

    return  result;
}

int Bin2ToDec(string bits)
{
    int result;

    bitset<8> buff(bits);

    result = buff.to_ullong();

    return  result;
}
