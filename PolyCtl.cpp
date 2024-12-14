// PolyCtl.cpp: реализация CPolyCtl
#include "pch.h"
#include "PolyCtl.h"


// CPolyCtl


STDMETHODIMP CPolyCtl::get_Sides(SHORT* pVal)
{
    *pVal = m_Sides;
    return S_OK;

    return S_OK;
}


STDMETHODIMP CPolyCtl::put_Sides(SHORT newVal)
{
    if (2 < newVal && newVal < 10)
    {
        m_Sides = newVal;
        return S_OK;
    }
    else
    {
        return Error(_T("Shape must have between 3 and 10 sides"));
    }

    return S_OK;
}
