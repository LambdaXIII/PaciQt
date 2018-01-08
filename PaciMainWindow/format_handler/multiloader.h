#ifndef MULTILOADER_H
#define MULTILOADER_H

#include <QObject>
#include "formatprofile.h"
#include "candy_macros.h"
#include "sequence.h"

namespace Multiloader {
using namespace FormatProfile;




Sequence* loadPlainText(QString path);

const QMap<Format, std::function<Sequence*(QString)>> functionMap{
  {PlainText, &loadPlainText},
};

} //namespace Multiloader

#endif // MULTILOADER_H
