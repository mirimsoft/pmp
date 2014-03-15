(Dialog BatchTools
    (Components
        (MenuBar                        MenuBar1
                                        MenuPane1
                                        MenuPane3
                                        MenuPane5)
        (Tab                            Tab1
                                        Layout1
                                        Layout2
                                        Layout3
                                        Layout4)
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

(MenuPane MenuPane3
    (Components
        (PushButton                     PB_LOAD_DRAWING)
        (PushButton                     PB_SAVE_SESSION)
        (PushButton                     PB_SESSION_BOM)
        (PushButton                     PB_SESSION_PARTLIST)
        (PushButton                     PB_FIND_PARAMETER)
    )

    (Resources
        (PB_LOAD_DRAWING.Label          "&Load Drawing")
        (PB_SAVE_SESSION.Label          "Save All in Session")
        (PB_SESSION_BOM.Label           "Session &BOM")
        (PB_SESSION_PARTLIST.Label      "Session &Part List")
        (PB_FIND_PARAMETER.Label        "Find Parameter")
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
        (.TopOffset                     4)
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
        (TABLE1.SelectionPolicy         4)
        (TABLE1.TopOffset               2)
        (TABLE1.BottomOffset            2)
        (TABLE1.RowNames                "A")
        (TABLE1.ColumnNames             "Name"
                                        "Type"
                                        "ReadOnly"
                                        "Default"
                                        "Names"
                                        "Remark")
        (TABLE1.RowLabels               "")
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
        (TABLE1.RowSelectionPolicy      4)
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
        (InputPanel                     IP_SOURCE)
        (OptionMenu                     OM_SOURCE)
        (CheckButton                    CB_SOURCE)
        (Label                          LB_SOURCE)
    )

    (Resources
        (LB_SOURCE.Bitmap               "PTC small logo image")
        (LB_SOURCE.Label                "Label")
        (LB_SOURCE.AttachLeft           True)
        (LB_SOURCE.AttachRight          True)
        (LB_SOURCE.AttachTop            True)
        (LB_SOURCE.AttachBottom         True)
        (LB_SOURCE.Alignment            0)
        (LB_SOURCE.Resizeable           True)
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
        (Label                          Label3)
        (InputPanel                     IP_TOTAL_LENGTH)
        (Label                          Label4)
        (InputPanel                     IP_PARTNR_START)
    )

    (Resources
        (PB_ADD_ROW1.Bitmap             "analysis_add")
        (PB_ADD_ROW1.HelpText           "Add New Item")
        (PB_ADD_ROW1.AttachLeft         True)
        (PB_ADD_ROW1.AttachRight        True)
        (PB_ADD_ROW1.AttachTop          True)
        (PB_ADD_ROW1.AttachBottom       True)
        (PB_REMOVE_ROW1.Bitmap          "remove_item")
        (PB_REMOVE_ROW1.HelpText        "Delete Current")
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
        (Label3.Label                   "Total Length: ")
        (Label3.AttachLeft              True)
        (Label3.AttachRight             True)
        (Label3.AttachTop               True)
        (Label3.AttachBottom            True)
        (Label3.LeftOffset              10)
        (IP_TOTAL_LENGTH.Columns        1)
        (IP_TOTAL_LENGTH.InputType      2)
        (Label4.Label                   "Part No Start: ")
        (Label4.AttachLeft              True)
        (Label4.AttachRight             True)
        (Label4.AttachTop               True)
        (Label4.AttachBottom            True)
        (Label4.LeftOffset              10)
        (IP_PARTNR_START.Columns        1)
        (IP_PARTNR_START.InputType      2)
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
        (TABLE2.ColumnNames             "Checked"
                                        "Name")
        (TABLE2.ColumnLabels            ""
                                        "Name")
        (TABLE2.ColumnWidths            2
                                        16)
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
        (PB_ADD_ROW2.HelpText           "Add New Item")
        (PB_ADD_ROW2.AttachLeft         True)
        (PB_ADD_ROW2.AttachRight        True)
        (PB_ADD_ROW2.AttachTop          True)
        (PB_ADD_ROW2.AttachBottom       True)
        (PB_REMOVE_ROW2.Bitmap          "remove_item")
        (PB_REMOVE_ROW2.HelpText        "Remove Current")
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
        (SubLayout                      Layout22)
    )

    (Resources
        (.Label                         "Edit Parameter")
        (.Decorated                     True)
        (.TopOffset                     4)
        (.Layout
            (Grid (Rows 0 1 0) (Cols 1)
                Layout22
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
        (TABLE3.SelectionPolicy         4)
        (TABLE3.TopOffset               2)
        (TABLE3.BottomOffset            2)
        (TABLE3.ColumnNames             "Name"
                                        "Type"
                                        "Qty")
        (TABLE3.ColumnLabels            "Name"
                                        "Type"
                                        "Qty")
        (TABLE3.ShowGrid                True)
        (TABLE3.LockedColumns           1)
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
    )

    (Resources
        (.Decorated                     True)
    )
)

(Layout Layout12
    (Components
        (SubLayout                      Layout17)
        (SubLayout                      Layout18)
    )

    (Resources
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 0 1)
                Layout17
                Layout18
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
        (PushButton                     PB_STANDARDIZE)
        (PushButton                     PB_APPLY_PARAM)
    )

    (Resources
        (PB_READ_PARAM.Label            "Read")
        (PB_STANDARDIZE.Label           "Standardize")
        (PB_APPLY_PARAM.Label           "Apply")
        (.Label                         "Session")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 1 1)
                PB_READ_PARAM
                PB_STANDARDIZE
                PB_APPLY_PARAM
            )
        )
    )
)

