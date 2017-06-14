#ifndef DECIMAL_H
#define DECIMAL_H
#include <stdint.h>
#include <QString>
class Decimal
{
private:
    int64_t value;
public:
    explicit Decimal(double v=0);
    explicit Decimal(int64_t v);
    QString toString() const;

    void operator =(double v);
    Decimal operator *(int iv);

    int64_t getValue() const;
};

#endif // DECIMAL_H
