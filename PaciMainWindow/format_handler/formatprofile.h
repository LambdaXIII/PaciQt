#ifndef FORMATPROFILE_H
#define FORMATPROFILE_H

#include <QObject>
#include <QMap>

namespace FormatProfile {

//QString tr(char* a);

enum Format {
  Unknown,
  PlainText,
  Fcp7Xml,
};

const QMap<Format, QString> formatNames{
  {PlainText, "文本文件"},
  {Fcp7Xml, "FCP7 XML 文件"}
};

const QMap<Format, QString> formatSuffixes{
  {PlainText, "*.txt"},
  {Fcp7Xml, "*.xml"}
};

QString getFilter(Format f);
QString getAllFilters();
Format searchFormat(QString selectedFilter);

} //namespace FormatProfile

#endif // FORMATPROFILE_H
