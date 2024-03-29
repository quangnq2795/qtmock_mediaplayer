#ifndef IAPPUICONTROL_H
#define IAPPUICONTROL_H

#include <QObject>

class IAppUIControl : public QObject {
    Q_OBJECT

public:
    explicit IAppUIControl(QObject *parent = nullptr) {};

public Q_SLOTS:
    virtual bool setAppVisible(bool val) = 0;
};

#endif // IAPPUICONTROL_H
