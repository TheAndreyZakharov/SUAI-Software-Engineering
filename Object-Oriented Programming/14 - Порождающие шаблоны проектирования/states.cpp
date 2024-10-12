#include "states.h"
States::States(QObject *parent) : QObject(parent)
{
actualData = nullptr;
States::~States()
}
{
// delete: actualData
if(actualData)
{
delete actualData;
actualData = nullptr;
}
// delete and clear: array
qDeleteAll(array);
array.clear();
void States::add(Estate *value)
}
{
array.append(value);
bool States::hasStates()
}
{
return !(States::array.empty());
Estate *States::getActualData()
}
{
return actualData;
void States::undo()
}
{
if (hasStates())
{
array.pop_back();
actualData = array.last();
}
else
actualData = nullptr;
int States::getSize()
}
{
return array.size();
}
