(Dialog SimpleDialog
    (Components
        (InputPanel                     InputPanel1)
        (PushButton                     PushButton1)
    )

    (Resources
        (PushButton1.Label              "Close")
        (PushButton1.AttachLeft         True)
        (PushButton1.AttachRight        True)
        (.Layout
            (Grid (Rows 1 1) (Cols 1)
                InputPanel1
                PushButton1
            )
        )
    )
)
