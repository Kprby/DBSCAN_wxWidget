/***************************************************************
 * Name:      DBSCANMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Gaby (2823925809@qq.com)
 * Created:   2016-06-07
 * Copyright: Gaby ()
 * License:
 **************************************************************/

#include "DBSCANMain.h"
#include <wx/msgdlg.h>
#include <wx/string.h>
#include <wx/colordlg.h>
#include <wx/filedlg.h>
#include <fstream>

//(*InternalHeaders(DBSCANFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(DBSCANFrame)
const long DBSCANFrame::ID_PaintPanel = wxNewId();
const long DBSCANFrame::ID_SCROLLEDWINDOW1 = wxNewId();
const long DBSCANFrame::ID_STATICTEXT1 = wxNewId();
const long DBSCANFrame::ID_SPINCTRLEPS = wxNewId();
const long DBSCANFrame::ID_PANEL1 = wxNewId();
const long DBSCANFrame::ID_STATICTEXT2 = wxNewId();
const long DBSCANFrame::ID_SPINCTRLMINPTS = wxNewId();
const long DBSCANFrame::ID_PANEL2 = wxNewId();
const long DBSCANFrame::ID_BUTTONStep = wxNewId();
const long DBSCANFrame::ID_BUTTONComplete = wxNewId();
const long DBSCANFrame::ID_BUTTONReset = wxNewId();
const long DBSCANFrame::ID_BUTTONClear = wxNewId();
const long DBSCANFrame::ID_PANEL3 = wxNewId();
const long DBSCANFrame::ID_MainPanel = wxNewId();
const long DBSCANFrame::ID_MENUITEMREAD = wxNewId();
const long DBSCANFrame::ID_MENUITEMSAVE = wxNewId();
const long DBSCANFrame::ID_MENUITEM1 = wxNewId();
const long DBSCANFrame::ID_MENUITEM2 = wxNewId();
const long DBSCANFrame::idMenuAbout = wxNewId();
const long DBSCANFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DBSCANFrame,wxFrame)
    //(*EventTable(DBSCANFrame)
    //*)
END_EVENT_TABLE()

