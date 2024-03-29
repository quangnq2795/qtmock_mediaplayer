#ifndef APPMANAGERUICONTROL_H
#define APPMANAGERUICONTROL_H

#include "QString"

#include "IAppManagerUIControl.h"

class AppManagerUIControl
{
public:
    static AppManagerUIControl& getInstance()
    {
        static AppManagerUIControl instance;
        return instance;
    }

    bool getAppVisible(QString appId);
    bool requestShow(QString appId);

private:
    AppManagerUIControl(const AppManagerUIControl&) = delete;
    void operator=(const AppManagerUIControl&) = delete;

    AppManagerUIControl();

private:
    QSharedPointer<local::IAppManagerUIControl> m_appMgrUICtr;
};


#endif // APPMANAGERUICONTROL_H
