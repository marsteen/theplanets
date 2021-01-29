#
# root - der Wurzelknoten
#
NAME ROOT root
CHILD MainKnot    0   0   VOID
#
# DiaglogBox "MainKnot befindet sich an Position 10/10
#
NAME KNOT MainKnot
CHILD MainBox 10  10  VOID
CHILD Infobox -20 10  RIGHT_TOP
CHILD AppInfoBox  0   0   CENTER_CENTER
STATUS INACTIVE
    GROUP   0
#
COLOR ROLLOVER    0.0 1.0 0.9882  1.0
COLOR TT_FRAME    0.5 0.5 0.5 1.0
COLOR TT_BOX  1.0 0.8 0.0 1.0
COLOR TT_FONT 0.0 0.0 0.0 1.0
#
COLOR CWHITE  1.0 1.0 1.0 1.0
COLOR CBLACK  0.0 0.0 0.0 1.0
COLOR CGREY   0.0 1.0 0.98    0.2
#
COLOR CRED    1.0 0.0 0.0 1.0
COLOR CGREEN  0.0 1.0 0.0 1.0
COLOR CBLUE   0.0 0.0 1.0 1.0
COLOR CGREY10 0.1 0.1 0.1 0.5
COLOR CGREY20 0.2 0.2 0.2 1.0
COLOR CGREY30 0.3 0.3 0.3 1.0
COLOR CGREY40 0.4 0.4 0.4 1.0
COLOR CGREY50 0.5 0.5 0.5 1.0
COLOR CGREY60 0.6 0.6 0.6 1.0
COLOR CGREY70 0.7 0.7 0.7 1.0
COLOR CGREY80 0.8 0.8 0.8 1.0
COLOR CGREY90 0.9 0.9 0.9 1.0
#
COLOR CRED50  0.5 0.0 0.0 1.0
COLOR CGREEN50    0.0 0.5 0.0 1.0
COLOR CBLUE50 0.0 0.0 0.5 1.0
#
COLOR CYELLOW 1.0 1.0 0.0 0.5
COLOR CVIOLETT    1.0 0.0 1.0 1.0
COLOR CTURKIS 0.0 1.0 1.0 1.0
#
COLOR CYELLOW50   0.5 0.5 0.0 0.5
COLOR CVIOLETT50  0.5 0.0 0.5 1.0
COLOR CTURKIS50   0.0 0.5 0.5 1.0
#
COLOR CLINE   0.757   0.784   0.824   1.0
COLOR CMENUBLUE   0.157   0.259   0.365   1.0
COLOR CMENUBLUE50 0.157   0.259   0.365   0.5
#
NAME BOX MainBox
    FRECT   0   0   200 700 VOID
COLORREF BOXCOLOR CGREY10 0
COLORREF FRAMECOLOR CGREY80 0
CHILD AllPlanetsBox   30  20  VOID
CHILD SizeBox 30  310 VOID
CHILD RotationBox 30  380 VOID
CHILD AnaglyphBox 30  450 VOID
CHILD LanguageBox 30  520 VOID
CHILD AppInfoButton   50  610 VOID
CHILD QuitButton  50  650 VOID
#
#
NAME BOX AllPlanetsBox
    FRECT   0   0   140 280 VOID
COLORREF FRAMECOLOR CGREEN50    0
CHILD DiePlanetenString   5   10  VOID
CHILD MerkurButton    20  35  VOID
CHILD VenusButton 20  65  VOID
CHILD EarthButton 20  95  VOID
CHILD MarsButton  20  125 VOID
CHILD JupiterButton   20  155 VOID
CHILD SaturnButton    20  185 VOID
CHILD UranusButton    20  215 VOID
CHILD NeptunButton    20  245 VOID
#
NAME BOX LanguageBox
    FRECT   0   0   140 60  VOID
COLORREF FRAMECOLOR CGREEN50    0
CHILD LanguageString  5   10  VOID
CHILD GermanButton    10  35  VOID
CHILD EnglishButton   75  35  VOID
#
NAME BOX SizeBox
    FRECT   0   0   140 60  VOID
