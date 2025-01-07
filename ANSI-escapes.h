// List of basic Console Virtual Terminal Sequences
// For more info: https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
#pragma once

#ifndef ANSI_ESCAPES_H
#define ANSI_ESCAPES_H
// ----------------------------------------------------------------------------
//  Operating System Command (OSC) sequences
// ----------------------------------------------------------------------------
#define WIN_TITLE(x) "\x1B]2;" x "\x07" // Set window title to string x

// ----------------------------------------------------------------------------
//  Control Sequence Introducer (CSI) sequences
// ----------------------------------------------------------------------------
#define RST_CUR     "\x1B[1;1H" // Reset cursor position to upper left
#define HDE_CUR     "\x1B[?25l" // Hide cursor
#define SHW_CUR     "\x1B[?25h" // Show cursor
#define CLR_DISP_A  "\x1B[0J"   // Erase in Display (after cursor)
#define CLR_DISP_B  "\x1B[1J"   // Erase in Display (before cursor)
#define CLR_DISP    "\x1B[2J"   // Erase in Display (entire)
#define CLR_LINE_A  "\x1B[0K"   // Erase in Line (after cursor)
#define CLR_LINE_B  "\x1B[1K"   // Erase in Line (before cursor)
#define CLR_LINE    "\x1B[2K"   // Erase in Line (entire)

// ----------------------------------------------------------------------------
//  Select Graphic Rendition (SGR) sequences
// ----------------------------------------------------------------------------
#define RESET "\x1B[0m"  // Reset all SRG parameters

#define BOLD  "\x1B[1m"  // Bold text
#define UND   "\x1B[4m"  // Underline text

// Text colour
//  BLK - Black   BLU - Blue
//  RED - Red     MAG - Magenta
//  GRN - Green   CYN - Cyan
//  YEL - Yellow  WHT - White
//  H-prefix - High intensity variant (brighter)
#define BLK "\x1B[30m"
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define HBLK "\x1B[90m"
#define HRED "\x1B[91m"
#define HGRN "\x1B[92m"
#define HYEL "\x1B[93m"
#define HBLU "\x1B[94m"
#define HMAG "\x1B[95m"
#define HCYN "\x1B[96m"
#define HWHT "\x1B[97m"


// Background colour (_B-suffix)
//  BLK - Black   BLU - Blue
//  RED - Red     MAG - Magenta
//  GRN - Green   CYN - Cyan
//  YEL - Yellow  WHT - White
//  H-prefix - High intensity variant (brighter)
#define BLK_B "\x1B[40m"
#define RED_B "\x1B[41m"
#define GRN_B "\x1B[42m"
#define YEL_B "\x1B[43m"
#define BLU_B "\x1B[44m"
#define MAG_B "\x1B[45m"
#define CYN_B "\x1B[46m"
#define WHT_B "\x1B[47m"
#define HBLK_B "\x1B[100m"
#define HRED_B "\x1B[101m"
#define HGRN_B "\x1B[102m"
#define HYEL_B "\x1B[103m"
#define HBLU_B "\x1B[104m"
#define HMAG_B "\x1B[105m"
#define HCYN_B "\x1B[106m"
#define HWHT_B "\x1B[107m"

// 24-bit true colour
#define COL_RGB(r, g, b)    "\x1B[38;2;"#r";"#g";"#b"m" // Select RGB foreground color
#define COL_B_RGB(r, g, b)  "\x1B[48;2;"#r";"#g";"#b"m" // Select RGB background color

#endif
