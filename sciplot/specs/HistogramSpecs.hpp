// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018-2021 Allan Leal
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

// sciplot includes
#include <sciplot/specs/Specs.hpp>
#include <sciplot/util.hpp>

namespace sciplot {

/// The class used to specify histogram style options.
class HistogramSpecs : virtual public Specs<HistogramSpecs>
{
  public:
    /// Construct a default HistogramSpecs instance.
    HistogramSpecs();

    /// Set the histogram style to be clustered.
    auto clustered() -> HistogramSpecs&;

    /// Set the histogram style to be clustered with a given gap size.
    auto clusteredWithGap(double value) -> HistogramSpecs&;

    /// Set the histogram style to be stacked with groups formed using data along rows.
    auto rowStacked() -> HistogramSpecs&;

    /// Set the histogram style to be stacked with groups formed using data along columns.
    auto columnStacked() -> HistogramSpecs&;

    /// Set the histogram style to be with error bars.
    auto errorBars() -> HistogramSpecs&;

    /// Set the histogram style to be with error bars and also set its gap size.
    auto errorBarsWithGap(double value) -> HistogramSpecs&;

    /// Set the histogram style to be with error bars and also set its line width.
    auto errorBarsWithLineWidth(double value) -> HistogramSpecs&;

    /// Convert this HistogramSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The type of the histogram (clustered, errorbars, rowstacked, columnstacked).
    std::string m_type;

    /// The gap size (for clustered).
    std::string m_gap_clustered;

    /// The gap size (for errorbars).
    std::string m_gap_errorbars;

    /// The line width (applicable only to errorbars).
    std::string m_linewidth;
};

HistogramSpecs::HistogramSpecs()
{
}

auto HistogramSpecs::clustered() -> HistogramSpecs&
{
    m_type = "clustered";
    return *this;
}

auto HistogramSpecs::clusteredWithGap(double value) -> HistogramSpecs&
{
    m_type = "clustered";
    m_gap_clustered = "gap " + internal::str(value);
    return *this;
}

auto HistogramSpecs::rowStacked() -> HistogramSpecs&
{
    m_type = "rowstacked";
    return *this;
}

auto HistogramSpecs::columnStacked() -> HistogramSpecs&
{
    m_type = "columnstacked";
    return *this;
}

auto HistogramSpecs::errorBars() -> HistogramSpecs&
{
    m_type = "errorbars";
    return *this;
}

auto HistogramSpecs::errorBarsWithGap(double value) -> HistogramSpecs&
{
    m_type = "errorbars";
    m_gap_errorbars = "gap " + internal::str(value);
    return *this;
}

auto HistogramSpecs::errorBarsWithLineWidth(double value) -> HistogramSpecs&
{
    m_type = "errorbars";
    m_linewidth = "linewidth " + internal::str(value);
    return *this;
}

auto HistogramSpecs::repr() const -> std::string
{
    const auto supports_gap = (m_type == "clustered" || m_type == "errorbars");
    const auto supports_linewidth = (m_type == "errorbars");

    std::stringstream ss;
    ss << "set style histogram" << " ";
    ss << m_type << " ";
    if(m_type == "clustered") ss << m_gap_clustered << " ";
    if(m_type == "errorbars") ss << m_gap_errorbars << " ";
    if(m_type == "errorbars") ss << m_linewidth << " ";
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
