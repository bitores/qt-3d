#ifndef __eScorePanel_h__
#define __eScorePanel_h__

#include "particle/BillboardSet.h"

class eScoreNote : public BillboardSet
{
private:
	void scoreNote(int score);

public:
	eScoreNote(Root* root, int score, int width, int span /*unsigned int poolSize = 2*/);
};

class eScorePanel : public BillboardSet
{
private:
	typedef HashMap<char, int> ScoreMap;
	ScoreMap mScoreMap;

	int mScore;
	GameObject* mParent;

	void updateUIRight();
	void updateUILeft();
public:
	void setScore(int score);
	int getScore();
	void addScore(int score = 1);
	void subScore(int score = -1);
	eScorePanel(Root* root, unsigned int poolSize = 20);
	void buildMap(int width, int height, int span);

	void resize(float width, float height, int span);

	void setParent(GameObject* parent);
	GameObject* getParent();
	void setPosition(float x, float y, float z);
};
#endif
