#ifndef __TextureSplit_h__
#define __TextureSplit_h__

#include "utils/include/prerequisites.h"
#include "utils/include/Common.h"
#include "ui/eRect.h"

class TextureSplit
{
private:
    typedef vector< FloatRect> TextureCoordSets;
    TextureCoordSets mTextureCoords;

public:
//    eRect* createRect(Root* root, int texcoordIndex, float width, float height, float depth);
    /** setTextureStacksAndSlices() will generate texture coordinate rects as if the
        texture for the billboard set contained 'stacks' rows of 'slices'
        images each, all equal size. Thus, if the texture size is 512x512
        and 'stacks' is 4 and 'slices' is 8, each sub-rectangle of the texture
        would be 128 texels tall and 64 texels wide.
      @remarks
        This function is short-hand for creating a regular set and calling
        setTextureCoords() yourself. The numbering used for Billboard::setTexcoordIndex()
        counts first across, then down, so top-left is 0, the one to the right
        of that is 1, and the lower-right is stacks*slices-1.
      @see
        BillboardSet::setTextureCoords()
      */
    void setTextureStacksAndSlices( uchar stacks, uchar slices, bool flipy = false);

    FloatRect getTextureCoord(int texcoordIndex);

    TextureCoordSets getTextureCoords();
};
#endif
