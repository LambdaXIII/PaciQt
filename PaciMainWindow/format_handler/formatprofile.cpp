#include "formatprofile.h"
#include <QCoreApplication>

namespace FormatProfile {

//QString tr(char *a)
//{
//  return QCoreApplication::translate(a, "Formats");
//}

QString getFilter(Format f)
{
  return formatNames[f] + "(" + formatSuffixes[f] + ")";
}

QString getAllFilters()
{
  QStringList filters;
  for (Format a : formatNames.keys()) {
    filters << getFilter(a);
  }
  return filters.join(";;");
}


Format searchFormat(QString selectedFilter)
{
  for (Format a : formatNames.keys()) {
    if (selectedFilter.contains(formatNames[a]))
      return a;
  }
  return Unknown;
}

} //namespace FormatProfile
