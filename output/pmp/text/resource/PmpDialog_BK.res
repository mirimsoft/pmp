(Dialog PmpDialog_BK
    (Components
        (MenuBar                        MenuBar1
                                        MenuPane1
                                        MenuPane2
                                        MenuPane3
                                        MenuPane5)
        (Tab                            Tab1
                                        Layout1
                                        Layout2
                                        Layout3
                                        Layout4
                                        Layout5)
    )

    (Resources
        (MenuBar1.AlwaysOnTop           True)
        (Tab1.Decorated                 True)
        (Tab1.TopOffset                 4)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                Tab1
            )
        )
    )
)

(MenuPane MenuPane1
    (Components
        (PushButton                     PB_OPTION)
        (PushButton                     PB_EXIT)
    )

    (Resources
        (PB_OPTION.Label                "&Option")
        (PB_EXIT.Label                  "&Exit")
        (.Label                         "&File")
    )
)

(MenuPane MenuPane2
    (Components
        (PushButton                     PB_FIND)
    )

    (Resources
        (PB_FIND.Label                  "&Find/Replace")
        (.Label                         "&Edit")
    )
)

(MenuPane MenuPane3
    (Components
        (PushButton                     PB_LOAD_DRAWING)
        (PushButton                     PB_SESSION_BOM)
        (PushButton                     PB_SESSION_PARTLIST)
    )

    (Resources
        (PB_LOAD_DRAWING.Label          "&Load Drawing")
        (PB_SESSION_BOM.Label           "Session &BOM")
        (PB_SESSION_PARTLIST.Label      "Session &Part List")
        (.Label                         "&Tools")
    )
)

(MenuPane MenuPane5
    (Components
        (PushButton                     PB_HELP_CONTENTS)
        (PushButton                     PB_SHOW_LOG)
        (PushButton                     PB_SET_LICENSE)
        (PushButton                     PB_ABOUT)
        (PushButton                     PB_ADMIN)
    )

    (Resources
        (PB_HELP_CONTENTS.Label         "&Contents")
        (PB_SHOW_LOG.Label              "&Show Log")
        (PB_SET_LICENSE.Label           "&License")
        (PB_ABOUT.Label                 "&About")
        (PB_ADMIN.Label                 "Admin")
        (.Label                         "&Help")
    )
)

(Layout Layout1
    (Components
        (SubLayout                      Layout6)
        (SubLayout                      Layout7)
    )

    (Resources
        (.Label                         "Define Parameter")
        (.Decorated                     True)
        (.Layout
            (Grid (Rows 1 0) (Cols 1)
                Layout6
                Layout7
            )
        )
    )
)

(Layout Layout6
    (Components
        (SubLayout                      Layout8)
        (SubLayout                      Layout9)
    )

    (Resources
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 0)
                Layout8
                Layout9
            )
        )
    )
)

(Layout Layout8
    (Components
        (SubLayout                      Layout10)
        (SubLayout                      Layout13)
    )

    (Resources
        (.Label                         "Standard Parameter")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1 0) (Cols 1)
                Layout10
                Layout13
            )
        )
    )
)

(Layout Layout10
    (Components
        (Table                          TABLE1)
    )

    (Resources
        (TABLE1.TopOffset               2)
        (TABLE1.BottomOffset            2)
        (TABLE1.RowNames                "A"
                                        "B")
        (TABLE1.ColumnNames             "Name"
                                        "Type"
                                        "ReadOnly"
                                        "Default"
                                        "Names"
                                        "Remark")
        (TABLE1.RowLabels               "A"
                                        "B")
        (TABLE1.ColumnLabels            "Name"
                                        "Type"
                                        "ReadOnly"
                                        "Default"
                                        "Old Names"
                                        "Remark")
        (TABLE1.ColumnWidths            10
                                        4
                                        4
                                        4
                                        20
                                        10)
        (TABLE1.ShowGrid                True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                TABLE1
            )
        )
    )
)

(TableLayout TABLE1
    (Components
        (InputPanel                     IP_SOURCE1)
        (OptionMenu                     OM_SOURCE1)
        (CheckButton                    CB_SOURCE1)
    )

    (Resources
        (.Decorated                     True)
    )
)

(Layout Layout13
    (Components
        (SubToolBar                     ToolBar3)
    )

    (Resources
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                ToolBar3
            )
        )
    )
)

