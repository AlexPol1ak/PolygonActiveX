﻿// PolyCtl.cpp: реализация CPolyCtl
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
    if (3 < newVal && newVal < 10)
    {
        m_Sides = newVal;
        FireViewChange();
        return S_OK;
    }
    else
    {
        return Error(_T("Shape must have between 3 and 10 sides"));
    }

    return S_OK;
}

void CPolyCtl::CalcPoints(const RECT& rc)
{
    const double pi = 3.14159265358979;
    POINT ptCenter;
    double dblRadiusx = (rc.right - rc.left) / 2;
    double dblRadiusy = (rc.bottom - rc.top) / 2;
    double dblAngle = 3 * pi / 2; // Start at the top
    double dblDiff = 2 * pi / m_Sides; // Angle each side will make
    ptCenter.x = (rc.left + rc.right) / 2;
    ptCenter.y = (rc.top + rc.bottom) / 2;
    // Calculate the points for each side
    for (int i = 0; i < m_Sides; i++)
    {
        m_arrPoint[i].x = (long)(dblRadiusx * cos(dblAngle
        ) + ptCenter.x + 0.5);
        m_arrPoint[i].y = (long)(dblRadiusy * sin(dblAngle
        ) + ptCenter.y + 0.5);
        dblAngle += dblDiff;
    }
}

LRESULT CPolyCtl::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam,
    BOOL& /*bHandled*/)
{
    HRGN hRgn;
    WORD xPos = LOWORD(lParam);  // horizontal position of cursor
    WORD yPos = HIWORD(lParam);  // vertical position of cursor
    CalcPoints(m_rcPos);
    // Create a region from our list of points
    hRgn = CreatePolygonRgn(&m_arrPoint[0], m_Sides, WINDING);
    // If the clicked point is in our polygon then fire the ClickIn
    //  event otherwise we fire the ClickOut event
    if (PtInRegion(hRgn, xPos, yPos))
        Fire_ClickIn(xPos, yPos);
    else
        Fire_ClickOut(xPos, yPos);
    // Delete the region that we created
    DeleteObject(hRgn);
    return 0;
}

