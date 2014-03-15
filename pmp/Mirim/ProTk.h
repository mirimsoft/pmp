#ifndef PROTK_H
#define PROTK_H

#pragma warning( disable : 4996 )
#pragma warning( disable : 4312 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4217 )
#pragma warning( disable : 4049 )

#include <StdAfx.h>
/*--------------------------------------------------------------------*\
Application Libraries
\*--------------------------------------------------------------------*/
// ANSI C Libraries
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cerrno>
#include <cfloat>
#include <assert.h>
#include <stdlib.h>
#include <crtdbg.h>

// ANSI C++ Libraries
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Windows C Libraries
#include <io.h>
#include <windows.h>
#include <comdef.h>
#include <direct.h>
#include <crtdefs.h>

using namespace std;

/*--------------------------------------------------------------------*\
Pro/Toolkit Libraries
\*--------------------------------------------------------------------*/
#include <ProToolkit.h>
#include <Pro2dEntdef.h>
#include <ProANSI.h>
#include <ProAnalysis.h>
#include <ProAnimate.h>
#include <ProArray.h>
#include <ProAsmcomp.h>
#include <ProAsmcompR20.h>
#include <ProAsmcomppath.h>
#include <ProAssembly.h>
#include <ProAutodrill.h>
#include <ProAxis.h>
#include <ProCabling.h>
#include <ProCavitylayout.h>
#include <ProCavlayrule.h>
#include <ProChamfer.h>
#include <ProClCmd.h>
#include <ProClcmdElem.h>
#include <ProCollect.h>
#include <ProColor.h>
#include <ProComm.h>
#include <ProConst.h>
#include <ProContour.h>
#include <ProContourdata.h>
#include <ProCopyGeom.h>
#include <ProCore.h>
#include <ProCsys.h>
#include <ProCsysdata.h>
#include <ProCurve.h>
#include <ProCurvedata.h>
#include <ProDatumdata.h>
#include <ProDimension.h>
#include <ProDisplist.h>
#include <ProDrawing.h>
#include <ProDtlattach.h>
#include <ProDtlentity.h>
#include <ProDtlgroup.h>
#include <ProDtlitem.h>
#include <ProDtlnote.h>
#include <ProDtlsymdef.h>
#include <ProDtlsyminst.h>
#include <ProDtmAxis.h>
#include <ProDtmCrv.h>
#include <ProDtmCrvSketch.h>
#include <ProDtmCsys.h>
#include <ProDtmPln.h>
#include <ProDtmPnt.h>
#include <ProDwgtable.h>
#include <ProEdge.h>
#include <ProEdgedata.h>
#include <ProElemId.h>
#include <ProElement.h>
#include <ProElempath.h>
#include <ProExpldstate.h>
#include <ProExtdata.h>
#include <ProExtobj.h>
#include <ProExtobjCB.h>
#include <ProExtobjDisp.h>
#include <ProExtobjRef.h>
#include <ProExtobjSel.h>
#include <ProExtrude.h>
#include <ProFaminstance.h>
#include <ProFamtable.h>
#include <ProFeatForm.h>
#include <ProFeatIntr.h>
#include <ProFeatType.h>
#include <ProFeature.h>
#include <ProFemMesh.h>
#include <ProFemObjects.h>
#include <ProFlatSrf.h>
#include <ProForeignCurve.h>
#include <ProGeomitem.h>
#include <ProGeomitemdata.h>
#include <ProGraphic.h>
#include <ProGroup.h>
#include <ProGtol.h>
#include <ProHardware.h>
#include <ProHole.h>
#include <ProImm.h>
#include <ProImportfeat.h>
#include <ProIntf3Dexport.h>
#include <ProIntfData.h>
#include <ProIntfimport.h>
#include <ProItemerr.h>
#include <ProJlink.h>
#include <ProLayer.h>
#include <ProLayerR19.h>
#include <ProMaterial.h>
#include <ProMdl.h>
#include <ProMdlChk.h>
#include <ProMenu.h>
#include <ProMenuBar.h>
#include <ProMessage.h>
#include <ProMfg.h>
#include <ProMfgdb.h>
#include <ProMfgoper.h>
#include <ProModFeat.h>
#include <ProMode.h>
#include <ProModelitem.h>
#include <ProMoldbase.h>
#include <ProNcseq.h>
#include <ProNcseqElem.h>
#include <ProNote.h>
#include <ProNotify.h>
#include <ProObjects.h>
#include <ProParameter.h>
#include <ProParamval.h>
#include <ProPart.h>
#include <ProPattern.h>
#include <ProPecktable.h>
#include <ProPdf.h>
#include <ProPiping.h>
#include <ProPoint.h>
#include <ProPrint.h>
#include <ProProcstep.h>
#include <ProQuilt.h>
#include <ProQuiltdata.h>
#include <ProRefInfo.h>
#include <ProRelSet.h>
#include <ProReplace.h>
#include <ProRevolve.h>
#include <ProRib.h>
#include <ProRmdt.h>
#include <ProRule.h>
#include <ProScope.h>
#include <ProSecConstr.h>
#include <ProSecdim.h>
#include <ProSecdimType.h>
#include <ProSecerror.h>
#include <ProSection.h>
#include <ProSelection.h>
#include <ProSheetmetal.h>
#include <ProShrinkwrap.h>
#include <ProSimprep.h>
#include <ProSimprepdata.h>
#include <ProSizeConst.h>
#include <ProSkeleton.h>
#include <ProSolid.h>
#include <ProStdSection.h>
#include <ProSurface.h>
#include <ProSurfacedata.h>
#include <ProSweep.h>
#include <ProTool.h>
#include <ProToolElem.h>
#include <ProToolinput.h>
#include <ProToolkitDll.h>
#include <ProUI.h>
#include <ProUICascadebutton.h>
#include <ProUICheckbutton.h>
#include <ProUICmd.h>
#include <ProUIDialog.h>
#include <ProUIInputpanel.h>
#include <ProUILabel.h>
#include <ProUILayout.h>
#include <ProUIList.h>
#include <ProUIMenubar.h>
#include <ProUIMenupane.h>
#include <ProUIMessage.h>
#include <ProUIOptionmenu.h>
#include <ProUIProgressbar.h>
#include <ProUIPushbutton.h>
#include <ProUIRadiogroup.h>
#include <ProUISlider.h>
#include <ProUISpinbox.h>
#include <ProUITab.h>
#include <ProUITable.h>
#include <ProUITextarea.h>
#include <ProUIThumbwheel.h>
#include <ProUITree.h>
#include <ProUdf.h>
#include <ProUtil.h>
#include <ProUvStat.h>
#include <ProValue.h>
#include <ProVerstamp.h>
#include <ProView.h>
#include <ProWcell.h>
#include <ProWchar.h>
#include <ProWeld.h>
#include <ProWindows.h>
#include <ProWorkspace.h>
#include <ProWstring.h>
#include <ProWTUtils.h>
#include <ProXsec.h>
#include <ProTKRunTime.h>


