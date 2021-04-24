#pragma once

static const char *CFG_FORMAT_DEFAULT = "$if(%isplaying%,\r\n"
"$if(%ispaused%,\r\n"
"paused\r\n"
",\r\n"
"playing\r\n"
"): %artist% - %title%,\r\n"
"stopped\r\n"
")";

static const char *CFG_SILENCE_DEFAULT = "not running";

// {DA9DCD74-54C3-43c4-BAC5-8B4370EB5165}
static const GUID cfg_fmt_guid = 
{ 0xda9dcd74, 0x54c3, 0x43c4, { 0xba, 0xc5, 0x8b, 0x43, 0x70, 0xeb, 0x51, 0x65 } };
static cfg_string cfg_fmt(cfg_fmt_guid, CFG_FORMAT_DEFAULT);

// {CBC3E777-9C0A-425a-8A9A-1888C3C8C9E6}
static const GUID cfg_path_guid = 
{ 0xcbc3e777, 0x9c0a, 0x425a, { 0x8a, 0x9a, 0x18, 0x88, 0xc3, 0xc8, 0xc9, 0xe6 } };
static cfg_string cfg_path(cfg_path_guid, "");

// {0BFCDDE8-EAB0-4da7-A04D-7B9157B236B4}
static const GUID cfg_silence_guid = 
{ 0xbfcdde8, 0xeab0, 0x4da7, { 0xa0, 0x4d, 0x7b, 0x91, 0x57, 0xb2, 0x36, 0xb4 } };
static cfg_string cfg_silence(cfg_silence_guid, CFG_SILENCE_DEFAULT);

enum
{
	ENC_UTF8,
	ENC_UTF8_HEADER,
	ENC_UNICODE,
	ENC_ANSI
};

// {8039889A-CEFB-4008-9900-67E850A88D82}
static const GUID cfg_encoding_guid = 
{ 0x8039889a, 0xcefb, 0x4008, { 0x99, 0x0, 0x67, 0xe8, 0x50, 0xa8, 0x8d, 0x82 } };
static cfg_uint cfg_encoding(cfg_encoding_guid, ENC_UTF8_HEADER);

// {33E4D4CE-7BAB-4010-9E81-C7FF087EE51A}
static const GUID cfg_logmode_guid = 
{ 0x33e4d4ce, 0x7bab, 0x4010, { 0x9e, 0x81, 0xc7, 0xff, 0x8, 0x7e, 0xe5, 0x1a } };
static cfg_uint cfg_logmode(cfg_logmode_guid, 0);

struct CFG_EVENTS_
{
	int on_new_track;
	int on_pause;
	int on_stop;
	int on_every_second;
	int use_delay;
	int delay_for_ms;
	int reserved3;
	int reserved4;
	int reserved5;
	int reserved6;
};
static const CFG_EVENTS_ cfg_events_default = {
	1, 1, 1, 0, 0,
	0, 0, 0, 0, 0,
};
// {A843B667-65A7-43b3-B954-2831298795D9}
static const GUID cfg_events_guid = 
{ 0xa843b667, 0x65a7, 0x43b3, { 0xb9, 0x54, 0x28, 0x31, 0x29, 0x87, 0x95, 0xd9 } };
static cfg_struct_t<CFG_EVENTS_> cfg_events(cfg_events_guid, cfg_events_default);
#define CFG_EVENTS cfg_events.get_value()

struct CFG_SAVE_TO_
{
	int to_file;
	int to_clipboard;
	int reserved1;
	int reserved2;
	int reserved3;
	int reserved4;
	int reserved5;
	int reserved6;
};

static const CFG_SAVE_TO_ cfg_save_to_default = {
	1, 0, 0, 0, 0, 0, 0, 0
};

// {2022701A-8B3D-4289-ABD8-78604CF93F00}
static const GUID cfg_save_to_guid = 
{ 0x2022701a, 0x8b3d, 0x4289, { 0xab, 0xd8, 0x78, 0x60, 0x4c, 0xf9, 0x3f, 0x0 } };
static cfg_struct_t<CFG_SAVE_TO_> cfg_save_to(cfg_save_to_guid, cfg_save_to_default);
#define CFG_SAVE_TO cfg_save_to.get_value()
