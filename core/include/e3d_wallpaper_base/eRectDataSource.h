#ifndef _eRectDataSource_h__
#define _eRectDataSource_h__

#include "utils/include/prerequisites.h"
#include "ui/eRect.h"
#ifdef _DEBUG_
#include "base/LogManager.h"
#endif
typedef std::vector<MaterialPtr> MaterialVector;

class eRectDataSource : public eBaseAdapter, public eRect
{
public:
	Root* mRoot;
	MaterialVector mMaterials;
	eRectPtr mRect;
	eRectDataSource(ResourceManager* creator, const String& name, ResourceHandle handle, const String& group, bool isManual = false, ManualResourceLoader* loader = 0)
	: eRect(creator, name, handle, group, isManual, loader)
	{
		mRoot = creator->mRoot;
	}
//	eRectDataSource(Root* root, MaterialVector materials, Anchor anchor): eRect(root, anchor, 640, 800) {
//		mRoot = root;
//		mMaterials = materials;
//	}
	~eRectDataSource() {
#ifdef _DEBUG_
		LogManager::log(LOG_TAG, "eRectDataSource::~eRectDataSource: begin...");
#endif
//		delete mRect;
#ifdef _DEBUG_
		LogManager::log(LOG_TAG, "eRectDataSource::~eRectDataSource: mRect deleted");
#endif
//		mRect = 0;
		mRoot = 0;
#ifdef _DEBUG_
		LogManager::log(LOG_TAG, "eRectDataSource::~eRectDataSource: finish");
#endif
	}

	void setMaterials(MaterialVector materials)
	{
		mMaterials = materials;
	}

	bool isHit(float x, float y)
	{
//		if (eRectDataSource) {
			return /*mRect->*/hitTest(x, y);
//		}
//		return false;
	}

//	void resize(float width, float height)
//	{
//		if (mRect) {
//			mRect->resize(width, height);
//		}
//	}

	int getSize() {
		return mMaterials.size();
	}

	int getItem(int position) {
		return position;//mMaterials[position];
	}

	GameObject* getUI(int position) {
		SceneManager* sceneMgr = mRoot->getSceneManager();
		OString os; os<<"gallery-"<<position;
		GameObject* ui = sceneMgr->createGameObject(os.str());
		ComponentPtr mf = ComponentPtr(new MeshFilter(/*mRect*/this, false));
		MaterialPtr mat = mMaterials[position];
		RendererPtr renderer = RendererPtr(new Renderer(mat.getPointer()));//TODO liuzx MaterialPtr ?
		ui->addComponent(mf);
		ui->setRenderer(renderer);
		return ui;
	}
};

#endif
