#ifndef __GLES2Support_H__
#define __GLES2Support_H__

#include "GLES2Prerequisites.h"
//#include "rendersystem/RenderWindow.h"
//#include "ConfigOptionMap.h"

class GLES2RenderSystem;
class GLES2StateCacheManager;

class GLES2Support
{
	public:
		GLES2Support() : mStateCacheMgr(0)  { }
		virtual ~GLES2Support() { }

//		/**
//		* Add any special config values to the system.
//		* Must have a "Full Screen" value that is a bool and a "Video Mode" value
//		* that is a string in the form of wxh
//		*/
//		virtual void addConfig() = 0;
//		virtual void setConfigOption(const String &name, const String &value);
//
//	   /**
//		* Make sure all the extra options are valid
//		* @return string with error message
//		*/
//		virtual String validateConfig() = 0;
//		virtual ConfigOptionMap& getConfigOptions(void);
//		virtual RenderWindow* createWindow(bool autoCreateWindow,
//										   GLES2RenderSystem *renderSystem,
//										   const String& windowTitle) = 0;
//
//		/// @copydoc RenderSystem::_createRenderWindow
//		virtual RenderWindow* newWindow(const String &name,
//										unsigned int width, unsigned int height,
//										bool fullScreen,
//										const NameValuePairList *miscParams = 0) = 0;

		/**
		* Get vendor information
		*/
		const String& getGLVendor(void) const
		{
			return mVendor;
		}

		/**
		* Get version information
		*/
		const String& getGLVersion(void) const
		{
			return mVersion;
		}

//		/**
//		* Get shader cache path
//		*/
//		const String& getShaderCachePath(void) const
//		{
//			return mShaderCachePath;
//		}
//
//		/**
//		* Get shader library path
//		*/
//		const String& getShaderLibraryPath(void) const
//		{
//			return mShaderLibraryPath;
//		}
//
//		/**
//		* Set shader cache path
//		*/
//		void setShaderCachePath(String path)
//		{
//			mShaderCachePath = path;
//		}
//
//		/**
//		* Set shader library path
//		*/
//		void setShaderLibraryPath(String path)
//		{
//			mShaderLibraryPath = path;
//		}

//		/**
//		* Get the address of a function
//		*/
//		virtual void *getProcAddress(const String& procname) = 0;

		/** Initialises GL extensions, must be done AFTER the GL context has been
		   established.
		*/
		virtual void initialiseExtensions();

		/**
		* Check if an extension is available
		*/
		virtual bool checkExtension(const String& ext) const;

//		/// @copydoc RenderSystem::getDisplayMonitorCount
//		virtual unsigned int getDisplayMonitorCount() const
//		{
//			return 1;
//		}

		/**
		* Get the state cache manager
		*/
		GLES2StateCacheManager* getStateCacheManager() const
		{
			return mStateCacheMgr;
		}

		/**
		* Set a valid state cache manager
		*/
		void setStateCacheManager(GLES2StateCacheManager* stateCacheMgr)
		{
			mStateCacheMgr = stateCacheMgr;
		}

//		/**
//		* Start anything special
//		*/
//		virtual void start() = 0;
//		/**
//		* Stop anything special
//		*/
//		virtual void stop() = 0;

	private:
		String mVersion;
		String mVendor;
		String mShaderCachePath;
		String mShaderLibraryPath;

	protected:
		// Stored options
//		ConfigOptionMap mOptions;

		// This contains the complete list of supported extensions
		set<String> extensionList;

		// State cache management
		GLES2StateCacheManager* mStateCacheMgr;
};
#endif
