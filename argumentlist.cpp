#include <QCoreApplication>
#include <QDebug>
#include "argumentlist.h"

ArgumentList::ArgumentList()
{
   if (qApp != nullptr)
      *this = qApp->arguments();
}

void ArgumentList::argsToStringList(int argc, char* argv[])
{
   for (int i=0; i<argc; ++i)
      *this += argv[i];
}

bool ArgumentList::getSwitch(QString option)
{
   QMutableStringListIterator itr{*this};
   while (itr.hasNext()) {
      if (option == itr.next()) {
         itr.remove();
         return true;
      }
   }
   return false;
}

QString ArgumentList::getSwitchArg(QString option, QString defaultValue)
{
   if (isEmpty())
      return defaultValue;
   QMutableStringListIterator itr{*this};
   while (itr.hasNext()) {
      if (option == itr.next()) {
         itr.remove();
         if (itr.hasNext()) {
            QString retval{itr.next()};
            itr.remove();
            return retval;
         }
         else {
            qDebug() << "Missing Argument for " << option;
            return QString{};
         }
      }
   }
   return defaultValue;
}
