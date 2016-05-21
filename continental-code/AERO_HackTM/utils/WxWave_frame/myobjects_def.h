#ifndef myobjects_def_h_included
#define myobjects_def_h_included


///////////////////////////////////////////////
//                 TYPES                     //
///////////////////////////////////////////////
#define OBJECT_TYPE_WINDOW                      "Window"
                                                
#define OBJECT_TYPE_ANALOGMETER                 "AnalogMeter"
#define OBJECT_TYPE_ANALOGMETERMULTI            "AnalogMeterMulti"
#define OBJECT_TYPE_ANALOGNEEDLE                "AnalogNeedle"
#define OBJECT_TYPE_ANGULARREGULATOR            "AngularRegulator"
#define OBJECT_TYPE_ANGULARMETER                "AngularMeter"
#define OBJECT_TYPE_BUTTON                      "Button"
#define OBJECT_TYPE_BITFIELD                    "BitField"
#define OBJECT_TYPE_BITMAPANIM                  "BitmapAnim"
#define OBJECT_TYPE_BITMAPBUTTON                "BitmapButton"
#define OBJECT_TYPE_BITMAPSLICE                 "BitmapSlice"
#define OBJECT_TYPE_CHECKBOX                    "CheckBox"
#define OBJECT_TYPE_CHECKLISTBOX                "CheckListBox"
#define OBJECT_TYPE_CHOICE                      "Choice"
#define OBJECT_TYPE_CIMG                        "CImg"
#define OBJECT_TYPE_DIAGRAM                     "Diagram"
#define OBJECT_TYPE_DIAGRAMCURVE                "DiagramCurve"
#define OBJECT_TYPE_DIRPICKER                   "DirPicker"
#define OBJECT_TYPE_FILEPICKER                  "FilePicker"
#define OBJECT_TYPE_GAUGE                       "Gauge"
#define OBJECT_TYPE_HTML                        "Html"
#define OBJECT_TYPE_LCD                         "LCD"
#define OBJECT_TYPE_LED                         "LED"
#define OBJECT_TYPE_LEDPANEL                    "LEDPanel"
#define OBJECT_TYPE_LINEARMETER                 "LinearMeter"
#define OBJECT_TYPE_LISTBOX                     "ListBox"
#define OBJECT_TYPE_MEDIA                       "Media"
#define OBJECT_TYPE_OSG                         "OSG"
#define OBJECT_TYPE_PLOTWINDOW                  "PlotWindow"
#define OBJECT_TYPE_PLOTCHANNEL                 "PlotChannel"
#define OBJECT_TYPE_SCROLLBAR                   "ScrollBar"
#define OBJECT_TYPE_SLIDER                      "Slider"
#define OBJECT_TYPE_SLIDERMULTI                 "SliderMulti"
#define OBJECT_TYPE_SLIDERMULTITHUMB            "SliderMultiThumb"
#define OBJECT_TYPE_SPINCTRL                    "SpinCtrl"
#define OBJECT_TYPE_STATICBITMAP                "StaticBitmap"
#define OBJECT_TYPE_STATICTEXT                  "StaticText"
#define OBJECT_TYPE_TEXTCTRL                    "TextCtrl"
#define OBJECT_TYPE_VARBITMAP                   "VarBitmap"


///////////////////////////////////////////////
//               CONFIG (COMMON)             //
///////////////////////////////////////////////
#define OBJECTCFG_NAME                          "Name"
#define OBJECTCFG_TYPE                          "Type"
#define OBJECTCFG_CONFIG_MODE                   "ConfigMode"
#define OBJECTCFG_CONFIG_NAME                   "ConfigName"
#define OBJECTCFG_RW                            "ReadWrite"
#define OBJECTCFG_PRIO                          "Priority"
#define OBJECTCFG_SIZE                          "Size"
#define OBJECTCFG_SIZE_MODE                     "SizeMode"
#define OBJECTCFG_PROP_MODE                     "PropMode"
#define OBJECTCFG_PANE_INFO                     "PaneInfo"
#define OBJECTCFG_GRID                          "Grid"
#define OBJECTCFG_STATE                         "State"
#define OBJECTCFG_MINMAX                        "MinMax"
#define OBJECTCFG_DISPLAY                       "Display"
#define OBJECTCFG_OBJALIGN                      "ObjAlign"
#define OBJECTCFG_PLUGINS                       "PlugIns"
#define OBJECTCFG_EVTSCRIPT                     "EvtScript"
                                                