(ToolBar ToolBar3
    (Components
        (PushButton                     PB_ADD_ROW1)
        (PushButton                     PB_REMOVE_ROW1)
        (PushButton                     PB_MOVE_UP1)
        (PushButton                     PB_MOVE_DOWN1)
    )

    (Resources
        (PB_ADD_ROW1.Bitmap             "analysis_add")
        (PB_ADD_ROW1.AttachLeft         True)
        (PB_ADD_ROW1.AttachRight        True)
        (PB_ADD_ROW1.AttachTop          True)
        (PB_ADD_ROW1.AttachBottom       True)
        (PB_REMOVE_ROW1.Bitmap          "remove_item")
        (PB_REMOVE_ROW1.AttachLeft      True)
        (PB_REMOVE_ROW1.AttachRight     True)
        (PB_REMOVE_ROW1.AttachTop       True)
        (PB_REMOVE_ROW1.AttachBottom    True)
        (PB_MOVE_UP1.Bitmap             "bbl_arrow_up")
        (PB_MOVE_UP1.AttachLeft         True)
        (PB_MOVE_UP1.AttachRight        True)
        (PB_MOVE_UP1.AttachTop          True)
        (PB_MOVE_UP1.AttachBottom       True)
        (PB_MOVE_DOWN1.Bitmap           "bbl_arrow_down")
        (PB_MOVE_DOWN1.AttachLeft       True)
        (PB_MOVE_DOWN1.AttachRight      True)
        (PB_MOVE_DOWN1.AttachTop        True)
        (PB_MOVE_DOWN1.AttachBottom     True)
    )
)

(Layout Layout9
    (Components
        (SubLayout                      Layout14)
        (SubLayout                      Layout15)
    )

    (Resources
        (.Label                         "Parameters To Delete")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1 0) (Cols 1)
                Layout14
                Layout15
            )
        )
    )
)

(Layout Layout14
    (Components
        (Table                          TABLE2)
    )

    (Resources
        (TABLE2.TopOffset               2)
        (TABLE2.BottomOffset            2)
        (TABLE2.RowNames                "A"
                                        "B")
        (TABLE2.ColumnNames             "Name")
        (TABLE2.RowLabels               "A"
                                        "B")
        (TABLE2.ColumnLabels            "Name")
        (TABLE2.ColumnWidths            20)
        (TABLE2.ShowGrid                True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                TABLE2
            )
        )
    )
)

(TableLayout TABLE2
    (Components
        (InputPanel                     IP_SOURCE2)
        (CheckButton                    CB_SOURCE2)
    )

    (Resources
        (.Decorated                     True)
    )
)

(Layout Layout15
    (Components
        (SubToolBar                     ToolBar4)
    )

    (Resources
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                ToolBar4
            )
        )
    )
)

(ToolBar ToolBar4
    (Components
        (PushButton                     PB_ADD_ROW2)
        (PushButton                     PB_REMOVE_ROW2)
        (PushButton                     PB_MOVE_UP2)
        (PushButton                     PB_MOVE_DOWN2)
    )

    (Resources
        (PB_ADD_ROW2.Bitmap             "analysis_add")
        (PB_ADD_ROW2.AttachLeft         True)
        (PB_ADD_ROW2.AttachRight        True)
        (PB_ADD_ROW2.AttachTop          True)
        (PB_ADD_ROW2.AttachBottom       True)
        (PB_REMOVE_ROW2.Bitmap          "remove_item")
        (PB_REMOVE_ROW2.AttachLeft      True)
        (PB_REMOVE_ROW2.AttachRight     True)
        (PB_REMOVE_ROW2.AttachTop       True)
        (PB_REMOVE_ROW2.AttachBottom    True)
        (PB_MOVE_UP2.Bitmap             "bbl_arrow_up")
        (PB_MOVE_UP2.AttachLeft         True)
        (PB_MOVE_UP2.AttachRight        True)
        (PB_MOVE_UP2.AttachTop          True)
        (PB_MOVE_UP2.AttachBottom       True)
        (PB_MOVE_DOWN2.Bitmap           "bbl_arrow_down")
        (PB_MOVE_DOWN2.AttachLeft       True)
        (PB_MOVE_DOWN2.AttachRight      True)
        (PB_MOVE_DOWN2.AttachTop        True)
        (PB_MOVE_DOWN2.AttachBottom     True)
    )
)

