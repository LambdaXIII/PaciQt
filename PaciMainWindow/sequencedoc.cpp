#include "sequencedoc.h"

SequenceDoc::SequenceDoc(QObject *parent) : QObject(parent)
{
  init();

}

void SequenceDoc::init()
{
  Q_ASSERT_X(!self, "SequenceDoc", "Only need one.");
  self = this;
}

SequenceDoc::~SequenceDoc()
{}

SequenceDoc* SequenceDoc::instance()
{
  return self;
}

SequenceDoc* SequenceDoc::self = 0;
