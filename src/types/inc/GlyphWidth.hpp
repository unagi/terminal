/*++
Copyright (c) Microsoft Corporation

Module Name:
- GlyphWidth.hpp

Abstract:
- Helpers for determining the width of a particular string of chars.

*/
#pragma once

#include <cstddef>
#include <string_view>

bool IsGlyphFullWidth(const std::wstring_view& glyph) noexcept;
bool IsGlyphFullWidth(const wchar_t wch) noexcept;

// Returns the total number of display columns occupied by text.
size_t MeasureDisplayWidth(const std::wstring_view& text) noexcept;

// Returns the display width for the suffix of length `suffixLength`.
// If suffixLength exceeds the text length, this returns suffixLength.
size_t MeasureDisplayWidthForSuffix(const std::wstring_view& text, const size_t suffixLength) noexcept;

// Returns the number of DEL/backspace operations needed to erase the full commandline.
size_t BackspaceCountForCommandline(const std::wstring_view& commandline) noexcept;

// Returns the number of DEL/backspace operations needed to erase a replacement suffix.
size_t BackspaceCountForCommandline(const std::wstring_view& commandline, const size_t replacementLength) noexcept;
