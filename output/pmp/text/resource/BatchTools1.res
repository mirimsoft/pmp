(Dialog BatchTools1
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
        (PushButton                     PushButton16)
        (PushButton                     PushButton17)
    )

    (Resources
        (PushButton16.Label             "&Option")
        (PushButton17.Label             "&Exit")
        (.Label                         "&File")
    )
)

(MenuPane MenuPane2
    (Components
        (PushButton                     PushButton19)
    )

    (Resources
        (PushButton19.Label             "&Find/Replace")
        (.Label                         "&Edit")
    )
)

(MenuPane MenuPane3
    (Components
        (PushButton                     PushButton22)
        (PushButton                     PushButton25)
        (PushButton                     PushButton26)
    )

    (Resources
        (PushButton22.Label             "&Load Drawing")
        (PushButton25.Label             "Session &BOM")
        (PushButton26.Label             "Session &Part List")
        (.Label                         "&Tools")
    )
)

(MenuPane MenuPane5
    (Components
        (PushButton                     PushButton34)
        (PushButton                     PushButton35)
        (PushButton                     PushButton36)
        (PushButton                     PushButton37)
    )

    (Resources
        (PushButton34.Label             "&Contents")
        (PushButton35.Label             "&Show Log")
        (PushButton36.Label             "&License")
        (PushButton37.Label             "&About")
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
            (Grid (Rows 1) (Cols 1 1)
                Layout8
                Layout9
            )
        )
    )
)

(Layout Layout8
    (Components
        (Table                          Table1)
    )

    (Resources
        (.Label                         "Standard Parameter")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                Table1
            )
        )
    )
)


(Layout Layout9
    (Components
        (Table                          Table2)
    )

    (Resources
        (.Label                         "Parameters To Delete")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                Table2
            )
        )
    )
)


(Layout Layout7
    (Components
        (PushButton                     PushButton1)
        (PushButton                     PushButton2)
        (PushButton                     PushButton3)
    )

    (Resources
        (PushButton1.Label              "Read Excel")
        (PushButton2.Label              "Save To Excel")
        (PushButton3.Label              "Save")
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 1 1)
                PushButton1
                PushButton2
                PushButton3
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
        (Table                          Table3)
    )

    (Resources
        (.Label                         "Standard Parameters")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                Table3
            )
        )
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
        (PushButton                     PushButton11)
        (PushButton                     PushButton12)
    )

    (Resources
        (PushButton11.Label             "Clean")
        (PushButton12.Label             "Standardize")
        (.Label                         "Screen")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 1)
                PushButton11
                PushButton12
            )
        )
    )
)

(Layout Layout17
    (Components
        (CheckButton                    CheckButton1)
        (CheckButton                    CheckButton2)
    )

    (Resources
        (CheckButton1.Label             "ASM")
        (CheckButton2.Label             "PRT")
        (.Label                         "Filter")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 1)
                CheckButton1
                CheckButton2
            )
        )
    )
)

(Layout Layout18
    (Components
        (PushButton                     PushButton13)
        (PushButton                     PushButton14)
    )

    (Resources
        (PushButton13.Label             "Read")
        (PushButton14.Label             "Apply")
        (.Label                         "Session")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 1)
                PushButton13
                PushButton14
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
        (Table                          Table4)
    )

    (Resources
        (.Label                         "Names")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                Table4
            )
        )
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
        (InputPanel                     InputPanel5)
        (PushButton                     PushButton28)
        (PushButton                     PushButton29)
    )

    (Resources
        (InputPanel5.Columns            1)
        (PushButton28.Label             "+")
        (PushButton28.AttachLeft        True)
        (PushButton28.AttachRight       True)
        (PushButton29.Label             "-")
        (PushButton29.AttachLeft        True)
        (PushButton29.AttachRight       True)
        (.Label                         "Prefix")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.Layout
            (Grid (Rows 1) (Cols 1 0 0)
                InputPanel5
                PushButton28
                PushButton29
            )
        )
    )
)