#define OBJECTCFG_TITLE                         "Title"
#define OBJECTCFG_TITLECOLOUR                   "TitleColour"
#define OBJECTCFG_TITLEFONT                     "TitleFont"
#define OBJECTCFG_TITLEALIGN                    "TitleAlign"
#define OBJECTCFG_STYLE                         "Style"
#define OBJECTCFG_ORIENTATION                   "Orientation"
#define OBJECTCFG_TRANSPARENCY                  "Transparency"
#define OBJECTCFG_COLOUR1                       "Colour1"
#define OBJECTCFG_COLOUR2                       "Colour2"
#define OBJECTCFG_FILE1                         "File1"
#define OBJECTCFG_FILE2                         "File2"
#define OBJECTCFG_FILELIST1                     "FileList1"
#define OBJECTCFG_FILELIST2                     "FileList2"
#define OBJECTCFG_DIR1                          "Dir1"
#define OBJECTCFG_DIR2                          "Dir2"
#define OBJECTCFG_BITMAP1                       "Bitmap1"
#define OBJECTCFG_BITMAP2                       "Bitmap2"
#define OBJECTCFG_BITMAPSTATE1                  "BitmapState1"
#define OBJECTCFG_BITMAPSTATE2                  "BitmapState2"
#define OBJECTCFG_VALUE1                        "Value1"
#define OBJECTCFG_VALUE2                        "Value2"
#define OBJECTCFG_VALUETICK                     "ValueTick"
#define OBJECTCFG_VALUEFORMAT                   "ValueFormat"
#define OBJECTCFG_VALUEALIGN                    "ValueAlign"
#define OBJECTCFG_SELECTION                     "Selection"
#define OBJECTCFG_SELECTION_MODE                "SelectionMode"
#define OBJECTCFG_VARTUPLE                      "VarTuple"
#define OBJECTCFG_VARIABLE                      "Variable"
#define OBJECTCFG_VARSCALE                      "VarScale"
#define OBJECTCFG_VAROFFSET                     "VarOffset"
#define OBJECTCFG_VARINDEX                      "VarIndex"

// OBJECTCFG_CONFIG
#define OBJECTCFG_CONFIG_MODE_INTERNAL          "Internal"
#define OBJECTCFG_CONFIG_MODE_EXTERNAL          "External"

// OBJECTCFG_RW                                 
#define OBJECTCFG_RW_NONE                       "None"
#define OBJECTCFG_RW_READ                       "Read"
#define OBJECTCFG_RW_WRITE                      "Write"
#define OBJECTCFG_RW_WRITE_ONCE                 "WriteOnce"
                                                
// OBJECTCFG_SIZE
#define OBJECTCFG_SIZE_MODE_NONE                "None"
#define OBJECTCFG_SIZE_MODE_PIXEL               "Pixel"
#define OBJECTCFG_SIZE_MODE_PERCENT             "Percent"
#define OBJECTCFG_SIZE_MODE_CENTERED            "Centered"

// OBJECTCFG_PROP
#define OBJECTCFG_PROP_MODE_OFF                 "Off"
#define OBJECTCFG_PROP_MODE_ON                  "On"

// OBJECTCFG_STATE                              
#define OBJECTCFG_STATE_OPENED                  "Opened"
#define OBJECTCFG_STATE_CLOSED                  "Closed"

// OBJECTCFG_DRAW                              
#define OBJECTCFG_DRAW_SHOWN                    "Shown"
#define OBJECTCFG_DRAW_HIDDEN                   "Hidden"

// OBJECTCFG_FUNCTION
#define OBJECTCFG_FUNCTION_ENABLED              "Enabled"
#define OBJECTCFG_FUNCTION_DISABLED             "Disabled"

// OBJECTCFG_MINMAX                              
#define OBJECTCFG_MINMAX_NONE                   "None"
#define OBJECTCFG_MINMAX_MAXIMIZED              "Maximized"
#define OBJECTCFG_MINMAX_MINIMIZED              "Minimized"
                                                
