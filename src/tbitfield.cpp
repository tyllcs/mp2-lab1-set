// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0) throw - 1;
    BitLen = len;
    MemLen = (BitLen + 31) / 32;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= BitLen) throw - 1;
    return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= BitLen) throw - 1;
    return 1 << (n % (sizeof(TELEM) * 8)); 
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= BitLen)) throw - 1;
    int ind = GetMemIndex(n); // в какой элемент установить
    TELEM mask = GetMemMask(n); // на какую позицию в этом эл-те
    pMem[ind] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen)) throw - 1;
    int ind = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[ind] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n >= BitLen)) throw - 1;
    int ind = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    return (pMem[ind] & mask) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf) return *this;

    delete[] pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];

    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return false;
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i])
            return false;
    }
    return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return true;
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i])
            return true;
    }
    return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (this == &bf) throw - 1;
    int maxLen, minMemLen;
    maxLen = std::max(BitLen, bf.BitLen);
    TBitField res(maxLen);
    minMemLen = std::min(MemLen, bf.MemLen);

    for (int i = 0; i < minMemLen; i++)
        res.pMem[i] = pMem[i] | bf.pMem[i];
    if (MemLen > bf.MemLen) {
        for (int i = minMemLen; i < MemLen; i++) {
            res.pMem[i] = pMem[i];
        }
    }
    else {
        for (int i = minMemLen; i < bf.MemLen; i++) {
            res.pMem[i] = bf.pMem[i];
        }
    }
    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (this == &bf) throw - 1; 
    int maxLen, minMemLen;
    maxLen = std::max(BitLen, bf.BitLen);
    TBitField res(maxLen);
    minMemLen = std::min(MemLen, bf.MemLen);

    for (int i = 0; i < minMemLen; i++)
        res.pMem[i] = pMem[i] & bf.pMem[i];
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);

    for (int i = 0; i < MemLen; i++) 
        res.pMem[i] = ~pMem[i];

    int lastBit = BitLen % (sizeof(TELEM) * 8);
    if (lastBit == 0) {
        res.pMem[MemLen - 1] = ~pMem[MemLen - 1];
    }
    else {
        res.pMem[MemLen - 1] = (~pMem[MemLen - 1]) & ((1 << lastBit) - 1);
    }

    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    char ch;
    for (int i = 0; i < bf.BitLen; i++) {
        istr >> ch;
        if (ch == '0')
            bf.ClrBit(i);
        else if (ch == '1')
            bf.SetBit(i);
        else
            break;
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++) {
        if (bf.GetBit(i) == true)
            ostr << '1';
        else
            ostr << '0';
    }

    return ostr;
}
