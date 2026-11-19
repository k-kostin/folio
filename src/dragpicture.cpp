#include "dragpicture.h"

#include <QQuickItem>

bool DragPicture::capture(QQuickItem *item) {
    if (!item)
        return false;
    auto grab = item->grabToImage();
    if (!grab)
        return false;
    m_source = item;
    m_grab = grab;
    connect(grab.data(), &QQuickItemGrabResult::ready, this, [this, request = grab.data()] {
        if (m_grab.data() == request && m_source)
            emit ready();
    });
    return true;
}

QUrl DragPicture::url() const {
    return m_grab ? m_grab->url() : QUrl();
}
