#ifndef _eScoreWidget2_cpp__
#define _eScoreWidget2_cpp__

#include "eScoreWidget2.h"
#include "utils/include/prerequisites.h"
#include "scenes.h"

/*
 * This score widget is written by Yijin Wang
 * An sample usage can be refer to prject: FlappingBirdWallpaper
 */
template <int DIGIT_NUM>
class eScoreWidget2
{
private:
	Easy3dJniData* mScene;
	Real mDigitWidth;
	Real mDigitHeight;
	Vector3 mPosition;
	int mNumberTexIds[10];

	int mScore;
	int _curTotalDigits;
	bool _initialized;

	struct Digit{
		eRect* digitRect;
		GameObject* digitGO;
	};
	Digit mDigits[DIGIT_NUM];

	void _updateDigitLayout();
	void _init(	Easy3dJniData* scene,
					int texIdOfNumber0,
					int texIdOfNumber1,
					int texIdOfNumber2,
					int texIdOfNumber3,
					int texIdOfNumber4,
					int texIdOfNumber5,
					int texIdOfNumber6,
					int texIdOfNumber7,
					int texIdOfNumber8,
					int texIdOfNumber9,
					Vector3 position = Vector3(0.0, 0.0, 0.0),
					Real digitWidth = 0.0,
					Real digitHeight = 0.0
					);

public:
	eScoreWidget2(	Easy3dJniData* scene = 0,
				int texIdOfNumber0 = 0,
				int texIdOfNumber1 = 0,
				int texIdOfNumber2 = 0,
				int texIdOfNumber3 = 0,
				int texIdOfNumber4 = 0,
				int texIdOfNumber5 = 0,
				int texIdOfNumber6 = 0,
				int texIdOfNumber7 = 0,
				int texIdOfNumber8 = 0,
				int texIdOfNumber9 = 0,
				Vector3 position = Vector3(0.0, 0.0, 0.0),
				Real digitWidth = 0.0,
				Real digitHeight = 0.0
				);
	~eScoreWidget2();


	void setPosition(Real x, Real y, Real z = 0.0);
	void setPosition(Vector3 pos);
	void setDigitSize(Real w, Real h);
	void setScore(int score);
};

template <int DIGIT_NUM>
eScoreWidget2<DIGIT_NUM>::eScoreWidget2(	Easy3dJniData* scene/* = 0*/,
									int texIdOfNumber0/* = 0*/,
									int texIdOfNumber1/* = 0*/,
									int texIdOfNumber2/* = 0*/,
									int texIdOfNumber3/* = 0*/,
									int texIdOfNumber4/* = 0*/,
									int texIdOfNumber5/* = 0*/,
									int texIdOfNumber6/* = 0*/,
									int texIdOfNumber7/* = 0*/,
									int texIdOfNumber8/* = 0*/,
									int texIdOfNumber9/* = 0*/,
									Vector3 position/* = Vector3(0.0, 0.0, 0.0)*/,
									Real digitWidth/* = 0.0*/,
									Real digitHeight/* = 0.0*/
									)
{
	_initialized = false;
	mScene = 0;
	_init(	scene,
			texIdOfNumber0,
			texIdOfNumber1,
			texIdOfNumber2,
			texIdOfNumber3,
			texIdOfNumber4,
			texIdOfNumber5,
			texIdOfNumber6,
			texIdOfNumber7,
			texIdOfNumber8,
			texIdOfNumber9,
			position,
			digitWidth,
			digitHeight
			);

}

template <int DIGIT_NUM>
eScoreWidget2<DIGIT_NUM>::~eScoreWidget2()
{
	mScene = 0;
}

