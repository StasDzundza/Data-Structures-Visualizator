#include "officials.h"

Official::Official()
{
    name = "Person";
    subdivision = 0;
    ministry = "International Affairs";
    organisation = "Goverment";
}

bool Official::operator<(const Official &other)
{
    return this->name < other.name;
}
bool Official::operator<=(const Official &other)
{
    return this->name <= other.name;
}
bool Official::operator>(const Official &other)
{
    return this->name > other.name;
}
bool Official::operator>=(const Official &other)
{
    return this->name >= other.name;
}
bool Official::operator==(const Official &other)
{
    return this->name == other.name;
}
