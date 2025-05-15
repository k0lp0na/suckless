/* Functions */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 20;       /* snap pixel */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int vertpad            = 4;       /* vertical padding of bar */
static const int sidepad            = 5;       /* horizontal padding of bar */
static const int horizpadbar        = 5;        /* horizontal padding for statusbar */
static const int vertpadbar         = 5;        /* vertical padding for statusbar */

#define ICONSIZE 20   /* icon size */
#define ICONSPACING 3 /* space between icon and title */

static const char *fonts[]          = {  "JetBrainsMono Nerd Font:antialias=true:autohint=true:size=11", "Noto Sans CJK JP:size=11"  };

/* Color Scheme */
static const char normal_bar_background[]                 = "#282828";
static const char selected_bar_background[]               = "#32303f";
static const char normal_bar_foreground[]                 = "#ebddd2";
static const char selected_bar_foreground[]               = "#ebddd2";
static const char normal_window_border[]                  = "#7c6f64";
static const char selected_window_border[]                = "#ebddd2";
static const char special_normal_window_border[]          = "#7c6f64";
static const char special_selected_window_border[]        = "#8ec07c";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
          [SchemeNorm] = { normal_bar_foreground, normal_bar_background, normal_window_border },
          [SchemeSel]  = { selected_bar_foreground, selected_bar_background, selected_window_border  },
   [SchemeScratchNorm] = { normal_bar_foreground, normal_bar_background, special_normal_window_border },
   [SchemeScratchSel]  = { selected_bar_foreground, selected_bar_background, special_selected_window_border },
};

/* AutoStart */
static const char *const autostart[] = {
	"nitrogen", "--restore", NULL,
        "dunst", NULL,
        "picom", NULL,
        "nm-applet", NULL,
        "xfce4-power-manager", NULL,
        "xsetroot", "-cursor_name", "left_ptr", NULL,
        "sh", "-c", "bar.sh", NULL,
        "sh", "-c", "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
        "sh", "-c", "greenclip daemon", NULL,
        "sxhkd", NULL,
        NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五" };

static const unsigned int ulinepad	= 1;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 1;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */


static const Rule rules[] = {
        /* xprop(1):
         *      WM_CLASS(STRING) = instance, class
         *      WM_NAME(STRING) = title
         */
   /* class      instance    title       tags mask     isfloating   monitor    scratch key */
   { "Anime",     NULL,       NULL,       0,            1,           -1,        0  },
   { "Spotify",   NULL,       NULL,       0,            1,           -1,       's' },
   { "Cmus",      NULL,       NULL,       0,            1,           -1,        0  },
   { NULL,        NULL,   "scratchpad",   0,            1,           -1,       'a' },
};

/* layout(s) */
static const float mfact     = 0.52; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " ",      tile },    /* first entry is default */
	{ " ",      monocle },
	{ " ",     dwindle },
	{ " ",      bstack },
	{ " ",      bstackhoriz },
	{ "󱗼 ",      grid },
	{ "󱇚 ",      horizgrid },
        { " ",      centeredmaster },
	{ " ",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "drun" , NULL };
static const char *termcmd[]  = { "alacritty", NULL };

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "scratchpad", NULL};

#include "movestack.c"
#include "unfloat.c"


static const Key keys[] = {
        /* modifier                     key        function        argument */
        { MODKEY,                    XK_space,     spawn,          {.v = dmenucmd } },
        { MODKEY,                   XK_Return,     spawn,          {.v = termcmd } },

        { MODKEY|Mod1Mask,              XK_b,      togglebar,      {0} },

        { MODKEY,                       XK_o,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_p,      focusstack,     {.i = -1 } },
        { MODKEY,                   XK_equal,      incnmaster,     {.i = +1 } },
        { MODKEY,                   XK_minus,      incnmaster,     {.i = -1 } },

        { MODKEY,             XK_bracketleft,      shiftview,      {.i = -1 } },
        { MODKEY,            XK_bracketright,      shiftview,      {.i = +1 } },
        { MODKEY,                     XK_Tab,      view,           {0} }, /* ws repeat*/

        { MODKEY,                       XK_j,      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_k,      setmfact,       {.f = +0.05} },

        { MODKEY|Mod1Mask,              XK_k,      setcfact,       {.f = -0.05} },
        { MODKEY|Mod1Mask,              XK_j,      setcfact,       {.f = +0.05} },
        { MODKEY,                       XK_l,      setcfact,       {.f = +0.00} },


        { MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
        { MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
        { MODKEY|Mod1Mask,          XK_equal,      incrgaps,       {.i = +1 } },
        { MODKEY|Mod1Mask,          XK_minus,      incrgaps,       {.i = -1 } },

        { MODKEY|ShiftMask,             XK_o,      movestack,      {.i = +1 } },
        { MODKEY|ShiftMask,             XK_p,      movestack,      {.i = -1 } },
        { MODKEY|ShiftMask,   XK_bracketleft,      shifttag,       {.i = -1 } },
        { MODKEY|ShiftMask,  XK_bracketright,      shifttag,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, /* Sticky window */
        { MODKEY|ShiftMask,        XK_Return,      zoom,           {0} },


        { MODKEY,                       XK_f,      togglefullscr,  {0} },
        { MODKEY,                       XK_s,      togglefloating, {0} },
        { MODKEY,                       XK_S,      unfloatvisible, {0} },

        { MODKEY,                       XK_w,      togglescratch,  {.v = scratchpadcmd } },
        { MODKEY,                       XK_q,      removescratch,  {.v = scratchpadcmd } },
        { MODKEY|Mod1Mask,         XK_Return,      setscratch,     {.v = scratchpadcmd } },


        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)

        { MODKEY|Mod1Mask,    XK_bracketleft,      cyclelayout,    {.i = -1 } },
        { MODKEY|Mod1Mask,   XK_bracketright,      cyclelayout,    {.i = +1 } },

        { MODKEY|Mod1Mask,              XK_1,      setlayout,      {.v = &layouts[0]} },
        { MODKEY|Mod1Mask,              XK_2,      setlayout,      {.v = &layouts[1]} },
        { MODKEY|Mod1Mask,              XK_3,      setlayout,      {.v = &layouts[2]} },
        { MODKEY|Mod1Mask,              XK_4,      setlayout,      {.v = &layouts[3]} },
        { MODKEY|Mod1Mask,              XK_5,      setlayout,      {.v = &layouts[4]} },
        { MODKEY|Mod1Mask,              XK_6,      setlayout,      {.v = &layouts[5]} },
        { MODKEY|Mod1Mask,              XK_7,      setlayout,      {.v = &layouts[6]} },
        { MODKEY|Mod1Mask,              XK_8,      setlayout,      {.v = &layouts[7]} },
        { MODKEY|Mod1Mask,              XK_9,      setlayout,      {.v = &layouts[8]} },

        { MODKEY,                       XK_q,      killclient,     {0} },
        { MODKEY|Mod1Mask,              XK_q,      quit,           {0} },
        { MODKEY|Mod1Mask,              XK_r,      quit,           {1} },
};
/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
        /* click                event mask      button          function        argument */
        { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
        { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
        { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
        { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
        { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
        { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
        { ClkClientWin,         MODKEY|Mod1Mask, Button3,       dragmfact,      {0} },
        { ClkClientWin,         MODKEY|Mod1Mask, Button3,       dragcfact,      {0} },
        { ClkTagBar,            0,              Button1,        view,           {0} },
        { ClkTagBar,            0,              Button3,        toggleview,     {0} },
        { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
        { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