(Layout Layout23
    (Components
        (InputPanel                     InputPanel8)
        (PushButton                     PushButton30)
        (PushButton                     PushButton31)
    )

    (Resources
        (InputPanel8.Columns            1)
        (PushButton30.Label             "+")
        (PushButton30.AttachLeft        True)
        (PushButton30.AttachRight       True)
        (PushButton31.Label             "-")
        (PushButton31.AttachLeft        True)
        (PushButton31.AttachRight       True)
        (.Label                         "Surfix")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.Layout
            (Grid (Rows 1) (Cols 1 0 0)
                InputPanel8
                PushButton30
                PushButton31
            )
        )
    )
)

(Layout Layout24
    (Components
        (PushButton                     PushButton32)
        (PushButton                     PushButton33)
    )

    (Resources
        (PushButton32.Label             "Read")
        (PushButton33.Label             "Apply")
        (.Label                         "Session")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.Layout
            (Grid (Rows 1) (Cols 1 1)
                PushButton32
                PushButton33
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
        (RadioGroup                     RadioGroup2)
        (CheckButton                    CheckButton11)
    )

    (Resources
        (RadioGroup2.AttachTop          False)
        (RadioGroup2.AttachBottom       False)
        (RadioGroup2.Names              "Session"
                                        "Workspace"
                                        "Disk")
        (RadioGroup2.Labels             "Session"
                                        "Workspace"
                                        "Local Disk")
        (CheckButton11.Label            "Subfolder")
        (CheckButton11.AttachLeft       True)
        (.Label                         "Source")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 0 1)
                RadioGroup2
                CheckButton11
            )
        )
    )
)

(Layout Layout38
    (Components
        (OptionMenu                     OptionMenu4)
    )

    (Resources
        (OptionMenu4.VisibleRows        3)
        (OptionMenu4.Names              "Postscript"
                                        "PDF"
                                        "HPGL")
        (OptionMenu4.Labels             "Postscript"
                                        "PDF"
                                        "HP-GL")
        (.Label                         "Intermediate Print Format")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                OptionMenu4
            )
        )
    )
)

(Layout Layout26
    (Components
        (OptionMenu                     OptionMenu1)
        (PushButton                     PushButton38)
    )

    (Resources
        (OptionMenu1.VisibleRows        12)
        (PushButton38.Label             "...")
        (PushButton38.AttachLeft        True)
        (PushButton38.AttachRight       True)
        (.Label                         "Folder")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 0)
                OptionMenu1
                PushButton38
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
        (Table                          Table5)
    )

    (Resources
        (.Label                         "Source")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                Table5
            )
        )
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
        (CheckButton                    CheckButton4)
        (CheckButton                    CheckButton5)
    )

    (Resources
        (CheckButton4.Label             "ASM")
        (CheckButton4.AttachLeft        True)
        (CheckButton5.Label             "DRW")
        (CheckButton5.AttachLeft        True)
        (.Label                         "Filter")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1 1) (Cols 1)
                CheckButton4
                CheckButton5
            )
        )
    )
)

(Layout Layout33
    (Components
        (PushButton                     PushButton39)
        (PushButton                     PushButton40)
        (PushButton                     PushButton41)
        (PushButton                     PushButton42)
    )

    (Resources
        (PushButton39.Label             ">")
        (PushButton39.AttachLeft        True)
        (PushButton39.AttachRight       True)
        (PushButton39.AttachTop         True)
        (PushButton40.Label             ">>")
        (PushButton40.AttachLeft        True)
        (PushButton40.AttachRight       True)
        (PushButton40.AttachTop         True)
        (PushButton41.Label             "<")
        (PushButton41.AttachLeft        True)
        (PushButton41.AttachRight       True)
        (PushButton41.AttachTop         True)
        (PushButton41.TopOffset         10)
        (PushButton42.Label             "<<")
        (PushButton42.AttachLeft        True)
        (PushButton42.AttachRight       True)
        (PushButton42.AttachTop         True)
        (.Label                         "Select")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 0 0 0 1) (Cols 1)
                PushButton39
                PushButton40
                PushButton41
                PushButton42
            )
        )
    )
)

