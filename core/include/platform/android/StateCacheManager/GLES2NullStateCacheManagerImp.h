#ifndef __GLES2NullStateCacheManagerImp_H__
#define __GLES2NullStateCacheManagerImp_H__

#include "platform/android/GLES2Prerequisites.h"
#include "platform/android/GLES2StateCacheManager.h"

//typedef Ogre::GeneralAllocatedObject StateCacheAlloc;

/** An in memory cache of the OpenGL ES state.
 @see GLES2StateCacheManager
 */
class GLES2StateCacheManagerImp/* : public StateCacheAlloc*/
{
private:

	GLES2StateCacheManager* mStateCacheManager;

	/// Stores the current clear colour
	vector<GLclampf> mClearColour;
	/// Stores the current colour write mask
	vector<GLboolean> mColourMask;
	/// Stores the current depth write mask
	GLboolean mDepthMask;
	/// Stores the current polygon rendering mode
	GLenum mPolygonMode;
	/// Stores the current blend equation
	GLenum mBlendEquation;
	/// Stores the current face culling setting
	GLenum mCullFace;
	/// Stores the current depth test function
	GLenum mDepthFunc;
	/// Stores the current stencil mask
	GLuint mStencilMask;
	/// Stores the currently active texture unit
	unsigned char mActiveTextureUnit;
	/// Mask of buffers who contents can be discarded if GL_EXT_discard_framebuffer is supported
	unsigned int mDiscardBuffers;
	/// Stores the current depth clearing colour
	GLclampf mClearDepth;

public:
	GLES2StateCacheManagerImp(GLES2StateCacheManager* StateCacheManager);
	~GLES2StateCacheManagerImp(void);

	/// See GLES2StateCacheManager.initializeCache.
	void initializeCache();

	/// See GLES2StateCacheManager.clearCache.
	void clearCache();

	/// See GLES2StateCacheManager.bindGLBuffer.
	void bindGLBuffer(GLenum target, GLuint buffer, bool force = false);

	/// See GLES2StateCacheManager.deleteGLBuffer.
	void deleteGLBuffer(GLenum target, GLuint buffer, bool force = false);

	/// See GLES2StateCacheManager.bindGLTexture.
	void bindGLTexture(GLenum target, GLuint texture);

	/// See GLES2StateCacheManager.invalidateStateForTexture.
	void invalidateStateForTexture(GLuint texture);

	/// See GLES2StateCacheManager.setTexParameteri.
	void setTexParameteri(GLenum target, GLenum pname, GLint param);

	/// See GLES2StateCacheManager.setTexParameterf.
	void setTexParameterf(GLenum target, GLenum pname, GLfloat params);

	/// See GLES2StateCacheManager.getTexParameterfv.
	void getTexParameterfv(GLenum target, GLenum pname, GLfloat *params);

	/// See GLES2StateCacheManager.activateGLTextureUnit.
	bool activateGLTextureUnit(unsigned char unit);

	/// See GLES2StateCacheManager.getBlendEquation.
	GLenum getBlendEquation(void) const { return mBlendEquation; }

	/// See GLES2StateCacheManager.setBlendEquation.
	void setBlendEquation(GLenum eq);

	/// See GLES2StateCacheManager.setBlendFunc.
	void setBlendFunc(GLenum source, GLenum dest);

	/// See GLES2StateCacheManager.getDepthMask.
	GLboolean getDepthMask(void) const { return mDepthMask; }

	/// See GLES2StateCacheManager.setDepthMask.
	void setDepthMask(GLboolean mask);

	/// See GLES2StateCacheManager.getDepthFunc.
	GLenum getDepthFunc(void) const { return mDepthFunc; }

	/// See GLES2StateCacheManager.setDepthFunc.
	void setDepthFunc(GLenum func);

	/// See GLES2StateCacheManager.getClearDepth.
	GLclampf getClearDepth(void) const { return mClearDepth; }

	/// See GLES2StateCacheManager.setClearDepth.
	void setClearDepth(GLclampf depth);

	/// See GLES2StateCacheManager.setClearColour.
	void setClearColour(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

	/// See GLES2StateCacheManager.getColourMask.
	vector<GLboolean> & getColourMask(void) { return mColourMask; }

	/// See GLES2StateCacheManager.setColourMask.
	void setColourMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

	/// See GLES2StateCacheManager.getStencilMask.
	GLuint getStencilMask(void) const { return mStencilMask; }

	/// See GLES2StateCacheManager.setStencilMask.
	void setStencilMask(GLuint mask);

	/// See GLES2StateCacheManager.setEnabled.
	void setEnabled(GLenum flag);

	/// See GLES2StateCacheManager.setDisabled.
	void setDisabled(GLenum flag);

	/// See GLES2StateCacheManager.setVertexAttribEnabled.
	void setVertexAttribEnabled(GLuint attrib);

	/// See GLES2StateCacheManager.setVertexAttribDisabled.
	void setVertexAttribDisabled(GLuint attrib);

	/// See GLES2StateCacheManager.getDiscardBuffers.
	unsigned int getDiscardBuffers(void) const { return mDiscardBuffers; }

	/// See GLES2StateCacheManager.setDiscardBuffers.
	void setDiscardBuffers(unsigned int flags) { mDiscardBuffers = flags; }

	/// See GLES2StateCacheManager.getPolygonMode.
	GLenum getPolygonMode(void) const { return mPolygonMode; }

	/// See GLES2StateCacheManager.setPolygonMode.
	void setPolygonMode(GLenum mode) { mPolygonMode = mode; }

	/// See GLES2StateCacheManager.getCullFace.
	GLenum getCullFace(void) const { return mCullFace; }

	/// See GLES2StateCacheManager.setCullFace.
	void setCullFace(GLenum face);
};

#endif