// OBJECTCFG_TITLEALIGN                              
#define OBJECTCFG_TITLEALIGN_NONE               "None"
#define OBJECTCFG_TITLEALIGN_LEFT               "Left"
#define OBJECTCFG_TITLEALIGN_RIGHT              "Right"
#define OBJECTCFG_TITLEALIGN_CENTER             "Center"

// OBJECTCFG_BITMAPSTATE                        
#define OBJECTCFG_BITMAPSTATE_NONE              "None"
#define OBJECTCFG_BITMAPSTATE_NORMAL            "Normal"
#define OBJECTCFG_BITMAPSTATE_STRETCHED         "Stretched"
#define OBJECTCFG_BITMAPSTATE_RATIO             "Ratio"
#define OBJECTCFG_BITMAPSTATE_SCALED            "Scaled"
#define OBJECTCFG_BITMAPSTATE_TRANSPARENT       "Transparent"

// OBJECTCFG_CURSORSTATE
#define OBJECTCFG_CURSORSTATE_NONE              "None"
#define OBJECTCFG_CURSORSTATE_STANDARD          "Standard"
#define OBJECTCFG_CURSORSTATE_CUSTOM            "Custom"

// OBJECTCFG_ORIENTATION                        
#define OBJECTCFG_ORIENTATION_HORIZONTAL        "Horizontal"
#define OBJECTCFG_ORIENTATION_VERTICAL          "Vertical"
                                                
// OBJECTCFG_STYLE
#define OBJECTCFG_STYLE_NO_BORDER               "NoBorder"
#define OBJECTCFG_STYLE_SIMPLE_BORDER           "SimpleBorder"
#define OBJECTCFG_STYLE_DOUBLE_BORDER           "DoubleBorder"
#define OBJECTCFG_STYLE_SUNKEN_BORDER           "SunkenBorder"

// OBJECTCFG_VALUEALIGN                              
#define OBJECTCFG_VALUEALIGN_NONE               "None"
#define OBJECTCFG_VALUEALIGN_LEFT               "Left"
#define OBJECTCFG_VALUEALIGN_RIGHT              "Right"
#define OBJECTCFG_VALUEALIGN_CENTER             "Center"

// OBJECTCFG_DESCRIPTION
#define OBJECTCFG_DESC_ALIGN                    "DescAlign"
#define OBJECTCFG_DESC_TITLE                    "DescTitle"
#define OBJECTCFG_DESC_TITLECOLOUR              "DescTitleColour"
#define OBJECTCFG_DESC_TITLEFONT                "DescTitleFont"
#define OBJECTCFG_DESC_BACKCOLOUR               "DescBackColour"
#define OBJECTCFG_DESC_BITMAP                   "DescBitmap"
#define OBJECTCFG_DESC_BITMAPSTATE              "DescBitmapState"
#define OBJECTCFG_DESC_CURSOR                   "DescCursor"
#define OBJECTCFG_DESC_CURSORSTATE              "DescCursorState"
#define OBJECTCFG_DESC_KEYVALUE                 "DescKeyValue"
#define OBJECTCFG_DESC_KEYSHIFT                 "DescKeyShift"
#define OBJECTCFG_DESC_KEYCONTROL               "DescKeyControl"
#define OBJECTCFG_DESC_KEYALT                   "DescKeyAlt"

// OBJECTCFG_DESCRIPTION_ALIGN
#define OBJECTCFG_DESC_ALIGN_NONE               "None"
#define OBJECTCFG_DESC_ALIGN_TOP                "Top"
#define OBJECTCFG_DESC_ALIGN_BOTTOM             "Bottom"
#define OBJECTCFG_DESC_ALIGN_LEFT               "Left"
#define OBJECTCFG_DESC_ALIGN_RIGHT              "Right"

// OBJECTCFG_DESC_KEYVALUE
#define OBJECTCFG_DESC_KEYVALUE_NONE            "None"

// OBJECTCFG_TOOLTIP
#define OBJECTCFG_TOOLTIP_MODE                  "ToolTipMode"
#define OBJECTCFG_TOOLTIP_TITLE                 "ToolTipTitle"

// OBJECTCFG_TOOLTIP_MODE
#define OBJECTCFG_TOOLTIP_MODE_NONE             "None"
#define OBJECTCFG_TOOLTIP_MODE_NORMAL           "Normal"

// OBJECTCFG_ZOOM
#define OBJECTCFG_ZOOM_MODE                     "ZoomMode"