(Layout Layout22
    (Components
        (PushButton                     PB_COPY1)
        (PushButton                     PB_PASTE1)
        (PushButton                     PB_CLEAR1)
        (PushButton                     PB_UNDO1)
        (PushButton                     PB_REDO1)
        (InputPanel                     IP_FIND1)
        (PushButton                     PB_FIND1)
        (OptionMenu                     OM_FIND_TARGET1)
        (InputPanel                     IP_REPLACE1)
        (PushButton                     PB_REPLACE1)
        (OptionMenu                     OM_REPLACE_TARGET1)
    )

    (Resources
        (PB_COPY1.Bitmap                "tb_copy")
        (PB_COPY1.HelpText              "Copy to clipboard")
        (PB_COPY1.AttachLeft            True)
        (PB_COPY1.AttachRight           True)
        (PB_COPY1.AttachTop             True)
        (PB_COPY1.AttachBottom          True)
        (PB_PASTE1.Bitmap               "tb_paste")
        (PB_PASTE1.HelpText             "Paste from clipboard")
        (PB_PASTE1.AttachLeft           True)
        (PB_PASTE1.AttachRight          True)
        (PB_PASTE1.AttachTop            True)
        (PB_PASTE1.AttachBottom         True)
        (PB_CLEAR1.Bitmap               "tb_delete")
        (PB_CLEAR1.HelpText             "Clear selected area")
        (PB_CLEAR1.AttachLeft           True)
        (PB_CLEAR1.AttachRight          True)
        (PB_CLEAR1.AttachTop            True)
        (PB_CLEAR1.AttachBottom         True)
        (PB_UNDO1.Bitmap                "undo")
        (PB_UNDO1.HelpText              "Undo last changes")
        (PB_UNDO1.AttachLeft            True)
        (PB_UNDO1.AttachRight           True)
        (PB_UNDO1.AttachTop             True)
        (PB_UNDO1.AttachBottom          True)
        (PB_REDO1.Bitmap                "redo")
        (PB_REDO1.HelpText              "Redo last undo")
        (PB_REDO1.AttachLeft            True)
        (PB_REDO1.AttachRight           True)
        (PB_REDO1.AttachTop             True)
        (PB_REDO1.AttachBottom          True)
        (IP_FIND1.Columns               1)
        (IP_FIND1.LeftOffset            10)
        (PB_FIND1.Bitmap                "tb_find")
        (PB_FIND1.AttachLeft            True)
        (PB_FIND1.AttachRight           True)
        (PB_FIND1.AttachTop             True)
        (PB_FIND1.AttachBottom          True)
        (OM_FIND_TARGET1.Columns        6)
        (OM_FIND_TARGET1.Names          "NextCell"
                                        "CurrentColumn"
                                        "All")
        (OM_FIND_TARGET1.Labels         "Next Cell"
                                        "Current Column"
                                        "All")
        (IP_REPLACE1.Columns            1)
        (IP_REPLACE1.LeftOffset         10)
        (PB_REPLACE1.Bitmap             "pgl_replace16x16")
        (PB_REPLACE1.AttachLeft         True)
        (PB_REPLACE1.AttachRight        True)
        (PB_REPLACE1.AttachTop          True)
        (PB_REPLACE1.AttachBottom       True)
        (OM_REPLACE_TARGET1.Columns     6)
        (OM_REPLACE_TARGET1.Names       "NextCell"
                                        "CurrentColumn"
                                        "All")
        (OM_REPLACE_TARGET1.Labels      "Next Cell"
                                        "Current Column"
                                        "All")
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 0 0 0 0 0 1 0 0 1 0 0)
                PB_COPY1
                PB_PASTE1
                PB_CLEAR1
                PB_UNDO1
                PB_REDO1
                IP_FIND1
                PB_FIND1
                OM_FIND_TARGET1
                IP_REPLACE1
                PB_REPLACE1
                OM_REPLACE_TARGET1
            )
        )
    )
)