template <int DIGIT_NUM>
void eScoreWidget2<DIGIT_NUM>::_init(	Easy3dJniData* scene,
									int texIdOfNumber0,
									int texIdOfNumber1,
									int texIdOfNumber2,
									int texIdOfNumber3,
									int texIdOfNumber4,
									int texIdOfNumber5,
									int texIdOfNumber6,
									int texIdOfNumber7,
									int texIdOfNumber8,
									int texIdOfNumber9,
									Vector3 position/* = Vector3(0.0, 0.0, 0.0)*/,
									Real digitWidth/* = 0.0*/,
									Real digitHeight/* = 0.0*/
									)
{
	if (scene == 0)
		return;

	mScene = scene;
	mNumberTexIds[0] = texIdOfNumber0;
	mNumberTexIds[1] = texIdOfNumber1;
	mNumberTexIds[2] = texIdOfNumber2;
	mNumberTexIds[3] = texIdOfNumber3;
	mNumberTexIds[4] = texIdOfNumber4;
	mNumberTexIds[5] = texIdOfNumber5;
	mNumberTexIds[6] = texIdOfNumber6;
	mNumberTexIds[7] = texIdOfNumber7;
	mNumberTexIds[8] = texIdOfNumber8;
	mNumberTexIds[9] = texIdOfNumber9;

	for (int i = 0; i < DIGIT_NUM; ++i)
	{
		mDigits[i].digitRect = new eRect(CENTER, 0, 0);
		mDigits[i].digitGO = mScene->createSceneGameobject(	mScene->mRoot->getSceneManager()->getSceneRoot(),
															String("digit_rect_") + StringConverter::toString(i),
															mDigits[i].digitRect,
															texIdOfNumber0
															);
	}

	mPosition = position;
	mDigitWidth = digitWidth;
	mDigitHeight = digitHeight;

	_curTotalDigits = 0;
	_initialized = true;
	setScore(0);
	_updateDigitLayout();
}

template <int DIGIT_NUM>
void eScoreWidget2<DIGIT_NUM>::setPosition(Real x, Real y, Real z/* = 0.0*/)
{
	Vector3 pos = Vector3(x, y, z);
	setPosition(pos);
}

template <int DIGIT_NUM>
void eScoreWidget2<DIGIT_NUM>::setPosition(Vector3 pos)
{
	mPosition = pos;
	_updateDigitLayout();
}

template <int DIGIT_NUM>
void eScoreWidget2<DIGIT_NUM>::setDigitSize(Real w, Real h)
{
	if (!_initialized)
		return;

	if (mDigitWidth != w || mDigitHeight != h)
	{
		mDigitWidth = w;
		mDigitHeight = h;
		for (int i = 0; i < DIGIT_NUM; ++i)
			mDigits[i].digitRect->resize(mDigitWidth, mDigitHeight);
		_updateDigitLayout();
	}
}

template <int DIGIT_NUM>
void eScoreWidget2<DIGIT_NUM>::setScore(int score)
{
	if (!_initialized)
		return;

	mScore = score % ((int)Math::Pow(10, DIGIT_NUM));

	int lefts = score / 10;
	int curDigit = score % 10;
	int preTotalDigits = _curTotalDigits;
	_curTotalDigits = 0;
	while (lefts || (!lefts && curDigit))
	{
		mDigits[_curTotalDigits].digitGO->useMaterial(mNumberTexIds[curDigit]);
		mDigits[_curTotalDigits].digitGO->setVisible(true);
		_curTotalDigits++;
		curDigit = lefts % 10;
		lefts /= 10;
	}

	for (int i = _curTotalDigits; i < DIGIT_NUM; ++i)
	{
		mDigits[i].digitGO->setVisible(false);
	}

	if (preTotalDigits != _curTotalDigits)
	{
		_updateDigitLayout();
	}
}

template <int DIGIT_NUM>
void eScoreWidget2<DIGIT_NUM>::_updateDigitLayout()
{
	if (!_initialized)
		return;

	Real posX = mPosition.x + _curTotalDigits * mDigitWidth / 2.0 - mDigitWidth / 2.0;
	for (int i = 0; i < _curTotalDigits; ++i)
	{

		mDigits[i].digitGO->getTransform()->setPosition(posX - i * mDigitWidth, mPosition.y, mPosition.z);
	}
}

#endif
