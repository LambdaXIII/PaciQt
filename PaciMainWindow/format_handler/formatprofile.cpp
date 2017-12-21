#include "formatprofile.h"

FormatProfile::FormatProfile()
  : QObject()
{
  formatNames = QMap<Format, QString>({
    {PlainText, tr("文本文件")},
  });

  formatSuffixes = QMap<Format, QString>({
    {PlainText, "*.txt"},
  });
}


QString FormatProfile::getFilter(Format f)
{
  return formatNames[f] + "(" + formatSuffixes + ")";
}

QString FormatProfile::getAllFilters()
{
  QStringList filters;
  for (Format a : formatNames.keys()) {
    filters << getFilter(a);
  }
  return filters.join(";;");
}


FormatProfile::Format FormatProfile::searchFormat(QString selectedFilter)
{
  for (Format a : formatNames.keys()) {
    if (selectedFilter.contains(formatNames[a]))
      return a;
  }
  return Unknown;
}