// OBJECTCFG_ZOOM_MODE
#define OBJECTCFG_ZOOM_MODE_NONE                "None"
#define OBJECTCFG_ZOOM_MODE_NORMAL              "Normal"

// OBJECTCFG_SELECTION_MODE
#define OBJECTCFG_SELECTION_MODE_NORMAL         "Normal"
#define OBJECTCFG_SELECTION_MODE_USEVARUNIT     "UseVarUnit"
#define OBJECTCFG_SELECTION_MODE_USEVARCOMMENT  "UseVarComment"


///////////////////////////////////////////////
//               CONFIG (PLG)                //
///////////////////////////////////////////////
#define PLGCFG_DLLFILENAME                      "DllFileName"
#define PLGCFG_DLLPARAMETER                     "DllParameter"


///////////////////////////////////////////////
//               CONFIG (IDL)                //
///////////////////////////////////////////////
#define IDLCFG_RW                               "ReadWrite"
#define IDLCFG_PARTIONNAME                      "PartitionName"
#define IDLCFG_GROUPNAME                        "GroupName"

// IDLCFG_RW
#define IDLCFG_RW_NONE                          "None"
#define IDLCFG_RW_READ                          "Read"
#define IDLCFG_RW_WRITE                         "Write"

///////////////////////////////////////////////
//               FUNCTIONS (IDL)             //
///////////////////////////////////////////////
// idl plugin functions
#define IDLFUN_SETINTERFACE                     "idlFUN_SetInterface"
#define IDLFUN_GETDATAFORMAT                    "idlFUN_GetDataFormat"
#define IDLFUN_GETDATALAYOUT                    "idlFUN_GetDataLayout"
#define IDLFUN_GETDATASIZE                      "idlFUN_GetDataSize"
#define IDLFUN_SETMEMFILE                       "idlFUN_SetMemFile"
#define IDLFUN_ACTIVATECALLBACK                 "idlFUN_ActivateCallback"
// idl plugin callbacks
#define IDLCB_ONDATAAVAILABLE                   "idlCB_OnDataAvailable"


///////////////////////////////////////////////
//                 EVENTS                    //
///////////////////////////////////////////////
#define OBJECTEVT_COMMAND_TEXT_UPDATED          "wxEVT_COMMAND_TEXT_UPDATED"
#define OBJECTEVT_COMMAND_TEXT_ENTER            "wxEVT_COMMAND_TEXT_ENTER"
#define OBJECTEVT_COMMAND_TEXT_URL              "wxEVT_COMMAND_TEXT_URL"
#define OBJECTEVT_COMMAND_TEXT_MAXLEN           "wxEVT_COMMAND_TEXT_MAXLEN"

#define OBJECTEVT_COMMAND_MENU_SELECTED         "wxEVT_COMMAND_MENU_SELECTED"
#define OBJECTEVT_COMMAND_SLIDER_UPDATED        "wxEVT_COMMAND_SLIDER_UPDATED"
#define OBJECTEVT_COMMAND_RADIOBOX_SELECTED     "wxEVT_COMMAND_RADIOBOX_SELECTED"
#define OBJECTEVT_COMMAND_RADIOBUTTON_SELECTED  "wxEVT_COMMAND_RADIOBUTTON_SELECTED"

#define OBJECTEVT_COMMAND_BUTTON_CLICKED        "wxEVT_COMMAND_BUTTON_CLICKED"
#define OBJECTEVT_COMMAND_CHECKBOX_CLICKED      "wxEVT_COMMAND_CHECKBOX_CLICKED"
#define OBJECTEVT_COMMAND_CHOICE_SELECTED       "wxEVT_COMMAND_CHOICE_SELECTED"
#define OBJECTEVT_COMMAND_LISTBOX_SELECTED      "wxEVT_COMMAND_LISTBOX_SELECTED"
#define OBJECTEVT_COMMAND_LISTBOX_DOUBLECLICKED "wxEVT_COMMAND_LISTBOX_DOUBLECLICKED"
#define OBJECTEVT_COMMAND_CHECKLISTBOX_TOGGLED  "wxEVT_COMMAND_CHECKLISTBOX_TOGGLED"

