#ifndef IAPPUICONTROLRECEIVER_H
#define IAPPUICONTROLRECEIVER_H

#include <QObject>
#include "iappuicontrol.h"
#include "iappuicontroladaptor.h"

class AppUIControl;

class IAppUIControlReceiver: public IAppUIControl
{
    Q_OBJECT
public:
    IAppUIControlReceiver(AppUIControl& uiCtr,QObject *parent = nullptr);

    bool setAppVisible(bool val) override;
signals:
    void appVisibleChanged(bool val);
    
private:
    AppUIControl& m_uiCtr;
    IAppUIControlAdaptor* m_adapter;
};

#endif // IAPPUICONTROLRECEIVER_H
