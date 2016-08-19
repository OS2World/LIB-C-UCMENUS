/***************************************************************************/
/***************************************************************************/
/*                        DISCLAIMER OF WARRANTIES.                        */
/***************************************************************************/
/***************************************************************************/
/*                                                                         */
/*  Copyright (C) 1995 IBM Corporation                                     */
/*                                                                         */
/*      DISCLAIMER OF WARRANTIES.  The following [enclosed] code is        */
/*      sample code created by IBM Corporation. This sample code is not    */
/*      part of any standard or IBM product and is provided to you solely  */
/*      for  the purpose of assisting you in the development of your       */
/*      applications.  The code is provided "AS IS", without               */
/*      warranty of any kind.  IBM shall not be liable for any damages     */
/*      arising out of your use of the sample code, even if they have been */
/*      advised of the possibility of such damages.                        */
/***************************************************************************/

// UCMBASE_ID defined in UCMENUS.H

#define UCMENUID_DEFAULTBMP            (UCMBASE_ID+0)     // Bitmap resources
#define ID_SHREDDER              (UCMBASE_ID+1)
#define UCMENUID_SPACERBMP             (UCMBASE_ID+2)
#define IDD_UCMCTXT              (UCMBASE_ID+10)    // Menu resource
#define IDD_UCMSETTINGS          (UCMBASE_ID+11)    // Dialog resources
#define IDD_UCMNBP1              (UCMBASE_ID+12)
#define IDD_UCMNBP2              (UCMBASE_ID+13)
#define IDD_UCMNBP0              (UCMBASE_ID+14)
#define IDD_UCMNSTYLE            (UCMBASE_ID+15)
#define IDD_UCMGETBMPNAME        (UCMBASE_ID+16)
#define IDD_RESBMP               (UCMBASE_ID+17)
#define IDD_UCMDLG               (UCMBASE_ID+18)
#define NLS_POSITION             (UCMBASE_ID+30)    // Strings
#define NLS_GENERAL              (UCMBASE_ID+31)
#define NLS_ACTION               (UCMBASE_ID+32)
#define NLS_ADDITEM              (UCMBASE_ID+33)
#define NLS_ITEMCREATION         (UCMBASE_ID+34)
#define NLS_DESCEXEC             (UCMBASE_ID+35)
#define NLS_UCMHLP               (UCMBASE_ID+36)
#define NLS_ITEMADDERROR         (UCMBASE_ID+37)
#define NLS_ERROR                (UCMBASE_ID+38)
#define NLS_NOICESTART           (UCMBASE_ID+39)
#define NLS_NOBMPFN              (UCMBASE_ID+40)
#define NLS_BADBMPFN             (UCMBASE_ID+41)
#define NLS_LOADBMP              (UCMBASE_ID+42)
#define NLS_OVERWRITE            (UCMBASE_ID+43)
#define NLS_OVERWRITETITLE       (UCMBASE_ID+44)
#define NLS_NOBMPRES             (UCMBASE_ID+45)
#define NLS_BMPLOADING           (UCMBASE_ID+46)
#define NLS_BMPLOADED            (UCMBASE_ID+47)
#define NLS_ITEMDESCR            (UCMBASE_ID+48)

#define UCMBASE_LASTID           (UCMBASE_ID+60)

//-----------------------------------------------------------------------------
#define IDC_UCMNB                    3106           // 0x00EA
#define IDB_UCMNBP1UNDO              3108           // 0x00EC
#define IDB_UCMNBP1Help              3109           // 0x00ED
#define IDC_UCMNBP1BITMAP            3110           // 0x00EE
#define IDB_UCMNBP1LOAD              3111           // 0x00EF
#define IDC_UCMNBP1FILENAME          3112           // 0x00F0
#define IDC_UCMNBP1TITLE             3113           // 0x00F1
#define IDB_UCMNBP2UNDO              3115           // 0x00F3
#define IDB_UCMNBP2HELP              3116           // 0x00F4
#define IDC_UCMNBP2FLIST             3117           // 0x00F5
#define IDC_UCMNBP2PARAMS            3118           // 0x00F6
#define IDB_UCMNBP0UNDO              3120           // 0x00F8
#define IDB_UCMNBP0HELP              3121           // 0x00F9
#define IDC_UCMNBP0STATIC            3122           // 0x00FA
#define IDC_UCMNBP0END               3123           // 0x00FB
#define IDC_UCMNBP0AFTER             3124           // 0x00FC
#define IDC_UCMNBP0BEFORE            3125           // 0x00FD
#define IDB_UCMNBP0OK                3127           // 0X00FF
#define IDB_UCMNBP1OK                3128           // 0X0100
#define IDB_UCMNBP2OK                3129           // 0X0101
#define IDB_UCMNBP0CANCEL            3130           // 0X0102
#define IDB_UCMNBP1CANCEL            3131           // 0X0103
#define IDB_UCMNBP2CANCEL            3132           // 0X0104
#define IDB_UCMNBP1HELP              3133           // 0X0106
#define IDC_UCMNSTLFORCESIZE         3135           // 0x0108
#define IDC_UCMNSTLCX                3136           // 0x010B
#define IDC_UCMNSTLCY                3137           // 0x010C
#define IDB_UCMNSTLHELP              3138           // 0x010D
#define IDB_UCMNSTLOK                3139           // 0x010E
#define IDB_UCMNSTLCANCEL            3140           // 0x010F
#define IDC_UCMNSTLCXLABEL           3141           // 0x0110
#define IDC_UCMNSTLCYLABEL           3142           // 0x0111
#define IDC_UCMNSTLTEXT              3143           // 0x0112
#define IDC_UCMNSTLFRAMED            3144           // 0x0113
#define IDC_UCMNSTLIGNORE            3145           // 0x0114
#define IDC_UCMNSTLOR                3146           // 0x0115
#define IDC_UCMNSTLAND               3147           // 0x0116
#define IDC_UCMNSTLBOX               3148           // 0x0117

