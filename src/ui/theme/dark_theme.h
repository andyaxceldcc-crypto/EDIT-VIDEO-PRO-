#ifndef DARK_THEME_H
#define DARK_THEME_H

#include <QString>

/**
 * @class DarkTheme
 * @brief Professional dark theme for VFX software
 */
class DarkTheme
{
public:
    static QString getStyleSheet();
    static QString getNodeGraphStyleSheet();
    static QString getViewerStyleSheet();

private:
    // Color palette
    static constexpr const char* COLOR_BG_DARK = "#1a1a1a";
    static constexpr const char* COLOR_BG_MEDIUM = "#252525";
    static constexpr const char* COLOR_BG_LIGHT = "#2d2d2d";
    static constexpr const char* COLOR_ACCENT = "#ff9d00";
    static constexpr const char* COLOR_TEXT = "#e0e0e0";
    static constexpr const char* COLOR_TEXT_DIM = "#a0a0a0";
};

#endif // DARK_THEME_H
