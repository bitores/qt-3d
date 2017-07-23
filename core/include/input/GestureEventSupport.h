#ifndef _GESTURE_EVENT_SUPPORT_H_
#define _GESTURE_EVENT_SUPPORT_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"

//#include "IGestureEventListener.h"
//#include "GestureEvent.h"

class GestureEventSupport 
{
//	private List<IGestureEventListener> gestureListeners;
	
	/** The gestureEvtSenders to listener. */
//	private Map<Class<? extends IInputProcessor>, IGestureEventListener[]> gestureSenderToGestureListener;
    typedef std::multimap<String, IGestureEventListener*> GestureToListenerMap;
    GestureToListenerMap gestureSenderToGestureListener;

	/** The Constant EMPTY. */
//	static const IGestureEventListener[] EMPTY = {};
	
public:	
	GestureEventSupport() {
		
//		this.gestureListeners = new ArrayList<IGestureEventListener>();
	}


//	/**
//	 * Constructs a <code>PropertyChangeSupport</code> object.
//	 * 
//	 * @param sourceBean  The bean to be given as the source for any events.
//	 */
//    public GestureEventSupport(Object sourceBean) {
//        if (sourceBean == null) {
//            throw new NullPointerException();
//        }
//        source = sourceBean;
//    }
    
    /**
     * Add a gestureEvtSenderChangeListener to the listener map.
     * If <code>listener</code> is null, no exception is thrown and no action
     * is taken.
     * 
     * @param gestureEvtSender the gestureEvtSender
     * @param listener  The gestureEvtSenderChangeListener to be added
     */
    void addGestureEvtListener(String gestureEvtSender, IGestureEventListener *listener) {
//        if (listener == 0) {
        if (listener == 0 || gestureEvtSender == "") {
            return;
        }
        
//        this.lazyInitializeMap();
        
//        IGestureEventListener[] array = this.gestureSenderToGestureListener.get(gestureEvtSender);
//        
//        //Add listener to array 
//        int size = (array != null) ? array.length  : 0;
//        IGestureEventListener[] clone = newArray(size + 1);
//        clone[size] = listener;
//        if (array != null) {
//            System.arraycopy(array, 0, clone, 0, size);
//        }
//        
//        //Put new listener array into map
//        this.gestureSenderToGestureListener.put(gestureEvtSender, clone);
        gestureSenderToGestureListener.insert(std::pair<String,IGestureEventListener*>(gestureEvtSender, listener));
    }
    
    
    /**
     * Creates a new array of listeners of the specified size.
     * 
     * @param length the length
     * 
     * @return the gestureEvtSender change listener[]
     */
//    protected IGestureEventListener[] newArray(int length) {
//        return (0 < length) ? new IGestureEventListener[length] : EMPTY;
//    }

    
    /**
     * Removes a IGestureEventListener to the listener map.
     * Throws no error if the listener isnt found.
     * 
     * @param gestureEvtSender the gestureEvtSender
     * @param listener the listener
     */
    void removeGestureEventListener(String gestureEvtSender, IGestureEventListener *listener) {
    	if (listener == 0 || gestureEvtSender == "") {
            return;
        }
    	
//    	 this.lazyInitializeMap();
//    	 
//    	  if (this.gestureSenderToGestureListener != null) {
//              IGestureEventListener[] array = this.gestureSenderToGestureListener.get(gestureEvtSender);
//              if (array != null) {
//            	  
//                  for (int i = 0; i < array.length; i++) {
//                      if (listener.equals(array[i])) {
//                          int size = array.length - 1;
//                          if (size > 0) {
//                        	  IGestureEventListener[] clone = newArray(size);
//                              System.arraycopy(array, 0, clone, 0, i);
//                              System.arraycopy(array, i + 1, clone, i, size - i);
//                              this.gestureSenderToGestureListener.put(gestureEvtSender, clone);
//                          }
//                          else {
//                              this.gestureSenderToGestureListener.remove(gestureEvtSender);
//                              if (this.gestureSenderToGestureListener.isEmpty()) {
//                                  this.gestureSenderToGestureListener = null;
//                              }
//                          }
//                          break;
//                      }
//                  }
//              }
//          }
        for(GestureToListenerMap::iterator it = gestureSenderToGestureListener.begin();
            it != gestureSenderToGestureListener.end(); it ++) {
            if((it->first == gestureEvtSender) && (it->second == listener)) {
                gestureSenderToGestureListener.erase(it);
                break;
            }
        }
    }