(Layout Layout7
    (Components
        (PushButton                     PB_READ_EXCEL)
        (PushButton                     PB_SAVE_EXCEL)
        (PushButton                     PB_SAVE_XML)
    )

    (Resources
        (PB_READ_EXCEL.Bitmap           "excel")
        (PB_READ_EXCEL.Label            "Read Excel")
        (PB_SAVE_EXCEL.Bitmap           "excel")
        (PB_SAVE_EXCEL.Label            "Save To Excel")
        (PB_SAVE_XML.Bitmap             "save")
        (PB_SAVE_XML.Label              "Save")
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 1 1)
                PB_READ_EXCEL
                PB_SAVE_EXCEL
                PB_SAVE_XML
            )
        )
    )
)

(Layout Layout2
    (Components
        (SubLayout                      Layout11)
        (SubLayout                      Layout12)
    )

    (Resources
        (.Label                         "Edit Parameter")
        (.Decorated                     True)
        (.Layout
            (Grid (Rows 1 0) (Cols 1)
                Layout11
                Layout12
            )
        )
    )
)

(Layout Layout11
    (Components
        (Table                          TABLE3)
    )

    (Resources
        (TABLE3.TopOffset               2)
        (TABLE3.BottomOffset            2)
        (TABLE3.RowNames                "1")
        (TABLE3.ColumnNames             "Name"
                                        "Type"
                                        "Qty")
        (TABLE3.RowLabels               "1")
        (TABLE3.ColumnLabels            "Name"
                                        "Type"
                                        "Qty")
        (TABLE3.ShowGrid                True)
        (.Label                         "Standard Parameters")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                TABLE3
            )
        )
    )
)

(TableLayout TABLE3
    (Components
        (InputPanel                     IP_SOURCE3)
        (Label                          LB_SOURCE3)
    )

    (Resources
        (LB_SOURCE3.Bitmap              "PTC small logo image")
        (LB_SOURCE3.Label               "TEXT")
        (LB_SOURCE3.AttachLeft          True)
        (LB_SOURCE3.AttachRight         True)
        (LB_SOURCE3.Alignment           0)
    )
)

(Layout Layout12
    (Components
        (SubLayout                      Layout16)
        (SubLayout                      Layout17)
        (SubLayout                      Layout18)
    )

    (Resources
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 0 0 1)
                Layout16
                Layout17
                Layout18
            )
        )
    )
)

(Layout Layout16
    (Components
        (PushButton                     PB_COPY)
        (PushButton                     PB_PASTE)
        (PushButton                     PB_CLEAR)
        (PushButton                     PB_STANDARDIZE)
    )

    (Resources
        (PB_COPY.Bitmap                 "tb_copy")
        (PB_COPY.Label                  "Copy")
        (PB_PASTE.Bitmap                "tb_paste")
        (PB_PASTE.Label                 "Paste")
        (PB_CLEAR.Bitmap                "tb_delete")
        (PB_CLEAR.Label                 "Clear")
        (PB_STANDARDIZE.Bitmap          "tb_swap")
        (PB_STANDARDIZE.Label           "Standardize")
        (.Label                         "Screen")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 1 1 1)
                PB_COPY
                PB_PASTE
                PB_CLEAR
                PB_STANDARDIZE
            )
        )
    )
)

(Layout Layout17
    (Components
        (CheckButton                    CB_ASM1)
        (CheckButton                    CB_PRT1)
    )

    (Resources
        (CB_ASM1.Label                  "ASM")
        (CB_ASM1.Set                    True)
        (CB_PRT1.Label                  "PRT")
        (CB_PRT1.Set                    True)
        (.Label                         "Filter")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 1)
                CB_ASM1
                CB_PRT1
            )
        )
    )
)

(Layout Layout18
    (Components
        (PushButton                     PB_READ_PARAM)
        (PushButton                     PB_APPLY_PARAM)
    )

    (Resources
        (PB_READ_PARAM.Label            "Read")
        (PB_APPLY_PARAM.Label           "Apply")
        (.Label                         "Session")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 1)
                PB_READ_PARAM
                PB_APPLY_PARAM
            )
        )
    )
)

(Layout Layout3
    (Components
        (SubLayout                      Layout19)
        (SubLayout                      Layout20)
    )

    (Resources
        (.Label                         "Assembly Rename")
        (.Decorated                     True)
        (.Layout
            (Grid (Rows 1 0) (Cols 1)
                Layout19
                Layout20
            )
        )
    )
)

(Layout Layout19
    (Components
        (Table                          TABLE4)
    )

    (Resources
        (TABLE4.TopOffset               2)
        (TABLE4.BottomOffset            2)
        (TABLE4.ShowGrid                True)
        (.Label                         "Names")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                TABLE4
            )
        )
    )
)

