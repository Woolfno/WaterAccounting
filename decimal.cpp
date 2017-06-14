#include "decimal.h"
#include <math.h>

int64_t Decimal::getValue() const
{
    return value;
}

Decimal::Decimal(double v)
{
    value=trunc(v*100);
}

Decimal::Decimal(int64_t v)
{
    value=v;
}

QString Decimal::toString() const
{
    return QString::number(value/100.0);
}

void Decimal::operator =(double v)
{
    value=trunc(v*100);
}

Decimal Decimal::operator *(int iv)
{
    Decimal d;
    d.value=value*iv;
    return d;
}