    void removeAllGesturEventListeners(String gestureEvtSender) {
    	if (gestureEvtSender == "") {
            return;
        }
    	
        gestureSenderToGestureListener.erase(gestureEvtSender);
    }
    
    /**
     * Clear listeners.
     */
    void clearListeners(){
//    	if (this.gestureSenderToGestureListener == null){
//    		return;
//    	}
//    	
//    	 this.lazyInitializeMap();
//    	 
//    	 this.gestureSenderToGestureListener.clear();
        gestureSenderToGestureListener.clear();
    }
    
    /**
     * Fire an existing GestureEvent to any registered listeners.
     * 
     * @param evt  The GestureEvent object.
     */
    void fireGestureEvt(GestureEvent &evt);

    
    
    /**
     * Fires the events to the listeners.
     * 
     * @param listeners the listeners
     * @param event the event
     */
//    private void fire(IGestureEventListener[] listeners, MTGestureEvent event) {
//        if (listeners != null) {
//            for (IGestureEventListener listener : listeners) {
//                listener.processGestureEvent(event);
//            }
//        }
//    }
    
    
    /**
     * Returns all listeners in the map.
     * 
     * @return an array of all listeners
     */
//    public final synchronized IGestureEventListener[] getListeners() {
//        if (this.gestureSenderToGestureListener == null) {
//            return newArray(0);
//        }
//        List<IGestureEventListener> list = new ArrayList<IGestureEventListener>();

//        IGestureEventListener[] listeners = this.gestureSenderToGestureListener.get(null);
//        if (listeners != null) {
//            list.addAll(Arrays.asList(listeners));
//            //for (IGestureEventListener listener : listeners) {
//             //   list.add(listener);
//            //}
//        }
//        
//        for (Entry<Class<? extends IInputProcessor>, IGestureEventListener[]> entry : this.gestureSenderToGestureListener.entrySet()) {
//        	Class<? extends IInputProcessor> gestureEvtSender = entry.getKey();
//            if (gestureEvtSender != null) {
//                list.addAll(Arrays.asList(entry.getValue()));
//                //for (IGestureEventListener listener : entry.getValue()) {
//                 //   list.add(listener);
//                //}
//            }
//        }
//        return list.toArray(newArray(list.size()));
//    }

    
    /**
     * Returns listeners that have been associated with the named gestureEvtSender.
     * 
     * @param gestureEvtSender  the name of the property
     * 
     * @return an array of listeners for the named property
     */
//    public final IGestureEventListener[] getListeners(Class<? extends IInputProcessor> gestureEvtSender) {
//        if (gestureEvtSender != null) {
//        	IGestureEventListener[] listeners =  this.gestureSenderToGestureListener.get(gestureEvtSender);
//            if (listeners != null) {
//                return listeners.clone();
//            }
//        }
//        return newArray(0);
//    }

    /**
     * Indicates whether the map contains
     * at least one listener to be notified.
     * 
     * @param gestureEvtSender the gestureEvtSender
     * 
     * @return      {@code true} if at least one listener exists or
     * {@code false} otherwise
     */
//    public final synchronized boolean hasListeners(Class<? extends IInputProcessor> gestureEvtSender) {
//        if (this.gestureSenderToGestureListener == null) {
//            return false;
//        }
//        IGestureEventListener[] array = this.gestureSenderToGestureListener.get(null);
//        return (array != null) || ((gestureEvtSender != null) && (null != this.gestureSenderToGestureListener.get(gestureEvtSender)));
//    }
    
    
    /**
     * Checks if the map is null and then lazily initializes it.
     */
//    private void lazyInitializeMap(){
//    	if (gestureSenderToGestureListener == null){
//    		 gestureSenderToGestureListener = new HashMap<Class<? extends IInputProcessor>, IGestureEventListener[]>();
//    	}
//    }

};

#endif /* _GESTURE_EVENT_SUPPORT_H_ */