(TableLayout TABLE4
    (Components
        (InputPanel                     InputPanel4)
    )

    (Resources
        (.Decorated                     True)
    )
)

(Layout Layout20
    (Components
        (SubLayout                      Layout21)
        (SubLayout                      Layout23)
        (SubLayout                      Layout24)
    )

    (Resources
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 0 0 1)
                Layout21
                Layout23
                Layout24
            )
        )
    )
)

(Layout Layout21
    (Components
        (InputPanel                     IP_PREFIX)
        (PushButton                     PB_ADD_PREFIX)
        (PushButton                     PB_REMOVE_PROFIX)
    )

    (Resources
        (IP_PREFIX.Columns              1)
        (PB_ADD_PREFIX.Label            "+")
        (PB_ADD_PREFIX.AttachLeft       True)
        (PB_ADD_PREFIX.AttachRight      True)
        (PB_REMOVE_PROFIX.Label         "-")
        (PB_REMOVE_PROFIX.AttachLeft    True)
        (PB_REMOVE_PROFIX.AttachRight   True)
        (.Label                         "Prefix")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.Layout
            (Grid (Rows 1) (Cols 1 0 0)
                IP_PREFIX
                PB_ADD_PREFIX
                PB_REMOVE_PROFIX
            )
        )
    )
)

(Layout Layout23
    (Components
        (InputPanel                     IP_SURFIX)
        (PushButton                     PB_ADD_SURFIX)
        (PushButton                     PB_REMOVE_SURFIX)
    )

    (Resources
        (IP_SURFIX.Columns              1)
        (PB_ADD_SURFIX.Label            "+")
        (PB_ADD_SURFIX.AttachLeft       True)
        (PB_ADD_SURFIX.AttachRight      True)
        (PB_REMOVE_SURFIX.Label         "-")
        (PB_REMOVE_SURFIX.AttachLeft    True)
        (PB_REMOVE_SURFIX.AttachRight   True)
        (.Label                         "Surfix")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.Layout
            (Grid (Rows 1) (Cols 1 0 0)
                IP_SURFIX
                PB_ADD_SURFIX
                PB_REMOVE_SURFIX
            )
        )
    )
)

(Layout Layout24
    (Components
        (PushButton                     PB_RAED_SESSION2)
        (PushButton                     PB_APPLY2)
        (CheckButton                    CB_SYNC_COMMONANME)
    )

    (Resources
        (PB_RAED_SESSION2.Label         "Read")
        (PB_APPLY2.Label                "Apply")
        (CB_SYNC_COMMONANME.Label       "Sync Common Name")
        (CB_SYNC_COMMONANME.Set         True)
        (.Label                         "Session")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.Layout
            (Grid (Rows 1) (Cols 1 1 1)
                PB_RAED_SESSION2
                PB_APPLY2
                CB_SYNC_COMMONANME
            )
        )
    )
)

(Layout Layout4
    (Components
        (SubLayout                      Layout25)
        (SubLayout                      Layout26)
        (SubLayout                      Layout27)
        (SubLayout                      Layout28)
    )

    (Resources
        (.Label                         "Batch Convert")
        (.Decorated                     True)
        (.Layout
            (Grid (Rows 0 0 1 0) (Cols 1)
                Layout25
                Layout26
                Layout27
                Layout28
            )
        )
    )
)

(Layout Layout25
    (Components
        (SubLayout                      Layout37)
        (SubLayout                      Layout38)
    )

    (Resources
        (.Decorated                     Mixed)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 0 1)
                Layout37
                Layout38
            )
        )
    )
)

(Layout Layout37
    (Components
        (RadioGroup                     RG_SOURCE)
        (CheckButton                    CB_SUBFOLDER)
    )

    (Resources
        (RG_SOURCE.AttachTop            False)
        (RG_SOURCE.AttachBottom         False)
        (RG_SOURCE.Names                "Session"
                                        "Workspace"
                                        "Disk")
        (RG_SOURCE.Labels               "Session"
                                        "Workspace"
                                        "Local Disk")
        (CB_SUBFOLDER.Label             "Subfolder")
        (CB_SUBFOLDER.Set               True)
        (CB_SUBFOLDER.AttachLeft        True)
        (.Label                         "Source")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 0 1)
                RG_SOURCE
                CB_SUBFOLDER
            )
        )
    )
)

