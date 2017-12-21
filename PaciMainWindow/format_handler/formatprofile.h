#ifndef FORMATPROFILE_H
#define FORMATPROFILE_H

#include <QObject>
#include <QMap>


class FormatProfile : public QObject
{
  Q_OBJECT
public:
  FormatProfile();

  enum Format {
    Unknown,
    PlainText,
  };

  QMap<Format, QString> formatNames;
  QMap<Format, QString> formatSuffixes;

  QString getFilter(Format f);
  QString getAllFilters();
  Format searchFormat(QString selectedFilter);

};

#endif // FORMATPROFILE_H
