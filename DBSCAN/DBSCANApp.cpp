/***************************************************************
 * Name:      DBSCANApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Gaby (2823925809@qq.com)
 * Created:   2016-06-07
 * Copyright: Gaby ()
 * License:
 **************************************************************/

#include "DBSCANApp.h"

//(*AppHeaders
#include "DBSCANMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(DBSCANApp);

bool DBSCANApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	DBSCANFrame* Frame = new DBSCANFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