(Layout Layout3
    (Components
        (SubLayout                      Layout19)
        (SubLayout                      Layout20)
        (SubLayout                      Layout39)
    )

    (Resources
        (.Label                         "Assembly Rename")
        (.Decorated                     True)
        (.TopOffset                     4)
        (.Layout
            (Grid (Rows 0 1 0) (Cols 1)
                Layout39
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
        (TABLE4.SelectionPolicy         4)
        (TABLE4.TopOffset               2)
        (TABLE4.BottomOffset            2)
        (TABLE4.ColumnNames             "Drw"
                                        "Name"
                                        "Type"
                                        "Modify"
                                        "CommonName"
                                        "Name1")
        (TABLE4.ColumnLabels            ""
                                        "Name"
                                        "Type"
                                        ""
                                        "Common Name"
                                        "New Name")
        (TABLE4.ColumnWidths            1
                                        20
                                        3
                                        1
                                        20
                                        20)
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
        (IP_PREFIX.Editable             False)
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
        (IP_SURFIX.Editable             False)
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
        (PushButton                     PB_READ_NAMES)
        (PushButton                     PB_SYNC_NAMES)
        (PushButton                     PB_APPLY_RENAME)
    )

    (Resources
        (PB_READ_NAMES.Label            "Read")
        (PB_SYNC_NAMES.Label            "Sync Names")
        (PB_APPLY_RENAME.Label          "Apply")
        (.Label                         "Session")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.Layout
            (Grid (Rows 1) (Cols 1 1 1)
                PB_READ_NAMES
                PB_SYNC_NAMES
                PB_APPLY_RENAME
            )
        )
    )
)

(Layout Layout39
    (Components
        (PushButton                     PB_COPY2)
        (PushButton                     PB_PASTE2)
        (PushButton                     PB_CLEAR2)
        (PushButton                     PB_UNDO2)
        (PushButton                     PB_REDO2)
        (InputPanel                     IP_FIND2)
        (PushButton                     PB_FIND2)
        (OptionMenu                     OM_FIND_TARGET2)
        (InputPanel                     IP_REPLACE2)
        (PushButton                     PB_REPLACE2)
        (OptionMenu                     OM_REPLACE_TARGET2)
    )

    (Resources
        (PB_COPY2.Bitmap                "tb_copy")
        (PB_COPY2.HelpText              "Copy to clipboard")
        (PB_COPY2.AttachLeft            True)
        (PB_COPY2.AttachRight           True)
        (PB_COPY2.AttachTop             True)
        (PB_COPY2.AttachBottom          True)
        (PB_PASTE2.Bitmap               "tb_paste")
        (PB_PASTE2.HelpText             "Paste from clipboard")
        (PB_PASTE2.AttachLeft           True)
        (PB_PASTE2.AttachRight          True)
        (PB_PASTE2.AttachTop            True)
        (PB_PASTE2.AttachBottom         True)
        (PB_CLEAR2.Bitmap               "tb_delete")
        (PB_CLEAR2.HelpText             "Clear selected area")
        (PB_CLEAR2.AttachLeft           True)
        (PB_CLEAR2.AttachRight          True)
        (PB_CLEAR2.AttachTop            True)
        (PB_CLEAR2.AttachBottom         True)
        (PB_UNDO2.Bitmap                "undo")
        (PB_UNDO2.HelpText              "Undo last changes")
        (PB_UNDO2.AttachLeft            True)
        (PB_UNDO2.AttachRight           True)
        (PB_UNDO2.AttachTop             True)
        (PB_UNDO2.AttachBottom          True)
        (PB_REDO2.Bitmap                "redo")
        (PB_REDO2.HelpText              "Redo last undo")
        (PB_REDO2.AttachLeft            True)
        (PB_REDO2.AttachRight           True)
        (PB_REDO2.AttachTop             True)
        (PB_REDO2.AttachBottom          True)
        (IP_FIND2.Columns               1)
        (IP_FIND2.LeftOffset            10)
        (PB_FIND2.Bitmap                "tb_find")
        (PB_FIND2.AttachLeft            True)
        (PB_FIND2.AttachRight           True)
        (PB_FIND2.AttachTop             True)
        (PB_FIND2.AttachBottom          True)
        (OM_FIND_TARGET2.Columns        6)
        (OM_FIND_TARGET2.Names          "NextCell"
                                        "CurrentColumn"
                                        "All")
        (OM_FIND_TARGET2.Labels         "Next Cell"
                                        "Current Column"
                                        "All")
        (IP_REPLACE2.Columns            1)
        (IP_REPLACE2.LeftOffset         10)
        (PB_REPLACE2.Bitmap             "pgl_replace16x16")
        (PB_REPLACE2.AttachLeft         True)
        (PB_REPLACE2.AttachRight        True)
        (PB_REPLACE2.AttachTop          True)
        (PB_REPLACE2.AttachBottom       True)
        (OM_REPLACE_TARGET2.Columns     6)
        (OM_REPLACE_TARGET2.Names       "NextCell"
                                        "CurrentColumn"
                                        "All")
        (OM_REPLACE_TARGET2.Labels      "Next Cell"
                                        "Current Column"
                                        "All")
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 0 0 0 0 0 1 0 0 1 0 0)
                PB_COPY2
                PB_PASTE2
                PB_CLEAR2
                PB_UNDO2
                PB_REDO2
                IP_FIND2
                PB_FIND2
                OM_FIND_TARGET2
                IP_REPLACE2
                PB_REPLACE2
                OM_REPLACE_TARGET2
            )
        )
    )
)

