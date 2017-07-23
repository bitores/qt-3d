#ifndef _PICK_RESULT_H_
#define _PICK_RESULT_H_
#include "utils/include/prerequisites.h"
#include "preinput.h"
#include "utils/include/Vector3.h"

class PickEntry //implements Comparable<PickEntry>
{
public:
		int originalOrderIndex;
		Vector3 intersectionPoint;
		float cameraDistance;
//		MTComponent hitObj;
        GameObject* hitObj;
		
		
		PickEntry( GameObject* hitObject, Vector3 intersectionPoint2, float distance) {
			hitObj = hitObject;
			intersectionPoint = intersectionPoint2;
			cameraDistance = distance;
		}

#if 0
		//We give the later picked objects with the same distance priority 
		//(by substracting the hit tolerance from their distance)
		//We do this because they are probably drawn ontop because they are located later in the scene graph
		//Also, we priorize objects that are drawn with depth buffer disabled because they are also in front of others,
		//even if camera distance is farther
		int compareTo(PickEntry o2) {
			if (o2.equals(this)){
				return 0;
			}
			if (this.originalOrderIndex >= o2.originalOrderIndex){ 
				if (this.cameraDistance - PickResult::HIT_TOLERANCE <= o2.cameraDistance || isDrawnWithoutDepthBuffer(this.hitObj)){
					return -1;
				}else{
					return 1;
				}
			}else{
				if (o2.cameraDistance - PickResult::HIT_TOLERANCE <= this.cameraDistance || isDrawnWithoutDepthBuffer(o2.hitObj)){
					return 1;
				}else{
					return -1;
				}
			}
		}
		
//		public boolean addedAfter(PickEntry other){
//			return this.originalOrderIndex >= other.originalOrderIndex;
//		}

		/**
		 * Checks if is drawn without depth buffer.
		 * Since this is inherited to children we have to check
		 * the parents.
		 * 
		 * @param comp the comp
		 * 
		 * @return true, if is drawn without depth buffer
		 */
		bool isDrawnWithoutDepthBuffer(GameObject *comp){
			if (comp.isDepthBufferDisabled())
				return true;
			
			GameObject* p = comp.getParent();
			while (p != 0){
				if (p.isDepthBufferDisabled())
					return true;
				p = p.getParent();
			}
			return false;
		}
#endif
};



class PickResult 
{
	std::list<PickEntry*> pickEntries;
	
	bool isAlreadySorted;
    
public:
	/** 
	 * Sometimes the wrong obj gets picked if they are on the same plane but with different inverted rays..
	 * probably math rounding off errors with floats etc. (at inverting the ray?) 
	 * <br>This makes sure, objs which are checked later for a hit, 
	 * (and are probably drawn ontop of the previous ones because drawn later), 
	 * are picked more likely.
	 * <br>Still this is kind of a hack
	 */
	 static const float HIT_TOLERANCE; // = 0.1f0.03f; //FIXME reset to old value!?
	
	/**
	 * Instantiates a new pick result.
	 */
	PickResult() {
//		pickList = new ArrayList<MTComponent>();
//		compToInterSectionPoint = new WeakHashMap<MTComponent, Vector3D[]>();
		
//		pickEntries = new ArrayList<PickEntry>();
		isAlreadySorted = false;
	}
    ~PickResult() {
        for(std::list<PickEntry*>::iterator it = pickEntries.begin(); it != pickEntries.end(); it ++) {
            if(*it) {
                delete *it;
            }
        }
    }


	/**
	 * This should only be called by the scene while this objects visits all scene nodes.
	 * 
	 * @param hitObject the hit object
	 * @param intersectionPoint the intersection point
	 * @param distance the distance
	 */
	void addPickedObject(GameObject *hitObject, Vector3 intersectionPoint, float distance){
		
		pickEntries.push_back(new PickEntry(hitObject, intersectionPoint, distance));
		int lastIndex = pickEntries.size()-1;
        pickEntries.back()->originalOrderIndex = lastIndex;
		isAlreadySorted = false;
	}


