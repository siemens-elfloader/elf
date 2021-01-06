// 
//   Copyright (C) 2007, 2008, 2009, 2010 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include "smart_ptr.h"
#include "DynamicShape.h"
#include "FillStyle.h"
#include "Renderer.h"
#include "DisplayObject.h"

#include <vector>

namespace gnash {

DynamicShape::DynamicShape()
	:
	_currpath(0),
	_currfill(0),
	_currline(0),
	_x(0),
	_y(0),
	_changed(false)
{}

void
DynamicShape::clear()
{
	_shape.clear();
	_currpath = 0; 
	_currfill = _currline = 0; 
	// TODO: worth setting _changed=true ? 
}

void
DynamicShape::display(Renderer& renderer, const DisplayObject& inst) const
{
    renderer.drawShape(_shape, inst.get_world_cxform(), inst.getWorldMatrix());
}

void
DynamicShape::add_path(const Path& pth)
{
	_shape.addPath(pth);
	_currpath = &_shape.currentPath();
}

void
DynamicShape::endFill()
{
	// Close the path
	if ( _currpath && _currfill )
	{
		// TODO: should not just close the last path
		//       but rather append the point where
		//       the fill actually begun (could be
		//       in a previous path).
		//
		// NOTE that doing so will require changing 
		// the hitTest code to do stop considering
		// each path in isolation when doing PIP testing
		//

		_currpath->close();

		// reset _x and _y to reflect closing point
		_x = _currpath->ap.x;
		_y = _currpath->ap.y;
	}

	// Remove reference to the "current" path, as
	// next drawing will happen on a different one
	_currpath = 0;
	// Remove fill information
	_currfill = 0;
}

void
DynamicShape::beginFill(const FillStyle& f)
{
	// End previous fill
	endFill();

	_currfill = addFillStyle(f);

	// TODO: how to know wheter the fill should be set
	//       as *left* or *right* fill ?
	//       A quick test shows that *left* always work fine !
	Path newPath(_x, _y, _currfill, 0, _currline, true); 
	add_path(newPath);
}

void
DynamicShape::startNewPath(bool newShape)
{
	// Close any pending filled path
	if ( _currpath && _currfill)
	{
		// TODO: this is probably bogus
		_currpath->close();
	}

	// The DrawingApiTest.swf file shows we should not
	// end the current fill when starting a new path.

	// A quick test shows that *left* always work fine !
	// More than that, using a *right* fill seems to break the tests !
	Path newPath(_x, _y, _currfill, 0, _currline, newShape);
	add_path(newPath);
}

void
DynamicShape::finalize() const
{
	// Nothing to do if not changed
	if ( ! _changed ) return;

	// Close any pending filled path (_currpath should be last path)
	if ( _currpath && _currfill)
	{
		assert(!_shape.paths().empty());
		assert(_currpath == &(_shape.paths().back()));
		_currpath->close();
	}

	// TODO: check consistency of fills and such !

	_changed = false;
}

void
DynamicShape::lineStyle(boost::uint16_t thickness, const rgba& color,
	bool vScale, bool hScale, bool pixelHinting, bool noClose,
	CapStyle startCapStyle, CapStyle endCapStyle,
	JoinStyle joinStyle, float miterLimitFactor)
{
	LineStyle style(thickness, color, vScale, hScale, pixelHinting,
		noClose, startCapStyle, endCapStyle, joinStyle,
		miterLimitFactor);

	_currline = add_line_style(style);
	startNewPath(false); 
}

void
DynamicShape::resetLineStyle()
{
	_currline = 0;
	startNewPath(false);
}

void
DynamicShape::moveTo(boost::int32_t x, boost::int32_t y)
{
    // It was manually tested that a moveTo, even
    // when moving to the same point of current cursor,
    // will start a new path.

    _x = x;
    _y = y;
    startNewPath(false);
}

void
DynamicShape::lineTo(boost::int32_t x, boost::int32_t y, int swfVersion)
{
	if (!_currpath) startNewPath(true); 
	assert(_currpath);

	_currpath->drawLineTo(x, y);

	// Update bounds 
    SWFRect bounds = _shape.getBounds();

	unsigned thickness = _currline ? 
        _shape.lineStyles().back().getThickness() : 0;

	if (_currpath->size() == 1) {
		_currpath->expandBounds(bounds, thickness, swfVersion);
	} else {
		bounds.expand_to_circle(x, y, swfVersion < 8 ? thickness :
                thickness / 2.0);
	}
    
    _shape.setBounds(bounds);

	// Update current pen position
	_x = x;
	_y = y;

	// Mark as changed
	_changed = true;
}

void
DynamicShape::curveTo(boost::int32_t cx, boost::int32_t cy, 
                      boost::int32_t ax, boost::int32_t ay, int swfVersion)
{
	if (!_currpath) startNewPath(true); 
	assert(_currpath);

	_currpath->drawCurveTo(cx, cy, ax, ay);

    SWFRect bounds = _shape.getBounds();

	unsigned thickness = _currline ? 
        _shape.lineStyles().back().getThickness() : 0;

	if (_currpath->size() == 1) {
		_currpath->expandBounds(bounds, thickness, swfVersion);
	}
    else {
		bounds.expand_to_circle(ax, ay, 
                swfVersion < 8 ? thickness : thickness / 2.0);
		bounds.expand_to_circle(cx, cy,
                swfVersion < 8 ? thickness : thickness / 2.0);
    }

    _shape.setBounds(bounds);

	// Update current pen position
	_x = ax;
	_y = ay;

	// Mark as changed
	_changed = true;
}

size_t
DynamicShape::addFillStyle(const FillStyle& stl)
{
    _shape.addFillStyle(stl);
    return _shape.fillStyles().size();
}

size_t
DynamicShape::add_line_style(const LineStyle& stl)
{
    _shape.addLineStyle(stl);
    return _shape.lineStyles().size();
}
	
}	// end namespace gnash


// Local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
