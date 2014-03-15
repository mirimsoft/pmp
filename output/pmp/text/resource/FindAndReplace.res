(Dialog FindAndReplace
    (Components
        (SubLayout                      Layout1)
        (SubLayout                      Layout2)
        (SubLayout                      Layout3)
    )

    (Resources
        (.Label                         "Find & Replace")
        (.Resizeable                    False)
        (.DefaultButton                 "PushButton1")
        (.AlwaysOnTop                   True)
        (.Layout
            (Grid (Rows 0 0 1) (Cols 1)
                Layout1
                Layout2
                Layout3
            )
        )
    )
)

(Layout Layout1
    (Components
        (InputPanel                     InputPanel1)
    )

    (Resources
        (.Label                         "Find what")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.TopOffset                     4)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                InputPanel1
            )
        )
    )
)

(Layout Layout2
    (Components
        (InputPanel                     InputPanel2)
    )

    (Resources
        (.Label                         "Replace with")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                InputPanel2
            )
        )
    )
)

(Layout Layout3
    (Components
        (PushButton                     PushButton1)
        (PushButton                     PushButton2)
        (PushButton                     PushButton3)
    )

    (Resources
        (PushButton1.Label              "Find")
        (PushButton2.Label              "Replace")
        (PushButton3.Label              "Replace All")
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
