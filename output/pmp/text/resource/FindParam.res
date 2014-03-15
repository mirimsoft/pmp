(Dialog FindParam
    (Components
        (SubLayout                      Layout1)
        (SubLayout                      Layout2)
        (SubLayout                      Layout3)
    )

    (Resources
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
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.TopOffset                     4)
        (.LeftOffset                    4)
        (.RightOffset                   4)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                InputPanel1
            )
        )
    )
)

(Layout Layout2
    (Components
        (PushButton                     PushButton1)
        (PushButton                     PushButton2)
    )

    (Resources
        (PushButton1.Label              "Find")
        (PushButton2.Label              "Close")
        (PushButton2.AttachTop          True)
        (PushButton2.AttachBottom       True)
        (PushButton2.TopOffset          4)
        (PushButton2.BottomOffset       4)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.LeftOffset                    4)
        (.RightOffset                   4)
        (.Layout
            (Grid (Rows 1) (Cols 1 1)
                PushButton1
                PushButton2
            )
        )
    )
)

(Layout Layout3
    (Components
        (TextArea                       TextArea1)
    )

    (Resources
        (.Label                         "Parameters Found")
        (.Decorated                     True)
        (.AttachLeft                    True)
        (.AttachRight                   True)
        (.AttachTop                     True)
        (.AttachBottom                  True)
        (.LeftOffset                    4)
        (.RightOffset                   4)
        (.Layout
            (Grid (Rows 1) (Cols 1)
                TextArea1
            )
        )
    )
)
