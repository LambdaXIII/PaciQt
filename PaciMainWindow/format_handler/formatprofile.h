#ifndef FORMATPROFILE_H
#define FORMATPROFILE_H

#include <QObject>
#include <QMap>

namespace FormatProfile {

//QString tr(char* a);

enum Format {
  Unknown,
  Paci,
  PlainText,
  Fcp7Xml,
  Fcp7XmlClipName,
  Csv,
  Srt,
  Ttml
};

const QMap<Format, QString> formatNames{
  {Paci, "啪词"},
  {PlainText, "文本台词本"},
  {Fcp7Xml, "FCP7 XML 文件"},
  {Fcp7XmlClipName, "XML 片段名模式"},
  {Csv, "逗号分割值"},
  {Srt, "SRT字幕文件"},
  {Ttml, "TTML字幕文件"}
};

const QMap<Format, QString> formatSuffixes{
  {Paci, "*.paci"},
  {PlainText, "*.txt"},
  {Fcp7Xml, "*.xml"},
  {Csv, "*.csv"},
  {Srt, "*.srt"},
  {Fcp7XmlClipName, "*.xml"},
  {Ttml, "*.xml"}
};

QString getFilter(Format f);
QString getAllFilters();
Format searchFormat(QString selectedFilter);

} //namespace FormatProfile

#endif // FORMATPROFILE_H
