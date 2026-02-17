// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "precomp.h"
#include "inc/CodepointWidthDetector.hpp"
#include "inc/GlyphWidth.hpp"

// Function Description:
// - determines if the glyph represented by the string of characters should be
//      wide or not. See CodepointWidthDetector::IsWide
bool IsGlyphFullWidth(const std::wstring_view& glyph) noexcept
{
    GraphemeState state;
    CodepointWidthDetector::Singleton().GraphemeNext(state, glyph);
    return state.width == 2;
}

// Function Description:
// - determines if the glyph represented by the single character should be
//      wide or not. See CodepointWidthDetector::IsWide
bool IsGlyphFullWidth(const wchar_t wch) noexcept
{
    return wch < 0x80 ? false : IsGlyphFullWidth({ &wch, 1 });
}

size_t MeasureDisplayWidth(const std::wstring_view& text) noexcept
{
    size_t width = 0;
    auto& widthDetector = CodepointWidthDetector::Singleton();
    for (GraphemeState state{}; widthDetector.GraphemeNext(state, text);)
    {
        width += gsl::narrow_cast<size_t>(state.width);
    }
    return width;
}

size_t MeasureDisplayWidthForSuffix(const std::wstring_view& text, const size_t suffixLength) noexcept
{
    if (suffixLength > text.size())
    {
        return suffixLength;
    }

    return MeasureDisplayWidth(text.substr(text.size() - suffixLength));
}

size_t BackspaceCountForCommandline(const std::wstring_view& commandline) noexcept
{
    return MeasureDisplayWidth(commandline);
}

size_t BackspaceCountForCommandline(const std::wstring_view& commandline, const size_t replacementLength) noexcept
{
    return MeasureDisplayWidthForSuffix(commandline, replacementLength);
}