(Layout Layout38
    (Components
        (OptionMenu                     OM_FORMAT)
    )

    (Resources
        (OM_FORMAT.VisibleRows          3)
        (OM_FORMAT.Names                "Postscript"
                                        "PDF"
                                        "HPGL")
        (OM_FORMAT.Labels               "Postscript"
                                        "PDF"
                                        "HP-GL")
        (.Label                         "Intermediate Print Format")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                OM_FORMAT
            )
        )
    )
)

(Layout Layout26
    (Components
        (OptionMenu                     OM_FOLDER)
        (PushButton                     PB_SELECT_FOLDER)
    )

    (Resources
        (OM_FOLDER.VisibleRows          12)
        (PB_SELECT_FOLDER.Label         "...")
        (PB_SELECT_FOLDER.AttachLeft    True)
        (PB_SELECT_FOLDER.AttachRight   True)
        (.Label                         "Folder")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 0)
                OM_FOLDER
                PB_SELECT_FOLDER
            )
        )
    )
)

(Layout Layout27
    (Components
        (SubLayout                      Layout29)
        (SubLayout                      Layout30)
        (SubLayout                      Layout31)
    )

    (Resources
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 0 1)
                Layout29
                Layout30
                Layout31
            )
        )
    )
)

(Layout Layout29
    (Components
        (Table                          TABLE5)
    )

    (Resources
        (TABLE5.TopOffset               2)
        (TABLE5.BottomOffset            2)
        (TABLE5.ShowGrid                True)
        (.Label                         "Source")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                TABLE5
            )
        )
    )
)

(TableLayout TABLE5
    (Components
        (InputPanel                     InputPanel5)
    )

    (Resources
        (.Decorated                     True)
    )
)

(Layout Layout30
    (Components
        (SubLayout                      Layout32)
        (SubLayout                      Layout33)
        (SubLayout                      Layout34)
    )

    (Resources
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 0 1 0) (Cols 1)
                Layout32
                Layout33
                Layout34
            )
        )
    )
)

(Layout Layout32
    (Components
        (CheckButton                    CB_ASM2)
        (CheckButton                    CB_DRW2)
    )

    (Resources
        (CB_ASM2.Label                  "ASM")
        (CB_ASM2.Set                    True)
        (CB_ASM2.AttachLeft             True)
        (CB_DRW2.Label                  "DRW")
        (CB_DRW2.Set                    True)
        (CB_DRW2.AttachLeft             True)
        (.Label                         "Filter")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1 1) (Cols 1)
                CB_ASM2
                CB_DRW2
            )
        )
    )
)

(Layout Layout33
    (Components
        (PushButton                     PB_ADD)
        (PushButton                     PB_ADD_ALL)
        (PushButton                     PB_REMOVE)
        (PushButton                     PB_REMOVE_ALL)
    )

    (Resources
        (PB_ADD.Label                   ">")
        (PB_ADD.AttachLeft              True)
        (PB_ADD.AttachRight             True)
        (PB_ADD.AttachTop               True)
        (PB_ADD_ALL.Label               ">>")
        (PB_ADD_ALL.AttachLeft          True)
        (PB_ADD_ALL.AttachRight         True)
        (PB_ADD_ALL.AttachTop           True)
        (PB_REMOVE.Label                "<")
        (PB_REMOVE.AttachLeft           True)
        (PB_REMOVE.AttachRight          True)
        (PB_REMOVE.AttachTop            True)
        (PB_REMOVE.TopOffset            10)
        (PB_REMOVE_ALL.Label            "<<")
        (PB_REMOVE_ALL.AttachLeft       True)
        (PB_REMOVE_ALL.AttachRight      True)
        (PB_REMOVE_ALL.AttachTop        True)
        (.Label                         "Select")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 0 0 0 1) (Cols 1)
                PB_ADD
                PB_ADD_ALL
                PB_REMOVE
                PB_REMOVE_ALL
            )
        )
    )
)

(Layout Layout34
    (Components
        (CheckButton                    CB_DXF)
        (CheckButton                    CB_DWG)
        (CheckButton                    CB_HPGL)
        (CheckButton                    CB_PDF)
        (CheckButton                    CB_PRINT)
    )

    (Resources
        (CB_DXF.Label                   "DXF")
        (CB_DXF.AttachLeft              True)
        (CB_DWG.Label                   "DWG")
        (CB_DWG.AttachLeft              True)
        (CB_HPGL.Label                  "HP-GL")
        (CB_HPGL.AttachLeft             True)
        (CB_PDF.Label                   "PDF")
        (CB_PDF.AttachLeft              True)
        (CB_PRINT.Label                 "Print")
        (CB_PRINT.AttachLeft            True)
        (.Label                         "Format")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1 1 1 1 1) (Cols 1)
                CB_DXF
                CB_DWG
                CB_HPGL
                CB_PDF
                CB_PRINT
            )
        )
    )
)