COLORREF FRAMECOLOR CGREEN50    0
CHILD SizeString  5   10  VOID
CHILD NormalButton    10  35  VOID
CHILD LargeButton 75  35  VOID
#
NAME BOX RotationBox
    FRECT   0   0   140 60  VOID
COLORREF FRAMECOLOR CGREEN50    0
CHILD Rotation2Str    5   10  VOID
CHILD RotateOnButton  10  35  VOID
CHILD RotateOffButton 75  35  VOID
#
NAME BUTTON MerkurButton
    GROUP   0
REF PlanetBox
CHILD MerkurName  0   0   CENTER_CENTER
#
NAME BUTTON VenusButton
    GROUP   0
REF PlanetBox
CHILD VenusName   0   0   CENTER_CENTER
#
NAME BUTTON EarthButton
    GROUP   0
REF PlanetBox
CHILD EarthName   0   0   CENTER_CENTER
#
NAME BUTTON MarsButton
    GROUP   0
REF PlanetBox
CHILD MarsName    0   0   CENTER_CENTER
#
NAME BUTTON JupiterButton
    GROUP   0
REF PlanetBox
CHILD JupiterName 0   0   CENTER_CENTER
#
NAME BUTTON SaturnButton
    GROUP   0
REF PlanetBox
CHILD SaturnName  0   0   CENTER_CENTER
#
NAME BUTTON UranusButton
    GROUP   0
REF PlanetBox
CHILD UranusName  0   0   CENTER_CENTER
#
NAME BUTTON NeptunButton
    GROUP   0
REF PlanetBox
CHILD NeptunName  0   0   CENTER_CENTER
#
NAME BUTTON NormalButton
    GROUP   1
REF SmallBox
CHILD SmallerName 0   0   CENTER_CENTER
#
NAME BUTTON LargeButton
    GROUP   1
REF SmallBox
CHILD LargerName  0   0   CENTER_CENTER
#
NAME BUTTON GermanButton
    GROUP   2
REF SmallBox
CHILD GermanName  0   0   CENTER_CENTER
#
NAME BUTTON EnglishButton
    GROUP   2
REF SmallBox
CHILD EnglishName 0   0   CENTER_CENTER
#
NAME BUTTON RotateOnButton
    GROUP   0
REF SmallBox
CHILD OnStr   0   0   CENTER_CENTER
#
NAME BUTTON RotateOffButton
    GROUP   0
REF SmallBox
CHILD OffStr  0   0   CENTER_CENTER
#
NAME BOX SmallBox
    FRECT   0   0   55  14  VOID
COLORREF BOXCOLOR CGREY30 0
COLORREF FRAMECOLOR CGREY60 0
COLORREF BOXCOLOR CGREY40 1
COLORREF FRAMECOLOR CGREY60 1
COLORREF BOXCOLOR CGREY40 2
COLORREF FRAMECOLOR CGREY60 2
#
NAME BOX PlanetBox
    FRECT   0   0   100 20  VOID
COLORREF BOXCOLOR CGREY30 0
COLORREF FRAMECOLOR CGREY60 0
COLORREF BOXCOLOR CGREY40 1
COLORREF FRAMECOLOR CGREY60 1
COLORREF BOXCOLOR CGREY40 2
COLORREF FRAMECOLOR CGREY60 2
#
NAME BOX Infobox
    FRECT   0   0   280 180 VOID
COLORREF BOXCOLOR CGREY10 0
COLORREF FRAMECOLOR CGREY60 0
CHILD LeftInfoBox 0   0   LEFT_CENTER
CHILD MerkurInfoBox   0   0   RIGHT_CENTER
STATUS INACTIVE
CHILD VenusInfoBox    0   0   RIGHT_CENTER
STATUS INACTIVE
CHILD EarthInfoBox    0   0   RIGHT_CENTER
STATUS INACTIVE
CHILD MarsInfoBox 0   0   RIGHT_CENTER
STATUS INACTIVE
CHILD JupiterInfoBox  0   0   RIGHT_CENTER
STATUS INACTIVE
CHILD SaturnInfoBox   0   0   RIGHT_CENTER
STATUS INACTIVE
CHILD UranusInfoBox   0   0   RIGHT_CENTER
STATUS INACTIVE
CHILD NeptunInfoBox   0   0   RIGHT_CENTER
STATUS INACTIVE
#
# Anaglyph Box
#
NAME BOX AnaglyphBox
    FRECT   0   0   140 60  VOID
