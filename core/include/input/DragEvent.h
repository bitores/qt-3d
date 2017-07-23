#ifndef _DRAG_EVENT_H_
#define _DRAG_EVENT_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "utils/include/Vector3.h"
#include "GestureEvent.h"

class DragEvent:public GestureEvent {
	
	/** The drag cursor. */
	InputCursor *dragCursor;
	
	/** The from. */
	Vector3 from;
	
	/** The to. */
	Vector3 to;
	
	/** The translation vect. */
	Vector3 translationVect;
	
public:	
    DragEvent():GestureEvent(0, 0, 0) {
        dragCursor = 0;
    }
	/**
	 * Instantiates a new drag event.
	 * 
	 * @param source the source
	 * @param id the id
	 * @param targetComponent the target component
	 * @param dragCursor the drag cursor
	 * @param from the from
	 * @param to the to
	 */
	DragEvent(IInputProcessor *source, int id, GameObject *targetComponent, InputCursor *_dragCursor, Vector3 _from, Vector3 _to)
	    :GestureEvent(source, id, targetComponent) {
		dragCursor = _dragCursor;
		from = _from;
		to = _to;
		translationVect = _to - _from;
	}

	/**
	 * Gets the drag cursor.
	 * 
	 * @return the drag cursor
	 */
	InputCursor *getDragCursor() {
		return dragCursor;
	}

	/**
	 * Gets the from.
	 * 
	 * @return the from
	 */
	Vector3 getFrom() {
		return from;
	}

	/**
	 * Gets the to.
	 * 
	 * @return the to
	 */
	Vector3 getTo() {
		return to;
	}

	/**
	 * Gets the translation vect.
	 * 
	 * @return the translation vect
	 */
	Vector3 getTranslationVect() {
		return translationVect;
	}
};

#endif /* _DRAG_EVENT_H_ */