(Layout Layout31
    (Components
        (Table                          TABLE6)
    )

    (Resources
        (TABLE6.TopOffset               2)
        (TABLE6.BottomOffset            2)
        (TABLE6.ShowGrid                True)
        (.Label                         "Selected")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                TABLE6
            )
        )
    )
)

(TableLayout TABLE6
    (Components
        (InputPanel                     InputPanel6)
    )

    (Resources
        (.Decorated                     True)
    )
)

(Layout Layout28
    (Components
        (Label                          Label1)
        (OptionMenu                     OM_PRINTER)
        (Label                          Label2)
        (OptionMenu                     OM_PAPER)
        (PushButton                     PB_EXECUTE)
    )

    (Resources
        (Label1.Label                   "Printer")
        (Label1.AttachLeft              True)
        (Label1.AttachRight             True)
        (Label1.LeftOffset              20)
        (Label1.RightOffset             4)
        (OM_PRINTER.Columns             8)
        (Label2.Label                   "Paper Size")
        (Label2.AttachLeft              True)
        (Label2.AttachRight             True)
        (Label2.LeftOffset              20)
        (Label2.RightOffset             4)
        (OM_PAPER.Columns               8)
        (PB_EXECUTE.Label               "Execute")
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 0 0 0 0 1)
                Label1
                OM_PRINTER
                Label2
                OM_PAPER
                PB_EXECUTE
            )
        )
    )
)

(Layout Layout5
    (Components
        (SubLayout                      Layout35)
        (SubLayout                      Layout36)
    )

    (Resources
        (.Label                         "Family Table")
        (.Decorated                     True)
        (.Layout
            (Grid (Rows 1) (Cols 0 1)
                Layout35
                Layout36
            )
        )
    )
)

(Layout Layout35
    (Components
        (PushButton                     PB_MODEL_BACKUP)
        (PushButton                     PB_SAVE_NAMES)
        (PushButton                     PB_SHOW_FAMTAB)
        (PushButton                     PushButton47)
        (PushButton                     PB_SHOW_ALL)
        (PushButton                     PB_RESTORE_NAMES)
        (PushButton                     PB_SAVE_ALL)
    )

    (Resources
        (PB_MODEL_BACKUP.Label          "Model Backup")
        (PB_MODEL_BACKUP.AttachLeft     True)
        (PB_MODEL_BACKUP.AttachRight    True)
        (PB_SAVE_NAMES.Label            "Save Names")
        (PB_SAVE_NAMES.AttachLeft       True)
        (PB_SAVE_NAMES.AttachRight      True)
        (PB_SHOW_FAMTAB.Label           "Show FamilyTable Parts")
        (PB_SHOW_FAMTAB.AttachLeft      True)
        (PB_SHOW_FAMTAB.AttachRight     True)
        (PushButton47.Label             "Replace FamilyTable Instance")
        (PushButton47.ButtonStyle       3)
        (PushButton47.AttachLeft        True)
        (PushButton47.AttachRight       True)
        (PB_SHOW_ALL.Label              "Show All")
        (PB_SHOW_ALL.AttachLeft         True)
        (PB_SHOW_ALL.AttachRight        True)
        (PB_RESTORE_NAMES.Label         "Restore Names")
        (PB_RESTORE_NAMES.AttachLeft    True)
        (PB_RESTORE_NAMES.AttachRight   True)
        (PB_SAVE_ALL.Label              "Save All")
        (PB_SAVE_ALL.AttachLeft         True)
        (PB_SAVE_ALL.AttachRight        True)
        (PB_SAVE_ALL.AttachTop          True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 0 0 0 0 0 0 1) (Cols 1)
                PB_MODEL_BACKUP
                PB_SAVE_NAMES
                PB_SHOW_FAMTAB
                PushButton47
                PB_SHOW_ALL
                PB_RESTORE_NAMES
                PB_SAVE_ALL
            )
        )
    )
)

(Layout Layout36
    (Components
        (TextArea                       TextArea1)
    )

    (Resources
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                TextArea1
            )
        )
    )
)
