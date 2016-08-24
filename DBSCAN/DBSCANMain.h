/***************************************************************
 * Name:      DBSCANMain.h
 * Purpose:   Defines Application Frame
 * Author:    Gaby (2823925809@qq.com)
 * Created:   2016-06-07
 * Copyright: Gaby ()
 * License:
 **************************************************************/

#ifndef DBSCANMAIN_H
#define DBSCANMAIN_H

//(*Headers(DBSCANFrame)
#include <wx/scrolwin.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <wx/dcclient.h>
#include <wx/pen.h>
#include <list>
#include <vector>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
#include "Point.h"

class DBSCANFrame: public wxFrame
{
    public:

        DBSCANFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~DBSCANFrame();

    private:

        //(*Handlers(DBSCANFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnPaintPanelLeftDown(wxMouseEvent& event);
        void OnPaintPanelPaint(wxPaintEvent& event);
        void OnSpinCtrl_EpsChange(wxSpinEvent& event);
        void OnSpinCtrl_MinPtsChange(wxSpinEvent& event);
        void OnButtonCompleteClick(wxCommandEvent& event);
        void OnButtonStepClick(wxCommandEvent& event);
        void OnButtonResetClick(wxCommandEvent& event);
        void OnPaintPanelMouseMove(wxMouseEvent& event);
        void OnButtonClearClick(wxCommandEvent& event);
        void OnMenuItem3Selected(wxCommandEvent& event);
        void OnMenuItemReadSelected(wxCommandEvent& event);
        void OnMenuItemSaveSelected(wxCommandEvent& event);
        //*)

        //(*Identifiers(DBSCANFrame)
        static const long ID_PaintPanel;
        static const long ID_SCROLLEDWINDOW1;
        static const long ID_STATICTEXT1;
        static const long ID_SPINCTRLEPS;
        static const long ID_PANEL1;
        static const long ID_STATICTEXT2;
        static const long ID_SPINCTRLMINPTS;
        static const long ID_PANEL2;
        static const long ID_BUTTONStep;
        static const long ID_BUTTONComplete;
        static const long ID_BUTTONReset;
        static const long ID_BUTTONClear;
        static const long ID_PANEL3;
        static const long ID_MainPanel;
        static const long ID_MENUITEMREAD;
        static const long ID_MENUITEMSAVE;
        static const long ID_MENUITEM1;
        static const long ID_MENUITEM2;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(DBSCANFrame)
        wxMenuItem* MenuItemRead;
        wxPanel* PaintPanel;
        wxButton* ButtonStep;
        wxMenuItem* MenuItemSave;
        wxSpinCtrl* SpinCtrl_MinPts;
        wxStaticText* StaticText2;
        wxScrolledWindow* ScrolledWindow1;
        wxMenu* Menu3;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxButton* ButtonClear;
        wxPanel* Panel3;
        wxMenuItem* MenuItem3;
        wxStatusBar* StatusBar1;
        wxPanel* MainPanel;
        wxButton* ButtonReset;
        wxPanel* Panel2;
        wxButton* ButtonComplete;
        wxSpinCtrl* SpinCtrl_Eps;
        //*)

        DECLARE_EVENT_TABLE()

        std::vector<wxButton*> ClusterButton;
        std::vector<long> ButtonID;
        wxFont ButtonFont{14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial Narrow"),wxFONTENCODING_DEFAULT};

        std::list<Point> D; //数据集D
        int Eps = 20;       //领域半径
        int MinPts = 3;     //最小包含点数
        int cluster_count = 0;

        std::list<Point>::iterator iD = D.begin();
        std::list<Point*> NEps;
        std::list<Point*> NewNEps;
        std::list<Point*>::iterator iNEps;
        bool NextCluster = true;
        bool ShowCoreEpsField = true;

        void DBSCAN();
        void DBSCANByStep();

        void init();
        void MarkNoise();
        void FindNewCluster();
        bool FindNewCoreInCluster();
        int getNeighbours(const Point &p, std::list<Point*> &cluster);
        void ExpandCluster(Point &p, std::list<Point*> &cluster);
        void ExpandClusterByStep();
        wxColour ChangeIntoColor(int color);
        void ChangeClusterButton();
        void AddClusterButton(int i);
        void UpdateInterface();
        void ResetDBSCAN();

        void OnClusterButtonClick(wxCommandEvent& event);

        wxColour XorColour(wxColour color);
        void test(int cluster);
};

#endif // DBSCANMAIN_H
