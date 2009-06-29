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
#ifndef CONTROLS_H
#define CONTROLS_H


#include <Box.h>
#include <Slider.h>
#include <TextControl.h>


class NumberControl : public BTextControl {

public:
						NumberControl(const char* label, const char* text,
							BMessage* message, int32 maxBytes = 5,
							bool allowNegative = false, bool continuos = true);

						NumberControl(BRect frame, const char* name,
							const char* label, const char* text,
							BMessage* message, int32 maxBytes = 5,
							bool allowNegative = false, bool continuos = true);


			int32		Value() const;
	virtual	void		SetValue(int32);

	virtual	void		AttachedToWindow();

private:
			void		_InitControl(int32 maxBytes, bool allowNegative,
							bool continuos);
};


class ControlSlider : public BSlider {
public:
						ControlSlider(const char* name, const char* label,
							BMessage* message, int32 minValue, int32 maxValue,
							thumb_style thumbType);

						ControlSlider(BRect frame, const char* name,
							const char* label, BMessage* message, int32 rangeMin,
							int32 rangeMax, thumb_style knob);

	virtual	void		MouseDown(BPoint where);

private:
	static	int32		track_entry(void*);
			int32		track_mouse();

};


// this class groups a NumberControl and ControlSlider - objects under the
// same parent and takes care that whenever the others value is changed, the
// other will be also updated then this informs the target about the change
class ControlSliderBox : public BBox {
	BSlider			*slider;
	NumberControl 	*number_control;

	// this stores the model-message that is to be sent to the target
	BMessage 		*msg;
	bool			continuos_messages;

	BMessenger		*target;	// If this is NULL, the target will be the window.
	float			min_value;
	float 			max_value;
	// this posts the message to the target
	void			sendMessage(int32 value, bool final = true);

	float			divider;

	int32			CheckValue(int32);

public:
	// The message that is passed to this constructor must not be NULL. It must
	// also contain an int32 named "value". Whatever the value is will be used
	// as the initial value for controller.
					ControlSliderBox(const char* name, const char* label,
						 const char* text, BMessage* message, int32 rangeMin,
						 int32 rangeMax, border_style border = B_PLAIN_BORDER,
						 bool continuos = true, thumb_style knob = B_TRIANGLE_THUMB);

					ControlSliderBox(BRect frame, const char *name,
						 const char *label, const char *text,
						 BMessage *message, int32 rangeMin, int32 rangeMax,
						 border_style border = B_PLAIN_BORDER,
						 bool continuos=TRUE,thumb_style knob=B_TRIANGLE_THUMB);

					virtual		~ControlSliderBox();

	virtual	void	AllAttached();
	virtual	void	MessageReceived(BMessage *message);

	void	setValue(int32 value);

	// The caller of this function retains the ownership of the message.
	void	SetMessage(BMessage*);

	void	SetTarget(BMessenger *t) { target = t; }

	// These functions return and set the point where the number-control and
	// slider meet. They can be used to arrange many controls to have equal look.
	float	Divider();
	void	SetDivider(float, bool resize_text_field = false);
};


#endif
