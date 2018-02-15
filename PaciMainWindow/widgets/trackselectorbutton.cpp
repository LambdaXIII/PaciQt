#include "trackselectorbutton.h"
#include <QPainter>
#include <QFontMetrics>

#define OVERLAY_OPACITY 30
#define OVERLAY_ALPHA 255.0/100.0 * OVERLAY_OPACITY

#define OVERLAY_FONT QFont(font().family(), 25)
#define PROP_FONT QFont(font().family(), 8)
#define TAG_FONT QFont(font().family(), 20)

#define TIMER_FPS 12
#define TIMER_INT 1000/TIMER_FPS
#define OVERLAY_SPEED 1

TrackSelectorButton::TrackSelectorButton(int i, Track *_track, QWidget *parent)
  : PaciBaseButton(parent), m_trackIndex(i), m_track(_track)
{
  setCheckable(true);
  setMinimumSize(150, 150);

  if (track()->tag().isEmpty()) {
    setText(QString("[%1]").arg(trackIndex() + 1));
  } else {
    setText(track()->tag());
  }

  drawPreviewMap();
  m_overlay_offset = 0;
  offsetTimer = new QTimer(this);
  offsetTimer->setInterval(TIMER_INT);
  connect(offsetTimer, &QTimer::timeout, this, &TrackSelectorButton::updateOffset);
  offsetTimer->start();
}

void TrackSelectorButton::updateOffset()
{
  if (! m_previewMap.isNull()) {
    if (m_overlay_offset > m_previewMap.height())
      m_overlay_offset -= m_previewMap.height();
    m_overlay_offset += OVERLAY_SPEED;
  }
  update(centralRect());
}

QStringList TrackSelectorButton::getPreviewLines()
{
  QStringList res;
  if (track()->isEmpty())
    res << tr("[空轨道]");
  else {
    int count = track()->size() >= 10 ? 9 : track()->size();

    for (int i = 0; i < count; i++) {
      res << track()->at(i)->content();
    }
    if (count >= 9) {
      res << "...";
    }
  }
  return res;
}

QString TrackSelectorButton::getTopLeftText()
{
  auto t = tr("轨道号:%1").arg(trackIndex());
  return t;
}

QString TrackSelectorButton::getBottomRightText()
{
  auto s = tr("片段数:%1").arg(track()->length());
  return s;
}

void TrackSelectorButton::drawPreviewMap()
{
  QString previewLines = getPreviewLines().join("\n");
  QSize size = QFontMetrics(OVERLAY_FONT).size(Qt::TextExpandTabs, previewLines);
  m_previewMap = QPixmap(size);
  m_previewMap.fill(Qt::transparent);
  QPainter p(&m_previewMap);
  QColor c(Qt::darkGray);
  c.setAlpha(OVERLAY_ALPHA);
  p.setPen(c);
  p.setFont(OVERLAY_FONT);
  p.drawText(m_previewMap.rect(), Qt::AlignTop | Qt::AlignLeft, previewLines);
}

void TrackSelectorButton::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  //TODO: 减少重绘工作量
  paintButtonShape(painter);
//  paintCheckableOverlay(painter);
  painter.drawTiledPixmap(centralRect(), m_previewMap, QPoint(0, m_overlay_offset));

  painter.setPen(Qt::white);
  painter.setFont(PROP_FONT);
  painter.drawText(centralRect(), Qt::AlignTop | Qt::AlignLeft, getTopLeftText());
  painter.drawText(centralRect(), Qt::AlignBottom | Qt::AlignRight, getBottomRightText());

  painter.setFont(TAG_FONT);
  painter.drawText(centralRect(), Qt::AlignCenter, text());

  painter.setFont(PROP_FONT);
  painter.setPen(isChecked() ? Qt::green : Qt::gray);
  painter.drawText(centralRect(), Qt::AlignBottom | Qt::AlignLeft,
                   isChecked() ? tr("已选") : tr("未选")
                  );

}
