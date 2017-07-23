#ifndef _FontManager_H__
#define _FontManager_H__

#include "OverlayPrerequisites.h"
#include "asset/ResourceManager.h"
#include "Font.h"

//namespace Ogre
//{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Resources
	*  @{
	*/
	/** Manages Font resources, parsing .fontdef files and generally organising them.*/
    class FontManager : public ResourceManager
    {
    public:

		FontManager(Root* root);
		~FontManager();

		/// Create a new font
		/// @see ResourceManager::createResource
		FontPtr create (const String& name, const String& group,
							bool isManual = false, ManualResourceLoader* loader = 0,
							const NameValuePairList* createParams = 0);

		/// Get a resource by name
		/// @see ResourceManager::getResourceByName
		FontPtr getByName(const String& name, const String& groupName/* = ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME*/);


        /** @copydoc ScriptLoader::parseScript */
        void parseScript(DataStreamPtr& stream, const String& groupName);
        /** Override standard Singleton retrieval.
        @remarks
        Why do we do this? Well, it's because the Singleton
        implementation is in a .h file, which means it gets compiled
        into anybody who includes it. This is needed for the
        Singleton template to work, but we actually only want it
        compiled into the implementation of the class based on the
        Singleton, not all of them. If we don't change this, we get
        link errors when trying to use the Singleton-based class from
        an outside dll.
        @par
        This method just delegates to the template version anyway,
        but the implementation stays in this single compilation unit,
        preventing link errors.
        */
        static FontManager& getSingleton(void);
        /** Override standard Singleton retrieval.
        @remarks
        Why do we do this? Well, it's because the Singleton
        implementation is in a .h file, which means it gets compiled
        into anybody who includes it. This is needed for the
        Singleton template to work, but we actually only want it
        compiled into the implementation of the class based on the
        Singleton, not all of them. If we don't change this, we get
        link errors when trying to use the Singleton-based class from
        an outside dll.
        @par
        This method just delegates to the template version anyway,
        but the implementation stays in this single compilation unit,
        preventing link errors.
        */
        static FontManager* getSingletonPtr(void);

    protected:

        /// Internal methods
		Resource* createImpl(const String& name, ResourceHandle handle, 
			const String& group, bool isManual, ManualResourceLoader* loader, 
            const NameValuePairList* params);
		void parseAttribute(const String& line, FontPtr& pFont);

        void logBadAttrib(const String& line, FontPtr& pFont);

    };
	/** @} */
	/** @} */
//}

#endif
