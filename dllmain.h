// dllmain.h: объявление класса модуля.

class CPolygonActiveXModule : public ATL::CAtlDllModuleT< CPolygonActiveXModule >
{
public :
	DECLARE_LIBID(LIBID_PolygonActiveXLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_POLYGONACTIVEX, "{b95af866-f0b0-41a6-bbbc-79d2fd29da77}")
};

extern class CPolygonActiveXModule _AtlModule;