DBSCANFrame::DBSCANFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(DBSCANFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(630,640));
    Move(wxPoint(0,0));
    MainPanel = new wxPanel(this, ID_MainPanel, wxPoint(0,0), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_MainPanel"));
    PaintPanel = new wxPanel(MainPanel, ID_PaintPanel, wxPoint(0,0), wxSize(500,500), wxSUNKEN_BORDER|wxTAB_TRAVERSAL, _T("ID_PaintPanel"));
    PaintPanel->SetBackgroundColour(wxColour(255,255,255));
    ScrolledWindow1 = new wxScrolledWindow(MainPanel, ID_SCROLLEDWINDOW1, wxPoint(500,0), wxSize(120,500), wxSUNKEN_BORDER|wxVSCROLL|wxHSCROLL, _T("ID_SCROLLEDWINDOW1"));
    Panel1 = new wxPanel(MainPanel, ID_PANEL1, wxPoint(0,500), wxSize(250,50), wxSUNKEN_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetBackgroundColour(wxColour(174,244,244));
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("领域半径(Eps)"), wxPoint(10,13), wxSize(110,24), wxST_NO_AUTORESIZE|wxALIGN_CENTRE|wxRAISED_BORDER, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    SpinCtrl_Eps = new wxSpinCtrl(Panel1, ID_SPINCTRLEPS, _T("20"), wxPoint(120,13), wxSize(70,24), wxRAISED_BORDER, 1, 500, 20, _T("ID_SPINCTRLEPS"));
    SpinCtrl_Eps->SetValue(_T("20"));
    wxFont SpinCtrl_EpsFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SpinCtrl_Eps->SetFont(SpinCtrl_EpsFont);
    Panel2 = new wxPanel(MainPanel, ID_PANEL2, wxPoint(250,500), wxSize(250,50), wxSUNKEN_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Panel2->SetBackgroundColour(wxColour(255,247,140));
    StaticText2 = new wxStaticText(Panel2, ID_STATICTEXT2, _("最小包含点数(MinPts)"), wxPoint(10,13), wxSize(160,24), wxST_NO_AUTORESIZE|wxALIGN_CENTRE|wxRAISED_BORDER, _T("ID_STATICTEXT2"));
    wxFont StaticText2Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    SpinCtrl_MinPts = new wxSpinCtrl(Panel2, ID_SPINCTRLMINPTS, _T("3"), wxPoint(170,13), wxSize(70,24), wxRAISED_BORDER, 1, 32767, 3, _T("ID_SPINCTRLMINPTS"));
    SpinCtrl_MinPts->SetValue(_T("3"));
    wxFont SpinCtrl_MinPtsFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SpinCtrl_MinPts->SetFont(SpinCtrl_MinPtsFont);
    Panel3 = new wxPanel(MainPanel, ID_PANEL3, wxPoint(0,550), wxSize(500,40), wxSUNKEN_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Panel3->SetBackgroundColour(wxColour(121,255,121));
    ButtonStep = new wxButton(Panel3, ID_BUTTONStep, _("逐步聚类"), wxPoint(20,5), wxSize(100,30), 0, wxDefaultValidator, _T("ID_BUTTONStep"));
    ButtonStep->Disable();
    wxFont ButtonStepFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    ButtonStep->SetFont(ButtonStepFont);
    ButtonComplete = new wxButton(Panel3, ID_BUTTONComplete, _("完全聚类"), wxPoint(140,5), wxSize(100,30), 0, wxDefaultValidator, _T("ID_BUTTONComplete"));
    ButtonComplete->Disable();
    wxFont ButtonCompleteFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    ButtonComplete->SetFont(ButtonCompleteFont);
    ButtonReset = new wxButton(Panel3, ID_BUTTONReset, _("重置"), wxPoint(260,5), wxSize(100,30), 0, wxDefaultValidator, _T("ID_BUTTONReset"));
    wxFont ButtonResetFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    ButtonReset->SetFont(ButtonResetFont);
    ButtonClear = new wxButton(Panel3, ID_BUTTONClear, _("清空"), wxPoint(380,5), wxSize(100,30), 0, wxDefaultValidator, _T("ID_BUTTONClear"));
    wxFont ButtonClearFont(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    ButtonClear->SetFont(ButtonClearFont);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItemRead = new wxMenuItem(Menu1, ID_MENUITEMREAD, _("Read"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItemRead);
    MenuItemSave = new wxMenuItem(Menu1, ID_MENUITEMSAVE, _("Save"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItemSave);
    MenuItem1 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu3, ID_MENUITEM2, _("显示核心点的Eps领域"), wxEmptyString, wxITEM_CHECK);
    Menu3->Append(MenuItem3);
    MenuItem3->Check(true);
    MenuBar1->Append(Menu3, _("Show"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    PaintPanel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&DBSCANFrame::OnPaintPanelPaint,0,this);
    PaintPanel->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&DBSCANFrame::OnPaintPanelLeftDown,0,this);
    PaintPanel->Connect(wxEVT_MOTION,(wxObjectEventFunction)&DBSCANFrame::OnPaintPanelMouseMove,0,this);
    Connect(ID_SPINCTRLEPS,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DBSCANFrame::OnSpinCtrl_EpsChange);
    Connect(ID_SPINCTRLMINPTS,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DBSCANFrame::OnSpinCtrl_MinPtsChange);
    Connect(ID_BUTTONStep,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DBSCANFrame::OnButtonStepClick);
    Connect(ID_BUTTONComplete,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DBSCANFrame::OnButtonCompleteClick);
    Connect(ID_BUTTONReset,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DBSCANFrame::OnButtonResetClick);
    Connect(ID_BUTTONClear,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DBSCANFrame::OnButtonClearClick);
    Connect(ID_MENUITEMREAD,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DBSCANFrame::OnMenuItemReadSelected);
    Connect(ID_MENUITEMSAVE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DBSCANFrame::OnMenuItemSaveSelected);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DBSCANFrame::OnQuit);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DBSCANFrame::OnMenuItem3Selected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DBSCANFrame::OnAbout);
    //*)

    this->SetLabel("基于密度的聚类算法DBSCAN");

    for (int i = 0; i < 7; ++i)
    {
        ButtonID.push_back(wxNewId());
        ClusterButton.push_back(new wxButton(ScrolledWindow1, ButtonID[i], _(""), wxPoint(0,i*100), wxSize(100,100)));
        ClusterButton[i]->SetFont(ButtonFont);
        ClusterButton[i]->SetLabel(wxString("簇") << i);
        Connect(ButtonID[i],wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DBSCANFrame::OnClusterButtonClick);
    }

    ClusterButton[0]->SetLabel(wxString("噪声"));

    ClusterButton[0]->SetBackgroundColour(wxColour(150, 150, 150));
    ClusterButton[1]->SetBackgroundColour(wxColour(255, 0, 0));
    ClusterButton[2]->SetBackgroundColour(wxColour(0, 255, 0));
    ClusterButton[3]->SetBackgroundColour(wxColour(0, 0, 255));
    ClusterButton[4]->SetBackgroundColour(wxColour(255, 255, 0));
    ClusterButton[5]->SetBackgroundColour(wxColour(255, 0, 255));
    ClusterButton[6]->SetBackgroundColour(wxColour(0, 255, 255));

    ChangeClusterButton();
    ScrolledWindow1->SetScrollRate(0, 100);
}

DBSCANFrame::~DBSCANFrame()
{
    //(*Destroy(DBSCANFrame)
    //*)
}


void DBSCANFrame::DBSCAN()
{
    init(); //初始化
    for (Point &pt : D) //遍历数据集D
    {
        if (!pt.visited)    //判断点pt是否访问过
        {
            pt.visited = true;
            std::list<Point*> cluster;  //创建空的点集
            if (getNeighbours(pt, cluster) >= MinPts)   //判断点pt是否为核心点
            {
                ++cluster_count;    //簇的个数加1
                ExpandCluster(pt, cluster); //扩展核心点pt所在的簇
            }
        }
    }
    MarkNoise();    //将未归入任何一个簇的点标记为噪声
}

void DBSCANFrame::DBSCANByStep()
{
    if (NextCluster)
    {
        if (iD != D.end())
        {
            if (iD == D.begin())
            {
                init();
                SpinCtrl_Eps->Enable(false);
                SpinCtrl_MinPts->Enable(false);
            }
            FindNewCluster();
        }
    }
    else
    {
        ExpandClusterByStep();
    }
}

wxColour DBSCANFrame::XorColour(wxColour color)
{
    wxColour xc;
    wxUint32 x = 0x00FFFFFF;
    xc.SetRGB(x ^ color.GetRGB());
    return xc;
}

void DBSCANFrame::init()
{
    cluster_count = 0;
    for (Point &pt : D)
    {
        pt.cluster = -1;
        pt.type = 0;
        pt.visited = false;
    }
}

void DBSCANFrame::MarkNoise()
{
    for (Point &pt : D)
    {
        if (pt.cluster == -1)
        {
            pt.cluster = 0;
        }
    }
}

void DBSCANFrame::FindNewCluster()
{
    while (iD != D.end())
    {
        Point &pt = *iD;
        ++iD;
        if (!pt.visited)
        {
            pt.visited = true;
            if (getNeighbours(pt, NewNEps) >= MinPts)
            {
                NEps.clear();
                ++cluster_count;
                NEps.push_back(&pt);
                iNEps = NEps.begin();
                ExpandClusterByStep();
                break;
            }
        }
    }
    if (iD == D.end())
    {
        SpinCtrl_Eps->Enable(true);
        SpinCtrl_MinPts->Enable(true);
        MarkNoise();
    }
}

bool DBSCANFrame::FindNewCoreInCluster()
{
    while (iNEps != NEps.end())
    {
        Point *cp = *iNEps;
        if (!cp->visited)
        {
            cp->visited = true;
            if (getNeighbours(*cp, NewNEps) >= MinPts)
            {
                return true;
            }
        }
        ++iNEps;
    }
    return false;
}

//在参数cluster保存点p的Eps半径内的点的集合。返回点p的Eps半径内的点的数目
int DBSCANFrame::getNeighbours(const Point &p, std::list<Point*> &cluster)
{
    cluster.clear();    //清空点集cluster
    int n = 0;
    for (Point &pt : D) //遍历数据集D
    {
        if (pt.distance(p) <= Eps)  //判断点pt是否在点p的Eps邻域中
        {
            ++n;
            cluster.push_back(&pt); //将点pt加入到点集cluster中
        }
    }
    return n;
}

//参数cluster为核心点p的Eps半径内的点的集合，应由函数getNeighbours得出。
//将未归入某个簇且与核心点p密度相连的点加入到与核心点p相同的簇
void DBSCANFrame::ExpandCluster(Point &p, std::list<Point*> &cluster)
{
    p.type = 1;
    for (Point *pt : cluster)   //遍历点集cluster
    {
        if (!pt->visited)   //判断点pt是否访问过
        {
            pt->visited = true;
            std::list<Point*> Newcluster;   //创建新的点集
            if (getNeighbours(*pt, Newcluster) >= MinPts)   //判断点pt是否为核心点
            {
                pt->type = 1;
                cluster.splice(cluster.end(), Newcluster);  //扩展点集cluster
            }
        }
        if (pt->cluster == -1)  //判断点pt是否归入某个簇
        {
            pt->cluster = cluster_count;
        }
    }
}

void DBSCANFrame::ExpandClusterByStep()
{
    (*iNEps)->type = 1;
    for (Point *ncp : NewNEps)
    {
        if (ncp->cluster == -1)
        {
            ncp->cluster = cluster_count;
        }
    }
    NEps.splice(NEps.end(), NewNEps);
    ++iNEps;
    if (FindNewCoreInCluster())
    {
        NextCluster = false;
    }
    else
    {
        NextCluster = true;
    }
}

wxColour DBSCANFrame::ChangeIntoColor(int color)
{
    int a, b, c, d;
    d = color % 3;
    a = color % 255;
    color /= 255;
    b = color % 255;
    color /= 255;
    c = color % 255;

    int f, s;
    f = a % 9;
    s = a / 9;
    a = (f * 255 / 9 + s) % 255;

    f = b % 9 + 3;
    s = b / 9;
    b = (f * 255 / 9 + s) % 255;

    f = c % 9 + 6;
    s = c / 9;
    c = (f * 255 / 9 + s) % 255;

    switch (d)
    {
    case 0:
        return wxColour(a, b, c);
    case 1:
        return wxColour(b, c, a);
    case 2:
        return wxColour(c, a, b);
    }

    return wxColour(a, b, c);
}

void DBSCANFrame::ChangeClusterButton()
{
    ScrolledWindow1->SetVirtualSize(100, 100);
    ScrolledWindow1->SetVirtualSize(100, 100 * (cluster_count + 1));
    int len = ClusterButton.size();
    if (len > cluster_count)
    {
        int i;
        for (i = 0; i <= cluster_count; ++i)
        {
            if (!ClusterButton[i]->IsShown())
            {
                ClusterButton[i]->Show();
            }
        }
        while (i < len)
        {
            if (ClusterButton[i]->IsShown())
            {
                ClusterButton[i]->Hide();
            }
            ++i;
        }
    }
    else
    {
        while (len <= cluster_count)
        {
            AddClusterButton(len);
            ++len;
        }
        for (wxButton *bt : ClusterButton)
        {
            if (!bt->IsShown())
            {
                bt->Show();
            }
        }
    }
}

void DBSCANFrame::AddClusterButton(int i)
{
    ButtonID.push_back(wxNewId());
    ClusterButton.push_back(new wxButton(ScrolledWindow1, ButtonID[i], _(""), wxPoint(0,i*100), wxSize(100,100)));
    ClusterButton[i]->SetFont(ButtonFont);
    ClusterButton[i]->SetLabel(wxString("簇") << i);
    ClusterButton[i]->SetBackgroundColour(ChangeIntoColor(i));
    Connect(ButtonID[i],wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DBSCANFrame::OnClusterButtonClick);
}

void DBSCANFrame::UpdateInterface()
{
    ChangeClusterButton();
    PaintPanel->Refresh();
    PaintPanel->Update();
}

void DBSCANFrame::ResetDBSCAN()
{
    init();
    iD = D.begin();
    NextCluster = true;
    SpinCtrl_Eps->Enable();
    SpinCtrl_MinPts->Enable();
    UpdateInterface();
}

void DBSCANFrame::test(int cluster)
{
    for (Point &p : D)
    {
        p.cluster = cluster;
    }
}

void DBSCANFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void DBSCANFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void DBSCANFrame::OnPaintPanelLeftDown(wxMouseEvent& event)
{
    wxClientDC dc(PaintPanel);
    wxColour cr(0, 0, 0);
    wxPen pen(cr, 1);
    wxBrush brush(cr);
    dc.SetPen(pen);
    dc.SetBrush(brush);
    wxPoint pt(event.GetLogicalPosition(dc));
    D.push_back(Point(pt.x, pt.y));
    init();
    iD = D.begin();
    NextCluster = true;
    SpinCtrl_Eps->Enable();
    SpinCtrl_MinPts->Enable();
    ButtonStep->Enable();
    ButtonComplete->Enable();
    dc.DrawCircle(pt, 2);
}

void DBSCANFrame::OnPaintPanelPaint(wxPaintEvent& event)
{
    wxPaintDC dc(PaintPanel);
    for (Point &pt : D)
    {
        wxColour cr;
        if (pt.cluster != -1)
        {
            cr = ClusterButton[pt.cluster]->GetBackgroundColour();
        }
        else
        {
            cr.Set(0, 0, 0);
        }
        wxPen pen(cr, 1);
        wxBrush brush(cr);
        dc.SetPen(pen);
        dc.SetBrush(brush);
        dc.DrawCircle(pt.x, pt.y, 2);
    }

    if (ShowCoreEpsField)
    {
        for (Point &pt : D)
        {
            if (pt.type == 1)
            {
                wxColour cr;
                if (pt.cluster != -1)
                {
                    cr = ClusterButton[pt.cluster]->GetBackgroundColour();
                }
                else
                {
                    cr.Set(0, 0, 0);
                }
                wxPen pen(cr, 1);
                wxBrush brush(cr, wxTRANSPARENT);
                dc.SetPen(pen);
                dc.SetBrush(brush);
                dc.DrawCircle(pt.x, pt.y, Eps);
            }
        }
    }
}

void DBSCANFrame::OnSpinCtrl_EpsChange(wxSpinEvent& event)
{
    Eps = SpinCtrl_Eps->GetValue();
    ResetDBSCAN();
}

void DBSCANFrame::OnSpinCtrl_MinPtsChange(wxSpinEvent& event)
{
    MinPts = SpinCtrl_MinPts->GetValue();
    ResetDBSCAN();
}

void DBSCANFrame::OnButtonCompleteClick(wxCommandEvent& event)
{
    DBSCAN();
    iD  = D.end();
    NextCluster = true;
    SpinCtrl_Eps->Enable(true);
    SpinCtrl_MinPts->Enable(true);
    UpdateInterface();
}

void DBSCANFrame::OnButtonStepClick(wxCommandEvent& event)
{
    DBSCANByStep();
    UpdateInterface();
}

void DBSCANFrame::OnButtonResetClick(wxCommandEvent& event)
{
    ResetDBSCAN();
}

void DBSCANFrame::OnPaintPanelMouseMove(wxMouseEvent& event)
{
    wxString s("(");
    wxClientDC dc(PaintPanel);
    wxPoint pt(event.GetLogicalPosition(dc));
    s << pt.x << ',' << pt.y << ')';
    StatusBar1->SetStatusText(s);
}

void DBSCANFrame::OnButtonClearClick(wxCommandEvent& event)
{
    ButtonStep->Enable(false);
    ButtonComplete->Enable(false);
    cluster_count = 0;
    D.clear();
    iD = D.begin();
    NextCluster = true;
    UpdateInterface();
}

void DBSCANFrame::OnClusterButtonClick(wxCommandEvent& event)
{
    wxButton *bt = (wxButton*)event.GetEventObject();
    wxColourData cdata;
    cdata.SetColour(bt->GetBackgroundColour());
    wxColourDialog cdialog(this, &cdata);
    if (cdialog.ShowModal() == wxID_OK)
    {
        bt->SetBackgroundColour(cdialog.GetColourData().GetColour());
    }
    PaintPanel->Refresh();
    PaintPanel->Update();
}

void DBSCANFrame::OnMenuItem3Selected(wxCommandEvent& event)
{
    ShowCoreEpsField = !ShowCoreEpsField;
    PaintPanel->Refresh();
    PaintPanel->Update();
}


void DBSCANFrame::OnMenuItemReadSelected(wxCommandEvent& event)
{
    wxFileDialog
        openFileDialog(this, _("打开点集"), "", "",
                       "txt files (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_OK)
    {
        std::ifstream input(openFileDialog.GetPath());
        if (input.is_open())
        {
            input >> Eps >> MinPts;
            SpinCtrl_Eps->SetValue(Eps);
            SpinCtrl_MinPts->SetValue(MinPts);
            D.clear();
            int x, y;
            while (input >> x >> y)
            {
                D.push_back(Point(x, y));
            }
            if (!D.empty())
            {
                ButtonStep->Enable();
                ButtonComplete->Enable();
            }
            ResetDBSCAN();
        }
        else
        {
            wxMessageBox("Failed to open the file");
        }
    }
}

void DBSCANFrame::OnMenuItemSaveSelected(wxCommandEvent& event)
{
    wxFileDialog
        saveFileDialog(this, _("保存点集"), "", "",
                       "txt files (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_OK)
    {
        std::ofstream output(saveFileDialog.GetPath(), std::ofstream::out);
        output << Eps << ' ' << MinPts << "\n\n";
        for (Point &pt : D)
        {
            output << pt.x << ' ' << pt.y << '\n';
        }
    }
}
