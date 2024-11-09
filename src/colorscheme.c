#include "colorscheme.h"

ColorScheme GetTheme(ColorSchemeVariant variant)
{
    switch (variant) {
    case (COLORSCHEME_DARK_TERMINAL): {
        ColorScheme c;
        c.variant = COLORSCHEME_DARK_TERMINAL;
        c.background = BLACK;
        c.foreground = BEIGE;
        c.foregroundHighlight = BLACK;
        c.cursor = GRAY;
        c.border = BEIGE;
        c.statusLineBackGround = BEIGE;
        c.statusLineForeGround = BLACK;
        c.statusLineCursor = GRAY;
        return c;
    } break;

    case (COLORSCHEME_LIGHT_BEIGE): {
        ColorScheme c;
        c.variant = COLORSCHEME_LIGHT_BEIGE;
        c.background = BEIGE;
        c.foreground = BLACK;
        c.foregroundHighlight = BEIGE;
        c.cursor = GRAY;
        c.border = BLACK;
        c.statusLineBackGround = BLACK;
        c.statusLineForeGround = BEIGE;
        return c;
    } break;

    case (COLORSCHEME_DARK_GRUVBOX): {
        ColorScheme c;
        c.variant = COLORSCHEME_DARK_GRUVBOX;
        c.background = BEIGE;
        c.foreground = BLACK;
        c.foregroundHighlight = BEIGE;
        c.cursor = GRAY;
        c.border = BLACK;
        c.statusLineBackGround = BLACK;
        c.statusLineForeGround = BEIGE;
        return c;
    } break;
    }
}
