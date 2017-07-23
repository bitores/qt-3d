#ifndef _eScoreWidget_h__
#define _eScoreWidget_h__

#include "utils/include/prerequisites.h"
//#include "rendersystem/Shader.h"
#include "ui/eRect.h"

class eScorePanel;

/*
 * It is composed of ScoreBackground, eScorePanel, SoundButton, PauseButton
 */
class eScoreWidget
{
private:
	Root *mRoot;
	ShaderPtr mShader;
	GameObject *mScoreWidgetRoot;

	eButton* mSoundButton;
	eButton* mPauseButton;
	eButton* mSettingButton;
	std::vector<eButton*> mButtons;
	bool mSoundButtonActived;
	bool mPauseButtonActived;
	bool mSettingButtonActived;

	int mBackgroundId;
	int mPanelId;

	float mStatusBarHeight;
	float mBackgroundHeight;
	float mMarginLeft;
	float mMarginRight;
	float mCellWidth;
	float mCellHeight;
	float mCellPadding;

	eScorePanel* mScorePanel;

	eRect* mScoreBg;

	void createScoreBackground();
	void createScorePanel();
	void createButton();
public:

	eScoreWidget(Root* root, ShaderPtr shader, int bgId, int pnId);
	~eScoreWidget();
	void createScoreWidget();

	eButton* getSoundButton() {
		return mSoundButton;
	}

	eButton* getPauseButton() {
		return mPauseButton;
	}

	eButton* getSettingButton() {
		return mSettingButton;
	}

	eScorePanel* getScorePanel();
	void resize(float width, float height);

	bool OnTouchEvent(int action, float x, float y);
};

#endif