(Layout Layout4
    (Components
        (SubLayout                      Layout25)
        (SubLayout                      Layout27)
        (SubLayout                      Layout28)
        (SubLayout                      Layout36)
    )

    (Resources
        (.Label                         "Batch Convert")
        (.Decorated                     True)
        (.TopOffset                     4)
        (.Layout
            (Grid (Rows 0 0 1 0) (Cols 1)
                Layout25
                Layout36
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
        (PushButton                     PB_REFRESH)
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
        (PB_REFRESH.Bitmap              "sab_refresh")
        (PB_REFRESH.HelpText            "Refresh")
        (PB_REFRESH.AttachLeft          True)
        (PB_REFRESH.AttachRight         True)
        (PB_REFRESH.AttachTop           True)
        (PB_REFRESH.AttachBottom        True)
        (PB_REFRESH.LeftOffset          10)
        (.Label                         "Source")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 0 1)
                RG_SOURCE
                PB_REFRESH
            )
        )
    )
)

(Layout Layout38
    (Components
        (OptionMenu                     OM_FORMAT)
    )

    (Resources
        (OM_FORMAT.Columns              6)
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
        (TABLE5.SelectionPolicy         4)
        (TABLE5.TopOffset               2)
        (TABLE5.BottomOffset            2)
        (TABLE5.ColumnNames             "Icon"
                                        "Name"
                                        "Type"
                                        "Device"
                                        "Path")
        (TABLE5.ColumnLabels            " "
                                        "Name"
                                        "Type"
                                        "Device"
                                        "Path")
        (TABLE5.ColumnWidths            2
                                        16
                                        4
                                        4
                                        120)
        (TABLE5.ColumnResizings         0
                                        0
                                        0
                                        0
                                        0)
        (TABLE5.ShowGrid                True)
        (TABLE5.LockedColumns           2)
        (TABLE5.RowSelectionPolicy      4)
        (TABLE5.ColumnResizables        0)
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
        (InputPanel                     InputPanel1)
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
            (Grid (Rows 0 0 1) (Cols 1)
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
        (CB_DXF.AttachTop               True)
        (CB_DWG.Label                   "DWG")
        (CB_DWG.AttachLeft              True)
        (CB_DWG.AttachTop               True)
        (CB_HPGL.Label                  "HP-GL")
        (CB_HPGL.AttachLeft             True)
        (CB_HPGL.AttachTop              True)
        (CB_PDF.Label                   "PDF")
        (CB_PDF.AttachLeft              True)
        (CB_PDF.AttachTop               True)
        (CB_PRINT.Label                 "Print")
        (CB_PRINT.AttachLeft            True)
        (CB_PRINT.AttachTop             True)
        (.Label                         "Format")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 0 0 0 0 1) (Cols 1)
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
        (SubLayout                      Layout5)
        (SubLayout                      Layout16)
    )

    (Resources
        (.Label                         "Selected")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1 0) (Cols 1)
                Layout5
                Layout16
            )
        )
    )
)

