/*
 * Copyright 2003, Heikki Suhonen
 * Copyright 2009, Karsten Heimrich
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 * 		Heikki Suhonen <heikki.suhonen@gmail.com>
 *		Karsten Heimrich <host.haiku@gmx.de>
 *
 */
#ifndef AIR_BRUSH_TOOL_H
#define AIR_BRUSH_TOOL_H

#include "DrawingTool.h"


class BRadioButton;
class ControlSliderBox;


class AirBrushTool : public DrawingTool {
public:
								AirBrushTool();
	virtual						~AirBrushTool();

			int32				UseToolWithScript(ToolScript*, BBitmap*);
			ToolScript*			UseTool(ImageView*, uint32, BPoint, BPoint);


			BView*				makeConfigView();
			const void*			ReturnToolCursor();
			const char*			ReturnHelpString(bool isInUse);

private:
			int32*				sqrt_table;
};


class AirBrushToolConfigView : public DrawingToolConfigView {
public:
								AirBrushToolConfigView(BRect rect,
									DrawingTool* drawingTool);

	virtual	void				AttachedToWindow();

private:
			ControlSliderBox*	fSizeSlider;
			ControlSliderBox*	fFlowSlider;
			BRadioButton*		fAirbrush;
			BRadioButton*		fSprayMode;
};

#endif