COLORREF FRAMECOLOR CGREEN50    0
CHILD AnaglyphStr 5   10  VOID
CHILD AnaglyphOnBt    10  35  VOID
CHILD AnaglyphOffBt   75  35  VOID
#
NAME BUTTON AnaglyphOnBt
    GROUP   0
REF SmallBox
CHILD OnStr   0   0   CENTER_CENTER
#
NAME BUTTON AnaglyphOffBt
    GROUP   0
REF SmallBox
CHILD OffStr  0   0   CENTER_CENTER
#
#
NAME BOX LeftInfoBox
    FRECT   0   0   140 180 VOID
CHILD MondeStr    -5  20  RIGHT_TOP
CHILD DurchmesserStr  -5  40  RIGHT_TOP
CHILD UmlaufzeitStr   -5  60  RIGHT_TOP
CHILD FluchtStr   -5  80  RIGHT_TOP
CHILD MasseStr    -5  100 RIGHT_TOP
CHILD FallStr -5  120 RIGHT_TOP
CHILD RotationStr -5  140 RIGHT_TOP
CHILD MondName
STATUS INACTIVE
#
NAME BUTTON QuitButton
REF PlanetBox
CHILD QuitStr 0   0   CENTER_CENTER
#
NAME BUTTON AppInfoButton
REF PlanetBox
CHILD AppInfoStr  0   0   CENTER_CENTER
BTPROP NOACTIVE
#
#
$ INCLUDE    AppInfoBox.r3d
    $INCLUDE    MerkurInfoBox.r3d
    $INCLUDE    VenusInfoBox.r3d
    $INCLUDE    ErdeInfoBox.r3d
    $INCLUDE    MarsInfoBox.r3d
    $INCLUDE    JupiterInfoBox.r3d
    $INCLUDE    SaturnInfoBox.r3d
    $INCLUDE    UranusInfoBox.r3d
    $INCLUDE    NeptunInfoBox.r3d
#
#-- ----------------------------------------------------------------
#
#  Strings
#
#-- ----------------------------------------------------------------
#
    NAME    STRING  MerkurName
    REF Verdana13
    TEXT    DE  Merkur
    TEXT    EN  Mercury
#
    NAME    STRING  VenusName
    REF Verdana13
    TEXT    DE  Venus
    TEXT    EN  Venus
#
    NAME    STRING  EarthName
    REF Verdana13
    TEXT    DE  Erde
    TEXT    EN  Earth
#
    NAME    STRING  MarsName
    REF Verdana13
    TEXT    DE  Mars
    TEXT    EN  Mars
#
    NAME    STRING  JupiterName
    REF Verdana13
    TEXT    DE  Jupiter
    TEXT    EN  Jupiter
#
    NAME    STRING  SaturnName
    REF Verdana13
    TEXT    DE  Saturn
    TEXT    EN  Saturn
#
    NAME    STRING  UranusName
    REF Verdana13
    TEXT    DE  Uranus
    TEXT    EN  Uranus
#
    NAME    STRING  NeptunName
    REF Verdana13
    TEXT    DE  Neptun
    TEXT    EN  Neptune
#
    NAME    STRING  SmallerName
    REF Verdana13
    TEXT    DE  Normal
    TEXT    EN  Normal
#
    NAME    STRING  LargerName
    REF Verdana13
    TEXT    DE  Groﬂ
    TEXT    EN  Large
#
    NAME    STRING  GermanName
    REF Verdana13
    TEXT    DE  Deutsch
    TEXT    EN  German
#
    NAME    STRING  EnglishName
    REF Verdana13
    TEXT    DE  Englisch
    TEXT    EN  English