	/**
	 * Returns the picked component.
	 * This is the last in the list of picked components, not neccessarily the one with
	 * the shortest distance from the pickray (<code>setComposite</code> can interfere with that). But usually it should be
	 * the nearest one to the origin of the pick. :)
	 * 
	 * @return the nearest pick result
	 * 
	 * the picked component or null if nothing could be picked
	 */
	GameObject* getNearestPickResult(){
		if (isEmpty())
			return 0;
		else{
            sort();
            return pickEntries.front()->hitObj;
		}
		
		/*
		if (this.isEmpty())
			return null;
		else
			return pickList.get(pickList.size()-1);
		 */
	}
	


	PickEntry* getNearestPickEntry(){
		if (isEmpty())
			return 0;
		else{
            sort();
			return pickEntries.front();
		}
	}

#if 0

	/**
	 * Gets the pick list.
	 * 
	 * @return the pick list
	 */
	public List<PickEntry> getPickList() {
//		return pickList;
		sort();
		return pickEntries;
	}

//	public void addPickedObjects(ArrayList<MTBaseComponent> pickList) {
//		pickList.addAll(pickList);
//	}
	
/**
 * Returns the distance of the origin of the pick to the nearest picked obj.
 * 
 * @return the distance nearest pick obj
 */
	public float getDistanceNearestPickObj(){
//		if (this.isEmpty()){
//			return Float.MAX_VALUE;
//		}else{
//			return getDistanceOfPickedObj(this.getNearestPickResult());
//		}
		return getNearestPickEntry().cameraDistance;
	}
	
	/**
	 * Returns the distance of the origin of the pick to the specified picked obj.
	 * 
	 * @param pickedObj the picked obj
	 * 
	 * @return the distance of picked obj
	 */
	public float getDistanceOfPickedObj(MTComponent pickedObj){
//		return compToInterSectionPoint.get(pickedObj)[1].x;
		
		for (int i = 0; i < getPickList().size(); i++) {
			PickEntry p = pickEntries.get(i);
			if (p.hitObj.equals(pickedObj))
				return p.cameraDistance;
		}
		return Float.MAX_VALUE;
	}
	
	/**
	 * Returns the interseciton point of the specified picked obj.
	 * Returns null if the object isnt in the pick list!
	 * 
	 * @param pickedObj the picked obj
	 * 
	 * @return the inter section point of picked obj
	 */
	public Vector3D getInterSectionPointOfPickedObj(MTComponent pickedObj){
//		return compToInterSectionPoint.get(pickedObj)[0];
		
		for (int i = 0; i < getPickList().size(); i++) {
			PickEntry p = pickEntries.get(i);
			if (p.hitObj.equals(pickedObj)) 
				return p.intersectionPoint;
		}
		return null;
	}
	
	/**
	 * Gets the inter section point nearest picked obj.
	 * 
	 * @return the inter section point nearest picked obj
	 */
	public Vector3D getInterSectionPointNearestPickedObj(){
		if (this.isEmpty()){
			return null;
		}else{
			return getInterSectionPointOfPickedObj(this.getNearestPickResult());
		}
	}
#endif
	
	/**
	 * Checks if is empty.
	 * 
	 * @return true, if is empty
	 */
	bool isEmpty();

    void sort();
#if 0
	public void sort() {
		if (!isAlreadySorted){
			Collections.sort(pickEntries);
			isAlreadySorted = true;
//			printList();
		}
	}
	
	public void printList() {
		sort();
		System.out.println("Pick Entries:");
        for (PickEntry p : pickEntries) {
            System.out.println("Entry: " + p.hitObj + " Distance: " + p.cameraDistance + " Intersection: " + p.intersectionPoint);
        }
	}
#endif
};


#endif /* _PICK_RESULT_H_ */