#define IDC_UCMNSTLBUBBLE            3181
#define IDC_UCMNSTLDELAY             3182
#define IDC_UCMNSTLREAD              3183
#define IDC_UCMNSTLDELAYLABEL        3184
#define IDC_UCMNSTLREADLABEL         3185
#define IDC_UCMNSTLMSECLABEL         3186

#define IDB_UCMNBP1CREATE            3149           // 0x0118
#define IDB_UCMNBP1EDIT              3150           // 0x0119
#define IDC_UCMBMPNAME               3152           // 0x011B
#define IDB_UCMBMPOK                 3153           // 0x011C
#define IDB_UCMBMPCANCEL             3154           // 0x011D
#define IDC_UCMBMPCX                 3155           // 0x011E
#define IDC_UCMBMPCY                 3156           // 0x011F
#define IDC_UCMNBP2DESC              3157           // 0x0120
#define IDC_UCMNBP2DLIST             3158           // 0x0121
#define IDC_UCMNBP0REGULAR           3159           // 0x0122
#define IDC_UCMNBP0SPACER            3160           // 0x0123
#define IDC_RESBMPTEXT               3162           // 0x0125
#define IDB_RESBMPCANCEL             3163           // 0x0126
#define IDB_UCMNBP1PREDEFINED        3164           // 0x0127
#define IDD_UCMDLG_OK                3166           // 0x0129
#define IDD_UCMDLG_CANCEL            3167           // 0x012A
#define IDD_UCMDLG_HELP              3168           // 0x012B
#define IDD_UCMDLG_TEXT              3169           // 0x012C
#define IDD_UCMDLG_BUFFETDESC        3170           // 0x012D
#define IDD_UCMDLG_CURRENTDESC       3171           // 0x012E
#define IDD_UCMDLG_BUFFET            3172           // 0x012F
#define IDD_UCMDLG_CURRENT           3173           // 0x0130
#define IDD_UCMDLG_DEFAULT           3174           // 0x0131
#define IDD_UCMDLG_SHREDDER          3175           // 0x0132
#define IDD_UCMDLG_ACTIONS           3176           // 0x0133
#define IDD_UCMDLG_DESCR             3177           // 0x0134
#define IDC_UCMNBP2LOADING           3179           // 0x0136
#define IDB_UCMNBP1NOBMP             3180           // 0x0137
// Help table IDs
// --
// #define IDH_UCM_TABLE                0x200
// #define IDH_SUBTABLE_STYLE           0x210
// #define IDH_SUBTABLE_SETTINGS        0x220
// #define IDH_SUBTABLE_NB_CREATE       0x221
// #define IDH_SUBTABLE_NB_BITMAP       0x222
// #define IDH_SUBTABLE_NB_ACTION       0x223
// #define IDH_SUBTABLE_HIDE            0x240

// String table IDs
// -- 


// IPF file panel IDs
// --
#define PANEL_STYLE           3230           // 10
#define PANEL_SETTINGS        3231           // 20
#define PANEL_ITEMPOS         3232           // 21
#define PANEL_ITEMBMP         3233           // 22
#define PANEL_ITEMACTION      3234           // 23
#define PANEL_DM              3235           // 30
#define PANEL_CM              3236           // 40
#define PANEL_CM_EDIT         3237           // 41
#define PANEL_CM_CREATE       3238           // 42
#define PANEL_CM_DELETE       3239           // 43
#define PANEL_CM_STYLE        3240           // 44
#define PANEL_CM_DEFAULT      3241           // 45
#define PANEL_CM_LOAD         3242           // 46
#define PANEL_CM_SAVEAS       3243           // 47
#define PANEL_BUFFET          3244           // 50