(Layout Layout34
    (Components
        (CheckButton                    CheckButton6)
        (CheckButton                    CheckButton7)
        (CheckButton                    CheckButton8)
        (CheckButton                    CheckButton9)
        (CheckButton                    CheckButton10)
    )

    (Resources
        (CheckButton6.Label             "DXF")
        (CheckButton6.AttachLeft        True)
        (CheckButton7.Label             "DWG")
        (CheckButton7.AttachLeft        True)
        (CheckButton8.Label             "HP-GL")
        (CheckButton8.AttachLeft        True)
        (CheckButton9.Label             "PDF")
        (CheckButton9.AttachLeft        True)
        (CheckButton10.Label            "Printer")
        (CheckButton10.AttachLeft       True)
        (.Label                         "Format")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1 1 1 1 1) (Cols 1)
                CheckButton6
                CheckButton7
                CheckButton8
                CheckButton9
                CheckButton10
            )
        )
    )
)

(Layout Layout31
    (Components
        (Table                          Table6)
    )

    (Resources
        (.Label                         "Selected")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                Table6
            )
        )
    )
)


(Layout Layout28
    (Components
        (Label                          Label1)
        (OptionMenu                     OptionMenu2)
        (Label                          Label2)
        (OptionMenu                     OptionMenu3)
        (PushButton                     PushButton43)
    )

    (Resources
        (Label1.Label                   "Printer")
        (Label1.AttachLeft              True)
        (Label1.AttachRight             True)
        (Label1.LeftOffset              20)
        (Label1.RightOffset             4)
        (OptionMenu2.Columns            8)
        (Label2.Label                   "Paper Size")
        (Label2.AttachLeft              True)
        (Label2.AttachRight             True)
        (Label2.LeftOffset              20)
        (Label2.RightOffset             4)
        (OptionMenu3.Columns            8)
        (PushButton43.Label             "Execute")
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 0 0 0 0 1)
                Label1
                OptionMenu2
                Label2
                OptionMenu3
                PushButton43
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
        (PushButton                     PushButton44)
        (PushButton                     PushButton45)
        (PushButton                     PushButton46)
        (PushButton                     PushButton47)
        (PushButton                     PushButton48)
        (PushButton                     PushButton49)
        (PushButton                     PushButton50)
    )

    (Resources
        (PushButton44.Label             "Model Backup")
        (PushButton44.AttachLeft        True)
        (PushButton44.AttachRight       True)
        (PushButton45.Label             "Save Names")
        (PushButton45.AttachLeft        True)
        (PushButton45.AttachRight       True)
        (PushButton46.Label             "Show FamilyTable Parts")
        (PushButton46.AttachLeft        True)
        (PushButton46.AttachRight       True)
        (PushButton47.Label             "Replace FamilyTable Instance")
        (PushButton47.AttachLeft        True)
        (PushButton47.AttachRight       True)
        (PushButton48.Label             "Show All")
        (PushButton48.AttachLeft        True)
        (PushButton48.AttachRight       True)
        (PushButton49.Label             "Restore Names")
        (PushButton49.AttachLeft        True)
        (PushButton49.AttachRight       True)
        (PushButton50.Label             "Save All")
        (PushButton50.AttachLeft        True)
        (PushButton50.AttachRight       True)
        (PushButton50.AttachTop         True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 0 0 0 0 0 0 1) (Cols 1)
                PushButton44
                PushButton45
                PushButton46
                PushButton47
                PushButton48
                PushButton49
                PushButton50
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
