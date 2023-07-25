#pragma once
#define RA8875_RESET 21
#define RA8875_INT   20
#define RA8875_MOSI  19
#define RA8875_SCLK  18
#define RA8875_CS    17
#define RA8875_MISO  16
#define RA8875_DISPLAY Adafruit_800x480

#define GUI_MAX_LOOP_FREQ_HZ 5
#define GUI_MIN_TOUCH_INTERVAL_MILLISECONDS 500

#define GUI_TEXT_SCALE_NORMAL 0
#define GUI_TEXT_SCALE_L      1
#define GUI_TEXT_SCALE_XL     2
#define GUI_TEXT_SCALE_XXL    3

static const int cal_an = -325760;
static const int cal_bn = 8320;
static const int cal_cn = 13838080;
static const int cal_dn = -5568;
static const int cal_en = -209472;
static const int cal_fn = 28447104;
static const int cal_div = -370464;

#define USE_ADAFRUIT
