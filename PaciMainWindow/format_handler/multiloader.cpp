#include "multiloader.h"

using namespace FormatProfile;




Multiloader::Multiloader(QString _path, QString _selectedFilter, QObject *parent)
  : QObject(parent)
{

}

const QMap<Format, std::function<BaseLoader*(QString)>> Multiloader::functionMap =  {
  {PlainText, &createInstance<TextLoader>},
};

