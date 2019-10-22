#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>

static const unsigned char qt_resource_tree[] = {
0,
0,0,0,0,2,0,0,0,10,0,0,0,1,0,0,1,
12,0,0,0,0,0,1,0,0,0,0,0,0,0,172,0,
0,0,0,0,1,0,0,0,0,0,0,0,142,0,0,0,
0,0,1,0,0,0,0,0,0,0,78,0,0,0,0,0,
1,0,0,0,0,0,0,0,108,0,0,0,0,0,1,0,
0,0,0,0,0,0,8,0,0,0,0,0,1,0,0,0,
0,0,0,1,38,0,0,0,0,0,1,0,0,0,0,0,
0,0,240,0,0,0,0,0,1,0,0,0,0,0,0,0,
48,0,0,0,0,0,1,0,0,0,0,0,0,0,200,0,
0,0,0,0,1,0,0,0,0};
static const unsigned char qt_resource_names[] = {
0,
1,0,0,0,47,0,47,0,17,8,137,115,28,0,78,0,
101,0,116,0,119,0,111,0,114,0,107,0,66,0,97,0,
110,0,110,0,101,0,114,0,46,0,113,0,109,0,108,0,
12,13,39,134,92,0,80,0,108,0,111,0,116,0,77,0,
97,0,105,0,110,0,46,0,113,0,109,0,108,0,12,5,
180,69,124,0,74,0,111,0,121,0,115,0,116,0,105,0,
99,0,107,0,46,0,113,0,109,0,108,0,14,7,235,75,
124,0,85,0,97,0,118,0,77,0,97,0,112,0,70,0,
111,0,114,0,109,0,46,0,113,0,109,0,108,0,12,5,
48,135,188,0,80,0,108,0,111,0,116,0,86,0,105,0,
101,0,119,0,46,0,113,0,109,0,108,0,11,4,107,8,
156,0,80,0,108,0,97,0,110,0,110,0,101,0,114,0,
46,0,113,0,109,0,108,0,17,14,217,244,156,0,68,0,
106,0,105,0,65,0,99,0,116,0,105,0,118,0,97,0,
116,0,101,0,85,0,73,0,46,0,113,0,109,0,108,0,
11,12,197,40,92,0,68,0,100,0,115,0,77,0,101,0,
110,0,117,0,46,0,113,0,109,0,108,0,10,3,136,41,
92,0,85,0,97,0,118,0,77,0,97,0,112,0,46,0,
113,0,109,0,108,0,9,11,126,164,252,0,115,0,112,0,
101,0,97,0,107,0,46,0,113,0,109,0,108};
static const unsigned char qt_resource_empty_payout[] = { 0, 0, 0, 0, 0 };
QT_BEGIN_NAMESPACE
extern Q_CORE_EXPORT bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
QT_END_NAMESPACE
namespace QmlCacheGeneratedCode {
namespace _0x5f__speak_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__UavMap_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__DdsMenu_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__DjiActivateUI_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Planner_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__PlotView_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__UavMapForm_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Joystick_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__PlotMain_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__NetworkBanner_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
        resourcePathToCachedUnit.insert(QStringLiteral("/speak.qml"), &QmlCacheGeneratedCode::_0x5f__speak_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/UavMap.qml"), &QmlCacheGeneratedCode::_0x5f__UavMap_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/DdsMenu.qml"), &QmlCacheGeneratedCode::_0x5f__DdsMenu_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/DjiActivateUI.qml"), &QmlCacheGeneratedCode::_0x5f__DjiActivateUI_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Planner.qml"), &QmlCacheGeneratedCode::_0x5f__Planner_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/PlotView.qml"), &QmlCacheGeneratedCode::_0x5f__PlotView_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/UavMapForm.qml"), &QmlCacheGeneratedCode::_0x5f__UavMapForm_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Joystick.qml"), &QmlCacheGeneratedCode::_0x5f__Joystick_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/PlotMain.qml"), &QmlCacheGeneratedCode::_0x5f__PlotMain_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/NetworkBanner.qml"), &QmlCacheGeneratedCode::_0x5f__NetworkBanner_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.version = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
QT_PREPEND_NAMESPACE(qRegisterResourceData)(/*version*/0x01, qt_resource_tree, qt_resource_names, qt_resource_empty_payout);
}
const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qml)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qml))
int QT_MANGLE_NAMESPACE(qCleanupResources_qml)() {
    return 1;
}