#define OBJECTEVT_COMMAND_VLBOX_SELECTED        "wxEVT_COMMAND_VLBOX_SELECTED"
#define OBJECTEVT_COMMAND_COMBOBOX_SELECTED     "wxEVT_COMMAND_COMBOBOX_SELECTED"
#define OBJECTEVT_COMMAND_TOOL_RCLICKED         "wxEVT_COMMAND_TOOL_RCLICKED"
#define OBJECTEVT_COMMAND_TOOL_ENTER            "wxEVT_COMMAND_TOOL_ENTER"
#define OBJECTEVT_COMMAND_SPINCTRL_UPDATED      "wxEVT_COMMAND_SPINCTRL_UPDATED"

#define OBJECTEVT_SOCKET                        "wxEVT_SOCKET"
#define OBJECTEVT_TIMER                         "wxEVT_TIMER "

#define OBJECTEVT_LEFT_DOWN                     "wxEVT_LEFT_DOWN"
#define OBJECTEVT_LEFT_UP                       "wxEVT_LEFT_UP"
#define OBJECTEVT_MIDDLE_DOWN                   "wxEVT_MIDDLE_DOWN"
#define OBJECTEVT_MIDDLE_UP                     "wxEVT_MIDDLE_UP"
#define OBJECTEVT_RIGHT_DOWN                    "wxEVT_RIGHT_DOWN"
#define OBJECTEVT_RIGHT_UP                      "wxEVT_RIGHT_UP"
#define OBJECTEVT_MOTION                        "wxEVT_MOTION"
#define OBJECTEVT_ENTER_WINDOW                  "wxEVT_ENTER_WINDOW"
#define OBJECTEVT_LEAVE_WINDOW                  "wxEVT_LEAVE_WINDOW"
#define OBJECTEVT_LEFT_DCLICK                   "wxEVT_LEFT_DCLICK"
#define OBJECTEVT_MIDDLE_DCLICK                 "wxEVT_MIDDLE_DCLICK"
#define OBJECTEVT_RIGHT_DCLICK                  "wxEVT_RIGHT_DCLICK"
#define OBJECTEVT_SET_FOCUS                     "wxEVT_SET_FOCUS"
#define OBJECTEVT_KILL_FOCUS                    "wxEVT_KILL_FOCUS"
#define OBJECTEVT_CHILD_FOCUS                   "wxEVT_CHILD_FOCUS"
#define OBJECTEVT_MOUSEWHEEL                    "wxEVT_MOUSEWHEEL"

#define OBJECTEVT_NC_LEFT_DOWN                  "wxEVT_NC_LEFT_DOWN"
#define OBJECTEVT_NC_LEFT_UP                    "wxEVT_NC_LEFT_UP"
#define OBJECTEVT_NC_MIDDLE_DOWN                "wxEVT_NC_MIDDLE_DOWN"
#define OBJECTEVT_NC_MIDDLE_UP                  "wxEVT_NC_MIDDLE_UP"
#define OBJECTEVT_NC_RIGHT_DOWN                 "wxEVT_NC_RIGHT_DOWN"
#define OBJECTEVT_NC_RIGHT_UP                   "wxEVT_NC_RIGHT_UP"
#define OBJECTEVT_NC_MOTION                     "wxEVT_NC_MOTION"
#define OBJECTEVT_NC_ENTER_WINDOW               "wxEVT_NC_ENTER_WINDOW"
#define OBJECTEVT_NC_LEAVE_WINDOW               "wxEVT_NC_LEAVE_WINDOW"
#define OBJECTEVT_NC_LEFT_DCLICK                "wxEVT_NC_LEFT_DCLICK"
#define OBJECTEVT_NC_MIDDLE_DCLICK              "wxEVT_NC_MIDDLE_DCLICK"
#define OBJECTEVT_NC_RIGHT_DCLICK               "wxEVT_NC_RIGHT_DCLICK"
    
#define OBJECTEVT_CHAR                          "wxEVT_CHAR"
#define OBJECTEVT_CHAR_HOOK                     "wxEVT_CHAR_HOOK"
#define OBJECTEVT_NAVIGATION_KEY                "wxEVT_NAVIGATION_KEY"
#define OBJECTEVT_KEY_DOWN                      "wxEVT_KEY_DOWN"
#define OBJECTEVT_KEY_UP                        "wxEVT_KEY_U"

