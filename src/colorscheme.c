#include "colorscheme.h"

ColorScheme GetTheme(ColorSchemeVariant variant)
{
    switch (variant) {
        case (COLORSCHEME_DARK_TERMINAL): {
            ColorScheme c;
            c.variant = COLORSCHEME_DARK_TERMINAL;
            c.background = BLACK;
            c.foreground = BEIGE;
            c.cursor = GRAY;
            c.border = BEIGE;
            c.statusLineBackGround = BEIGE;
            c.statusLineForeGround = BLACK;
            return c;
        } break;

        case (COLORSCHEME_LIGHT_BEIGE): {
            ColorScheme c;
            c.variant = COLORSCHEME_LIGHT_BEIGE;
            c.background = BEIGE;
            c.foreground = BLACK;
            c.cursor = GRAY;
            c.border = BLACK;
            c.statusLineBackGround = BLACK;
            c.statusLineForeGround = BEIGE;
            return c;
        } break;

        case (COLORSCHEME_DARK_GRUVBOX): {
            ColorScheme c;
            c.variant = COLORSCHEME_DARK_GRUVBOX;
            c.background = CLITERAL(Color){29, 32, 33, 255};
            c.foreground = CLITERAL(Color){235, 219, 178, 255};
            c.border = CLITERAL(Color){235, 219, 178, 255};
            c.cursor = CLITERAL(Color){214, 93, 14, 255};
            c.statusLineBackGround = CLITERAL(Color){80, 73, 69, 255};
            c.statusLineForeGround = CLITERAL(Color){235, 219, 178, 255};
            return c;
        } break;
    }
}
