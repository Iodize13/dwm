/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=11", "JoyPixels:pixelsize=11:antialias=true:autohint=true"};
static const char dmenufont[]       = "JetBrains Mono:size=11";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444"; static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
// static char selbordercolor[]        = "#005577";
static char selbordercolor[]        = "#FF0000";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                                  instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "obs",                                  NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Lutris",                               NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "zenity",     	                  NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "DBeaver",     	                  NULL,     NULL,           1 << 1,    0,          0,           0,        -1 },
	{ "Brave-browser",	                  NULL,     NULL,           1 << 2,    0,          0,           0,        -1 },
	{ "Zathura",     	                  NULL,     NULL,           1 << 3,    0,          0,           0,        -1 },
	{ "discord",                              NULL,     NULL,           1 << 4,    0,          0,           0,        -1 },
	{ "messenger-nativefier",                 NULL,     NULL,           1 << 5,    0,          0,           0,        -1 },
	{ NULL,                                   NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
// #define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont};
static const char *termcmd[]  = { "wezterm", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ Mod4Mask|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ Mod4Mask,                       XK_l,      focusstack,     {.i = -1 } },
	{ Mod4Mask,                       XK_h,      focusstack,     {.i = +1 } },
	{ Mod4Mask|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ Mod4Mask,                       XK_g,      togglebar,      {0} },
	{ Mod1Mask,                       XK_Return, zoom,           {0} },
	{ Mod4Mask,                       XK_k,      incnmaster,     {.i = -1 } },
	{ Mod4Mask,                       XK_j,      incnmaster,     {.i = +1 } },
	{ Mod4Mask,		          XK_q,      killclient,     {0} },
	{ Mod4Mask,                       XK_w,      setlayout,      {.v = &layouts[0]} },
	{ Mod4Mask,                       XK_e,      setlayout,      {.v = &layouts[1]} },
	{ Mod4Mask,                       XK_u,      setlayout,      {.v = &layouts[2]} },
	{ Mod4Mask|ShiftMask,             XK_f,      togglefloating, {0} },
	// { Mod4Mask,                       XK_t,      setlayout,      {0} },
	{ Mod4Mask,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ Mod4Mask|ShiftMask,		  XK_Return, spawn,          {.v = termcmd } },
	{ Mod4Mask,                       XK_Tab,    view,           {0} },
	{ Mod1Mask,                       XK_0,      view,           {.ui = ~0 } },
	{ Mod1Mask|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ Mod4Mask,                       XK_comma,  focusmon,       {.i = -1 } },
	{ Mod4Mask,                       XK_period, focusmon,       {.i = +1 } },
	{ Mod4Mask|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ Mod4Mask|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ Mod4Mask,                       XK_F5,     xrdb,           {.v = NULL } },
	TAGKEYS(                        XK_n,                      0)
	TAGKEYS(                        XK_a,                      1)
	TAGKEYS(                        XK_r,                      2)
	TAGKEYS(                        XK_u,                      3)
	TAGKEYS(                        XK_i,                      4)
	TAGKEYS(                        XK_m,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_Thai_lakkhangyao,       0)
	TAGKEYS(                        XK_slash,                  1)
	TAGKEYS(                        XK_minus,                  2)
	TAGKEYS(                        XK_Thai_phosamphao,        3)
	TAGKEYS(                        XK_Thai_thothung,          4)
	TAGKEYS(                        XK_Thai_sarau,             5)
	TAGKEYS(                        XK_Thai_saraue,            6)
	TAGKEYS(                        XK_Thai_khokhwai,          7)
	TAGKEYS(                        XK_Thai_totao,             8)
	{ MODKEY|ShiftMask,		XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