(Layout Layout5
    (Components
        (Table                          TABLE6)
    )

    (Resources
        (TABLE6.SelectionPolicy         4)
        (TABLE6.ColumnNames             "Icon"
                                        "Name"
                                        "Type"
                                        "Device"
                                        "Path")
        (TABLE6.ColumnLabels            " "
                                        "Name"
                                        "Type"
                                        "Device"
                                        "Path")
        (TABLE6.ColumnWidths            2
                                        16
                                        4
                                        4
                                        120)
        (TABLE6.ShowGrid                True)
        (TABLE6.LockedColumns           2)
        (TABLE6.RowSelectionPolicy      4)
        (TABLE6.ColumnResizables        0
                                        1)
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
        (InputPanel                     InputPanel2)
    )

    (Resources
        (.Decorated                     True)
    )
)

(Layout Layout16
    (Components
        (PushButton                     PB_MOVE_UP3)
        (PushButton                     PB_MOVE_DOWN3)
    )

    (Resources
        (PB_MOVE_UP3.Bitmap             "bbl_arrow_up")
        (PB_MOVE_UP3.HelpText           "Move up")
        (PB_MOVE_UP3.AttachLeft         True)
        (PB_MOVE_UP3.AttachRight        True)
        (PB_MOVE_UP3.AttachTop          True)
        (PB_MOVE_UP3.AttachBottom       True)
        (PB_MOVE_DOWN3.Bitmap           "bbl_arrow_down")
        (PB_MOVE_DOWN3.HelpText         "Move down")
        (PB_MOVE_DOWN3.AttachLeft       True)
        (PB_MOVE_DOWN3.AttachTop        True)
        (PB_MOVE_DOWN3.AttachBottom     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 0 1)
                PB_MOVE_UP3
                PB_MOVE_DOWN3
            )
        )
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
            (Grid (Rows 1) (Cols 0 1 0 0 1)
                Label1
                OM_PRINTER
                Label2
                OM_PAPER
                PB_EXECUTE
            )
        )
    )
)

(Layout Layout36
    (Components
        (OptionMenu                     OM_FOLDER)
        (PushButton                     PB_SELECT_FOLDER)
        (CheckButton                    CB_SUBFOLDER)
    )

    (Resources
        (PB_SELECT_FOLDER.Label         "...")
        (PB_SELECT_FOLDER.AttachLeft    True)
        (PB_SELECT_FOLDER.AttachRight   True)
        (CB_SUBFOLDER.Label             "Sub Folder")
        (CB_SUBFOLDER.AttachLeft        True)
        (CB_SUBFOLDER.AttachRight       True)
        (.Label                         "Source Folder")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 0 0)
                OM_FOLDER
                PB_SELECT_FOLDER
                CB_SUBFOLDER
            )
        )
    )
)