#ifdef __cplusplus
extern "C" {
#endif

    /*--------------------------------------------------------------------*\
    Pro/TOOLKIT Example header
    \*--------------------------------------------------------------------*/

#include "UtilCable.h"
#include "UtilCollect.h"
#include "UtilCollectDtmpnt.h"
#include "UtilFiles.h"
#include "UtilGroups.h"
#include "UtilIntfData.h"
#include "UtilMath.h"
#include "UtilMatrix.h"
#include "UtilMenu.h"
#include "UtilMessage.h"
#include "UtilNames.h"
#include "UtilString.h"
#include "UtilTree.h"
#include "UtilTypes.h"
#include "UtilVisit.h"

#ifdef __cplusplus
}
#endif

#include "pugixml.hpp"
#include "MsgBox.h"
#include "TLog.h"
#include "Util.h"
#include "Option.h"
//#include "Table.h"


/*--------------------------------------------------------------------*\
Application global/external data
\*--------------------------------------------------------------------*/
static wchar_t  MSGFIL[] = L"pmp_msg.txt";

namespace Gui
{
    struct TableData
    {
		char *dialog;
        char *table;
        char *row;
        char *col;
        char *label;

        char *inputpanel;
        char *optionmenu;
        char *checkbutton;
        char **optionmenu_items;
    };
}

#endif // PROTK_H