#define OBJECTEVT_SET_CURSOR                    "wxEVT_SET_CURSOR"
    
#define OBJECTEVT_SCROLL_TOP                    "wxEVT_SCROLL_TOP"
#define OBJECTEVT_SCROLL_BOTTOM                 "wxEVT_SCROLL_BOTTOM"
#define OBJECTEVT_SCROLL_LINEUP                 "wxEVT_SCROLL_LINEUP"
#define OBJECTEVT_SCROLL_LINEDOWN               "wxEVT_SCROLL_LINEDOWN"
#define OBJECTEVT_SCROLL_PAGEUP                 "wxEVT_SCROLL_PAGEUP"
#define OBJECTEVT_SCROLL_PAGEDOWN               "wxEVT_SCROLL_PAGEDOWN"
#define OBJECTEVT_SCROLL_THUMBTRACK             "wxEVT_SCROLL_THUMBTRACK"
#define OBJECTEVT_SCROLL_THUMBRELEASE           "wxEVT_SCROLL_THUMBRELEASE"
#define OBJECTEVT_SCROLL_CHANGED                "wxEVT_SCROLL_CHANGED"

#define OBJECTEVT_SCROLLWIN_TOP                 "wxEVT_SCROLLWIN_TOP"
#define OBJECTEVT_SCROLLWIN_BOTTOM              "wxEVT_SCROLLWIN_BOTTOM"
#define OBJECTEVT_SCROLLWIN_LINEUP              "wxEVT_SCROLLWIN_LINEUP"
#define OBJECTEVT_SCROLLWIN_LINEDOWN            "wxEVT_SCROLLWIN_LINEDOWN"
#define OBJECTEVT_SCROLLWIN_PAGEUP              "wxEVT_SCROLLWIN_PAGEUP"
#define OBJECTEVT_SCROLLWIN_PAGEDOWN            "wxEVT_SCROLLWIN_PAGEDOWN"
#define OBJECTEVT_SCROLLWIN_THUMBTRACK          "wxEVT_SCROLLWIN_THUMBTRACK"
#define OBJECTEVT_SCROLLWIN_THUMBRELEASE        "wxEVT_SCROLLWIN_THUMBRELEASE"

#define OBJECTEVT_SIZE                          "wxEVT_SIZE"
#define OBJECTEVT_MOVE                          "wxEVT_MOVE"
#define OBJECTEVT_CLOSE_WINDOW                  "wxEVT_CLOSE_WINDOW"
#define OBJECTEVT_END_SESSION                   "wxEVT_END_SESSION"
#define OBJECTEVT_QUERY_END_SESSION             "wxEVT_QUERY_END_SESSION"
#define OBJECTEVT_ACTIVATE_APP                  "wxEVT_ACTIVATE_APP"
#define OBJECTEVT_POWER                         "wxEVT_POWER"
#define OBJECTEVT_ACTIVATE                      "wxEVT_ACTIVATE"
#define OBJECTEVT_CREATE                        "wxEVT_CREATE"
#define OBJECTEVT_DESTROY                       "wxEVT_DESTROY"
#define OBJECTEVT_SHOW                          "wxEVT_SHOW"
#define OBJECTEVT_ICONIZE                       "wxEVT_ICONIZE"
#define OBJECTEVT_MAXIMIZE                      "wxEVT_MAXIMIZE"
#define OBJECTEVT_MOUSE_CAPTURE_CHANGED         "wxEVT_MOUSE_CAPTURE_CHANGED"
#define OBJECTEVT_PAINT                         "wxEVT_PAINT"
#define OBJECTEVT_ERASE_BACKGROUND              "wxEVT_ERASE_BACKGROUND"
#define OBJECTEVT_NC_PAINT                      "wxEVT_NC_PAINT"
#define OBJECTEVT_PAINT_ICON                    "wxEVT_PAINT_ICON"
#define OBJECTEVT_MENU_OPEN                     "wxEVT_MENU_OPEN"
#define OBJECTEVT_MENU_CLOSE                    "wxEVT_MENU_CLOSE"
#define OBJECTEVT_MENU_HIGHLIGHT                "wxEVT_MENU_HIGHLIGHT"
#define OBJECTEVT_CONTEXT_MENU                  "wxEVT_CONTEXT_MENU"
#define OBJECTEVT_SYS_COLOUR_CHANGED            "wxEVT_SYS_COLOUR_CHANGED"
#define OBJECTEVT_DISPLAY_CHANGED               "wxEVT_DISPLAY_CHANGED"
#define OBJECTEVT_SETTING_CHANGED               "wxEVT_SETTING_CHANGED"
#define OBJECTEVT_QUERY_NEW_PALETTE             "wxEVT_QUERY_NEW_PALETTE"
#define OBJECTEVT_PALETTE_CHANGED               "wxEVT_PALETTE_CHANGED"
#define OBJECTEVT_JOY_BUTTON_DOWN               "wxEVT_JOY_BUTTON_DOWN"
#define OBJECTEVT_JOY_BUTTON_UP                 "wxEVT_JOY_BUTTON_UP"
#define OBJECTEVT_JOY_MOVE                      "wxEVT_JOY_MOVE"
#define OBJECTEVT_JOY_ZMOVE                     "wxEVT_JOY_ZMOVE"
#define OBJECTEVT_DROP_FILES                    "wxEVT_DROP_FILES"
#define OBJECTEVT_DRAW_ITEM                     "wxEVT_DRAW_ITEM"
#define OBJECTEVT_MEASURE_ITEM                  "wxEVT_MEASURE_ITEM"
#define OBJECTEVT_COMPARE_ITEM                  "wxEVT_COMPARE_ITEM"
#define OBJECTEVT_INIT_DIALOG                   "wxEVT_INIT_DIALOG"
#define OBJECTEVT_UPDATE_UI                     "wxEVT_UPDATE_UI"