#
    NAME    STRING  LanguageString
    REF Verdana13
    TEXT    DE  Sprache
    TEXT    EN  Language
#
#
    NAME    STRING  SizeString
    REF Verdana13
    TEXT    DE  Ansicht
    TEXT    EN  View
#
    NAME    STRING  DiePlanetenString
    REF Verdana13
    TEXT    DE  Die Planeten
    TEXT    EN  The Planets
#
    NAME    STRING  MondeStr
    REF Verdana13
    TEXT    DE  Monde
    TEXT    EN  Moons
#
    NAME    STRING  DurchmesserStr
    REF Verdana13
    TEXT    DE  Durchmesser
    TEXT    EN  Diameter
#
    NAME    STRING  UmlaufzeitStr
    REF Verdana13
    TEXT    DE  Umlaufzeit
    TEXT    EN  Period
#
    NAME    STRING  FluchtStr
    REF Verdana13
    TEXT    DE  Fluchtgeschwindigkeit
    TEXT    EN  Escape velocity
#
    NAME    STRING  MasseStr
    REF Verdana13
    TEXT    DE  Masse
    TEXT    EN  Mass
#
    NAME    STRING  FallStr
    REF Verdana13
    TEXT    DE  Fallbeschleunigung
    TEXT    EN  Gravity acceleration
#
    NAME    STRING  RotationStr
    REF Verdana13
    TEXT    DE  Rotationsperiode
    TEXT    EN  Rotation peroid
#
    NAME    STRING  hoch2str
    REF Verdana12
    TEXT    DE  2
    TEXT    EN  2
#
    NAME    STRING  hoch20str
    REF Verdana12
    TEXT    DE  20
    TEXT    EN  20
#
    NAME    STRING  hoch21str
    REF Verdana12
    TEXT    DE  21
    TEXT    EN  21
#
    NAME    STRING  hoch22str
    REF Verdana12
    TEXT    DE  22
    TEXT    EN  22
#
    NAME    STRING  hoch23str
    REF Verdana12
    TEXT    DE  23
    TEXT    EN  23
#
    NAME    STRING  hoch24str
    REF Verdana12
    TEXT    DE  24
    TEXT    EN  24
#
    NAME    STRING  hoch25str
    REF Verdana12
    TEXT    DE  25
    TEXT    EN  25
#
    NAME    STRING  hoch26str
    REF Verdana12
    TEXT    DE  26
    TEXT    EN  26
#
    NAME    STRING  hoch27str
    REF Verdana12
    TEXT    DE  27
    TEXT    EN  27
#
    NAME    STRING  Rotation2Str
    REF Verdana13
    TEXT    DE  Rotation
    TEXT    EN  Rotation
#
    NAME    STRING  OnStr
    REF Verdana13
    TEXT    DE  An
    TEXT    EN  On
#
    NAME    STRING  QuitStr
    REF Verdana13
    TEXT    DE  Beenden
    TEXT    EN  Quit
#
    NAME    STRING  OffStr
    REF Verdana13
    TEXT    DE  Aus
    TEXT    EN  Off
#
    NAME    STRING  AppInfoStr
    REF Verdana13
    TEXT    DE  ‹ber..
    TEXT    EN  About..
#
    NAME    STRING  MondName
    REF Verdana12
    COLORREF    STRCOLOR    CYELLOW
    TEXT    DE  MondName
    TEXT    EN  MondName
#
    NAME    STRING  OkStr
    REF Verdana13
    TEXT    DE  OK
    TEXT    EN  OK
#
    NAME    STRING  AnaglyphStr
    REF Verdana13
    TEXT    DE  Anaglyph (Rot/Cyan)
    TEXT    EN  Anaglyph (red/cyan)
#
#-- ----------------------------------------------------------------
#
#  Fonts
#
#-- ----------------------------------------------------------------
#
    NAME    FONT    Verdana13
    FILES   Fonts   Verdana8
#
    NAME    FONT    Verdana12
    FILES   Fonts   Verdana7
    #
