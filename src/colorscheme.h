#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <raylib.h>

typedef enum {
    COLORSCHEME_DARK_GRUVBOX,
    COLORSCHEME_DARK_TERMINAL,
    COLORSCHEME_LIGHT_BEIGE
} ColorSchemeVariant;

typedef struct {
    ColorSchemeVariant variant;

    Color background;
    Color foreground;
    Color foregroundHighlight;
    Color cursor;
    Color border;
    Color statusLineBackGround;
    Color statusLineForeGround;
    Color statusLineCursor;
} ColorScheme;

ColorScheme GetTheme(ColorSchemeVariant variant);

#endif // COLORSCHEME_H
