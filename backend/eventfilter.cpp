#include <QMainWindow>
#include <QKeyEvent>

#include "eventfilter.h"
#include "preferences.h"
#include "trace.h"

EventFilter::EventFilter(QObject *parent): QObject(parent), active(false) {
    TRACE;
    resourceSet = new ResourcePolicy::ResourceSet("player");
    resourceSet->addResourceObject(new ResourcePolicy::ScaleButtonResource);
    settings = Preferences::instance();
    captureVolumeKeys = settings->value("usevolumekeys").toBool();
    connect(settings, SIGNAL(valueChanged(QString)), this, SLOT(onSettingChanged(QString)));
}

EventFilter::~EventFilter() {
    resourceSet->release();
    resourceSet->deleteResource(ResourcePolicy::ScaleButtonType);
    delete resourceSet;
}

bool EventFilter::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::ApplicationDeactivate) {
        qDebug() << "EventFilter::eventFilter: Releasing volume keys";
        active = false;
        resourceSet->release();
    } else if (event->type() == QEvent::ApplicationActivate) {
        active = true;
        if (captureVolumeKeys) {
            qDebug() << "EventFilter::eventFilter: Acquiring volume keys";
            resourceSet->acquire();
        }
    } else if (event->type() == QEvent::ActivationChange) {
        qDebug() << "EventFilter::eventFilter: ActivationChange";
        if (active) {
            active = false;
            qDebug() << "EventFilter::eventFilter: Releasing volume keys";
            resourceSet->release();
        } else {
            active = true;
            if (captureVolumeKeys) {
                qDebug() << "EventFilter::eventFilter: Acquiring volume keys";
                resourceSet->acquire();
            }
        }
    } else if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        int key = keyEvent->key();
        if (!captureVolumeKeys && (key == Qt::Key_VolumeUp || key == Qt::Key_VolumeDown)) {
            qDebug() << "EventFilter::eventFilter: Ate volume key";
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}

void EventFilter::onSettingChanged(const QString &key) {
    TRACE;
    if (key != "usevolumekeys") {
        return;
    }
    captureVolumeKeys = settings->value(key).toBool();
    qDebug() << "Capture volume keys?" << captureVolumeKeys;
    if (active) {
        if (captureVolumeKeys) {
            qDebug() << "Acquiring volume keys";
            resourceSet->acquire();
        } else {
            qDebug() << "Releasing volume keys";
            resourceSet->release();
        }
    } else {
        qDebug() << "Not active";
    }
}
