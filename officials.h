#ifndef OFFICIALS_H
#define OFFICIALS_H
#include <QString>

class Official
{
public:
    Official();

    bool operator<(const Official&other);
    bool operator<=(const Official&other);
    bool operator>(const Official&other);
    bool operator>=(const Official&other);
    bool operator==(const Official&other);

private:
    QString ministry;
    QString organisation;
    int subdivision;
    QString name;
};

#endif // OFFICIALS_H
