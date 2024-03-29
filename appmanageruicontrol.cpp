#include "appmanageruicontrol.h"

AppManagerUIControl::AppManagerUIControl()
{
    m_appMgrUICtr = QSharedPointer<local::IAppManagerUIControl>::create("com.services.appmanager", "/com/services/appmanager/uicontrol", QDBusConnection::sessionBus());
    m_appMgrUICtr->registerUIControl("mediaplayer","com.services.mediaplayer","/com/services/mediaplayer/uicontrol");
}

bool AppManagerUIControl::getAppVisible(QString appId)
{
    return m_appMgrUICtr->getAppVisible(appId);
}

bool AppManagerUIControl::requestShow(QString appId)
{
    return m_appMgrUICtr->requestShow(appId);
}
