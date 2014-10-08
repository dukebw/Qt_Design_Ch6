#include <QString>
#include <QDebug>
#include "argumentlist.h"

void processFile(QString filename, bool verbose)
{
   if (verbose)
      qDebug() << QString{"Do something chatty with %1."}.arg(filename);
   else
      qDebug() << filename;
}

void runTestOnly(QStringList& listOfFiles, bool verbose)
{
   foreach (const QString& current, listOfFiles) {
      processFile(current, verbose);
   }
}

int main(int argc, char* argv[])
{
   ArgumentList al{argc, argv};
   QString appname{al.takeFirst()};
   qDebug() << "Running " << appname;
   bool verbose = al.getSwitch("-v");
   bool testing = al.getSwitch("-t");
   if (testing) {
      runTestOnly(al, verbose);
      return 0;
   }
   else qDebug() << "This is not a test";
}
