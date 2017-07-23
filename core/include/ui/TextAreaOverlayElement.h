#ifndef _TextAreaOverlayElement_H__
#define _TextAreaOverlayElement_H__

#include "ui/OverlayElement.h"
#include "asset/Font.h"

//namespace E3D {
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Overlays
	*  @{
	*/
	/** This class implements an overlay element which contains simple unformatted text.
    */
    class TextAreaOverlayElement : public OverlayElement
    {
    public:
        enum Alignment
        {
            Left,
            Right,
            Center
        };

    public:
        /** Constructor. */
        TextAreaOverlayElement(Root* root, const String& name);
        virtual ~TextAreaOverlayElement();

        virtual void initialise(void);
		virtual void setCaption(const DisplayString& text);

        void setCharHeight( Real height );
        Real getCharHeight() const;

        void setSpaceWidth( Real width );
        Real getSpaceWidth() const;

        void setFontName( const String& font );
        const String& getFontName() const;

        /** See OverlayElement. */
        virtual const String& getTypeName(void) const;
        /** See Renderable. */
		//const MaterialPtr& getMaterial(void) const;
        /** See Renderable. */
        void getRenderOperation(RenderOperationList& op);
        /** Overridden from OverlayElement */
        //void setMaterialName(const String& matName);

        /** Sets the colour of the text. 
        @remarks
            This method establishes a constant colour for 
            the entire text. Also see setColourBottom and 
            setColourTop which allow you to set a colour gradient.
        */
        void setColour(const ColourValue& col);

        /** Gets the colour of the text. */
        const ColourValue& getColour(void) const;
        /** Sets the colour of the bottom of the letters.
        @remarks
            By setting a separate top and bottom colour, you
            can create a text area which has a graduated colour
            effect to it.
        */
        void setColourBottom(const ColourValue& col);
        /** Gets the colour of the bottom of the letters. */
        const ColourValue& getColourBottom(void) const;
        /** Sets the colour of the top of the letters.
        @remarks
            By setting a separate top and bottom colour, you
            can create a text area which has a graduated colour
            effect to it.
        */
        void setColourTop(const ColourValue& col);
        /** Gets the colour of the top of the letters. */
        const ColourValue& getColourTop(void) const;

        inline void setAlignment( Alignment a )
        {
            mAlignment = a;
			mGeomPositionsOutOfDate = true;
        }
        inline Alignment getAlignment() const
        {
            return mAlignment;
        }

		inline void setFlipUV(bool flipu = false, bool flipv = true)
		{
			mFlipU = flipu;
			mFlipV = flipv;
		}

		inline bool getFlipU() const
		{
			return mFlipU;
		}

		inline bool getFlipV() const
		{
			return mFlipV;
		}

        /** Overridden from OverlayElement */
        void setMetricsMode(GuiMetricsMode gmm);

        /** Overridden from OverlayElement */
        void _update(void);

        //-----------------------------------------------------------------------------------------
        /** Command object for setting the caption.
                @see ParamCommand
        */
        class CmdCaption : public ParamCommand
        {
        public:
            String doGet( const void* target ) const;
            void doSet( void* target, const String& val );
        };
        //-----------------------------------------------------------------------------------------
        /** Command object for setting the char height.
                @see ParamCommand
        */
        class CmdCharHeight : public ParamCommand
        {
        public:
            String doGet( const void* target ) const;
            void doSet( void* target, const String& val );
        };
        //-----------------------------------------------------------------------------------------
        /** Command object for setting the width of a space.
                @see ParamCommand
        */
        class CmdSpaceWidth : public ParamCommand
        {
        public:
            String doGet( const void* target ) const;
            void doSet( void* target, const String& val );
        };
        //-----------------------------------------------------------------------------------------
        /** Command object for setting the caption.
                @see ParamCommand
        */
        class CmdFontName : public ParamCommand
        {
        public:
            String doGet( const void* target ) const;
            void doSet( void* target, const String& val );
        };
        //-----------------------------------------------------------------------------------------
        /** Command object for setting the top colour.
                @see ParamCommand
        */
        class CmdColourTop : public ParamCommand
        {
        public:
            String doGet( const void* target ) const;
            void doSet( void* target, const String& val );
        };
        //-----------------------------------------------------------------------------------------
        /** Command object for setting the bottom colour.
                @see ParamCommand
        */
        class CmdColourBottom : public ParamCommand
        {
        public:
            String doGet( const void* target ) const;
            void doSet( void* target, const String& val );
        };
        //-----------------------------------------------------------------------------------------
        /** Command object for setting the constant colour.
                @see ParamCommand
        */
        class CmdColour : public ParamCommand
        {
        public:
            String doGet( const void* target ) const;
            void doSet( void* target, const String& val );
        };
        //-----------------------------------------------------------------------------------------
        /** Command object for setting the alignment.
                @see ParamCommand
        */
        class CmdAlignment : public ParamCommand
        {
        public:
            String doGet( const void* target ) const;
            void doSet( void* target, const String& val );
        };
		class CmdFlipUV : public ParamCommand
		{
		public:
			String doGet( const void* target ) const;
			void doSet( void* target, const String& val );
		};
    protected:
        /// The text alignment
        Alignment mAlignment;

        /// Flag indicating if this panel should be visual or just group things
        bool mTransparent;

		bool mFlipU;
		bool mFlipV;

        /// Render operation
        RenderOperation mRenderOp;

        /// Method for setting up base parameters for this class
        void addBaseParameters(void);

        static String msTypeName;

        // Command objects
        static CmdCharHeight msCmdCharHeight;
        static CmdSpaceWidth msCmdSpaceWidth;
        static CmdFontName msCmdFontName;
        static CmdColour msCmdColour;
        static CmdColourTop msCmdColourTop;
        static CmdColourBottom msCmdColourBottom;
        static CmdAlignment msCmdAlignment;
		static CmdFlipUV msCmdFlipUV;

        FontPtr mFont;
        Real mCharHeight;
        ushort mPixelCharHeight;
        Real mSpaceWidth;
        ushort mPixelSpaceWidth;
        size_t mAllocSize;
		Real mViewportAspectCoef;

        /// Colours to use for the vertices
        ColourValue mColourBottom;
        ColourValue mColourTop;
        bool mColoursChanged;


        /// Internal method to allocate memory, only reallocates when necessary
        void checkMemoryAllocation( size_t numChars );
        /// Inherited function
        virtual void updatePositionGeometry();
		/// Inherited function
		virtual void updateTextureGeometry();
        /// Updates vertex colours
        virtual void updateColours(void);
    };
	/** @} */
	/** @} */
//}

#endif