#define OBJECTEVT_COMMAND_DIRPICKER_CHANGED     "wxEVT_COMMAND_DIRPICKER_CHANGED"
#define OBJECTEVT_COMMAND_FILEPICKER_CHANGED    "wxEVT_COMMAND_FILEPICKER_CHANGED"

#define OBJECTEVT_COMMAND_LEFT_CLICK            "wxEVT_COMMAND_LEFT_CLICK"
#define OBJECTEVT_COMMAND_LEFT_DCLICK           "wxEVT_COMMAND_LEFT_DCLICK"
#define OBJECTEVT_COMMAND_RIGHT_CLICK           "wxEVT_COMMAND_RIGHT_CLICK"
#define OBJECTEVT_COMMAND_RIGHT_DCLICK          "wxEVT_COMMAND_RIGHT_DCLICK"
#define OBJECTEVT_COMMAND_SET_FOCUS             "wxEVT_COMMAND_SET_FOCUS"
#define OBJECTEVT_COMMAND_KILL_FOCUS            "wxEVT_COMMAND_KILL_FOCUS"
#define OBJECTEVT_COMMAND_ENTER                 "wxEVT_COMMAND_ENTER"

#define OBJECTEVT_HELP                          "wxEVT_HELP"
#define OBJECTEVT_DETAILED_HELP                 "wxEVT_DETAILED_HELP"

// wxWavE custom events
#define OBJECTEVT_IDLE                          "wxEVT_IDLE"
#define OBJECTEVT_OPEN                          "wxEVT_OPEN"
#define OBJECTEVT_CLOSE                         "wxEVT_CLOSE"
#define OBJECTEVT_CONNECT                       "wxEVT_CONNECT"
#define OBJECTEVT_DISCONNECT                    "wxEVT_DISCONNECT"
#define OBJECTEVT_PRESTEP                       "wxEVT_PRESTEP"
#define OBJECTEVT_STEP                          "wxEVT_STEP"
#define OBJECTEVT_POSTSTEP                      "wxEVT_POSTSTEP"
#define OBJECTEVT_RENDER                        "wxEVT_RENDER"
#define OBJECTEVT_DRAW2D                        "wxEVT_DRAW2D"
#define OBJECTEVT_DRAW3D                        "wxEVT_DRAW3D"

// wxWavE CAN events
#define CANEVT_MESSAGE                          "wxEVT_CAN_MESSAGE"
#define CANEVT_SIGNAL                           "wxEVT_CAN_SIGNAL"

// wxWavE FlexRay events
#define FREVT_MESSAGE                           "wxEVT_FR_MESSAGE"
#define FREVT_SIGNAL                            "wxEVT_FR_SIGNAL"


#endif // myobjects_def_h_included
