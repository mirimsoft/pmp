(Dialog BatchTools
    (Components
        (SubLayout                      Layout1)
        (SubLayout                      Layout2)
        (SubLayout                      Layout3)
    )

    (Resources
        (.Layout
            (Grid (Rows 0 1 0) (Cols 1)
                Layout1
                Layout2
                Layout3
            )
        )
    )
)

(Layout Layout1
    (Components
        (SubLayout                      Layout7)
        (SubLayout                      Layout8)
    )

    (Resources
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.TopOffset                     2)
        (.Layout
            (Grid (Rows 1 1) (Cols 1)
                Layout7
                Layout8
            )
        )
    )
)

(Layout Layout7
    (Components
        (RadioGroup                     RadioGroupSource)
    )

    (Resources
        (RadioGroupSource.AttachRight   False)
        (RadioGroupSource.AttachBottom  False)
        (RadioGroupSource.Names         "Session"
                                        "Local Disk"
                                        "Work Space")
        (RadioGroupSource.Labels        "Session"
                                        "Local Disk"
                                        "Work Space")
        (.Label                         "Source")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                RadioGroupSource
            )
        )
    )
)

(Layout Layout8
    (Components
        (OptionMenu                     OptionMenuFolder)
        (PushButton                     PushButtonSelect)
        (CheckButton                    CheckButtonAll)
    )

    (Resources
        (PushButtonSelect.Label         "...")
        (PushButtonSelect.AttachLeft    True)
        (PushButtonSelect.AttachRight   True)
        (CheckButtonAll.Label           "Sub Folder")
        (CheckButtonAll.AttachLeft      True)
        (CheckButtonAll.AttachRight     True)
        (.Label                         "Folder")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 0 0)
                OptionMenuFolder
                PushButtonSelect
                CheckButtonAll
            )
        )
    )
)

(Layout Layout2
    (Components
        (SubLayout                      Layout4)
        (SubLayout                      Layout5)
        (SubLayout                      Layout6)
    )

    (Resources
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 0 1)
                Layout4
                Layout5
                Layout6
            )
        )
    )
)

(Layout Layout4
    (Components
        (Table                          Table1)
    )

    (Resources
        (.Label                         "Items")
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


(Layout Layout5
    (Components
        (SubLayout                      Layout12)
        (SubLayout                      Layout13)
        (SubLayout                      Layout14)
    )

    (Resources
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 0 0 1) (Cols 1)
                Layout12
                Layout13
                Layout14
            )
        )
    )
)

(Layout Layout12
    (Components
        (CheckButton                    CheckButtonAsm)
        (CheckButton                    CheckButtonDrw)
    )

    (Resources
        (CheckButtonAsm.Label           "ASM")
        (CheckButtonAsm.AttachLeft      True)
        (CheckButtonDrw.Label           "DRW")
        (CheckButtonDrw.AttachLeft      True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.TopOffset                     6)
        (.Layout
            (Grid (Rows 1 1) (Cols 1)
                CheckButtonAsm
                CheckButtonDrw
            )
        )
    )
)

(Layout Layout13
    (Components
        (PushButton                     PushButtonAdd)
        (PushButton                     PushButtonAddAll)
        (PushButton                     PushButtonRemove)
        (PushButton                     PushButtonRemoveAll)
    )

    (Resources
        (PushButtonAdd.Label            ">")
        (PushButtonAdd.AttachLeft       True)
        (PushButtonAdd.AttachRight      True)
        (PushButtonAddAll.Label         ">>")
        (PushButtonAddAll.AttachLeft    True)
        (PushButtonAddAll.AttachRight   True)
        (PushButtonRemove.Label         "<")
        (PushButtonRemove.AttachLeft    True)
        (PushButtonRemove.AttachRight   True)
        (PushButtonRemoveAll.Label      "<<")
        (PushButtonRemoveAll.AttachLeft True)
        (PushButtonRemoveAll.AttachRight True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.TopOffset                     6)
        (.Layout
            (Grid (Rows 1 1 1 1) (Cols 1)
                PushButtonAdd
                PushButtonAddAll
                PushButtonRemove
                PushButtonRemoveAll
            )
        )
    )
)

(Layout Layout14
    (Components
        (CheckButton                    CheckButtonDxf)
        (CheckButton                    CheckButtonDwg)
        (CheckButton                    CheckButtonPdf)
        (CheckButton                    CheckButtonHpgl)
        (CheckButton                    CheckButtonPrint)
    )

    (Resources
        (CheckButtonDxf.Label           "DXF")
        (CheckButtonDxf.AttachLeft      True)
        (CheckButtonDwg.Label           "DWG")
        (CheckButtonDwg.AttachLeft      True)
        (CheckButtonPdf.Label           "PDF")
        (CheckButtonPdf.AttachLeft      True)
        (CheckButtonHpgl.Label          "HP-GL")
        (CheckButtonHpgl.AttachLeft     True)
        (CheckButtonPrint.Label         "Print")
        (CheckButtonPrint.AttachLeft    True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.TopOffset                     6)
        (.Layout
            (Grid (Rows 1 1 1 1 1) (Cols 1)
                CheckButtonDxf
                CheckButtonDwg
                CheckButtonPdf
                CheckButtonHpgl
                CheckButtonPrint
            )
        )
    )
)

(Layout Layout6
    (Components
        (Table                          Table2)
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
                Table2
            )
        )
    )
)


(Layout Layout3
    (Components
        (OptionMenu                     OptionMenuPrinter)
        (OptionMenu                     OptionMenuPaper)
        (PushButton                     PushButtonExecute)
    )

    (Resources
        (OptionMenuPrinter.TopOffset    10)
        (OptionMenuPrinter.BottomOffset 10)
        (OptionMenuPrinter.LeftOffset   10)
        (OptionMenuPrinter.RightOffset  10)
        (PushButtonExecute.Label        "Execute")
        (PushButtonExecute.AttachLeft   True)
        (PushButtonExecute.AttachRight  True)
        (PushButtonExecute.LeftOffset   10)
        (PushButtonExecute.RightOffset  10)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1 1 0)
                OptionMenuPrinter
                OptionMenuPaper
                PushButtonExecute
            )
        )
    )
)
