# DialogHandler
Makes dialog boxes on numpad inputs! Make a dialogs folder in your Geometry Dash folder, then put the number as the title of a json file (`1.json`, `2.json`, etc.). Then, when you press that number on the **numpad** the dialog box will show up!

### JSON Syntax
```json
{
    "color": 2,
    "lines": [
        {
            "portrait": 12,
            "title": "Rick",
            "message": "We're no strangers to love, {user}!"
        },
        {
            "portrait": 13,
            "title": "Rick",
            "message": "You know the rules and so do I"
        },
    ]
}
```

### Enums
The portrait enum is based on png files in your Geometry Dash Resources folder. Look for `dialogIcon_001` through `dialogIcon_025` in that folder. The enum corresponds to the number at the end of the png name.

The color enum is as follows
| Key | Value        |
|-----|--------------|
| 1   | Orange/Brown |
| 2   | Blue         |
| 3   | Green        |
| 4   | Purple       |
| 5   | Grey/Black   |
